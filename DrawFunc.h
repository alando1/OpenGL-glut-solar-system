#pragma once
#include <cstdlib>
#include <string>
#include <iostream>
#include <cmath>
//#include <queue>
//#include "vector.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <SOIL.h>

void orbitSnowmen();
void drawSnowstorm();
void drawgrid();
void otherGrid();
void drawFloor();
void spinner();
void spinner2();
void drawSnowMan();
void drawSnowDude();
void openPortal(float x, float y, float z, float lx, float ly, float lz);
void texturePlane(int testTexture);
//void setVSync(int i);