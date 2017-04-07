#ifndef PRZYCISK_H
#define PRZYCISK_H
//
#include<string>
#include<SFML/Graphics.hpp>

#include "kontrolka.h"
#include "wlas.hpp"

class przycisk : public kontrolka
{
	protected:
		sf::RectangleShape tlo; // tlo przycisku
		sf::Text etykieta; // etykieta przycisku
		sf::Time licznik;
		sf::Font cz; // czcionka przycisku
		sf::Color kolorTla; // kolor tla
		float margin; // margines
	public:
		//kontruktory
		przycisk(const sf::Vector2f pozycja, const sf::Font czcionka, K_ZDARZENIE _id, const std::wstring opis = L"Przycisk", const int rozmiarTekstu = 10, const sf::Color kolorTekstu = sf::Color::Black, const sf::Color kolorTla = sf::Color(195, 195, 195), const float margines = 8);
		przycisk();
		// funkcje
		void rysuj(sf::RenderWindow &okno, const sf::Time c_rzecz);
		bool klikniety(sf::RenderWindow &okno);
		std::wstring get_etykieta() const; // zwraca tresc etykiety
		void set_etykieta(std::wstring opis);
		sf::Vector2f rozmiary() const;
		void set_poz_r(sf::Vector2f pozycja);
		void set_poz(sf::Vector2f pozycja);
		
};

#endif
