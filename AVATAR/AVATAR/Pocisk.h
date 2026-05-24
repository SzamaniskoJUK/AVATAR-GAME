#ifndef POCISK_H
#define POCISK_H

#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace sf;

class Pocisk : public Entity
{
private:
	Vector2f direction;
	float movementSpeed;

public:
	Pocisk(Texture* texture,float posx,float posy, float dirx, float diry,float movement_speed);
	virtual ~Pocisk();

	const FloatRect getBounds() const override;

	void update() override;
	void render(RenderTarget& cel) override;
};
#endif 