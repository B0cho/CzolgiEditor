#ifndef TEKST_H
#define TEKST_H
//
#include "kontrolka.h"
#include <SFML/Graphics.hpp>
#include <string>
class tekst : public kontrolka
{
	protected:
		sf::Font czcionka;
	public:
		sf::Text t;
		tekst(const std::wstring opis, const sf::Font _czcionka, const sf::Vector2f pozycja, const int rozmiarTekstu = 10, const sf::Color kolorTekstu = sf::Color::White);
		void rysuj(sf::RenderWindow &okno, const sf::Time c_rzecz);
		sf::Vector2f rozmiary() const;
		void set_poz(sf::Vector2f pozycja);
		void set_poz_r(sf::Vector2f pozycja);
		// test
};

#endif
