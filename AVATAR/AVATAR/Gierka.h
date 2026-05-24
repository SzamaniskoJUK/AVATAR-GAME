#pragma once
#include "Tekstury.h"
#include "Gracz.h"
#include "Pocisk.h"
#include "Enemy.h"
#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
using namespace std;
using namespace sf;

class Gierka
{
private:
	//okno
	sf::RenderWindow* okno;

	//Pauza
	bool pauza;
	Sprite* pauzaScreen;
	Texture pauzaScreenTex;

	//GUI / interface
	Font font;
	Text pointText{font};
	Text gameOverText{font};
	float points;
	float scoreTimer;
	int bestScore;
	int bestKills;

	//gracz
	Gracz* gracz;
	RectangleShape HpBar;
	RectangleShape HpBarMax;

	//swiat
	sf::Sprite* worldBackground;
	sf::Texture worldBackgroundTex;

	//wrogowie
	vector<Enemy*> enemies;
	float spawntimer;
	float spawntimerMax;

	//przedmioty
	float healSpawntimer;
	float healSpawntimerMax;

	float avatarSpawntimer;
	float avatarSpawntimerMax;

	//poziom trudnosci 
	int trudnosc;
	Text trudnoscText{font};
	SoundBuffer levelUpBf;
	Sound levelUp{levelUpBf};

	//resources
	TeksturkiRepository textures;
	vector<Pocisk*> pociski;

	//Muzyka
	SoundBuffer tlobf;
	SoundBuffer strzalbf;
	SoundBuffer killbf;

	Sound strzal{ strzalbf };
	Sound kill{ killbf };
	Music muzyka;

	float strzalSoundCooldown;

	//inicjalizacje
	void inicjalizacjaokna();
	void initTextures();
	void initWorld();
	void initGracz();
	void initEnemies();
	void initGUI();
	void initDane();
	void initPauza();
	void pollEventsOnly();
	void initAudio();

	//czas a nie klatki
	sf::Clock clock;
	float dt;  //czas trwania jednej klatki

public:
	Gierka();
	virtual ~Gierka();

	void start();
	void updateInput();
	void updateGUI();
	void updatePocisk();
	void updateEnemies();
	void updateWalka();
	void update();
	void render();
	void renderGUI();
	void renderWorld();
	void updateWorld();
	void updateKolizja();
};

