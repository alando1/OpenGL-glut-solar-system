#include "renderUpdates.h"

extern void printScreenText();
extern Planet planets[10];
extern list<Portal*> portalList;
extern Planet Mercury, Venus, Earth, Moon, Mars, Jupiter, Saturn, Uranus, Neptune, Pluto;
extern bool keyStates[256], keyTaps[256], planetBools[3], shiftKeyState, pause,
			EarthBool, MarsBool, orbitLock;
extern GLUquadricObj* quadric;
extern float earthRadius, boost, aspectratio, perspective,
			 heading, pitch, rot, rot2, relative, speed;
extern Vec3 campos, camlook, vec;
extern int centerX, centerY, testTexture, SunTexture, MercuryTexture, VenusTexture, EarthTexture,
	MarsTexture, JupiterTexture, SaturnTexture, UranusTexture, NeptuneTexture, PlutoTexture,
	SaturnRingTexture, UranusRingTexture, MoonTexture, StarTexture, GalaxyTexture,
	Nebula, Lense, Spiral, Portals, PortalsCenter, PortalsOuter, EarthSky, Grass, Rocks;
extern void* font;
float FPS =0;
int currentPlanet;

void handleFunc()
{
	float vecx =0.0f, vecy=0.0f, vecz=0.0f;

	speed = 3.0f;
	if(EarthBool)
		speed = .55f;
	if(MarsBool)
		speed = .75f;

	if((keyStates['q'] || keyStates['Q']))
	{
		campos+=camlook*speed;
	}
	if(keyStates['r'] || keyStates['R'])
	{
		float tmp;
		if(!EarthBool && !MarsBool)
			tmp = 50.5;
		else
		{
			tmp = 13.5;
		}
		campos+=camlook*tmp*speed;
	}
	/*--------Move-Foward---------*/
	if(keyStates['w'] || keyStates['W'])
	{
		campos.x+=camlook.x*speed;
		//campos.y+=camlook.y*speed;	//comment out to walk forward on plane
		campos.z+=camlook.z*speed;
	}
	/*--------Move-Backwards------*/
	if(keyStates['s'] || keyStates['S'])
	{
		campos.x-=camlook.x*speed;
		//y-=ly*speed;  //comment out to walk backwards on plane
		campos.z-=camlook.z*speed;
	}
	/*--------Move-Left----------*/
	if(keyStates['a'] || keyStates['A'])
	{
		vecx = camlook.z;
		vecy = camlook.y;
		vecz = -camlook.x;
		campos.x+= vecx*speed;
		campos.z+= vecz*speed;
	}
	/*--------Move-Right----------*/
	if(keyStates['d'] || keyStates['D'])
	{

		vecx = camlook.z;
		vecy = camlook.y;
		vecz = -camlook.x;
		campos.x-= vecx*speed;
		campos.z-= vecz*speed;		

	}
	/*---------crouch-------------*/
	if(keyStates['c'] || keyStates['C'])
	{
		campos.y-= .75*speed;
	}
	/*----------jump--------------*/
	if(keyStates[' '])
	{
		campos.y+= .75*speed;
	}
	/*--------Zoom out------------*/
	if(keyStates['z'] || keyStates['Z'])
	{
		campos-=camlook*speed;
	}
	/*--------Zoom in-------------*/
	if(keyStates['x'] || keyStates['X'])
	{
		campos+=camlook*speed;
	}
	/*-------change locations--------*/
	if(keyStates['\t'])
	{
		campos.x=0.0f; campos.y=1.0f; campos.z=5.0f;
		Vec3 newl(campos);
		newl.normalize();
		camlook.x = 0;//newl.x;
		camlook.y = 0;//newl.y;
		camlook.z = -1;//newl.z;
	}
	if(keyStates['='])
	{
		campos.x=0.0f; campos.y=0.0f; campos.z=-3009.0f;
		Vec3 newl(campos);
		newl.normalize();
		camlook = newl;
	}
	if(keyStates['0'])
	{
		campos.x=0.0f; campos.y=3000.0f; campos.z=-2009.0f;
		Vec3 newl(campos);
		newl.normalize();
		camlook = newl;
	}
	if(keyStates['-'])
	{
		campos.x=0.0f; campos.y=13000.0f; campos.z=0.0f;
		Vec3 newl(campos);
		newl.normalize();
		camlook = newl;
	}	
	/*--------change perspective---------*/
	if(keyStates['`'])
	{
		perspective -= 1.0f;
		if(perspective <= 1.0f)
			perspective = 180.0f;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(perspective, aspectratio, 0.1f, 40000.0f);
		glMatrixMode(GL_MODELVIEW);
	}
	if(keyStates['1'])
	{
		perspective= 45.0f;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(perspective, aspectratio, 0.1f, 40000.0f);
		glMatrixMode(GL_MODELVIEW);
	}
	if(keyStates['2'])
	{
		perspective += 1.0f;
		if(perspective >= 180.0f)
			perspective = 0.0f;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(perspective, aspectratio, 0.1f, 40000.0f);
		glMatrixMode(GL_MODELVIEW);
	}
	if(keyStates['\\'])
		relative=0.0f;
	if(keyStates[']'])
		relative=0.01f;
	if(keyStates[';'])
		relative+=0.01f;
	if(keyStates['.'])
		relative-=0.01f;
	if(keyStates['\''])
		relative+=0.0001f;
	if(keyStates['/'])
		relative-=0.0001f;

	if((keyTaps['p'] || keyTaps['P']) && (pause == FALSE))
	{
		pause = TRUE;
		cout << "> Pause:\tTRUE"<< endl;
	}
	else if((keyTaps['p'] || keyTaps['P']) && (pause == TRUE))		
	{
			pause = FALSE;
		cout << "> Pause:\tFALSE" << endl;
	}

	if((keyTaps['o'] || keyTaps['O']) && (orbitLock == FALSE))
	{
		orbitLock = TRUE;
		cout << "> Orbital Lock:\tEngaged" << endl;
	}
	else if((keyTaps['o'] || keyTaps['O']) && (orbitLock == TRUE))
	{
		orbitLock = FALSE;
		cout << "> Orbital Lock:\tDisengaged" << endl;
	}
	if((keyTaps['e'] || keyTaps['E']) && (EarthBool == FALSE))
	{
		EarthBool = TRUE;
		cout << "> Load:\t\tEarth" << endl;
	}
	else if((keyTaps['e'] || keyTaps['E']) && (EarthBool == TRUE))
	{
		EarthBool = FALSE;
		cout << "> Load:\t\tSolar Sytem" << endl;
	}
	if((keyTaps['m'] || keyTaps['M']) && (MarsBool == FALSE))
	{
		MarsBool = TRUE;
		cout << "> Load:\t\tMars" << endl;
	}
	else if((keyTaps['m'] || keyTaps['M']) && (MarsBool == TRUE))
	{
		MarsBool = FALSE;
		cout << "> Load:\t\tSolar Sytem" << endl;
	}
	if(keyTaps['t'] || keyTaps['T'])
	{
		Portal* warp = new Portal(campos, camlook, chrono::steady_clock::now());
		portalList.push_back(warp);
		cout << "> Warp:\t\tPortal Opened" << endl;
	}
}

