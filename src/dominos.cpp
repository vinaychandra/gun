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
    /*//Ground
    /! \var b1 
     * \brief pointer to the body ground 
      
    b2Body* b1;  
    {
      
      b2EdgeShape shape; 
      shape.Set(b2Vec2(-90.0f, 0.0f), b2Vec2(90.0f, 0.0f));
      b2BodyDef bd; 
      b1 = m_world->CreateBody(&bd); 
      b1->CreateFixture(&shape, 0.0f);
    }
          
    //Top horizontal shelf
    {
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.25f);
	
      b2BodyDef bd;
      bd.position.Set(-31.0f, 30.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

    //Dominos
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.0f);
	
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;
		
      for (int i = 0; i < 10; ++i)
	{
	  b2BodyDef bd;
	  bd.type = b2_dynamicBody;
	  bd.position.Set(-35.5f + 1.0f * i, 31.25f);
	  b2Body* body = m_world->CreateBody(&bd);
	  body->CreateFixture(&fd);
	}
    }
      
    //Another horizontal shelf
    {
      b2PolygonShape shape;
      shape.SetAsBox(7.0f, 0.25f, b2Vec2(-20.f,20.f), 0.0f);
	
      b2BodyDef bd;
      bd.position.Set(1.0f, 6.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }


    //The pendulum that knocks the dominos off
    {
      b2Body* b2;
      {
	b2PolygonShape shape;
	shape.SetAsBox(0.25f, 1.5f);
	  
	b2BodyDef bd;
	bd.position.Set(-36.5f, 28.0f);
	b2 = m_world->CreateBody(&bd);
	b2->CreateFixture(&shape, 10.0f);
      }
	
      b2Body* b4;
      {
	b2PolygonShape shape;
	shape.SetAsBox(0.25f, 0.25f);
	  
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(-40.0f, 33.0f);
	b4 = m_world->CreateBody(&bd);
	b4->CreateFixture(&shape, 2.0f);
      }
	
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(-37.0f, 40.0f);
      jd.Initialize(b2, b4, anchor);
      m_world->CreateJoint(&jd);
    }
      
    //The train of small spheres
    {
      b2Body* spherebody;
	
      b2CircleShape circle;
      circle.m_radius = 0.5;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 1.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
	
      for (int i = 0; i < 10; ++i)
	{
	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(-22.2f + i*1.0, 26.6f);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	}
    }
*/
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
      bs7.SetAsBox(4,0.2, b2Vec2(4.0f,-15.f), 0);
      fd7->shape = &bs7;
      
      b2FixtureDef *fd8 = new b2FixtureDef;
      fd8->density = 10.0;
      fd8->friction = 0.5;
      fd8->restitution = 0.f;
      fd8->shape = new b2PolygonShape;
      b2PolygonShape bs8;
      bs8.SetAsBox(0.2,7.5, b2Vec2(8.f,-7.5f), 0);
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
      vert[0].Set(8.f,0.f);
      vert[1].Set(8.f,3.9f);
      vert[2].Set(11.f,3.9f);
      bs11.Set(vert,3);
      fd11->shape = &bs11;
       
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
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
      bs1.SetAsBox(4,2, b2Vec2(-26.f,2.f), 0);
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
      bs3.SetAsBox(5,1.5, b2Vec2(5.f,5.5f), 0);
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
      bs1.SetAsBox(3.9,0.2, b2Vec2(4.f,0.f), 0);
      fd1->shape = &bs1;
       
     /* b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.0;
      fd2->friction = 0;
      fd2->restitution = 1.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(11,0.2, b2Vec2(-19.f,7.2f), 0);
      fd2->shape = &bs2;
      
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 10.0;
      fd3->friction = 0;
      fd3->restitution = 1.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(5,1.5, b2Vec2(5.f,5.5f), 0);
      fd3->shape = &bs3;*/
        
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      //box1->CreateFixture(fd2);
      //box1->CreateFixture(fd3);
      box1->SetLinearVelocity(b2Vec2(0,3));
      
      b2DistanceJointDef spring1;
      spring1.Initialize(box1, invi, box1->GetWorldCenter(), invi->GetWorldCenter());
      spring1.collideConnected=true;
      spring1.frequencyHz = 0.85f;
      spring1.dampingRatio = 0.0f;
      m_world->CreateJoint(&spring1);
  }
  //bullet part
  {
	      b2FixtureDef *bf = new b2FixtureDef;
		  bf->density = 5.0;
		  bf->friction = 0.0;
		  bf->restitution = 0.0f;
		  bf->shape = new b2PolygonShape;
		  b2PolygonShape bs;
		  b2Vec2 vert[5];
		  vert[0].Set(0.f,0.f);
		  vert[1].Set(1.f,1.4f);
		  vert[2].Set(6.f,1.4f);
		  vert[3].Set(6.f,-1.4f);
		  vert[4].Set(1.f,-1.4f);
		  bs.Set(vert,5);
		  bf->shape = &bs;
		  
	  for(int i=0; i<6 ;i++){
		  b2BodyDef *bulletDef = new b2BodyDef;
          bulletDef->type = b2_dynamicBody;
          bulletDef->position.Set(0,26-2*i);
          bulletDef->fixedRotation = true;
      

		  b2Body* bullet = m_world->CreateBody(bulletDef);
		  bullet->CreateFixture(bf);
	}
	}
		  
	   
	   
  /*

      //The bar
      bd->position.Set(10,15);	
      fd1->density = 34.0;	  
      b2Body* box2 = m_world->CreateBody(bd);
      box2->CreateFixture(fd1);

      // The pulley joint
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      b2Vec2 worldAnchorOnBody1(-10, 15); // Anchor point on body 1 in world axis
      b2Vec2 worldAnchorOnBody2(10, 15); // Anchor point on body 2 in world axis
      b2Vec2 worldAnchorGround1(-10, 20); // Anchor point for ground 1 in world axis
      b2Vec2 worldAnchorGround2(10, 20); // Anchor point for ground 2 in world axis
      float32 ratio = 1.0f; // Define ratio
      myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);
    }

    //The revolving horizontal platform
    {
      b2PolygonShape shape;
      shape.SetAsBox(2.2f, 0.2f);
	
      b2BodyDef bd;
      bd.position.Set(14.0f, 14.0f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f);
      b2BodyDef bd2;
      bd2.position.Set(14.0f, 16.0f);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    }

    //The heavy sphere on the platform
    {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 1.0;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 50.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(14.0f, 18.0f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    }


    //The see-saw system at the bottom
    {
      //The triangle wedge
      b2Body* sbody;
      b2PolygonShape poly;
      b2Vec2 vertices[3];
      vertices[0].Set(-1,0);
      vertices[1].Set(1,0);
      vertices[2].Set(0,1.5);
      poly.Set(vertices, 3);
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly;
      wedgefd.density = 10.0f;
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 0.0f;
      b2BodyDef wedgebd;
      wedgebd.position.Set(30.0f, 0.0f);
      sbody = m_world->CreateBody(&wedgebd);
      sbody->CreateFixture(&wedgefd);

      //The plank on top of the wedge
      b2PolygonShape shape;
      shape.SetAsBox(15.0f, 0.2f);
      b2BodyDef bd2;
      bd2.position.Set(30.0f, 1.5f);
      bd2.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd2);
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      body->CreateFixture(fd2);

      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(30.0f, 1.5f);
      jd.Initialize(sbody, body, anchor);
      m_world->CreateJoint(&jd);

      //The light box on the right side of the see-saw
      b2PolygonShape shape2;
      shape2.SetAsBox(2.0f, 2.0f);
      b2BodyDef bd3;
      bd3.position.Set(40.0f, 2.0f);
      bd3.type = b2_dynamicBody;
      b2Body* body3 = m_world->CreateBody(&bd3);
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 0.01f;
      fd3->shape = new b2PolygonShape;
      fd3->shape = &shape2;
      body3->CreateFixture(fd3);
    }*/
  }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
