#ifndef PRZELACZNIK_H
#define PRZELACZNIK_H
//
#include "kontrolka.h"
#include "wlas.hpp"
class przelacznik : public kontrolka
{
	protected:
		sf::ConvexShape tlo; // tlo przelacznika
		sf::Time licznik;
		sf::Color kolorTla; // kolor tla
	public:
		// kontruktory
		przelacznik(const sf::Vector2f pozycja, const K_ZDARZENIE _id, const float _kat = 0, const float rozmiar = 30,  const sf::Color kolorTla = sf::Color(195, 195, 195));
		~przelacznik();
		//funkcje
		void rysuj(sf::RenderWindow &okno, const sf::Time c_rzecz);
		bool klikniety(sf::RenderWindow &okno);
		sf::Vector2f rozmiary() const;
		void set_poz(sf::Vector2f pozycja);
		void set_poz_r(sf::Vector2f pozycja);
		
};


#endif
