#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "bch/bch.hpp"
#include "obiekt.h"
#include "przycisk.h"
#include "tekst.h"
#include "menu.h"
#include "ekran.h"
#include "przelacznik.h"
#include "e_edytor.h"
#include "flin_sf.h"
int main()
{
	// Okno
	sf::VideoMode pulpit = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(pulpit, "Czolgi EDYTOR MAP");
    // Czcionki
    sf::Font def_font;
    def_font.loadFromFile("arial.ttf");
    // Ekrany
    ekran *wsk;
 	ekran *start = new menu(L"Menu Glowne", M_GLOWNE);
 	start->dodaj_kontrolke(new przycisk(sf::Vector2f(500, 500), def_font, P_OK, L"TEST", 20));
 	sf::RectangleShape p = flin_sf::linia(sf::Vector2f(100, 100), sf::Vector2f(100, 200), 1);
 	start->dodaj_ksztalt(&p);
 	wsk = start;
 	// Kontrolki Menu
 	flin_sf f(45, 0);
 	bch::p pr = {0, 1500};
 	//petla
	while (window.isOpen())
    {
        sf::Event event;
        K_ZDARZENIE zdarzenie;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            // zdarzenia wlasne
            kontrolka *w;
            zdarzenie = (*wsk).get_aktywny(event, window, w);
            switch((*wsk).get_id())
            {
            	case M_GLOWNE: // zdarzenia w menu glownym
            		if(zdarzenie == P_WYJSCIE) window.close();
            		if(zdarzenie == P_OK) window.close();
            		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) (*wsk).go_rodzic(wsk, window);
            		break;
            }
            
            
        }
		window.clear();
		f.rysuj(window, pr);
		(*wsk).rysuj(window); // rysowanie poszcegolnego ekranu
		window.display();
    }
    return 0;
}
