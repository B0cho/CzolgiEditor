#ifndef SKRZYNIA_H
#define SKRZYNIA_H
//
#include "obiekt.h"
#include "palhsv.h"
//
class skrzynia : public obiekt // klasa skrzyni
{
	protected:
		sf::Texture tekstura; // tekstura skrzyni
		unsigned rozmiar; // rozmiar skrzyni w pikselach
		sf::ConvexShape maska; // maska skrzyni
		sf::Vector2f model[4]; // model skrzyni
	public:
		skrzynia(sf::Vector2f pozycja, double masa_kg, unsigned rozmiar); // konstruktor
		~skrzynia();
		void rysuj(sf::RenderWindow &okno); // rysuje obiekt
		void obroc(sf::Vector2f origin, double kat); // obraca obiekt wzglêdem osi origin
		bool kolizja(sf::Vector2f punkt); // sprawdza, czy punkt zawiera siê w obiekcie
		void obroc(double kat); // obraca dany obiekt wzgledem srodka masy
		void przesun(sf::Vector2f wektor); // przesuwa obiekt o wektor
		void ustaw(sf::Vector2f pozycja); // ustawia obiekt na zadanej pozycji
		sf::Vector2f rozmiary() const;
		void Scolor(sf::Color nowy_kolor);
		list<sf::Vector2f> Gmodel() const;
		
};
//
#endif
