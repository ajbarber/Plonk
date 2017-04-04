#include "Item.h"

Item::Item(float x, float y, float z): 
			x(x),
			y(y),
			z(z)
{
}

Item::~Item()
{
}


float Item::getX() const              { return x; }
float Item::getY() const              { return y; }
float Item::getZ() const              { return z; }