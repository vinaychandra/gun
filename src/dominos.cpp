/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

/* 
* Base code for CS 296 Software Systems Lab 
* Department of Computer Science and Engineering, IIT Bombay
* Instructor: Parag Chaudhuri
*/


#include "cs296_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include "GL/freeglut.h"
#endif

#include <cstring>
using namespace std;

#include "dominos.hpp"

namespace cs296
{
/**  The is the constructor 
* This is the documentation block for the constructor.
*/ 

  dominos_t::dominos_t()
  {
  //Ground
  /*! \var b1 
  * \brief pointer to the body ground 
  */ 
    b2Body* b1;  
    {

      b2EdgeShape shape; 
      shape.Set(b2Vec2(-90.0f, 0.0f), b2Vec2(90.0f, 0.0f));
      b2BodyDef bd; 
      b1 = m_world->CreateBody(&bd); 
      b1->CreateFixture(&shape, 0.0f);
    }

   
    {
      //Body 1

      b2BodyDef bodyDef; 
      bodyDef.type = b2_dynamicBody; 
      bodyDef.position.Set(0.0f, 30.0f); 
      b2Body* body = m_world->CreateBody(&bodyDef); 

      b2PolygonShape dynamicBox; 
      dynamicBox.SetAsBox(2.0f, 2.0f); 

      b2FixtureDef fixtureDef; 
      fixtureDef.shape = &dynamicBox; 
      fixtureDef.density = 1.0f; 
      fixtureDef.friction = 0.3f; 
      fixtureDef.restitution = 0.75f;

      body->CreateFixture(&fixtureDef); 
    


      //Body 2
    
      b2BodyDef bodyDef2; 
      bodyDef2.type = b2_dynamicBody; 
      bodyDef2.position.Set(0.0f, 15.0f); 
      b2Body* body2 = m_world->CreateBody(&bodyDef2); 

      b2PolygonShape dynamicBox2; 
      dynamicBox2.SetAsBox(2.0f, 2.0f); 

      b2FixtureDef fixtureDef2; 
      fixtureDef2.shape = &dynamicBox2; 
      fixtureDef2.density = 1.0f; 
      fixtureDef2.friction = 0.3f; 
      fixtureDef2.restitution = 0.75f;

      body2->CreateFixture(&fixtureDef2); 
    

      //Trying a Spring
      b2DistanceJointDef jointDef; 
      jointDef.Initialize(body, body2, body->GetWorldCenter(), body2->GetWorldCenter()); 
      jointDef.collideConnected = true; 

      jointDef.frequencyHz = 1.0f; 
      jointDef.dampingRatio = 0.0f; 

      m_world->CreateJoint(&jointDef);
    }


  }

sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
