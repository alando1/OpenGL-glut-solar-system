#include "Planet.h"
extern float rot, relative;

Planet::Planet()
{}

void Planet::drawPlanet()
{
	int slicedisk;
	if(radius <= 100.0f)
		slicedisk = 45;
	if(radius > 100.0f && radius <= 500.0f)
		slicedisk = 100;
	if(radius > 500.0f)
		slicedisk = 250;

	glRotatef(-90,1,0,0);
	glColor3f(1,1,1);	

	glRotatef(rot*revolution*relative, 0,0,1);
	glTranslatef(pos.x,pos.y,pos.z);
	glRotatef(rot*rotation*relative, 0,0,1);
	gluSphere(quadric, radius, slicedisk, slicedisk);


}
Vec3 Planet::getPosition()
{
	vector.x = (pos.x*cosf(revolution*rot*relative));
	vector.z = ((radius+50)*sinf(revolution*rot*relative));
	vector.y = ((radius+50)*cosf(revolution*rot*relative));
	return vector;
}

void Planet::initialize(float X, float Y, float Z, GLUquadricObj* Quadric, string Name, 
						float Radius, float Revolution, float Rotation, int Texture)
{
	pos.x=X;
	pos.y=Y;
	pos.z=Z;
	quadric = Quadric;
	name = Name;
	radius = Radius;
	rotation = Rotation;
	revolution = Revolution;
	texture = Texture;

}