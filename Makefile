.SUFFIXES: .cpp .hpp

# Programs
SHELL 	= bash
CC     	= g++
LD	= ld
RM 	= rm
ECHO	= /bin/echo
CAT	= cat
PRINTF	= printf
SED	= sed
DOXYGEN = doxygen
AR	= ar

#Shared Libraries
SHARED_LIB = TRUE
#Shared Library name
MY_LIB = libCS296test
######################################
# Project Name (generate executable with this name)
TARGET = cs296_31_exe
#TARGET2 = cs296_31_exelib
TARGET_PATH = $(BINDIR)/$(TARGET)
#TARGET_PATH2 = $(BINDIR)/$(TARGET2)

# Project Paths
PROJECT_ROOT=./
EXTERNAL_ROOT=$(PROJECT_ROOT)/external
SRCDIR = $(PROJECT_ROOT)/src
OBJDIR = $(PROJECT_ROOT)/myobjs
BINDIR = $(PROJECT_ROOT)/mybins
LIBDIR = $(PROJECT_ROOT)/mylibs
DOCDIR = $(PROJECT_ROOT)/doc
INSTALLDIR = $(PROJECT_ROOT)/install

# Library Paths
BOX2D_ROOT=$(EXTERNAL_ROOT)
GLUI_ROOT=usr
GL_ROOT=usr/include/

#Box2D files
BOX2D_SRCDIR = $(EXTERNAL_ROOT)/src
BOX2D_INCLUDE = include
BOX2D_LIB = lib
BOX2D_INCLUDE_FIND = $(shell find $(EXTERNAL_ROOT) -name $(BOX2D_INCLUDE))
BOX2D_LIB_FIND = $(shell find $(EXTERNAL_ROOT) -name $(BOX2D_LIB))

#Libraries
LIBS = -lBox2D -lglui -lglut -lGLU -lGL

# Compiler and Linker flags
CPPFLAGS =-g -O3 -Wall -fno-strict-aliasing -fPIC
CPPFLAGS+=-I $(BOX2D_ROOT)/include -I $(GLUI_ROOT)/include
LDFLAGS+=-L $(BOX2D_ROOT)/lib -L $(GLUI_ROOT)/lib


######################################

NO_COLOR=\e[0m
OK_COLOR=\e[1;32m
ERR_COLOR=\e[1;31m
WARN_COLOR=\e[1;33m
MESG_COLOR=\e[1;34m
FILE_COLOR=\e[1;37m

OK_STRING="[OK]"
ERR_STRING="[ERRORS]"
WARN_STRING="[WARNINGS]"
OK_FMT="${OK_COLOR}%30s\n${NO_COLOR}"
ERR_FMT="${ERR_COLOR}%30s\n${NO_COLOR}"
WARN_FMT="${WARN_COLOR}%30s\n${NO_COLOR}"
######################################

SRCS := $(wildcard $(SRCDIR)/*.cpp)
INCS := $(wildcard $(SRCDIR)/*.hpp)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

SRCS2 := $(wildcard $(SRCDIR)/[!main]*.cpp)
INCS2 := $(wildcard $(SRCDIR)/[!main]*.hpp)
OBJS2 := $(SRCS2:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

MAIN_OBJ  = $(OBJDIR)/main.o

#####################################
.PHONY: all setup doc clean distclean

all: setup exe

setup:
	@$(ECHO) "Setting up compilation..."
	@mkdir -p myobjs
	@mkdir -p mybins
	@mkdir -p mylibs
ifneq (,$(BOX2D_INCLUDE_FIND))
ifneq (,$(BOX2D_LIB_FIND))
	@$(ECHO) "Box2D Found.. No installation required"
else
	@$(ECHO) "Box2D not found [lib]"
	@tar xvzf $(BOX2D_SRCDIR)/Box2D.tgz -C $(BOX2D_SRCDIR)

	@$(ECHO) "Patching Box2D files..."
	@patch $(BOX2D_SRCDIR)/Box2D/Box2D/Common/b2Timer.cpp < $(BOX2D_SRCDIR)/patch/b2Timer_cpp.patch
	@patch $(BOX2D_SRCDIR)/Box2D/Box2D/Common/b2Timer.h < $(BOX2D_SRCDIR)/patch/b2Timer_h.patch
	@$(ECHO) "Patching Done"

	@mkdir -p $(BOX2D_SRCDIR)/Box2D/build296
	@cd $(BOX2D_SRCDIR)/Box2D/build296; cmake ../; make; make install;
	@$(ECHO) "Box2D Build Complete"
endif
else
	@$(ECHO) "Box2D not found [include]"
	@tar xzf $(BOX2D_SRCDIR)/Box2D.tgz -C $(BOX2D_SRCDIR)

	@$(ECHO) "Patching Box2D files..."
	@patch $(BOX2D_SRCDIR)/Box2D/Box2D/Common/b2Timer.cpp < $(BOX2D_SRCDIR)/patch/b2Timer_cpp.patch
	@patch $(BOX2D_SRCDIR)/Box2D/Box2D/Common/b2Timer.h < $(BOX2D_SRCDIR)/patch/b2Timer_h.patch
	@$(ECHO) "Patching Done"
	
	@mkdir -p $(BOX2D_SRCDIR)/Box2D/build296
	@cd $(BOX2D_SRCDIR)/Box2D/build296; cmake ../; make; make install;
	@$(ECHO) "Box2D Build Complete"
endif

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(PRINTF) "$(MESG_COLOR)Compiling: $(NO_COLOR) $(FILE_COLOR) %25s$(NO_COLOR)" "$(notdir $<)"
	@$(CC) $(CPPFLAGS) -c $< -o $@ -MD 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else printf "${OK_COLOR}%30s\n${NO_COLOR}" "[OK]"; \
	fi;
	@$(RM) -f temp.log temp.err

exe : setup $(OBJS)
	@$(PRINTF) "$(MESG_COLOR)Building executable:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "$(notdir $(TARGET_PATH))"
	@$(CC) -o $(TARGET_PATH) $(LDFLAGS) $(OBJS) $(LIBS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.e

doc:
	@$(ECHO) -n "Generating Doxygen Documentation ...  "
	@$(RM) -rf doc/html
	@$(DOXYGEN) $(DOCDIR)/Doxyfile 2 > /dev/null
	@$(ECHO) "Done"

dist: distclean
	@cd ../;\
	tar czf cs296_g31_project.tar.gz gun

install: doc exe report
	@$(RM) -rf $(INSTALLDIR)
	@mkdir $(INSTALLDIR)
	@cp -r mybins/ $(INSTALLDIR)
	@cp -r doc/ $(INSTALLDIR)
	@cp -r details/ $(INSTALLDIR)
	@cp -r scripts/ $(INSTALLDIR)

report: 
	@cd doc;\
	pdflatex project;\
	bibtex project; \
	pdflatex project; \
	bibtex project;\
	pdflatex project; \
	rm project.aux project.log project.blg project.bbl;
	@python3 scripts/g31_gen_html.py; \


clean:
	@$(ECHO) -n "Cleaning up..."
	@$(RM) -rf $(OBJDIR) $(LIBDIR) *~ $(DEPS) $(SRCDIR)/*~
	@$(ECHO) "Done"

distclean: clean
	@$(RM) -rf $(BINDIR) $(DOCDIR)/html $(LIBDIR)
	@$(RM) -Rf $(BOX2D_SRCDIR)/Box2D doc/project.pdf $(INSTALLDIR)
	@$(RM) -Rf $(BOX2D_ROOT)/lib $(BOX2D_ROOT)/include doc/g31_lab09_report.html

