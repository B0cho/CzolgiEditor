#ifndef CZESC_H
#define CZESC_H
#include <SFML/Graphics.hpp>
//
class czesc
{
	protected:
		sf::Vector2f srdk_mas;
		sf::ConvexShape part;
		sf::Texture tekstura;
		double kat;
	public:
		czesc(double masa_kg, sf::Vector2f pozycja, sf::ConvexShape kontur, sf::Texture tekstura);
		~czesc();
		double masa;
		sf::Vector2f poz;
		void rysuj(double skala = 1);
		void ustaw_kat(double kat_dgrs);
		};

#endif
