#pragma once
#include "Entity.h"
#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
using namespace sf;

class Gracz : public Entity
{
private:

	float movementspeed;
	float cooldown;
	float cooldownMax;
	int hp;
	int hpMax;

	void initVariables();
	void initTexture();
	void initSprite();

public:
	Gracz();
	virtual ~Gracz();

	//STAN AVATARA
	bool avatarState;
	float avatarTimer;
	float avatarTimerMax;
	Texture normalTexture;
	Texture avatarstateTexture;

	void aktywacjaAvatara();
	void updateAvatarMode(float dt);
	const bool isAvatarMode() const;

	const Vector2f& getPos() const;
	const FloatRect getBounds() const override;
	const int& getHp() const;
	const int& getHpMax() const;

	void setPosition(const Vector2f pos);
	void setPosition(const float x, const float y);
	void setHp(const int hp);
	void loseHp(const int value);

	//funkcje
	void move(const float dirX, const float dirY, const float dt);
	const bool czyjuzgit();


	void updateCollDown();
	void update() override;
	void render(RenderTarget& target) override;
};

