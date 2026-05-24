#include "Enemy.h"
using namespace std;
using namespace sf;

int Enemy::zabitychWrogow = 0;

Enemy::Enemy(float posX, float posY, Type type) : Entity()
{
	this->type = static_cast<int>(type);
	this->sprite.setPosition({ posX, posY });
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Enemy::~Enemy()
{

}

const FloatRect Enemy::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	return this->points;
}

const int& Enemy::getDamage() const
{
	return this->damage;
}

void Enemy::loseLife(int damage)
{
	this->hp -= damage;
}

const bool Enemy::isDead() const
{
	return this->hp <= 0;
}

int Enemy::getZabitych()
{
	return Enemy::zabitychWrogow;
}

void Enemy::dodajZabitego()
{
	Enemy::zabitychWrogow++;
}

void Enemy::initVariables()
{
	if (this->type == static_cast<int>(Enemy::Type::FIREBALL))
	{
		this->hpMax = 1;
		this->hp = 1;
		this->damage = 10;
		this->points = 10;
		this->speed = 6.f;
	}
	else if (this->type == static_cast<int>(Enemy::Type::FIREWARRIOR))
	{
		this->hpMax = 2;
		this->hp = 2;
		this->damage = 20;
		this->points = 30;
		this->speed = 2.2f;
	}
	else if (this->type == static_cast<int>(Enemy::Type::HEAL))
	{
		this->hpMax = 1;
		this->hp = 1;
		this->damage = -30;
		this->points = 22;
		this->speed = 5.f;
	}
	else if (this->type == static_cast<int>(Enemy::Type::AVATAR))
	{
		this->hpMax = 1;
		this->hp = 1;
		this->damage = -20;
		this->points = 100;
		this->speed = 4.f;
	}
}

void Enemy::initTexture()
{
	string sciezka;
	if (this->type == static_cast<int>(Enemy::Type::FIREBALL))
		sciezka = "Textures/fireball.png";
	else if(this->type == static_cast<int>(Enemy::Type::FIREWARRIOR))
		sciezka = "Textures/fire-soldier.png";
	else if (this->type == static_cast<int>(Enemy::Type::HEAL))
		sciezka = "Textures/heal.png";
	else if (this->type == static_cast<int>(Enemy::Type::AVATAR))
		sciezka = "Textures/avatar-state.png";

	if (!this->texture.loadFromFile(sciezka))
	{
		cout << "ERROR   ::   TEKSTURA PRZECIWNIKA NIE MOZE SIE ZALADOWAC" << endl;
	}
}

void Enemy::initSprite()
{
	this->sprite.setTexture(this->texture, true);
	
	if(this->type == static_cast<int>(Enemy::Type::FIREWARRIOR))
		this->sprite.scale({ 0.25f, 0.25f });
	else
		this->sprite.scale({ 0.4f, 0.4f });
	//texture.setSmooth(true);
}

void Enemy::render(RenderTarget& target)
{
	target.draw(this->sprite);
}

void Enemy::setPosition(const sf::Vector2f& position)
{
	this->sprite.setPosition(position);
}

void Enemy::update()
{
	this->sprite.move({ 0.f, this->speed });
}
