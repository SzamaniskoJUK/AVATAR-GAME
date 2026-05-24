#ifndef ENEMY_H
#define ENEMY_H
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

class Enemy : public Entity
{
private:
	//staty przeciwników (pomys³ jest na 3 spoko by by³o gdyby by³o z 5)

	int type;
	int hpMax;
	int hp;
	int damage;
	int points;
	float speed;

	void initVariables();
	void initTexture();
	void initSprite();

	static int zabitychWrogow;

public:
	enum class Type { FIREBALL = 0, FIREWARRIOR = 1, HEAL = 2 , AVATAR = 3};

	void loseLife(int damage);
	const bool isDead() const;

	static int getZabitych();
	static void dodajZabitego();

	Enemy(float posX, float posY, Type type = Type::FIREBALL);
	virtual ~Enemy();

	const int& getPoints() const;
	const int& getDamage() const;

	void update() override;
	void render(RenderTarget& target) override;
	void setPosition(const sf::Vector2f& position) override;
	const FloatRect getBounds() const override;
};

#endif