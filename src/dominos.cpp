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
    

    /**Skeleton (static system)
     * */
    {
      b2BodyDef *bd = new b2BodyDef;
      //bd->type = b2_staticBody;
      bd->position.Set(0,20);
      bd->fixedRotation = true;
      
      //The open box
      
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 10.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2EdgeShape;
      b2EdgeShape bs1;
      bs1.Set(b2Vec2(-30.f, 7.f), b2Vec2(0.f,7.f));
      fd1->shape = &bs1;
      
      b2FixtureDef *window = new b2FixtureDef;
      (*window).filter.groupIndex=-1;
      window->density = 10.0;
      window->friction = 0.5;
      window->restitution = 0.f;
      window->shape = new b2EdgeShape;
      b2EdgeShape windows;
      windows.Set(b2Vec2(0.f, 7.f), b2Vec2(8.f,7.f));
      window->shape = &windows;
      
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2EdgeShape;
      b2EdgeShape bs2;
      bs2.Set(b2Vec2(-30.f, 4.f), b2Vec2(-1.f, 4.f));
      fd2->shape = &bs2;
      
      b2FixtureDef *fd22 = new b2FixtureDef;
      fd22->density = 10.0;
      fd22->friction = 0.5;
      fd22->restitution = 0.f;
      fd22->shape = new b2EdgeShape;
      b2EdgeShape bs22;
      bs22.Set(b2Vec2(-1.f, 4.f), b2Vec2(0.f, 3.f));
      fd22->shape = &bs22;
      
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 10.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(15,0.2, b2Vec2(-15.f,0.f), 0);
      fd3->shape = &bs3;
      
      
      b2FixtureDef *fd4 = new b2FixtureDef;
      fd4->density = 10.0;
      fd4->friction = 0.5;
      fd4->restitution = 0.f;
      fd4->shape = new b2PolygonShape;
      b2PolygonShape bs4;
      bs4.SetAsBox(0.2,1.9, b2Vec2(-8.f,-2.f), 0);
      fd4->shape = &bs4;
      
      b2FixtureDef *fd5 = new b2FixtureDef;
      fd5->density = 10.0;
      fd5->friction = 0.5;
      fd5->restitution = 0.f;
      fd5->shape = new b2PolygonShape;
      b2PolygonShape bs5;
      bs5.SetAsBox(4, 0.2, b2Vec2(-4.f,-4.f), 0);
      fd5->shape = &bs5;
       
      b2FixtureDef *fd6 = new b2FixtureDef;
      fd6->density = 10.0;
      fd6->friction = 0.5;
      fd6->restitution = 0.f;
      fd6->shape = new b2PolygonShape;
      b2PolygonShape bs6;
      bs6.SetAsBox(0.2,9.0, b2Vec2(0.f,-5.75f), 0);
      fd6->shape = &bs6;
      
      b2FixtureDef *fd7 = new b2FixtureDef;
      fd7->density = 10.0;
      fd7->friction = 0.5;
      fd7->restitution = 0.f;
      fd7->shape = new b2PolygonShape;
      b2PolygonShape bs7;
      bs7.SetAsBox(3.7,0.2, b2Vec2(3.7f,-15.f), 0);
      fd7->shape = &bs7;
      
      b2FixtureDef *fd8 = new b2FixtureDef;
      fd8->density = 10.0;
      fd8->friction = 0.5;
      fd8->restitution = 0.f;
      fd8->shape = new b2PolygonShape;
      b2PolygonShape bs8;
      bs8.SetAsBox(0.2,7.5, b2Vec2(8.0f,-7.5f), 0);
      fd8->shape = &bs8;
      
      b2FixtureDef *fd9 = new b2FixtureDef;
      fd9->density = 10.0;
      fd9->friction = 0.5;
      fd9->restitution = 0.f;
      fd9->shape = new b2PolygonShape;
      b2PolygonShape bs9;
      bs9.SetAsBox(0.3,2, b2Vec2(-6.f,2.f), 0);
      fd9->shape = &bs9;
      
      b2FixtureDef *fd10 = new b2FixtureDef;
      fd10->density = 10.0;
      fd10->friction = 0.5;
      fd10->restitution = 0.f;
      fd10->shape = new b2EdgeShape;
      b2EdgeShape bs10;
      bs10.Set(b2Vec2(-30.f, 4.f), b2Vec2(-30.f, 3.f));
      fd10->shape = &bs10;
      
      b2FixtureDef *fd11 = new b2FixtureDef;
      fd11->density = 10.0;
      fd11->friction = 0.5;
      fd11->restitution = 0.f;
      fd11->shape = new b2PolygonShape;
      b2PolygonShape bs11;
      b2Vec2 vert[3];
      vert[0].Set(7.8f,0.f);
      vert[1].Set(7.8f,3.9f);
      vert[2].Set(11.f,3.9f);
      bs11.Set(vert,3);
      fd11->shape = &bs11;
       
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(window);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd22);
      box1->CreateFixture(fd3);
      box1->CreateFixture(fd4);
      box1->CreateFixture(fd5);
      box1->CreateFixture(fd6);
      box1->CreateFixture(fd7);
      box1->CreateFixture(fd8);
      box1->CreateFixture(fd9);
      box1->CreateFixture(fd10);
      box1->CreateFixture(fd11);
  }
  
  /** dynamic part
   * */
   {
	  b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(0,20);
      bd->fixedRotation = true;
      
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 50.0;
      fd1->friction = 0;
      fd1->restitution = 1.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(4,1.85, b2Vec2(-26.f,2.f), 0);
      fd1->shape = &bs1;
       
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 50.0;
      fd2->friction = 0;
      fd2->restitution = 1.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(11,0.2, b2Vec2(-19.f,7.2f), 0);
      fd2->shape = &bs2;
      
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 50.0;
      fd3->friction = 0;
      fd3->restitution = 1.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(5,1.4, b2Vec2(5.f,5.4f), 0);
      fd3->shape = &bs3;
      
      b2BodyDef *invibd = new b2BodyDef;
      invibd->type = b2_staticBody;
      invibd->position.Set(0-6,20+2);
      invibd->fixedRotation = true;
      b2Body* invi = m_world->CreateBody(invibd);
      
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);
      box1->SetLinearVelocity(b2Vec2(3,0));
      
      b2DistanceJointDef spring1;
      spring1.Initialize(box1, invi, b2Vec2(-22,22), invi->GetWorldCenter());
      spring1.collideConnected=true;
      spring1.frequencyHz = 0.04f;
      spring1.dampingRatio = 0.0f;
      m_world->CreateJoint(&spring1);
        
     }
     //bullets
	   {
	      //shell
		  b2FixtureDef *sf = new b2FixtureDef;
		  sf->density = 10.0;
		  sf->friction = 0.5;
		  sf->restitution = 0.f;
		  b2Vec2 vs[8];
          vs[0].Set(3.5f, 1.0f);
          vs[1].Set(0.0f, 1.0f);
	      vs[2].Set(0.3f, 1.3f);
		  vs[3].Set(5.2f, 1.3f);
		  vs[4].Set(5.2f, -1.3f);
		  vs[5].Set(0.3f, -1.3f);
		  vs[6].Set(0.0f, -1.0f);
		  vs[7].Set(3.5f, -1.0f);
		  b2ChainShape chain;
          chain.CreateChain(vs, 8);
          sf->shape = &chain;
          		 
	      
	      b2FixtureDef *bf = new b2FixtureDef;
		  bf->density = 5.0;
		  bf->friction = 0.0;
		  bf->restitution = 0.0f;
		  bf->shape = new b2PolygonShape;
		  b2PolygonShape bs;
		  b2Vec2 vert[5];
		  vert[0].Set(0.f,0.f);
		  vert[1].Set(1.f,1.f);
		  vert[2].Set(6.f,1.f);
		  vert[3].Set(6.f,-1.f);
		  vert[4].Set(1.f,-1.f);
		  bs.Set(vert,5);
		  bf->shape = &bs;
		  
	  for(int i=0; i<6 ;i++){
		  b2BodyDef *bulletDef = new b2BodyDef;
          (*bf).filter.groupIndex=i;
          bulletDef->type = b2_dynamicBody;
          bulletDef->position.Set(0.4,24-2.6*i);
          bulletDef->fixedRotation = true;
          
          b2Body* bullet = m_world->CreateBody(bulletDef);
		  bullet->CreateFixture(bf);
		  
		  b2BodyDef *shellDef = new b2BodyDef;
          shellDef->type = b2_dynamicBody;
          shellDef->position.Set(1.9,25-2.6*i);
          (*sf).filter.groupIndex=-1;
          b2Body* shell = m_world->CreateBody(shellDef);
		  shell->CreateFixture(sf);
		  
		  b2DistanceJointDef stuff;
		  stuff.Initialize(bullet, shell, bullet->GetWorldCenter(), shell->GetWorldCenter());
		  stuff.collideConnected=true;
		  stuff.frequencyHz = 10.f;
		  m_world->CreateJoint(&stuff);
		  
      
		  
		  
	}
		  b2BodyDef *bulletDef = new b2BodyDef;
          bulletDef->type = b2_dynamicBody;
          bulletDef->position.Set(0,-20);
          bulletDef->fixedRotation = true;
          
          b2Body* bullet = m_world->CreateBody(bulletDef);
		  bullet->CreateFixture(bf);
      
	}
	
	 /**bullet spring part
	  * */
	  
	{
	  b2BodyDef *invibd = new b2BodyDef;
      invibd->type = b2_staticBody;
      invibd->position.Set(0+4,20-15);
      invibd->fixedRotation = true;
      b2Body* invi = m_world->CreateBody(invibd);
      
	  b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(0,20);
      bd->fixedRotation = true;
      
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 10.0;
      fd1->friction = 0;
      fd1->restitution = 1.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(3.2,0.2, b2Vec2(3.8f,-10.f), 0);
      fd1->shape = &bs1;
       
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->SetLinearVelocity(b2Vec2(0,3));
      
      b2DistanceJointDef spring1;
      spring1.Initialize(box1, invi, box1->GetWorldCenter(), invi->GetWorldCenter());
      spring1.collideConnected=true;
      spring1.frequencyHz = 1.1f;
      spring1.dampingRatio = 0.0f;
      spring1.length = 15.0f;
      m_world->CreateJoint(&spring1);
  }
 }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
