import re
html = "./doc/g31_lab09_report.html"
tex_file = "./doc/project.tex"

with open (tex_file, "r") as myfile:
	data = myfile.read().splitlines()

#removing from section profiling
answer = []
for line in data :
	answer.append(line)
data = answer

#Removing all use packages
answer = []
for line in data :
	if line.find("\\usepackage") == 0 or line.find("\\maketitle") == 0 or line.find("\\date") != -1:
		continue
	else :
		answer.append(line)
data = answer

#begin and end of something
answer = []
for line in data :
	if line.find("\\begin{") == 0 :
		answer.append(line.replace("\\begin{","<",1).replace("}",">",1))
	elif line.find("\\end{") == 0 :
		answer.append(line.replace("\\end{","</",1).replace("}",">",1))
	else:
		answer.append(line)
data = answer

#sections and title
answer = []
for line in data :
	if line.find("\\section{") == 0:
		answer.append(line.replace("\\section{","<br><br><section>").replace("}","</section><br><br>",1))
	elif line.find("\\subsection{") == 0:
		answer.append(line.replace("\\subsection{","<br><br><subsection>").replace("}","</subsection><br><br>",1))
	elif line.find("\\title{") == 0:
		answer.append(line.replace("\\title{","<h2>").replace("}","</h2><br><br>",1))
		#answer.append("<link href=\"index.css\" rel=\"stylesheet\">")
	else :
		answer.append(line)

data = answer;

#replace newlines, 
answer = []
for line in data :
	answer.append(line.replace("\\newline","<br>").replace("\\and","<br><br>").replace("\\\\","<br>"))
data = answer

#replace  \it and \rm and [here]
answer = []
for line in data :
	answer.append(line.replace("\\it","<it>").replace("\\rm","</it>").replace("[here]",""))
data = answer

#replace  \bf and \rm
answer = []
for line in data :
	answer.append(line.replace("\\bf","").replace("\\rm",""))
data = answer

#image processing
answer = []
for line in data :
	if line.find("\\includegraphics") != -1 :
		#temp = line.replace("\\includegraphics","xxxxxx")
		answer.append(re.sub(r"\\includegraphics\[.*\]{",'<br><img src="',line).replace("}",'" alt="image not found" ><br>',1))
	else :
		answer.append(line)
data = answer

#removing captions
answer = []
for line in data :
	if line.find("\\caption") != -1 :
		#temp = line.replace("\\includegraphics","xxxxxx")
		answer.append(re.sub(r"\\caption{",'',line).replace("}",'',1))
	else :
		answer.append(line)
data = answer

#Parsing $xxx$ (Coding Terms)
answer = []
for line in data :
	temp = line
	while temp.find("$") != -1 :
		temp = temp.replace("$","<code>",1).replace("$","</code>",1)
	answer.append(temp)

data = answer

#\documentclass with HTML
answer = []
for line in data :
	if (line.find("\\documentclass") == 0):
		answer.append("<!DOCTYPE html><html><head><title>CS 296 Report</title><link href=\"a.css\" rel=\"stylesheet\"></head><body>")
	else :
		answer.append(line)
data = answer

#\texttt
answer = []
for line in data:
	if (line.find("\\texttt{")) != -1 :
		answer.append(line.replace("\\texttt{","<texttt>",1).replace("}","</texttt>"))
	else :
		answer.append(line)
data = answer

#Data Compressor
data = ''.join(data)

#author fix
data = data.replace("\\author{",'<center style="font-size:15px;">',1).replace("}","</center><br>",1)
data = data.replace("\\bibliographystyle{plain}\\bibliography{project}",'')


thefile = open(html,'w')
#for x in data :
thefile.write("%s\n" % data)
thefile.write("</body></html>")
thefile.close()
