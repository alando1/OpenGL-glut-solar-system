#include "vector.h"
#include <GL/glut.h>
using namespace std;

class SnowMan
{
	public:
		Vec3 pos;
		Vec3 dir;
		Vec3 vel;
		Vec3 color;
		float mass;
		float speed;

		SnowMan(Vec3 pos, Vec3 dir, Vec3 vel, Vec3 color, float mass, float speed);
		drawSnowMan();
		
};