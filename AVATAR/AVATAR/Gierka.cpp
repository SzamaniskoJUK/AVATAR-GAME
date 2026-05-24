/*
Taki jakby "silnik gierki"
*/
#include <cstdlib> 
#include "Gierka.h"
#include "Enemy.h"
#include "Gracz.h"
#include "Utility.h"
#include "Tekstury.h"
#include <ctime> 
#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>


using namespace std;
using namespace sf;

void Gierka::start() {
	while (this->okno->isOpen()) {
		this->dt = this->clock.restart().asSeconds();//mierzenie czasu trwania klatki w czasie poniewa¿ gdy ruvh by³ uzele¿niony id klatek a nie od czasu gra nie chodzi³a p³ynnie
		if (this->gracz->getHp() > 0 && !this->pauza)
			this->update();
		else
			this->pollEventsOnly();
		this->render();

	}
}

void Gierka::pollEventsOnly()
{
	while (const auto event = this->okno->pollEvent())
	{
		if (event->is<Event::Closed>())
			this->okno->close();
		if (const auto* keyPressed = event->getIf<Event::KeyPressed>())
		{
			if (keyPressed->code == Keyboard::Key::Escape)
				this->pauza = !this->pauza;
		}
	}
}

void Gierka::initAudio()
{
	//muzyka w tle
	if(!this->muzyka.openFromFile("Sounds/Aang (The Avatar State) - Jeremy Zuckerman.mp3"))
		cout << "ERROR   ::   Muzyka w tle sie nie wczytuje" << endl;
	this->muzyka.setLooping(true);
	this->muzyka.setVolume(25.f);
	this->muzyka.play();

	//dzwiek strzalu
	if (!this->strzalbf.loadFromFile("Sounds/universfield-swoosh-015-383769.mp3"))
		cout << "ERROR   ::   Dzwiek pocisku sie nie wczytuje" << endl;
	this->strzal.setVolume(40.f);

	//dzwiêk gdy trafimy pociskiem
	if (!this->killbf.loadFromFile("Sounds/dragon-studio-boom-copyright-free-487662.mp3"))
		cout << "ERROR   ::   Dzwiek trafienia przeciwnika sie nie wczytuje" << endl;
	this->kill.setVolume(20.f);

	this->strzal.setBuffer(this->strzalbf);
	this->kill.setBuffer(this->killbf);;

	//dzwiêk lvl up
	if (!this->levelUpBf.loadFromFile("Sounds/tithuh-level-up-03-523644.mp3"))
		cout << "ERROR   ::   Dzwiek Level upa sie nie wczytuje" << endl;
	this->levelUp.setBuffer(this->levelUpBf);
	this->levelUp.setVolume(40.f);
}

void Gierka::initPauza()
{
	if (!this->pauzaScreenTex.loadFromFile("Textures/stop.png"))
	{
		cout << "ERROR   ::   Nie dziala tekstura pauzy" << endl;
	}
	this->pauzaScreen = new Sprite(this->pauzaScreenTex);
	this->pauza = false;
}

//prywatka
void Gierka::inicjalizacjaokna()
{
	this->okno = new RenderWindow(VideoMode({ 1200, 800 }), "AVATAR RUN - The game", Style::Close | Style::Titlebar);
	this->okno->setFramerateLimit(120);
	this->okno->setVerticalSyncEnabled(false);
}

void Gierka::renderWorld()
{
	this->okno->draw(*this->worldBackground);
}

void Gierka::updateWorld()
{

}

void Gierka::updateKolizja()
{
	//lewa strona
	if (this->gracz->getBounds().position.x < 0.f)
	{
		this->gracz->setPosition( 0.f,this->gracz->getBounds().position.y );
	}

	//prawa
	else if (this->gracz->getBounds().position.x + this->gracz->getBounds().size.x >= this->okno->getSize().x)
	{
		float max_x = this->okno->getSize().x - this->gracz->getBounds().size.x;
		this->gracz->setPosition({ max_x, this->gracz->getBounds().position.y });
	}

	//góra
	if (this->gracz->getBounds().position.y < 0.f)
	{
		this->gracz->setPosition(this->gracz->getBounds().position.x, 0.f);
	}

	//dó³
	else if (this->gracz->getBounds().position.y + this->gracz->getBounds().size.y >= this->okno->getSize().y)
	{
		float max_y = this->okno->getSize().y - this->gracz->getBounds().size.y;
		this->gracz->setPosition({this->gracz->getBounds().position.x, max_y, });
	}
}

