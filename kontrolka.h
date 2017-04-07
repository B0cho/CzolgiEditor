#ifndef KONTROLKA_H
#define KONTROLKA_H
//
#include <SFML/Graphics.hpp>
#include "wlas.hpp"
class kontrolka //abstrakcyjna
{
	protected:
		sf::Vector2f poz; // pozycja kontrolki
		K_ZDARZENIE id; // id danej kontrolki
	public:
		// konstruktory
		kontrolka(const sf::Vector2f pozycja, K_ZDARZENIE _id);
		kontrolka();
		virtual ~kontrolka();
		void set_id(K_ZDARZENIE nowe_id);
		// funkcje 
		virtual void rysuj(sf::RenderWindow &okno, const sf::Time c_rzecz) = 0; // rysuje kontrolke na ekranie
		K_ZDARZENIE get_id() const; // zwraca id przycisku
		virtual bool klikniety(sf::RenderWindow &okno); // sprawdza, czy przycisk jest klikniety
		virtual sf::Vector2f rozmiary() const = 0;  // zwraca rozmiary kontrolki
		// inne
		bool dis; // czy kontrolka jest wylaczona
		virtual void set_poz(sf::Vector2f pozycja) = 0;
		virtual void set_poz_r(sf::Vector2f pozycja) = 0;
		sf::Vector2f get_poz() const;
		
		
};
#endif
