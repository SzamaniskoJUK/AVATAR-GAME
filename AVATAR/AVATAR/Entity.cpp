#include "Entity.h"

Entity::Entity() : sprite(texture)
{

}

Entity::Entity(Texture* tex) : sprite(*tex)
{
    this->texture = *tex;
}

Entity::~Entity()
{

}

const FloatRect Entity::getBounds() const
{
    return this->sprite.getGlobalBounds();
}

void Entity::setPosition(const Vector2f& position)
{
    this->sprite.setPosition(position);
}