//con/des
Gierka::Gierka()
{
	this->inicjalizacjaokna();
	this->initGUI();
	this->initAudio();
	this->initTextures();
	this->initWorld();
	this->initPauza();
	this->initDane();
	this->initGracz();
	this->initEnemies();

}

Gierka::~Gierka()
{
	delete this->okno;
	delete this->pauzaScreen;
	delete this->worldBackground;
	delete this->gracz;

	//Pociski postaci delete
	for (auto* p : this->pociski)
	{
		delete p;
	}

	//enemy delete
	for (auto* p : this->enemies)
	{
		delete p;
	}

}

//renderowanie wszytkiego
void Gierka::render()
{
	this->okno->clear();
	this->renderWorld();


	//posick
	for (auto* pocisk : this->pociski)
	{
		pocisk->render(*this->okno);
	}

	//enemy
	for (auto* enemy : this->enemies)
	{
		enemy->render(*this->okno);
	}

	this->gracz->render(*this->okno);
	this->renderGUI();
	
	if (this->gracz->getHp() <= 0)
	{
		this->okno->draw(this->gameOverText);
	}

	if (this->pauza)
	{
		this->okno->draw(*this->pauzaScreen);
	}

	this->okno->display();

}

void Gierka::updateGUI()
{
	if (static_cast<int>(this->points) > this->bestScore)
	{
		this->bestScore = static_cast<int>(this->points);

		try
		{
			ofstream plik("score.txt");
			if (!plik.is_open())
				throw runtime_error("Nie mozna zapisac pliku score.txt");
			plik << this->bestScore;
			plik.close();
		}
		catch (const runtime_error& e)
		{
			cout << "BLAD ZAPISU :: " << e.what() << endl;
		}
	}

	if (Enemy::getZabitych() > this->bestKills)
	{
		this->bestKills = Enemy::getZabitych();

		try
		{
			ofstream plik("kills.txt");
			if (!plik.is_open())
				throw runtime_error("Nie mozna zapisac pliku kills.txt");
			plik << this->bestKills;
			plik.close();
		}
		catch (const runtime_error& e)
		{
			cout << "BLAD ZAPISU :: " << e.what() << endl;
		}
	}

	stringstream ss;
	ss << "SCORE : " << static_cast<int>(this->points) << endl;
	ss << "BEST SCORE: " << this->bestScore << endl;
	ss << endl;
	ss << "KILLS : " << Enemy::getZabitych() << endl;
	ss << "BEST KILLS : " << this->bestKills << endl;
	this->pointText.setString(ss.str());

	float hpProcent = static_cast<float>(this->gracz->getHp()) / this->gracz->getHpMax() * 100.f;
	this->HpBar.setSize(Vector2f(300.f * (hpProcent / 100.f), this->HpBar.getSize().y));

	int poziom = static_cast<int>(this->points) / 500;
	
	stringstream ss2;
	ss2 << "LEVEL : " << poziom;
	this->trudnoscText.setString(ss2.str());
}

void Gierka::renderGUI()
{
	this->okno->draw(this->pointText);
	this->okno->draw(this->HpBarMax);
	this->okno->draw(this->HpBar);
	this->okno->draw(this->trudnoscText);
}

void Gierka::initGUI()
{
	//czcionki
	if (!this->font.openFromFile("Fonts/GrapeSoda.ttf"))
	{
		cout << "ERROR   ::   Nie dziala czcionka" << endl;
	}

	this->pointText = Text(this->font);
	this->pointText.setCharacterSize(35);
	this->pointText.setFillColor(Color::Black);
	this->pointText.setPosition(Vector2f(10.f, 0.f));
	//this->pointText.setString("test");

	this->trudnoscText = Text(this->font);
	this->trudnoscText.setCharacterSize(30);
	this->trudnoscText.setFillColor(Color::Black);
	this->trudnoscText.setPosition(Vector2f(600.f, 0.f));

	this->gameOverText = Text(this->font);
	this->gameOverText.setCharacterSize(100);
	this->gameOverText.setFillColor(Color::Red);
	this->gameOverText.setString("GAME OVER");
	//ustawianie game over IDEALNIE na srodek ekranu 
	this->gameOverText.setPosition(Vector2f(this->okno->getSize().x / 2.f - this->gameOverText.getGlobalBounds().size.x / 2.f, this->okno->getSize().y / 2.f - this->gameOverText.getGlobalBounds().size.y / 2.f));

	this->HpBar.setSize(Vector2f(300.f, 30.f));
	this->HpBar.setFillColor(Color(255, 0, 0, 180));
	this->HpBar.setPosition(Vector2f(890.f, 10.f));

	this->HpBarMax = this->HpBar;
	this->HpBarMax.setFillColor(Color(0, 0, 0, 180));
	this->HpBar.setPosition(Vector2f(890.f, 10.f));
}