void updatePortals()
{
	list<Portal*>::iterator it;
	auto now = chrono::steady_clock::now();

	while(it != portalList.end())
		{
			for(it = portalList.begin(); it!=portalList.end(); ++it)
			{
				auto end = (*it)->End();
				if(end < now)
				{
					portalList.erase(it);
					break;
				}
			}
		}

	it = portalList.begin();
	chrono::steady_clock::time_point followthru;

	while(it != portalList.end())
	{
		for(it = portalList.begin(); it!=portalList.end(); ++it)
		{
			Vec3 tmp = (*it)->returnPosition();
			Vec3 r = campos-tmp;
			auto opentime = (*it)->Open();
			if((r.length()<20.0f) && (opentime < now))
			{
				if(MarsBool)
				{
					if((now-followthru)> chrono::milliseconds(500))
					{
						memset(planetBools,0,3*sizeof(bool));
						followthru = chrono::steady_clock::now();
						MarsBool=FALSE;
						EarthBool=TRUE;
						return;
					}
				}
				else if(!MarsBool)
				{
					if((now-followthru)> chrono::milliseconds(500))
					{
						//memset(planetBools,0,3*sizeof(bool));
						followthru = chrono::steady_clock::now();
						MarsBool=TRUE;
						EarthBool=FALSE;
						return;
					}
				}
			}
		}
	}
}

