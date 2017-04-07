#ifndef IKONA_OBIEKT_H
#define IKONA_OBIEKT_H
//
#include "kontrolka.h"
#include "skrzynia.h"
class ikona_obiekt : public kontrolka // klasa ikony obiektu
{
	protected:
		obiekt *ob; // obiekt ikony
		sf::Vector2f model[4]; // model ikony
		unsigned grubosc; // grubosc ramki
	public:
		ikona_obiekt(sf::Vector2f pozycja, K_ZDARZENIE id, unsigned rozmiar, TYP_OBIEKT typ, unsigned grubosc_ramki = 3); // konstruktor
		~ikona_obiekt();
		void rysuj(sf::RenderWindow &okno, sf::Time c_rzecz); // funkcja rysowania ikony
		bool klikniety(sf::RenderWindow &okno); // klikniecie ikony
		sf::Vector2f rozmiary() const; // rozmiary ikony
		void set_poz(sf::Vector2f pozycja); // zbedne
		void set_poz_r(sf::Vector2f pozycja); // zbedne
};

#endif