//////////////////////UPDATE
void Gierka::update()
{
	while (const optional event = this->okno->pollEvent())
	{
		if (event->is<Event::Closed>())
			this->okno->close();

		if (const auto* keyPressed = event->getIf<Event::KeyPressed>())
		{
			if (keyPressed->code == Keyboard::Key::Escape)
				this->pauza = !this->pauza;
		}
	}

	this->scoreTimer += this->dt;
	if (this->scoreTimer >= 1.f)
	{
		this->points += 2.f * this->dt;
		//cout << "dt: " << this->dt << " points: " << this->points << endl;
	}

	if (static_cast<int>(this->points) / 500 > this->trudnosc / 500)
	{
		//wartoœci troche losowe (dobierane tak d³ugo a¿ w miare nie by³o t³oku na ekranie)
		this->spawntimerMax -= 3.f;
		if (this->spawntimerMax < 15.f)
			this->spawntimerMax = 15.f;
		this->healSpawntimerMax -= 2.f;

		if (this->healSpawntimerMax < 40.f)
			this->healSpawntimerMax = 40.f;
		this->trudnosc = static_cast<int>(this->points);

		this->levelUp.play();
	}

	this->updateInput();
	this->updateWorld();
	this->updatePocisk();
	this->updateEnemies();
	this->updateWalka();
	this->gracz->update();
	this->updateKolizja();
	this->updateGUI();
}

void Gierka::initTextures()
{
	this->textures.ladowanie("POCISK", "Textures/wiatr.png");

	//po dodaniu repozytorium ju¿ nie potrzebna
	/*this->textures["POCISK"] = new Texture();

	if (!this->textures["POCISK"]->loadFromFile("Textures/wiatr.png"))
	{
		cout << "ERROR   ::   Nie dziala textura pocisku" << endl;
	}
	*/
}

void Gierka::initWorld()
{
	this->worldBackground;
	if(!this->worldBackgroundTex.loadFromFile("Textures/bcg.png"))
	{
		cout << "ERROR   ::   Nie dziala textura tla" << endl;
	}

	this->worldBackground = new sf::Sprite(this->worldBackgroundTex);
}

void Gierka::initGracz()
{
	this->gracz = new Gracz();
}

void Gierka::initEnemies()
{
	this->spawntimerMax = 40.f;
	this->spawntimer = this->spawntimerMax;

	this->healSpawntimerMax = 300.f;
	this->healSpawntimer = 0.f;

}

void Gierka::initDane()
{
	this->points = 0.f;
	this->scoreTimer = 0.f;
	this->trudnosc = 0;
	this->strzalSoundCooldown = 0.f;

	//best score
	this->bestKills = 0;
	this->bestScore = 0;
	try
	{
		ifstream zapis("score.txt");
		if (!zapis.is_open())
			throw runtime_error("Nie mozna otworzyc pliku score.txt");
		zapis >> this->bestScore;
		zapis.close();
		cout << "Wczytano best score: " << this->bestScore << endl;
	}
	catch (const runtime_error& e)
	{
		cout << "INFO :: " << e.what() << " - ustawiam score na 0" << endl;
		this->bestScore = 0;
	}

	try
	{
		ifstream zapis("kills.txt");
		if (!zapis.is_open())
			throw runtime_error("Nie mozna otworzyc pliku kills.txt");
		zapis >> this->bestKills;
		zapis.close();
		cout << "Wczytano best kills: " << this->bestKills << endl;
	}
	catch (const runtime_error& e)
	{
		cout << "INFO :: " << e.what() << " - ustawiam kille na 0" << endl;
		this->bestKills = 0;
	}
}

