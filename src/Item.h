#ifndef PROPS_H
#define PROPS_H

class Item
{
public:
	Item(float x, float y, float z);	
	~Item();
	float getX() const;
	float getY() const;
	float getZ() const;
	
private:
	
	float x;
	float y;
	float z;
};

#endif // PROPS_H
