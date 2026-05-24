#include "Pocisk.h"

Pocisk::Pocisk(Texture* texture, float posx, float posy, float dirx, float diry, float movement_speed) : Entity(texture)
{
	this->sprite.setTexture(*texture);

	this->sprite.setPosition({ posx, posy });
	this->direction.x = dirx;
	this->direction.y = diry;
	this->movementSpeed = movement_speed;
	this->sprite.setScale({ 0.4f, 0.4f });


}

Pocisk::~Pocisk()
{

}

const FloatRect Pocisk::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Pocisk::update()
{
	//ruch poisku
	this->sprite.move(this->direction * this->movementSpeed);
}

void Pocisk::render(RenderTarget& cel)
{
	cel.draw(this->sprite);
}