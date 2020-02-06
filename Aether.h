#ifndef AETHER_H
#define AETHER_H

#include "olcPixelGameEngine/olcPixelGameEngine.h"
#include "plane/Plane.h"

class Rocket;
class Aether
	: public Plane
{

private:
//	std::vector<Drawable*> world;
	std::vector<std::pair<std::pair<double,double>, std::string>> _points;

public:
	Aether();
	~Aether();

	virtual bool OnUserCreate();
	virtual bool OnUserUpdate(float fElapsedTime);

private:

};

#endif // AETHER_H