void renderPortals()
{
	list<Portal*>::iterator it;
	for(it = portalList.begin(); it!=portalList.end(); ++it)
	{
		(*it)->openPortal();
	}
}
void renderScene(void) 
{
    auto start = chrono::steady_clock::now();

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	handleFunc();
	updatePortals();
    printScreenText();

	// Reset transformations
	glLoadIdentity();
	// Set the camera



	if(!EarthBool && !MarsBool)
	{
	/*---------star background------------*/
		gluLookAt(0,0,0,camlook.x,camlook.y,camlook.z,0,1,0);

			glPushMatrix();
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, StarTexture);
				glColor3f(1,1,1);
				glRotatef(90,0,1,0);
				gluSphere(quadric, 30000, 180,180);
			glPopMatrix();
		/*-----------Bubble planet----------*/
		glPushMatrix();
			glRotatef(90,0,1,0);
			glTranslatef(5000,0,0);
			glBindTexture(GL_TEXTURE_2D, GalaxyTexture);
			glColor3f(1,1,1);
			gluSphere(quadric, 1000, 100,100);
		glPopMatrix();

		/*----------Crown Nebula-------------*/
		glPushMatrix();
			glTranslatef(-25000,0,0);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture(GL_TEXTURE_2D, Nebula);

			glScalef(3000,3000,3000);
			glBegin(GL_QUADS);
				glColor4f(1,1,1,0.7f);
				glTexCoord2f(0, 0);
				glVertex3f( 0,-1,1);
				glTexCoord2f(1, 0);
				glVertex3f( 0,1,1);
				glTexCoord2f(1, 1);
				glVertex3f(0,1,-1);
				glTexCoord2f(0, 1);
				glVertex3f( 0,-1,-1);
			glEnd();

			glDisable(GL_BLEND);
		glPopMatrix();

		/*------------Black Hole---------------*/

		glPushMatrix();
			glTranslatef(25000,0,0);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture(GL_TEXTURE_2D, Lense);

			glRotatef(rot,1,0,0);
			glScalef(10,10,10);
			glBegin(GL_QUADS);
				glColor4f(1,1,1,0.1f);
				glTexCoord2f(0, 0);
				glVertex3f( 0,-640,360);
				glTexCoord2f(1, 0);
				glVertex3f( 0,640,360);
				glTexCoord2f(1, 1);
				glVertex3f(0,640,-360);
				glTexCoord2f(0, 1);
				glVertex3f( 0,-640,-360);
			glEnd();

			glTranslatef(-100,0,0);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture(GL_TEXTURE_2D, Spiral);

			glRotatef(rot*(-5),1,0,0);
			glBegin(GL_QUADS);
				glColor4f(1,1,1,0.1f);
				glTexCoord2f(0, 0);
				glVertex3f( 0,-168,169);
				glTexCoord2f(1, 0);
				glVertex3f( 0,168,169);
				glTexCoord2f(1, 1);
				glVertex3f(0,168,-169);
				glTexCoord2f(0, 1);
				glVertex3f( 0,-168,-169);
			glEnd();

			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		/*---------end of background-----------*/
			glLoadIdentity();

			if(orbitLock)
			{
				vec = Jupiter.getPosition();
				campos = vec;
			}
			gluLookAt(campos.x, campos.y, campos.z, campos.x+camlook.x, campos.y+camlook.y, campos.z+camlook.z, 0.0f, 1.0f, 0.0f);

			glPushMatrix();
				glRotatef(rot, 0,1,0);
				spinner2();
			glPopMatrix();

			/*-----------Draw the sun-------------*/
			glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, testTexture);

				glRotatef(rot*.3, 0.45f,0.67f,0.23f);
				glColor3f(1,0.718f,0.074f);
				gluSphere(quadric, 500.0f, 250, 250);

			glBindTexture(GL_TEXTURE_2D, SunTexture);
				glColor3f(1,1,1);
				gluSphere(quadric, 501.0f, 250, 250);
			glPopMatrix();

			/*----------Draw sun's planets-----------*/
			/*------------Mercury--------------------*/
			glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, MercuryTexture);
				Mercury.drawPlanet();
			glPopMatrix();

			//-------------Venus--------------
			glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, VenusTexture);
				Venus.drawPlanet();
			glPopMatrix();

			//-----------Earth&Moon-----------	
			glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, EarthTexture);
				Earth.drawPlanet();

				glBindTexture(GL_TEXTURE_2D, MoonTexture);
				glRotatef(-90,1,0,0);
				Moon.drawPlanet();
			glPopMatrix();

			//-------------Mars----------------
			glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, MarsTexture);
				Mars.drawPlanet();
			glPopMatrix();

			//------------Jupiter--------------
			glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, JupiterTexture);
				Jupiter.drawPlanet();
			glPopMatrix();
			
			//-------------Saturn--------------
			glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, SaturnTexture);
				Saturn.drawPlanet();
				//rotate for shadow angle
				glRotatef(20,0,0,1);
				glBindTexture(GL_TEXTURE_2D, SaturnRingTexture);
				glEnable(GL_BLEND);
				glColor4f(1,1,1,.7f);
				glRotatef(5,1,0,0);
				gluDisk(quadric, 600, 1100, 360, 40);
				glDisable(GL_BLEND);
			glPopMatrix();

			//--------------Uranus-------------
			glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, UranusTexture);
				Uranus.drawPlanet();
				glBindTexture(GL_TEXTURE_2D, UranusRingTexture);
				gluDisk(quadric, 320, 325.0f, 100, 200);
			glPopMatrix();

			//------------Neptune--------------
			glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, NeptuneTexture);
				Neptune.drawPlanet();
			glPopMatrix();	

			//-------------pluto---------------
			glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, PlutoTexture);
				Pluto.drawPlanet();
			glPopMatrix();

		glDisable(GL_TEXTURE_2D);
		glPushMatrix();
		drawSnowstorm();
		glPopMatrix();
		renderPortals();
	}
	if(EarthBool)
	{
		campos.y = 10;
		/*---------Earth's Sky Sphere------------*/
		gluLookAt(0,0,0,camlook.x,camlook.y,camlook.z,0,1,0);

			glPushMatrix();
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, EarthSky);
				glColor3f(1,1,1);
				glRotatef(-90,1,0,0);
				glRotatef(rot*0.002f,0,1,0);
				gluSphere(quadric, 3000, 180,180);
			glPopMatrix();

		glLoadIdentity();
		gluLookAt(campos.x, campos.y, campos.z, campos.x+camlook.x, campos.y+camlook.y, campos.z+camlook.z, 0.0f, 1.0f, 0.0f);

		glPushMatrix();
		glTranslatef(-5000,0,-5000);
		glScalef(10,10,10);
		for(int i=0; i<10; i++)
		{
			for(int j=0; j<10; j++)
			{
				texturePlane(Grass);
				glTranslatef(100,0,0);
			}
			glTranslatef(-1000,0,100);
		}
		glPopMatrix();
		renderPortals();
	}

