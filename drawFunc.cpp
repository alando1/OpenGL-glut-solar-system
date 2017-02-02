#include "DrawFunc.h"
extern float rot2, x,y,z, lx,ly,lz;
extern int Portals;

void drawSnowstorm()
{
glRotatef(rot2*22, 0.45f,0.67f,0.23f);
	for(int i = -10; i < 10; i++)
		for(int j=-10; j < 10; j++) 
		{
        	glPushMatrix();
			glTranslatef(i*20.0,0, j * 20.0);
			
			if(j%2==0)
				drawSnowDude();
			else
            	drawSnowMan();
			glPopMatrix();
		}
}

void drawgrid()
{
	glBegin(GL_LINES);
	float xx;
	for (int a = -200; a < 200; a++)
		{	
			xx= (float)(a+200)/(400.0f);
			glColor3f(1.0f, xx/2, a);
			glVertex3f(-200, 0, a);
			glVertex3f(200, 0, a);

			glColor3f(1.0f, xx/2, a);
			glVertex3f(a, 0, -200);
			glVertex3f(a, 0, 200);

			glColor3f(a, 1.0f, xx/2);
			glVertex3f(a, -200, 0);
			glVertex3f(a, 200, 0);

			glColor3f(a, 1.0f, xx/2);
			glVertex3f(-200, a, 0);
			glVertex3f(200, a, 0);

			glColor3f(xx/2, a, 1.0f);
			glVertex3f(0, a, -200.0f);
			glVertex3f(0, a, 200.0f);

			glColor3f(xx/2, a, 1.0f);
			glVertex3f(0, -200, a);
			glVertex3f(0, 200, a);
		}
	glEnd();
}
void orbitSnowmen()
{
	/*-----Draw orbiting snowmen------*/
	glPushMatrix();
	glRotatef(rot2, 0,0,1);
	glTranslatef(0,500.0f,0);
	glScalef(25.0f, 25.0f, 25.0f);
	drawSnowMan();
	glPopMatrix();

	glPushMatrix();
	glRotatef(rot2+180, 1,0,0);
	glTranslatef(0,500.0f,0);
	glScalef(25.0f, 25.0f, 25.0f);
	drawSnowMan();
	glPopMatrix();

	glPushMatrix();
	glRotatef(rot2, 0,1,0);
	glTranslatef(500.0f,0,0);
	glScalef(55.0f, 55.0f, 55.0f);
	drawSnowMan();
	glPopMatrix();
}

void otherGrid()
{
	glBegin(GL_LINES);
	glColor3f(0.250f, 0.325f, 0.75f);
	float w;
	for (int a = -2000; a < -1000; a++)
		{	
			w= (float)(a+2000)/1000.0f;
			glColor3f(1.0f, w/2, a);
			glVertex3f(-2000, -2000, a);
			glVertex3f(-1000, -2000, a);

			glColor3f(1.0f, w/2, a);
			glVertex3f(a, -2000, -2000);
			glVertex3f(a, -2000, -1000);

			glColor3f(a, 1.0f, w/2);
			glVertex3f(a, -2000, -2000);
			glVertex3f(a, -1000, -2000);

			glColor3f(a, 1.0f, w/2);
			glVertex3f(-2000, a, -2000);
			glVertex3f(-1000, a, -2000);

			glColor3f(w/2, a, 1.0f);
			glVertex3f(-2000, a, -2000.0f);
			glVertex3f(-2000, a, -1000.0f);

			glColor3f(w/2, a, 1.0f);
			glVertex3f(-2000, -2000, a);
			glVertex3f(-2000, -1000, a);
		}
	glEnd();
}

