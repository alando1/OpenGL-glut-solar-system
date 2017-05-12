#pragma once
#include <ctime>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <list>
#include "vector.h"
#include "Portal.h"
#include "Planet.h"
#include "DrawFunc.h"
#include "SuppliedGlutFuncs.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void handleFunc();
void renderScene(void);
void loadTextures(bool loadHiRes);
