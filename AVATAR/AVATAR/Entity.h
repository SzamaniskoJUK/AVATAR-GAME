#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Entity
{
protected:
    Texture texture;
    Sprite sprite;

public:
    Entity();
    Entity(Texture* tex);
    virtual ~Entity();

    virtual void update() = 0;
    virtual void render(RenderTarget& target) = 0;

    virtual const FloatRect getBounds() const;
    virtual void setPosition(const Vector2f& position);
};

