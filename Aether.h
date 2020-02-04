#ifndef AETHER_H
#define AETHER_H

#include "olcPixelGameEngine/olcPixelGameEngine.h"
#include "plane/Plane.h"
#include "Drawable.h"

class Rocket;
class Aether
	: public Plane
{

private:
	std::vector<Drawable*> world;

public:
	Aether() = default;
	~Aether();

	virtual bool OnUserCreate();
	virtual bool OnUserUpdate(float fElapsedTime);

private:

};

#endif // AETHER_H
