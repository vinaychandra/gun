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
#include "iostream"
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
  b2Body* hitter;
  b2Body* stick;
  int shellcount=5;
  b2Body* shell[5];
  b2Body* bullet[5];
  b2Body* brick[40][5];
  b2Body *ground;

  
  dominos_t::dominos_t()
  {
    /*! \b The \b Static \b Part
     * 
     * This constitutes the static part of the gun.
     * It includes the outer skeleton of the gun which is static.
     * Since they are all static, all the fixtures below are mapped to the same body.
     * maskBits, categoryBits are used to avoid collision between some bodies.
     */
    {
      b2BodyDef *bd = new b2BodyDef;
      bd->position.Set(0,20);
      bd->fixedRotation = true;
      /*! f1
       * 
       * This is the topmost static part of the gun i.e the outer ring of the barrel of the gun
       * It is an edge from (-30,7) to (3.5,7)
       */
      b2FixtureDef *f1 = new b2FixtureDef;
      f1->density = 10.0;
      f1->friction = 0.5;
      f1->restitution = 0.f;
      f1->shape = new b2EdgeShape;
      b2EdgeShape e1;
      e1.Set(b2Vec2(-30.f, 7.f), b2Vec2(5.0f,7.f));
      f1->shape = &e1;
      f1->filter.maskBits = 0x0010;
      f1->filter.categoryBits = 0x0011;
      /*! f2
       * 
       * This is the bottom outer ring of the barrel 
       * It is an edge from (-30,4) to (-1,4)
       */
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
      /*! f5
       * 
       * This is the slant edge which allows the bullet to be placed before the firing pin to be hit
       */    
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
      /*! f3
       * 
       * This is the rectangle which holds a block attached to a spring above it
       */
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
      /*! f9
       * 
       * It is a part of the trigger guard.
       * shape - rectangle(the one to the left of trigger)
       */
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
      /*! f10
       * 
       * It is a part of the trigger guard.
       * shape - rectangle(the one to the bottom of trigger)
       */
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
      /*! f6
       * 
       * This rectangle is the separator between the bullets and the trigger.
       * It is to the left of the bullets
       */
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
      /*! f8
       * 
       * This rectangle is below the bullets
       */
      b2FixtureDef *f8 = new b2FixtureDef;
      f8->density = 10.0;
      f8->friction = 0.5;
      f8->restitution = 0.f;
      f8->shape = new b2PolygonShape;
      b2PolygonShape p8;
      p8.SetAsBox(4,0.2, b2Vec2(4.f,-15.f), 0);
      f8->shape = &p8;
      f8->filter.maskBits = 0x0010;
      f8->filter.categoryBits = 0x0018;
      /*! f7
       * 
       * This rectangle is to the right of the bullets
       */       
      b2FixtureDef *f7 = new b2FixtureDef;
      f7->density = 10.0;
      f7->friction = 0.5;
      f7->restitution = 0.f;
      f7->shape = new b2PolygonShape;
      b2PolygonShape p7;
      p7.SetAsBox(0.2,9.3, b2Vec2(8.0f,-5.9f), 0);
      f7->shape = &p7;
      f7->filter.maskBits = 0x0010;
      f7->filter.categoryBits = 0x0017;
      /*! f4
       * 
       * This rectangle is to constrain the motion of the dynamic block to the left of it
       */  
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
      /*! ac1
       * 
       * This is the lower part of the inner ring of the barrel.
       * shape - chain shape on 3 vertices
       * This is needed in order to stop the shell and to allow only the bullet
       */ 
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
      /*! ac2
       * 
       * This is the upper part of the inner ring of the barrel.
       * shape - chain shape on 3 vertices
       * This is needed in order to stop the shell and to allow only the bullet
       */ 
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
      /*! fd11
       * 
       * This is a small hinge to constrain the translation of the block
       */
      b2FixtureDef *fd11 = new b2FixtureDef;
      fd11->density = 10.0;
      fd11->friction = 0.5;
      fd11->restitution = 0.f;
      fd11->shape = new b2EdgeShape;
      b2EdgeShape bs11;
      bs11.Set(b2Vec2(-30.f, 4.f), b2Vec2(-30.f, 3.f));
      fd11->shape = &bs11;
      /*! shellescape
       * 
       * This is the slant edge shape to let the shell escape
       */
      b2FixtureDef *shellescape = new b2FixtureDef;
      shellescape->density = 10.0;
      shellescape->friction = 0.5;
      shellescape->restitution = 0.f;
      shellescape->shape = new b2EdgeShape;
      b2EdgeShape bs12;
      bs12.Set(b2Vec2(8.f, 3.7f), b2Vec2(10.f, 5.3f));
      shellescape->shape = &bs12;
      shellescape->filter.maskBits = 0x8000;
      shellescape->filter.categoryBits = 0x8000;
      
      
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
      box1->CreateFixture(shellescape);

  }
  
  /*! \b Firing \b pin
   * 
   *  This part consists of some dynamic bodies
   */
   {
	  b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(0,20);
      bd->fixedRotation = true;
      /*! fd1
	   * 
       * This is the block which is connected to the spring. 
       * This acts like a constraint to the movement of the ring around the firing pin
	   */
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 50.0;
      fd1->friction = 0;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(4,1.9, b2Vec2(-26.f,2.f), 0);
      fd1->shape = &bs1;
      fd1->filter.categoryBits = 0x0010;
      /*! fd2
       * 
       * This is the slide(rectangle) on top of the barrel
       */
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 50.0;
      fd2->friction = 0;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(7,0.2, b2Vec2(-23.f,7.2f), 0);
      fd2->shape = &bs2;
      fd2->filter.categoryBits = 0x0010;
      /*! fd3
	   * 
       * This is the upper half of the ring around the firing pin
       * shape - polygon on 4 vertices
	   */ 
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
	  fd3->filter.categoryBits = 0x0110;
	  fd3->filter.maskBits = 0x1010;
	  /*! fd4
	   * 
       * This is the lower half of the ring around the firing pin
       * shape - polygon on 4 vertices
	   */
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
	  fd4->filter.categoryBits = 0x0110;
	  fd4->filter.maskBits = 0x1010;
	  /*! fd5
	   * 
       * This is the firing pin
       * shape - polygon on 5 vertices
	   */
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
	  
	  b2BodyDef *stickbd = new b2BodyDef;
      stickbd->type = b2_dynamicBody;
      stickbd->position.Set(0,20);
      stickbd->fixedRotation = true;
	  stick = m_world->CreateBody(stickbd);
      stick->CreateFixture(fd5);
      stick->SetLinearVelocity(b2Vec2(-20,0));
      /*! invibd
	   * 
       * This is a static body, created to connect the right end of the spring
	   */
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
      /**
        * fd1, fd2, fd3, fd4 are mapped to the same body as they all move together \n
	   * Two springs are created between fd5 and fd3,fd4. \n
	   * Another spring is created between fd1, invibd
	   */
      b2DistanceJointDef internal1;
      internal1.Initialize(box1, stick, b2Vec2(9.8,25.3), stick->GetWorldCenter());
      internal1.collideConnected=true;
      internal1.frequencyHz = 0.7f;
      internal1.dampingRatio = 1.0f;
      m_world->CreateJoint(&internal1);
      b2DistanceJointDef internal2;
      internal2.Initialize(box1, stick, b2Vec2(9.8,24.0), stick->GetWorldCenter());
      internal2.collideConnected=true;
      internal2.frequencyHz = 0.7f;
      internal2.dampingRatio = 1.0f;
      m_world->CreateJoint(&internal2);
      b2DistanceJointDef spring1;
      spring1.Initialize(box1, invi, b2Vec2(-22,22), invi->GetWorldCenter());
      spring1.collideConnected=true;
      spring1.frequencyHz = 0.07f;
      spring1.dampingRatio = 0.1f;
      m_world->CreateJoint(&spring1);
        
     }
     
	  /*! \b Bullets
	  * 
      *  This part consists of bullets, shells
	  */
	   {
	      /*! sf1
		   * 
		   * This fixture is a part of the shell. It is the top part
		   * shape - polygon on 4 vertices
		   */
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
		  sf1->filter.categoryBits = 0x8010;
		  /*! sf2
		   * 
		   * This fixture is a part of the shell. It is the bottom part
		   * shape - polygon on 4 vertices
		   */
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
		  sf2->filter.categoryBits = 0x8010;
		  /*! sf3
		   * 
		   * This fixture is a part of the shell. It is the right part.
		   * shape - polygon on 4 vertices
		   */ 
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
		  sf3->filter.categoryBits = 0x8010;
		  /*! bf
		   * 
		   * This is the fixture of the bullet. It is a polygon on 5 vertices
		   */
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
		  /** In every loop, a bullet and a shell surrounding it are created
		   * */
	  for(int i=0; i<shellcount ;i++){
		  b2BodyDef *bulletDef = new b2BodyDef;
          bulletDef->type = b2_dynamicBody;
          bulletDef->position.Set(0.4,22-3.0*i);
          bulletDef->fixedRotation = true;
          
          bullet[i] = m_world->CreateBody(bulletDef);
		  bullet[i]->CreateFixture(bf);
		  
		  b2BodyDef *shellDef = new b2BodyDef;
          shellDef->type = b2_dynamicBody;
          shellDef->position.Set(1.9,22-3.0*i);
          shell[i] = m_world->CreateBody(shellDef);
		  shell[i]->CreateFixture(sf1);
		  shell[i]->CreateFixture(sf2);
		  shell[i]->CreateFixture(sf3);
		  
	}
      
	}
	
	 /*! \b Bullet \b base
	  * 
	  */
	  
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
      /*! fd1
       * 
       * It acts as a base for all the bullets. shape - rectangle
       */ 
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
      /**
       * There is a spring between the base and the bottom of the gun.
       * It is kept in a compressed state to push the bullets upward.
       */
      b2DistanceJointDef spring1;
      spring1.Initialize(box1, invi, box1->GetWorldCenter(), invi->GetWorldCenter());
      spring1.collideConnected=true;
      spring1.frequencyHz = 1.0f;
      spring1.dampingRatio = 1.0f;
      spring1.length = 18.8f;
      m_world->CreateJoint(&spring1);
  }
  /*! \b Trigger, \b Hammer
   * 
   *  This set of objects will not collide with the bullets, and the base due to their
   *  maskBits, categoryBits.
   */
  {
	  	//the ground part
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.Set(b2Vec2(100.0f, -20.0f), b2Vec2(-200.0f, -20.0f));
			ground->CreateFixture(&shape, 0.0f);


			b2RevoluteJoint* m_joint1;
			b2PrismaticJoint* m_joint2;
			b2PrismaticJoint* m_joint3;
			b2CircleShape circle1;
			circle1.m_radius = 1.0f;
		  /*! rod1, trigger, verticallong, rod2 
	       * 
	       * trigger, rod1, verticallong, rod2 : shape - rectangle
	       * rod1 is connected to the trigger, and determines the rotation of the gear
	       * verticallong is static 
	       * rod2 is the other rod in the gear
	       */
			b2PolygonShape rod1,rod2,verticallong,trigger;
			b2Vec2 vert[4];
			vert[0].Set(0.f,0.f);
			vert[1].Set(-8.f,0.f);
			vert[2].Set(-8.f,1.f);
			vert[3].Set(0.f,1.f);
			rod1.Set(vert,4);
      
			vert[0].Set(-8.f,1.f);
			vert[1].Set(-9.f,1.f);
			vert[2].Set(-9.f,-3.f);
			vert[3].Set(-8.f,-3.f);
			trigger.Set(vert,4);
			
			verticallong.SetAsBox(0.5f, 5.f);
			
			rod2.SetAsBox(3.f, 0.5f);
	
			/*! body1
			 * 
			 * body mapped with circle1
			 */
			t1.type = b2_dynamicBody;
			t1.position.Set(4.0f, 20.0f);
			b2Body* body1 = m_world->CreateBody(&t1);
			b2FixtureDef *tf1 = new b2FixtureDef;
			tf1->shape = &circle1;
			tf1->density = 5.0f;
			tf1->filter.categoryBits=0x0100;
			tf1->filter.maskBits=0x0100;
			body1->CreateFixture(tf1);
	
			/*! hidden
			 * 
			 * body mapped with verticallong, does not interact with any other body
			 */
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
			
			/*! jd1
			 * 
			 * revolute joint between hidden, body1
			 */
	
			b2RevoluteJointDef jd1;
			jd1.bodyA = hidden;
			jd1.bodyB = body1;
			jd1.localAnchorA = hidden->GetLocalPoint(t1.position);
			jd1.localAnchorB = body1->GetLocalPoint(t1.position);
			jd1.referenceAngle = body1->GetAngle() - ground->GetAngle();
			m_joint1 = (b2RevoluteJoint*)m_world->CreateJoint(&jd1);
	
			/*! body2
			 * 
			 * body mapped with trigger, rod1
			 */
			t2.type = b2_dynamicBody;
			t2.position.Set(4.5f, 21.f);
			body2 = m_world->CreateBody(&t2);
			b2FixtureDef *tf21 = new b2FixtureDef;
			tf21->shape = &rod1;
			tf21->density = 5.0f;
			tf21->filter.categoryBits=0x0100;
			tf21->filter.maskBits=0x0100;
			body2->CreateFixture(tf21);
			
			b2FixtureDef *tf23 = new b2FixtureDef;
			tf23->shape = &trigger;
			tf23->density = 5.0f;
			tf23->filter.categoryBits=0x0100;
			tf23->filter.maskBits=0x0100;
			body2->CreateFixture(tf23);
			/*! jd2
			 * 
			 * prismatic joint between hidden, body2 in direction b2Vec2(-1.0f, 0.0f)
			 * Since hidden is static, this allows body2 to move only along x
			 */
	
			b2PrismaticJointDef jd2;
			jd2.Initialize(hidden, body2, t2.position, b2Vec2(1.0f, 0.0f));
			jd2.lowerTranslation = -5.0f;
			jd2.upperTranslation = 5.0f;
			jd2.enableLimit = true;

			m_joint2 = (b2PrismaticJoint*)m_world->CreateJoint(&jd2);
	
			/*! body3
			 * 
			 * body mapped with rod2
			 */
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
	
			/*! jd3
			 * 
			 * prismatic joint between hidden, body3 in direction b2Vec2(-1.0f, 0.0f)
			 * Since hidden is static, this allows body3 to move only along x
			 */
			b2PrismaticJointDef jd3;
			jd3.Initialize(hidden, body3, t3.position, b2Vec2(-1.0f, 0.0f));
			jd3.lowerTranslation = -5.0f;
			jd3.upperTranslation = 5.0f;
			jd3.enableLimit = true;

			m_joint3 = (b2PrismaticJoint*)m_world->CreateJoint(&jd3);
			/*! jd4, jd5
			 * 
			 * jd4 is the gear joint between body1, body2
			 * jd5 is the gear joint between body1, body3
			 */
	
			b2GearJointDef jd4;
			jd4.bodyA = body1;
			jd4.bodyB = body2;
			jd4.joint1 = m_joint1;
			jd4.joint2 = m_joint2;
			jd4.ratio = -1.0f  / circle1.m_radius;
			(b2GearJoint*)m_world->CreateJoint(&jd4);
	
			b2GearJointDef jd5;
			jd5.bodyA = body1;
			jd5.bodyB = body3;
			jd5.joint1 = m_joint1;
			jd5.joint2 = m_joint3;
			jd5.ratio = -1.0f / circle1.m_radius;
			(b2GearJoint*)m_world->CreateJoint(&jd5);
			
			/*! spring3
			 * 
			 * spring3 is the spring between body2, hidden
			 */
			b2DistanceJointDef spring3;
			spring3.Initialize(body2, hidden ,b2Vec2(1.f,22.f), b2Vec2(8.f,22.f));
			spring3.collideConnected=true;
			spring3.frequencyHz = 0.2f;
			spring3.dampingRatio = 1.0f;
			m_world->CreateJoint(&spring3);
			/*! lock
			 * 
			 * lock is the rectangular body whick acts as a lock to hammer
			 */
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
			/*! jd8
			 * 
			 * jd8 is the revolute joint between hidden, lock
			 */
			b2RevoluteJointDef jd8;
			jd8.bodyA = hidden;
			jd8.bodyB = lock;
			jd8.localAnchorA.Set(0,-1.3);
			jd8.localAnchorB.Set(-2.0,0);
			jd8.collideConnected = false;
			jd8.referenceAngle = lock->GetAngle() - hidden->GetAngle();
			jd8.upperAngle = 0;
		    (b2RevoluteJoint*)m_world->CreateJoint(&jd8);
			/*! hitter
			 * 
			 * hitter is the hammer
			 */
			b2BodyDef t6;
			t6.type = b2_dynamicBody;
			t6.position.Set(15.f, 22.f);
			hitter = m_world->CreateBody(&t6);
			
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
			/*! jd9
			 * 
			 * jd9 is the revolute joint between hidden, hitter
			 */
			b2RevoluteJointDef jd9;
			jd9.bodyA = hidden;
			jd9.bodyB = hitter;
			jd9.localAnchorA.Set(6.,0.);
			jd9.localAnchorB.Set(0.,0);
			jd9.referenceAngle = hitter->GetAngle() - hidden->GetAngle();
			(b2RevoluteJoint*)m_world->CreateJoint(&jd9);
			/*! spring4
			 * 
			 * spring4 is the spring between hidden, hitter
			 */
			b2DistanceJointDef spring4;
			spring4.Initialize(hidden, hitter ,b2Vec2(10.f,23.f), b2Vec2(12.f,20.5f));
			spring4.collideConnected=true;
			spring4.frequencyHz = 0.2f;
			spring4.length = 15.f;
			spring4.dampingRatio = 1.0f;
			
			m_world->CreateJoint(&spring4);
  }
  /*! \b Bricks
   * 
   */
  {
	  /*! brf
	   *   
	   * brf is a rectangle
	   */
      b2FixtureDef *brf = new b2FixtureDef;
      brf->density = 1.0;
      brf->friction = 0.5;
      brf->restitution = 0.0f;
      brf->shape = new b2PolygonShape;
      b2PolygonShape cons;
      cons.SetAsBox(1.0,1.0, b2Vec2(7.0,2.6), 0);
      brf->shape = &cons;
      for(int i = 0; i< 40; i++){
		  for(int j = 0 ;j < 5; j++){
			    b2BodyDef* brickDef = new b2BodyDef;
			    brickDef->type = b2_dynamicBody;
				brickDef->position.Set(-150 + 2.5*j ,-20+ 2.5*i);
				brick[i][j] = m_world->CreateBody(brickDef);
				brick[i][j]->CreateFixture(brf);
		}
	  }  
			  
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
			 
		    case 'b':
		    for(int i = 0; i< 40; i++){
				for(int j = 0 ;j < 5; j++){
			    brick[i][j]->SetTransform(b2Vec2(-150 + 2.5*j ,-20+ 2.5*i),ground->GetAngle());
			    brick[i][j]->SetLinearVelocity(b2Vec2(0.,0.));
			    brick[i][j]->SetAngularVelocity(0.f);
			    
			}
	  } 
		     
	  //! The default case. Why is this needed?
			default:
				cs296::base_sim_t::keyboard(key);
		}
	}
	
			void dominos_t::step(settings_t* settings){
			for(b2Contact* contact = m_world->GetContactList();contact;contact=contact->GetNext())
			{
				if(contact != NULL)
				{
					b2Body* a = contact->GetFixtureA()->GetBody();
					b2Body* b = contact->GetFixtureB()->GetBody();
						if(((a == hitter) && (b == stick)) || ((a == stick) && (b == hitter))){
						if(contact -> IsTouching())
							{
								int i = int((25.5  - shell[shellcount-1]->GetPosition().y)/2.5);
								bullet[shellcount-1-i]->SetLinearVelocity(b2Vec2(-200,0));
								box1->SetLinearVelocity(b2Vec2(60,0));
								stick->SetLinearVelocity(b2Vec2(60,0));;
								shell[shellcount-1-i]->SetLinearVelocity(b2Vec2(60,0));
								
								
							}
						}
				}
			}
			cs296::base_sim_t::step(settings);
		}

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
