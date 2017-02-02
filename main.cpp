#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <list>
#include "vector.h"
#include "Snowman.h"
#include "Portal.h"
#include "planet.h"
#include "DrawFunc.h"
#include "suppliedGlutFuncs.h"
#include "renderUpdates.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <SOIL.h>

using namespace std;
#define MAX_SNOWMEN	100

Planet planets[10];

list<Portal*> portalList;
GLUquadricObj* quadric;
// angle of rotation for the camera direction
float speed;
float rot=0;
float rot2=0;
float relative= 0.01f;
float heading = 0.0f;
float pitch = 0.0f;
float perspective = 45;
float aspectratio = 1024.0f/768.0f;
float boost=1;
float earthRadius = 63.71f;

bool keyStates[256], keyTaps[256], planetBools[3];
bool shiftKeyState;
bool loadHiRes;
bool pause=FALSE;
bool EarthBool=FALSE;
bool MarsBool=FALSE;
bool orbitLock=FALSE;



Vec3 vec;
int centerX, centerY;
int testTexture, SunTexture, MercuryTexture, VenusTexture, EarthTexture, MarsTexture, 
	JupiterTexture, SaturnTexture, UranusTexture, NeptuneTexture, PlutoTexture,
	SaturnRingTexture, UranusRingTexture, MoonTexture, StarTexture, GalaxyTexture,
	Nebula, Lense, Spiral, Portals, PortalsCenter, PortalsOuter, EarthSky, Grass, Rocks;

Planet Mercury, Venus, Earth, Moon, Mars, Jupiter, Saturn, Uranus, Neptune, Pluto;

void* font = GLUT_BITMAP_HELVETICA_18;

// actual vector representing the camera's look direction
// initial XYZ position of the camera
Vec3 camlook(0,0,-1);
Vec3 campos(0,1,5);

void Clear_Keyboard_Input_Buffer()
{
	while (cin.get() != '\n');
}

void createPlanets()
{
	Mercury.initialize(775,0,0,quadric,"Mercury",24.40f,15.20f,3,MercuryTexture);
	Venus.initialize(1000,0,0,quadric,"Venus",60.02f,13.624f,-1,VenusTexture);
	Earth.initialize(1550,0,0,quadric,"Earth",63.71f,10.0f,365,EarthTexture);
	Moon.initialize(220,0,0,quadric,"Moon",25.0f,133.5f,10,MoonTexture);
	Mars.initialize(2150,0,0,quadric,"Mars",33.89f,7,700,MarsTexture);
	Jupiter.initialize(4400,0,0,quadric,"Jupiter",699.11f,2.0f,1900,JupiterTexture);
	Saturn.initialize(7625,0,0,quadric,"Saturn",582.3f,2.5f,1050,SaturnTexture);
	Uranus.initialize(14850,0,0,quadric,"Uranus",230.62f,1,1712,UranusTexture);
	Neptune.initialize(25500,0,0,quadric,"Neptune",226.2f,0.8f,2600,NeptuneTexture);
	Pluto.initialize(25625,0,0,quadric,"Pluto",110.3f,0.77f,5,PlutoTexture);
	planetBools[0]=EarthBool;
	planetBools[1]=MarsBool;
}

int main(int argc, char **argv)
{
	time_t start, finish;
	char input;

	if(argc == 1)
	{
		loadHiRes = FALSE;
		cout <<"> Loading Lo-Res textures ..." << endl;
	}
	else
	{
		if(argv[1][0] == '0')
		{
			cout <<"> Loading Lo-Res textures ..." << endl;
			loadHiRes = FALSE;
		}
		else if(argv[1][0] == '1')
		{
			cout <<"> Loading Hi-Res textures ..." << endl;
			loadHiRes = TRUE;
		}
		else 
		{
			cout <<"> Invalid arguements, loading Lo-Res textures ..." << endl;
			loadHiRes = FALSE;
		}

	}

	// init GLUT and create window
	GLinitialize(argc, argv);
	quadric = gluNewQuadric();
	time(&start);
	loadTextures(loadHiRes);
	time(&finish);
	cout << "> Textures loaded in " << finish-start << " seconds."	<< endl;

/*cout << "              ___.......___								"<< endl;
cout << "         _.-\"\'             `\"-._ 						"<< endl;
cout << "      .-'                       `-.						"<< endl;
cout << "    .'                             `.						"<< endl;
cout << "  .'                                 `.					"<< endl;
cout << " .                                     .					"<< endl<< endl;
cout << ":                                       :					"<< endl;
cout << ":   .---.._                   _..---.   :					"<< endl;
cout << ":    \\     `\"-.           .-\"'     /    :				"<< endl;
cout << ":     \\        `.       .'        /     :					"<< endl;
cout << ":      `.        \\     /        .'      :					"<< endl;
cout << ":        `\"--..___\\   /___..--\"'        :				"<< endl;
cout << ":                                       :					"<< endl;
cout << ":                                       :					"<< endl;
cout << "`                                       '					"<< endl;
cout << " .                 ^ ^                 .					"<< endl;
cout << "  .                                   .					"<< endl;
cout << "   \\                                 /					"<< endl;
cout << "    .                               .						"<< endl;
cout << "     `.            -=-            .'						"<< endl;
cout << "       `.                       .'							"<< endl;
cout << "         `-.                 .-'							"<< endl;
cout << "            `-.           .-'								"<< endl;
cout << "               `\"--...--\"'								"<< endl;
*/
	cout << ">-------Command List--------" << endl;
	createPlanets();
	glutMainLoop();
	glutSetCursor(GLUT_CURSOR_INHERIT);

	cout <<"end of main..." << endl;

	return 1;
}