#ifndef OBIEKT_H
#define OBIEKT_H
//
#include <SFML/Graphics.hpp>
#include "flin_sf.h"
#include "e_mapa.h"
//
enum TYP_OBIEKT // typ rodzaju obiektu
{
	SKRZYNIA, // skrzynia
	TNT,
	ZASIEK
};
//
class obiekt // klasa obiektu
{
	protected:
		sf::Vector2f srd_masy; // pozycja srodka masy
		double kat; // kat pochylenia skrzyni
		sf::Vector2f pozycja; // pozycja obiektu
		double masa; // masa obiektu w kg
		sf::Color kolor; // kolor obiektu
	public:
		obiekt(sf::Vector2f pozycja, double masa_kg, TYP_OBIEKT rodzaj); // konstruktor
		~obiekt();
		double hp; // hp
		const TYP_OBIEKT rodzaj; // rodzaj obiektu
		sf::Vector2f Gpos() const; // zwraca pozycjê obiektu
		virtual void Scolor(sf::Color nowy_kolor) = 0; // ustawia kolor obiektu
		virtual void rysuj(sf::RenderWindow &okno) = 0; // funkcja rysowania
		virtual void obroc(sf::Vector2f origin, double kat) = 0; // obraca dany obiekt
		virtual void obroc(double kat) = 0; // obraca dany obiekt
		virtual void przesun(sf::Vector2f wektor) = 0; // przesuwa obiekt o wektor
		virtual void ustaw(sf::Vector2f pozycja) = 0; // ustawia obiekt na zadanej pozycji
		virtual bool kolizja(sf::Vector2f punkt) = 0; // sprawdza, czy punkt zawiera sie w obiekcie
		virtual sf::Vector2f rozmiary() const = 0; // zwraca rozmiary
		virtual list<sf::Vector2f> Gmodel() const = 0; // zwraca ca³y model
};

#endif
