#include "Gracz.h"
#include "Utility.h"

using namespace std;
using namespace sf;

void Gracz::initTexture()
{
	//wczytywanie tekstury z pliku
	if (!this->normalTexture.loadFromFile("Textures/aangpixel500.png"))
	{
		cout << "ERROR   ::   TEKSTURA POSTACI NIE MOZE SIE ZALADOWAC" << endl;
	}
	if (!this->avatarstateTexture.loadFromFile("Textures/aangpixel500.png"))
	{
		cout << "ERROR   ::   TEKSTURA STANU AVATARA NIE MOZE SIE ZALADOWAC" << endl;
	}
	this->texture = this->normalTexture;
}
void Gracz::initSprite()
{
	//ustawianie tekstury
	this->sprite.setTexture(this->texture, true);
	this->sprite.scale({ 0.4f, 0.4f });
	texture.setSmooth(true);

	//usawienie pozycji na start
	float x = (1200.f / 2.f) - (this->sprite.getGlobalBounds().size.x / 2.f);
	float y = 800.f - this->sprite.getGlobalBounds().size.y - 10.f; // 10px odstêp od do³u troche lepiej estetycznie to wygl¹da wg mnie
	this->sprite.setPosition({ x, y });

}

void Gracz::aktywacjaAvatara()
{
	this->avatarState = true;
	this->avatarTimer = 0.f;
	this->cooldownMax = 4.f;
	this->sprite.setTexture(this->avatarstateTexture, true);
}

void Gracz::updateAvatarMode(float dt)
{
	if (!this->avatarState) return;

	this->avatarTimer += dt;

	if (this->avatarTimer >= this->avatarTimerMax)
	{
		this->avatarState = false;
		this->cooldownMax = 10.f;
		this->sprite.setTexture(this->normalTexture, true);
	}
}

const bool Gracz::isAvatarMode() const
{
	return this->avatarState;
}

const Vector2f& Gracz::getPos() const
{
	return this->sprite.getPosition();
}

const FloatRect Gracz::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Gracz::getHp() const
{
	return this->hp;
}

const int& Gracz::getHpMax() const
{
	return this->hpMax;
}

void Gracz::setPosition(const Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Gracz::setPosition(const float x, const float y)
{
	this->sprite.setPosition({ x, y });
}

void Gracz::setHp(const int hp)
{
	this->hp = clampValue(hp, 0, this->hpMax);
}

void Gracz::loseHp(const int wartosc)
{
	this->hp -= wartosc;
	this->hp = clampValue(this->hp, 0, this->hpMax);
}

Gracz::Gracz()
{
	this->movementspeed = 700.f; // ~~700px na sek

	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Gracz::~Gracz()
{

}

void Gracz::move(const float dirX, const float dirY, const float dt)
{
	this->sprite.move({ dirX * movementspeed * dt, dirY * movementspeed * dt });
}

//funkcyjki
void Gracz::update()
{
	this->updateCollDown();
	//this->updateAvatarMode();
}

void Gracz::render(RenderTarget& target)
{
	target.draw(this->sprite);
}

const bool Gracz::czyjuzgit()
{
	if (this->cooldown >= this->cooldownMax)
	{
		this->cooldown = 0.5f;
		return true;
	}
	return false;
}


void Gracz::updateCollDown()
{
	if(this->cooldown < this->cooldownMax)
		this->cooldown += 0.5f;
}

void Gracz::initVariables()
{
	this->avatarTimerMax = 10.f;
	this->avatarTimer = 0.f;
	this->avatarState = false;
	this->cooldown = 0.f;
	this->cooldownMax = 10.f;
	this->hpMax = 100;
	this->hp = this->hpMax;
}