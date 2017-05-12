#include <iostream>
#include <cmath>
#include "vector.h"
#include "Snowman.h"

SnowMan::SnowMan(Vec3 p, Vec3 d, Vec3 v, Vec3 c, float m, float s) :
	pos(p), dir(d), vel(v), color(c), mass(m), speed(s)
	{

	}

void SnowMan::drawSnowMan()
{


//draw SnowDude
        glColor3f(1.0f, 0.0f, 0.0f);

// Draw Body
        glTranslatef(0.0f ,0.75f, 0.0f);
        glutWireSphere(0.75f,10,10);

// Draw Head
        glTranslatef(0.0f, 1.0f, 0.0f);
        glutSolidSphere(0.2f,20,20);

// Draw Eyes
        glPushMatrix();
        glColor3f(0.0f,0.0f,0.0f);
        glTranslatef(0.05f, 0.10f, 0.18f);
        glutSolidSphere(0.05f,10,10);
        glTranslatef(-0.1f, 0.0f, 0.0f);
        glutSolidSphere(0.05f,10,10);
        glPopMatrix();

// Draw Nose
        glColor3f(1.0f, 0.5f , 0.5f);
        glRotatef(0.0f,1.0f, 0.0f, 0.0f);
        glutSolidCone(0.08f,0.5f,10,2);

}