void Gierka::updateInput()
{
	if (Keyboard::isKeyPressed(Keyboard::Key::A))
		this->gracz->move(-1.f, 0.f, this->dt);
	if (Keyboard::isKeyPressed(Keyboard::Key::W))
		this->gracz->move(0.f, -1.f, this->dt);
	if (Keyboard::isKeyPressed(Keyboard::Key::S))
		this->gracz->move(0.f, 1.f, this->dt);
	if (Keyboard::isKeyPressed(Keyboard::Key::D))
		this->gracz->move(1.f, 0.f, this->dt);

	//lekki cooldown na dzwiêk strza³u bo niefajnie to brzmia³o jak sie przytrzymowa³o przycisk albo szybko klika³o
	if (this->strzalSoundCooldown > 0.f)
		this->strzalSoundCooldown -= this->dt;

	if (Mouse::isButtonPressed(Mouse::Button::Left) && this->gracz->czyjuzgit())
	{
		this->pociski.push_back(new Pocisk(textures.get("POCISK"), this->gracz->getPos().x+24.f, this->gracz->getPos().y, 0.f, -1.f, 20.f));
		
		if (this->strzalSoundCooldown <= 0.f)
		{
			this->strzal.play();
			this->strzalSoundCooldown = 0.5f;
		}
		
	}


}


void Gierka::updatePocisk()
{
	int counter = 0;
	for (auto* pocisk : this->pociski)
	{
		pocisk->update();


		//granice pocisku
		if (pocisk->getBounds().position.y + pocisk->getBounds().size.y <= 0.f)
		{
			//usuwanie pocisku
			delete this->pociski.at(counter);
			this->pociski.erase(this->pociski.begin() + counter);
			--counter;

			//cout << this->pociski.size() << endl;
		}
		++counter;
	}
}

void Gierka::updateEnemies()
{
	//spawn
	
	this->spawntimer += 0.6f;
	if (this->spawntimer >= this->spawntimerMax)
	{
		int los = rand() % 10;
		Enemy::Type losowyTyp;
		// losowanie typu FIREBALL spawnuje siê w 70% a FIREWARRIOR w 30%
		if (los < 7)
			losowyTyp = Enemy::Type::FIREBALL;
		else if (los < 10)
			losowyTyp = Enemy::Type::FIREWARRIOR;


		Enemy* nowy_wrog = new Enemy(0.f, -100.f, losowyTyp);

		//spawn przeciwnika na podstawie jego wielkosci sprite
		float szerokosc_wroga = nowy_wrog->getBounds().size.x;
		int max_x = static_cast<int>(this->okno->getSize().x - szerokosc_wroga);
		float wylosowany_x = static_cast<float>(rand() % max_x);
		nowy_wrog->setPosition({ wylosowany_x, -100.f });
		this->enemies.push_back(nowy_wrog);
		this->spawntimer = 0.f;
	}

	//heal
	this->healSpawntimer += 0.2f;
	if (this->healSpawntimer >= this->healSpawntimerMax)
	{
		Enemy* heal = new Enemy(0.f, -100.f, Enemy::Type::HEAL);
		float szerokosc_heal = heal->getBounds().size.x;
		int max_x = static_cast<int>(this->okno->getSize().x - szerokosc_heal);
		heal->setPosition({ static_cast<float>(rand() % max_x), -100.f });
		this->enemies.push_back(heal);
		this->healSpawntimer = 0.f;
	}

	int counter = 0;
	for (auto* enemy : this->enemies)
	{
		enemy->update();

		//granice wrogów na giga podobne do pocisków
		if (enemy->getBounds().position.y > this->okno->getSize().y)
		{
			//obra¿enia gdy przepuœcimy wroga
			this->gracz->loseHp(this->enemies.at(counter)->getDamage() * 0.1);
			
			//usuwanie wroga
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			--counter;
		}
		//kolizja
		else if(enemy->getBounds().findIntersection(this->gracz->getBounds()))
		{
			this->gracz->loseHp(this->enemies.at(counter)->getDamage());
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			--counter;
		}
		++counter;
	}
}

void Gierka::updateWalka()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_usun = false;
		for (size_t k = 0; k < this->pociski.size() && !enemy_usun; k++)
		{
			if (this->enemies[i]->getBounds().findIntersection(this->pociski[k]->getBounds()))
			{
				this->enemies[i]->loseLife(1);

				delete this->pociski[k];
				this->pociski.erase(this->pociski.begin() + k);

				if (this->enemies[i]->isDead())
				{
					if (this->enemies[i]->getDamage() <= 0)
					{
						this->gracz->loseHp(this->enemies[i]->getDamage());
					}
					else
					{
						Enemy::dodajZabitego();
						this->kill.play();
					}
					this->points += this->enemies[i]->getPoints();
					delete this->enemies[i];
					this->enemies.erase(this->enemies.begin() + i);
					enemy_usun = true;
				}
			}
		}
		if (enemy_usun)
		{
			i--;
		}
	}
}
