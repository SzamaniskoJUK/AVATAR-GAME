/*
Projekt bardzo prosty ale jest to pierwsze tak zaawansowane programowanie w moim życiu (co daje tez liczne rozwiązania które można by było pewnie zrobić 50razy lepiej ale jestem zadowolony

SPEŁNIONE PODPUNKTY:
*1	Deklaracja i definicja klasy. Metody składowe i statyczne klasy.
Wszystkie klasy mają plik .h (deklaracja) i .cpp (definicja). 
Metody statyczne  np. void Enemy::dodajZabitego();.		Pole statyczne int Enemy::zabitychWrogow.

*2	Konstruktor i destruktor klasy. Przeciążanie konstruktorów i ich rodzaje.
Wszędzie destruktory wirtualne.

*3	Dziedziczenie i hierarchia klas.
Entity->Gracz, Entity->Enemy, Entity->Pocisk

*4	Klasy zagnieżdżone (wewnętrzne).
np. enumy wewnątrz klasy Enemy (Type istnieje tylko w kontekscie Enemy)

*5	Klasy i funkcje wirtualne.
np. virtual void update() = 0; . Destruktory do klas

*6	Polimorfizm i klasy abstrakcyjne.
np.virtual void update() = 0; render() wskaźnik Entity* może trzymać enemy , gracza i pocisk i każdy zachowuje się normalnie bez błędów

*7	Pojęcie interfejsu
Nwm czy o to chodziło ale Entity troche pełni tę role chyba bo każda klasa dziedziczy po Entity i dzięki temu "Gierka" ma prościej bo tylko update i render

*8	Strumienie i pliki.
Zapisywanie najlepszego wyniki i największej ilości pokonanych przeciwnikow do score.txt oraz kills.txt przy pomocy ofstream

*9	Operacje wejścia/wyjścia i obsługa wyjątków.
Tu było zamieszanie ale mam to np w  Gierka::updateGUI() (throw,catch itp) 

*10	Typy generyczne funkcji i klas.
np.template<typename A> w Utility jeden kod obsługuje wszystko

*11	Kolekcje
np. vector<Enemy*> enemies;, vector<Pocisk*> pociski;

*12	Przykładowe wzorce programistyczne (Repository, IoC)
To było kongo ale się udało. Tekstury.h TeksturkiRepository klasa odpowiedzialna za zasób tekstur 


(na 98% wszystkie punkty zrobione był problem z 12,10,9,11 ale po paru poradnikach i małą pomocą ai szczególnie przy 12 i 9 udało się to ogarnąc)

DZIAŁANIE I CEL GRY:
Gra w stylu galaga w której wcielamy się w postać AVATARA AANGA walczącego z narodem ognia (z serialu Avatar the Last Airbender który ostatnio oglądałem i tak powstał pomysł na gre)
Z góry ekranu w losowych miejscach idą przeciwnicy (Ich ilość zwiększa się z ilością zdobytych punktów (co 500pkt przeciwników jest coraz więcej (poziom trudności))
Pod LPM strzeamy posickami wiatru a pod AWSD sterujemy postacią. Za pokonywanie przeciwników dostajemy punkty których chcemy mieć jak najwięcej.
(Są różne typy przeciwników (narazie tylko 2 ale chce żeby ich było około 4 + boss przy dobiciu określonej ilości punktów)
Przy kontakcie bezpośrednim z przeciwnikami otrzymujemy obrażenia więc lepiej się nie zbliżać.
Tak samo w przypadku gdy przeciwnik nas ominie i dotknie dołu ekranu jednak wtedy obrażenia są mniejsze o 90 % ( zapobiega to taktyce na stanie w miejsu i strzelanie ale nie robi gry bardzo trudnej)
Z góry co jakiś czas spadają rzeczy dobre dla postaci (heal albo 4 żywioły wprowadzające nas w stan avatara)
Pod klawiszem ESC można zatrzymać gre.
(Gre chciałbym ulepszać ale narazie w celu zaliczenia przedmiotu jest w takiej formie)
(!!!WSZYSTKIE TEKSTURY ZOSTAŁY ZROBIONE PRZEZEMNIE DLATEGO PRZECIWNIKÓW JEST NARAZIE MAŁO XD!!!)
MIŁEGO GRANIA!!!

*/
#include <iostream>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include "Gierka.h"
using namespace sf;


int main()
{
	srand(static_cast<unsigned>(time(nullptr)));

	Gierka gierka;

	gierka.start();

	return 0;
}