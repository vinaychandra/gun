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
  b2BodyDef t1,t2;
  b2Body* box1;
  b2Body* body2;
  dominos_t::dominos_t()
  {
    

    /**Skeleton (static system)
     * */
    {
      b2BodyDef *bd = new b2BodyDef;
      //bd->type = b2_staticBody;
      bd->position.Set(0,20);
      bd->fixedRotation = true;
      
      b2FixtureDef *f1 = new b2FixtureDef;
      f1->density = 10.0;
      f1->friction = 0.5;
      f1->restitution = 0.f;
      f1->shape = new b2EdgeShape;
      b2EdgeShape e1;
      e1.Set(b2Vec2(-30.f, 7.f), b2Vec2(3.5f,7.f));
      f1->shape = &e1;
      f1->filter.maskBits = 0x0010;
      f1->filter.categoryBits = 0x0011;
      //b2FixtureDef *window = new b2FixtureDef;
      //window->density = 10.0;
      //window->friction = 0.5;
      //window->restitution = 0.f;
      //window->shape = new b2EdgeShape;
      //b2EdgeShape windows;
      //windows.Set(b2Vec2(0.f, 7.f), b2Vec2(8.f,7.f));
      //window->shape = &windows;
      
      b2FixtureDef *f2 = new b2FixtureDef;
      f2->density = 10.0;
      f2->friction = 0.5;
      f2->restitution = 0.f;
      f2->shape = new b2EdgeShape;
      b2EdgeShape e2;
      e2.Set(b2Vec2(-30.f, 4.f), b2Vec2(-1.f, 4.f));
      f2->shape = &e2;
      f2->filter.maskBits = 0x0010;
      f2->filter.categoryBits = 0x0012;
      
    
      b2FixtureDef *f5 = new b2FixtureDef;
      f5->density = 10.0;
      f5->friction = 0.5;
      f5->restitution = 0.f;
      f5->shape = new b2EdgeShape;
      b2EdgeShape e5;
      e5.Set(b2Vec2(-1.f, 4.f), b2Vec2(0.f, 3.f));
      f5->shape = &e5;
      f5->filter.maskBits = 0x0010;
      f5->filter.categoryBits = 0x0015;
      
      b2FixtureDef *f3 = new b2FixtureDef;
      f3->density = 10.0;
      f3->friction = 0.5;
      f3->restitution = 0.f;
      f3->shape = new b2PolygonShape;
      b2PolygonShape p3;
      p3.SetAsBox(15,0.2, b2Vec2(-15.f,0.f), 0);
      f3->shape = &p3;
      f3->filter.maskBits = 0x0010;
      f3->filter.categoryBits = 0x0013;
      
      b2FixtureDef *f9 = new b2FixtureDef;
      f9->density = 10.0;
      f9->friction = 0.5;
      f9->restitution = 0.f;
      f9->shape = new b2PolygonShape;
      b2PolygonShape p9;
      p9.SetAsBox(0.2,1.9, b2Vec2(-8.f,-2.f), 0);
      f9->shape = &p9;
      f9->filter.maskBits = 0x0010;
      f9->filter.categoryBits = 0x0019;
      
      b2FixtureDef *f10 = new b2FixtureDef;
      f10->density = 10.0;
      f10->friction = 0.5;
      f10->restitution = 0.f;
      f10->shape = new b2PolygonShape;
      b2PolygonShape p10;
      p10.SetAsBox(4, 0.2, b2Vec2(-4.f,-4.f), 0);
      f10->shape = &p10;
      f10->filter.maskBits = 0x0010;
      f10->filter.categoryBits = 0x001a;
       
      b2FixtureDef *f6 = new b2FixtureDef;
      f6->density = 10.0;
      f6->friction = 0.5;
      f6->restitution = 0.f;
      f6->shape = new b2PolygonShape;
      b2PolygonShape p6;
      p6.SetAsBox(0.2,9.0, b2Vec2(0.f,-5.75f), 0);
      f6->shape = &p6;
      f6->filter.maskBits = 0x0010;
      f6->filter.categoryBits = 0x0016;
      
      b2FixtureDef *f8 = new b2FixtureDef;
      f8->density = 10.0;
      f8->friction = 0.5;
      f8->restitution = 0.f;
      f8->shape = new b2PolygonShape;
      b2PolygonShape p8;
      p8.SetAsBox(3.7,0.2, b2Vec2(3.7f,-15.f), 0);
      f8->shape = &p8;
      f8->filter.maskBits = 0x0010;
      f8->filter.categoryBits = 0x0018;
      
      
      b2FixtureDef *f7 = new b2FixtureDef;
      f7->density = 10.0;
      f7->friction = 0.5;
      f7->restitution = 0.f;
      f7->shape = new b2PolygonShape;
      b2PolygonShape p7;
      p7.SetAsBox(0.2,9., b2Vec2(8.0f,-5.f), 0);
      f7->shape = &p7;
      f7->filter.maskBits = 0x0010;
      f7->filter.categoryBits = 0x0017;
      
      b2FixtureDef *f4 = new b2FixtureDef;
      f4->density = 10.0;
      f4->friction = 0.5;
      f4->restitution = 0.f;
      f4->shape = new b2PolygonShape;
      b2PolygonShape p4;
      p4.SetAsBox(0.3,2, b2Vec2(-6.f,2.f), 0);
      f4->shape = &p4;
      f4->filter.maskBits = 0x0010;
      f4->filter.categoryBits = 0x0014;
      
      b2FixtureDef *ac1 = new b2FixtureDef;
      ac1->density = 10.0;
      ac1->friction = 0.5;
      ac1->restitution = 0.f;
      b2Vec2 b[3];
      b[0].Set(-4.f, 4.f);
      b[1].Set(-4.f, 4.3f);
      b[2].Set(-30.f, 4.3f);
      b2ChainShape bar1;
      bar1.CreateChain(b,3);
      ac1->shape = &bar1;
      
      b2FixtureDef *ac2 = new b2FixtureDef;
      ac2->density = 10.0;
      ac2->friction = 0.5;
      ac2->restitution = 0.f;
      b2Vec2 c[3];
      c[0].Set(-4.f, 7.0f);
      c[1].Set(-4.f, 6.6f);
      c[2].Set(-30.f, 6.6f);
      b2ChainShape bar2;
      bar2.CreateChain(c,3);
      ac2->shape = &bar2;
      
      
      
      b2FixtureDef *fd11 = new b2FixtureDef;
      fd11->density = 10.0;
      fd11->friction = 0.5;
      fd11->restitution = 0.f;
      fd11->shape = new b2EdgeShape;
      b2EdgeShape bs11;
      bs11.Set(b2Vec2(-30.f, 4.f), b2Vec2(-30.f, 3.f));
      fd11->shape = &bs11;
      
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(f1);
      box1->CreateFixture(f2);
      box1->CreateFixture(f3);
      box1->CreateFixture(f4);
      box1->CreateFixture(f5);
      box1->CreateFixture(f6);
      box1->CreateFixture(f7);
      box1->CreateFixture(f8);
      box1->CreateFixture(f9);
      box1->CreateFixture(f10);
      box1->CreateFixture(ac1);
      box1->CreateFixture(ac2);
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
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(4,1.9, b2Vec2(-26.f,2.f), 0);
      fd1->shape = &bs1;
      fd1->filter.categoryBits = 0x0010;
       
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 50.0;
      fd2->friction = 0;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(11,0.2, b2Vec2(-19.f,7.2f), 0);
      fd2->shape = &bs2;
      fd2->filter.categoryBits = 0x0010;
      //upper part 
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 50.0;
      fd3->friction = 0;
      fd3->restitution = 0.f;
      b2Vec2 vs[4];
      vs[0].Set(-0.8f, 5.2f);
	  vs[1].Set(0.f, 6.8f);
      vs[2].Set(10.f, 6.8f);
      vs[3].Set(10.f, 5.2f);
	  b2PolygonShape quad1;
	  quad1.Set(vs,4);
	  fd3->shape = &quad1;
	  fd3->filter.categoryBits = 0x0010;
	  fd3->filter.maskBits = 0x0111;
	  //lower part
	  b2FixtureDef *fd4 = new b2FixtureDef;
      fd4->density = 50.0;
      fd4->friction = 0;
      fd4->restitution = 0.f;
      vs[0].Set(-0.8f, 4.5f);
	  vs[1].Set(10.f, 4.5f);
      vs[2].Set(10.f, 4.2f);
      vs[3].Set(0.f, 4.2f);
	  b2PolygonShape quad2;
	  quad2.Set(vs,4);
	  fd4->shape = &quad2;
	  fd4->filter.categoryBits = 0x0010;
	  fd4->filter.maskBits = 0x0111;
	  //stick fixture
	  b2FixtureDef *fd5 = new b2FixtureDef;
      fd5->density = 0.5;
      fd5->friction = 0;
      fd5->restitution = 0.f;
      b2Vec2 v[5];
      v[0].Set(0.2f, 4.5f);
      v[1].Set(0.f, 4.8f);
	  v[2].Set(0.2f, 5.2f);
      v[3].Set(10.4f, 5.2f);
      v[4].Set(10.4f, 4.5f);
	  b2PolygonShape pent;
	  pent.Set(v,5);
	  fd5->shape = &pent;
	  fd5->filter.categoryBits = 0x0110;
	  fd5->filter.maskBits = 0x1010;
	  //stick body
	  b2BodyDef *stickbd = new b2BodyDef;
      stickbd->type = b2_dynamicBody;
      stickbd->position.Set(0,20);
      stickbd->fixedRotation = true;
	  b2Body* stick = m_world->CreateBody(stickbd);
      stick->CreateFixture(fd5);
      stick->SetLinearVelocity(b2Vec2(-20,0));
      //arbit invisible body
	  b2BodyDef *invibd = new b2BodyDef;
      invibd->type = b2_staticBody;
      invibd->position.Set(0-6,20+2);
      invibd->fixedRotation = true;
      b2Body* invi = m_world->CreateBody(invibd);
      
      box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);
      box1->CreateFixture(fd4);
      box1->SetLinearVelocity(b2Vec2(4,0));
      //spring between stick and invisible point
      b2DistanceJointDef internal;
      internal.Initialize(box1, stick, b2Vec2(9.8,25.3), stick->GetWorldCenter());
      internal.collideConnected=true;
      internal.frequencyHz = 0.5f;
      internal.dampingRatio = 1.0f;
      m_world->CreateJoint(&internal);
      //spring necessary for the reload part.
      b2DistanceJointDef spring1;
      spring1.Initialize(box1, invi, b2Vec2(-22,22), invi->GetWorldCenter());
      spring1.collideConnected=true;
      spring1.frequencyHz = 0.07f;
      spring1.dampingRatio = 0.1f;
      m_world->CreateJoint(&spring1);
        
     }
     
	  //bullets
	   {
	      //shell fixture
		  b2FixtureDef *sf1 = new b2FixtureDef;
		  sf1->density = 5.0;
		  sf1->friction = 0;
		  sf1->restitution = 0.f;
		  b2Vec2 vs[4];
          vs[0].Set(5.2f, 1.0f);
          vs[1].Set(0.0f, 1.0f);
	      vs[2].Set(0.3f, 1.4f);
		  vs[3].Set(5.2f, 1.4f);
		  b2PolygonShape s1;
		  s1.Set(vs,4);
		  sf1->shape = &s1;
		  sf1->filter.categoryBits = 0x0010;
		  
		  b2FixtureDef *sf2 = new b2FixtureDef;
		  sf2->density = 5.0;
		  sf2->friction = 0.1;
		  sf2->restitution = 0.f;
		  vs[0].Set(5.2f, -1.4f);
          vs[1].Set(0.3f, -1.4f);
	      vs[2].Set(0.0f, -1.0f);
		  vs[3].Set(5.2f, -1.0f);
		  b2PolygonShape s2;
		  s2.Set(vs,4);
		  sf2->shape = &s2;
		  sf2->filter.categoryBits = 0x0010;
		  
		  b2FixtureDef *sf3 = new b2FixtureDef;
		  sf3->density = 5.0;
		  sf3->friction = 0;
		  sf3->restitution = 0.f;
		  vs[0].Set(5.2f, 1.0f);
          vs[1].Set(4.7f, 1.0f);
	      vs[2].Set(4.7f, -1.0f);
		  vs[3].Set(5.2f, -1.0f);
		  b2PolygonShape s3;
		  s3.Set(vs,4);
		  sf3->shape = &s3;  
		  sf3->filter.categoryBits = 0x0010;
		  
		  //bullet fixture
		  b2FixtureDef *bf = new b2FixtureDef;
		  bf->density = 5.0;
		  bf->friction = 5.0;
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
		  bf->filter.categoryBits = 0x0010;
		  //creating bullet bodies
	  for(int i=0; i<3 ;i++){
		  b2BodyDef *bulletDef = new b2BodyDef;
          bulletDef->type = b2_dynamicBody;
          bulletDef->position.Set(0.4,22-3.0*i);
          bulletDef->fixedRotation = true;
          
          b2Body* bullet = m_world->CreateBody(bulletDef);
		  bullet->CreateFixture(bf);
		  
		  b2BodyDef *shellDef = new b2BodyDef;
          shellDef->type = b2_dynamicBody;
          shellDef->position.Set(1.9,22-3.0*i);
          b2Body* shell = m_world->CreateBody(shellDef);
		  shell->CreateFixture(sf1);
		  shell->CreateFixture(sf2);
		  shell->CreateFixture(sf3);
		  
	}
      
	}
	
	 /**bullet spring part
	  * */
	  
	{
	  b2BodyDef *invibd = new b2BodyDef;
      invibd->type = b2_staticBody;
      invibd->position.Set(0+3.8,20-15);
      invibd->fixedRotation = true;
      b2Body* invi = m_world->CreateBody(invibd);
      
	  b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(0,20);
      bd->fixedRotation = true;
      //base 
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 10.0;
      fd1->friction = 0;
      fd1->restitution = 1.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(3.6,0.2, b2Vec2(3.8f,-12.f), 0);
      fd1->shape = &bs1;
      fd1->filter.categoryBits = 0x0010;
       
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->SetLinearVelocity(b2Vec2(0,3));
      
      b2DistanceJointDef spring1;
      spring1.Initialize(box1, invi, box1->GetWorldCenter(), invi->GetWorldCenter());
      spring1.collideConnected=true;
      spring1.frequencyHz = 1.0f;
      spring1.dampingRatio = 1.0f;
      spring1.length = 18.7f;
      m_world->CreateJoint(&spring1);
  }
  //trigger part
  {
	  	//the ground part
			b2BodyDef bd;
			b2Body *ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.Set(b2Vec2(50.0f, 0.0f), b2Vec2(-50.0f, 0.0f));
			ground->CreateFixture(&shape, 0.0f);


			b2RevoluteJoint* m_joint1;
			b2PrismaticJoint* m_joint2;
			b2PrismaticJoint* m_joint3;
			b2CircleShape circle1;
			circle1.m_radius = 1.0f;
	//shapes
			b2PolygonShape rod1,rod1weld,springrest,verticallong,trigger;
			b2Vec2 vert[4];
			vert[0].Set(0.f,0.f);
			vert[1].Set(-8.f,0.f);
			vert[2].Set(-8.f,1.f);
			vert[3].Set(0.f,1.f);
			rod1.Set(vert,4);
      
            vert[0].Set(0.f,1.f);
			vert[1].Set(0.f,4.f);
			vert[2].Set(-1.f,4.f);
			vert[3].Set(-1.f,1.f);
			rod1weld.Set(vert,4);
			
			vert[0].Set(-8.f,1.f);
			vert[1].Set(-9.f,1.f);
			vert[2].Set(-9.f,-3.f);
			vert[3].Set(-8.f,-3.f);
			trigger.Set(vert,4);
			
			springrest.SetAsBox(3.0f, 0.5f);

			verticallong.SetAsBox(0.5f, 5.f);
			
			b2PolygonShape rod2;
			rod2.SetAsBox(3.f, 0.5f);
	//circular gear body	
			t1.type = b2_dynamicBody;
			t1.position.Set(4.0f, 20.0f);
			b2Body* body1 = m_world->CreateBody(&t1);
			b2FixtureDef *tf1 = new b2FixtureDef;
			tf1->shape = &circle1;
			tf1->density = 5.0f;
			tf1->filter.categoryBits=0x0100;
			tf1->filter.maskBits=0x0100;
			body1->CreateFixture(tf1);
	//hidden static body in trigger part
			b2BodyDef t4;
			t4.type = b2_staticBody;
			t4.position.Set(7.f, 21.f);
			b2Body* hidden = m_world->CreateBody(&t4);
			b2FixtureDef *tf4 = new b2FixtureDef;
			tf4->filter.groupIndex = -1;
			tf4->shape = &verticallong;
			tf4->filter.maskBits=0x0100;
			tf4->filter.categoryBits=0x0100;
			hidden->CreateFixture(tf4);
			//hidden->CreateFixture(&springrest, 1.0f);
			
	//revolute joint of circular gear
			b2RevoluteJointDef jd1;
			jd1.bodyA = hidden;
			jd1.bodyB = body1;
			jd1.localAnchorA = hidden->GetLocalPoint(t1.position);
			jd1.localAnchorB = body1->GetLocalPoint(t1.position);
			jd1.referenceAngle = body1->GetAngle() - ground->GetAngle();
			m_joint1 = (b2RevoluteJoint*)m_world->CreateJoint(&jd1);
	//trigger
			t2.type = b2_dynamicBody;
			t2.position.Set(4.5f, 21.f);
			body2 = m_world->CreateBody(&t2);
			b2FixtureDef *tf21 = new b2FixtureDef;
			tf21->shape = &rod1;
			tf21->density = 5.0f;
			tf21->filter.categoryBits=0x0100;
			tf21->filter.maskBits=0x0100;
			body2->CreateFixture(tf21);
			b2FixtureDef *tf22 = new b2FixtureDef;
			tf22->shape = &rod1weld;
			tf22->density = 5.0f;
			tf22->filter.categoryBits=0x0100;
			tf22->filter.maskBits=0x0100;
			body2->CreateFixture(tf22);
			b2FixtureDef *tf23 = new b2FixtureDef;
			tf23->shape = &trigger;
			tf23->density = 5.0f;
			tf23->filter.categoryBits=0x0100;
			tf23->filter.maskBits=0x0100;
			body2->CreateFixture(tf23);

	//prismatic joint for trigger rod
			b2PrismaticJointDef jd2;
			jd2.Initialize(hidden, body2, t2.position, b2Vec2(1.0f, 0.0f));
			jd2.lowerTranslation = -5.0f;
			jd2.upperTranslation = 5.0f;
			jd2.enableLimit = true;

			m_joint2 = (b2PrismaticJoint*)m_world->CreateJoint(&jd2);
	//the other rod in the gear
			b2BodyDef t3;
			t3.type = b2_dynamicBody;
			t3.position.Set(6.f, 18.5f);
			b2Body* body3 = m_world->CreateBody(&t3);
			b2FixtureDef *tf3 = new b2FixtureDef;
			tf3->filter.groupIndex = -1;
			tf3->density=1.f;
			tf3->shape = &rod2;
			tf3->filter.maskBits=0x0100;
			tf3->filter.categoryBits=0x0100;
			body3->CreateFixture(tf3);
	//prismatic joint for the other rod
			b2PrismaticJointDef jd3;
			jd3.Initialize(hidden, body3, t3.position, b2Vec2(-1.0f, 0.0f));
			jd3.lowerTranslation = -5.0f;
			jd3.upperTranslation = 5.0f;
			jd3.enableLimit = true;

			m_joint3 = (b2PrismaticJoint*)m_world->CreateJoint(&jd3);
	//gear joint for circle and trigger
			b2GearJointDef jd4;
			jd4.bodyA = body1;
			jd4.bodyB = body2;
			jd4.joint1 = m_joint1;
			jd4.joint2 = m_joint2;
			jd4.ratio = -1.0f  / circle1.m_radius;
			(b2GearJoint*)m_world->CreateJoint(&jd4);
	//gear joint for the rod and circle
			b2GearJointDef jd5;
			jd5.bodyA = body1;
			jd5.bodyB = body3;
			jd5.joint1 = m_joint1;
			jd5.joint2 = m_joint3;
			jd5.ratio = -1.0f / circle1.m_radius;
			(b2GearJoint*)m_world->CreateJoint(&jd5);
			
			//body2->SetLinearVelocity(b2Vec2(30,0));
	//spring between hidden static part and trigger
		    b2DistanceJointDef spring3;
			spring3.Initialize(body2, hidden ,b2Vec2(1.f,22.f), b2Vec2(8.f,22.f));
			spring3.collideConnected=true;
			spring3.frequencyHz = 0.2f;
			spring3.dampingRatio = 1.0f;
			m_world->CreateJoint(&spring3);
	// lock 
			b2BodyDef t5;
			t5.type = b2_dynamicBody;
			t5.position.Set(10.f, 19.f);
			b2Body* lock = m_world->CreateBody(&t5);
			b2FixtureDef *tf5 = new b2FixtureDef;
			b2PolygonShape bs5;
			bs5.SetAsBox(1.0,0.5);
			tf5->density=1.0f;
			tf5->shape = &bs5;
			tf5->filter.maskBits=0x0100;
			tf5->filter.categoryBits=0x0100;
			lock->CreateFixture(tf5);
	//revolute joint between lock and hidden static part
			b2RevoluteJointDef jd8;
			jd8.bodyA = hidden;
			jd8.bodyB = lock;
			jd8.localAnchorA.Set(0,-1.3);
			jd8.localAnchorB.Set(-2.0,0);
			jd8.collideConnected = false;
			jd8.referenceAngle = lock->GetAngle() - hidden->GetAngle();
			jd8.upperAngle = 0;
		    (b2RevoluteJoint*)m_world->CreateJoint(&jd8);
	//the hitter part
			b2BodyDef t6;
			t6.type = b2_dynamicBody;
			t6.position.Set(15.f, 22.f);
			b2Body* hitter = m_world->CreateBody(&t6);
			
			b2FixtureDef *tf61 = new b2FixtureDef;
			b2FixtureDef *tf62 = new b2FixtureDef;
			b2PolygonShape ps61;
			b2PolygonShape ps62;
			ps61.SetAsBox(4.0,0.5);
			b2Vec2 v[3];
			v[0].Set(3,0.5);
			v[1].Set(4,0.5);
			v[2].Set(3.5,2);
			ps62.Set(v,3);
			tf61->density=1.0f;
			tf61->shape = &ps61;
			tf61->filter.maskBits=0x1100;
			tf61->filter.categoryBits=0x0110;
			tf62->filter.maskBits=0x1100;
			tf62->filter.categoryBits=0x0110;
			tf62->density=1.0f;
			tf62->shape = &ps62;
				
			hitter->CreateFixture(tf61);
			hitter->CreateFixture(tf62);
	//revolute joint about hitter
			b2RevoluteJointDef jd9;
			jd9.bodyA = hidden;
			jd9.bodyB = hitter;
			jd9.localAnchorA.Set(6.,0.);
			jd9.localAnchorB.Set(0.,0);
			jd9.referenceAngle = hitter->GetAngle() - hidden->GetAngle();
			(b2RevoluteJoint*)m_world->CreateJoint(&jd9);
	//spring between hitter and hidden static part
			b2DistanceJointDef spring4;
			spring4.Initialize(hidden, hitter ,b2Vec2(10.f,23.f), b2Vec2(12.f,20.5f));
			spring4.collideConnected=true;
			spring4.frequencyHz = 0.2f;
			spring4.length = 15.f;
			spring4.dampingRatio = 1.0f;
			
			m_world->CreateJoint(&spring4);
  }
 }
	void dominos_t::keyboard(unsigned char key)
	{
		 switch (key)
		{
			case 's':
			 body2->SetLinearVelocity(b2Vec2(30,0));
			 break;
			 
			case 'w':
			 box1->SetLinearVelocity(b2Vec2(15,0));
			 break;
			 
			  
	  //! The default case. Why is this needed?
			default:
				cs296::base_sim_t::keyboard(key);
		}
	}

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