{
	if(MarsBool && !EarthBool)
	{
		/*---------star background------------*/
		gluLookAt(0,0,0,camlook.x,camlook.y,camlook.z,0,1,0);

			glPushMatrix();
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, StarTexture);
				glColor3f(1,1,1);
				glRotatef(-90,1,0,0);
				glRotatef(rot*0.025f,0,1,0);
				gluSphere(quadric, 30000, 180,180);
			glPopMatrix();

		glLoadIdentity();
		gluLookAt(campos.x, campos.y, campos.z, campos.x+camlook.x, campos.y+camlook.y, campos.z+camlook.z, 0.0f, 1.0f, 0.0f);

		glPushMatrix();
		glTranslatef(-5000,0,-5000);
		glScalef(10,10,10);
		for(int i=0; i<10; i++)
		{
			for(int j=0; j<10; j++)
			{
				texturePlane(Rocks);
				glTranslatef(100,0,0);
			}
			glTranslatef(-1000,0,100);
		}
		glPopMatrix();
		renderPortals();
	}
}
	if(!pause)
	{
		rot+= 1;
		rot2+= 1;
	}

glutSwapBuffers();
memset(keyTaps,0,256*sizeof(bool));

    auto end = chrono::steady_clock::now();
    auto elapsed = chrono::duration_cast<chrono::microseconds>(end - start);
    FPS =static_cast<float>(1/(elapsed.count()/(1000000.0f)));
}