void drawFloor()
{
	glBegin(GL_QUADS);
		glVertex3f(-200.0f, 0.0f, -200.0f);
		glVertex3f(-200.0f, 0.0f,  200.0f);
		glVertex3f( 200.0f, 0.0f,  200.0f);
		glVertex3f( 200.0f, 0.0f, -200.0f);
	glEnd();
}
void spinner2()
{
	/*-----front of polygon--------*/
	glScalef(25,10,25);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0,0,0);
	glVertex3f(0, 20, 0);
	glColor3f(1,0,0);
	glVertex3f(8.66f,0,5.0f);
	glColor3f(0,1,0);
	glVertex3f(0,0,10);
	glColor3f(0,0,1);
	glVertex3f(-8.66f,0,5.0f);
	glColor3f(1,1,0);
	glVertex3f(-8.66f,0,-5.0f);
	glColor3f(0,1,1);
	glVertex3f(0,0,-10);
	glColor3f(1,0,1);
	glVertex3f(8.66f,0,-5.0f);
	glColor3f(1,0,0);
	glVertex3f(8.66f,0,5.0f);
	glEnd();

	/*-------base of polygon--------*/

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0,0,0);
	glVertex3f(0, -0.01f, 0);
	glColor3f(1,0,0);
	glVertex3f(8.66f,0,5.0f);
	glColor3f(0,1,0);
	glVertex3f(0,0,10);
	glColor3f(0,0,1);
	glVertex3f(-8.66f,0,5.0f);
	glColor3f(1,1,0);
	glVertex3f(-8.66f,0,-5.0f);
	glColor3f(0,1,1);
	glVertex3f(0,0,-10);
	glColor3f(1,0,1);
	glVertex3f(8.66f,0,-5.0f);
	glColor3f(1,0,0);
	glVertex3f(8.66f,0,5.0f);
	glEnd();
}
void spinner()
{
	glScalef(7.5f,7.5f,4.445f);
	/*-----front of polygon--------*/
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1,1,1);
	glVertex3f(0, 0, 45);
	glColor3f(1,0,0);
	glVertex3f(0, 25, 0);
	glColor3f(0,1,0);
	glVertex3f(25, 5, 0);

	glColor3f(0,0,1);
	glVertex3f(15, -25, 0);
	glColor3f(1,1,0);
	glVertex3f(-15, -25, 0);
	glColor3f(0,1,1);
	glVertex3f(-25, 5, 0);
	glColor3f(1,0,1);
	glVertex3f(0,25,0);

	/*-------base of polygon--------*/
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1,1,1);
	glVertex3f(0, 0, -1);
	glColor3f(1,0,0);
	glVertex3f(0, 25, 0);
	glColor3f(0,1,0);
	glVertex3f(25, 5, 0);

	glColor3f(0,0,1);
	glVertex3f(15, -25, 0);
	glColor3f(1,1,0);
	glVertex3f(-15, -25, 0);
	glColor3f(0,1,1);
	glVertex3f(-25, 5, 0);
	glColor3f(1,0,1);
	glVertex3f(0,25,0);
	glScalef((1/7.5f),(1/7.5f),(1/4.445f));
	glEnd();
}

void drawSnowMan() {

	glColor3f(1.0f, 1.0f, 1.0f);

// Draw Body
	glTranslatef(0.0f ,0.75f, 0.0f);
	glutSolidSphere(0.75f,20,20);

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


void drawSnowDude() 
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

void texturePlane(int testTexture)
{
	/*-------test texturing----*/
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, testTexture);
	glColor4f(1.0f,1.0f,1.0f,1.0f);

	glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(-50.0f, 0.0f, 50.0f);
		glTexCoord2f(1, 0);
		glVertex3f( 50.0f, 0.0f, 50.0f);
		glTexCoord2f(1, 1);
		glVertex3f( 50.0f, 0.0f, -50.0f);
		glTexCoord2f(0, 1);
		glVertex3f(-50.0f, 0.0f, -50.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void openPortal(float x, float y, float z, float lx, float ly, float lz)
{
	glTranslatef(x+lx,y+ly,z+lz);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, Portals);
	glColor4f(1.0f,1.0f,1.0f,0.7f);

	glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(-46.8f,45,0);
		glTexCoord2f(1, 0);
		glVertex3f(-46.8f,-45,0);
		glTexCoord2f(1, 1);
		glVertex3f(46.8f,-45,0);
		glTexCoord2f(0, 1);
		glVertex3f(46.8f,45,0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}
/*
void setVSync(int interval=1)
{

	typedef BOOL (APIENTRY *PFNWGLSWAPINTERVALFARPROC)( int );
	PFNWGLSWAPINTERVALFARPROC wglSwapIntervalEXT = 0;

  const GLubyte* extensions= glGetString(GL_EXTENSIONS);
  cout << endl << endl << "Printing extensions:" <<endl << endl <<extensions << endl << endl;

  if( strstr( reinterpret_cast<const char*>(extensions), "WGL_EXT_swap_control" ) == 0 )
    {cout << "\n>Vsync not supported.\n";
    return; // Error: WGL_EXT_swap_control extension not supported on your computer.\n";
	}
  else
  {
    wglSwapIntervalEXT = (PFNWGLSWAPINTERVALFARPROC)wglGetProcAddress( "wglSwapIntervalEXT" );

    if( wglSwapIntervalEXT ){
      wglSwapIntervalEXT(interval);
      cout << "\n>Vsync set.\n";
    }
  }
}
*/