void loadTextures(bool loadHiRes)
{
	Portals = SOIL_load_OGL_texture("./textures/portal.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
	PortalsCenter = SOIL_load_OGL_texture("./textures/portalcenter.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
	PortalsOuter = SOIL_load_OGL_texture("./textures/spiral2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
	gluQuadricTexture(quadric, GL_TRUE);

	if(loadHiRes)
	{
		Lense = SOIL_load_OGL_texture("./textures/blackstar.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
		Nebula = SOIL_load_OGL_texture("./textures/The_Crab.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
		testTexture = SOIL_load_OGL_texture("./textures/solarflare.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
		SunTexture = SOIL_load_OGL_texture("./textures/Sun1.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y); 
		MercuryTexture = SOIL_load_OGL_texture("./textures/Mercury.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
		VenusTexture =  SOIL_load_OGL_texture("./textures/Venus.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
		EarthTexture = SOIL_load_OGL_texture("./textures/Earth.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
	 	MarsTexture = SOIL_load_OGL_texture("./textures/Mars.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);  
		JupiterTexture = SOIL_load_OGL_texture("./textures/surfacejupiter.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
		SaturnTexture = SOIL_load_OGL_texture("./textures/saturn.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
		UranusTexture = SOIL_load_OGL_texture("./textures/texture_uranus.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
		NeptuneTexture = SOIL_load_OGL_texture("./textures/texture_neptune.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
		PlutoTexture =  SOIL_load_OGL_texture("./textures/pluto.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
		SaturnRingTexture = SOIL_load_OGL_texture("./textures/saturnrings.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
		UranusRingTexture = SOIL_load_OGL_texture("./textures/texture_uranus_ring.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
		MoonTexture = SOIL_load_OGL_texture("./textures/moon.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
		//StarTexture = SOIL_load_OGL_texture("./textures/hiresgalaxy.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

		StarTexture = SOIL_load_OGL_texture("./textures/biggalaxy.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
		GalaxyTexture = SOIL_load_OGL_texture("./textures/nebula.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
		Spiral =  SOIL_load_OGL_texture("./textures/whitespiral.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
		EarthSky = SOIL_load_OGL_texture("./textures/sky_lightblue.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
		Rocks = SOIL_load_OGL_texture("./textures/rocks.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
		Grass = SOIL_load_OGL_texture("./textures/grass.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
	}
	else
	{
		Lense = SOIL_load_OGL_texture("./textures/gridsphere.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
		Nebula = Lense;
		testTexture = Lense;
		SunTexture = Lense; 
		MercuryTexture = Lense;
		VenusTexture =  Lense;
		EarthTexture = Lense;
	 	MarsTexture = Lense;  
		JupiterTexture = Lense;
		SaturnTexture =Lense;
		UranusTexture = Lense;
		NeptuneTexture = Lense;
		PlutoTexture =  Lense;
		SaturnRingTexture = Lense;
		UranusRingTexture = Lense;
		MoonTexture = Lense;
		//StarTexture = Lense;

		StarTexture = Lense;
		GalaxyTexture = Lense;
		Spiral =  Lense;
		EarthSky = Lense;
		Rocks = Lense;
		Grass = Lense;
	}
}