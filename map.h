#ifndef MAP_H
#define MAP_H
//
#include <SFML/Graphics.hpp>
#include <vector>
//#include "obiekt.h"
#include "flin_sf.h"
class obiekt;
class mapa
{
	protected:
		bool edit; // czy mapa jest edytowalna
		float destr; // wspolczynnik zniszczalnosci gruntu
		vector<obiekt*> obiekty; // tablica obiektow
		sf::Texture tekstura_grunt; // tekstura gruntu
		sf::Texture tekstura_ziemia; // tekstura ziemii
		sf::Texture tekstura_tlo; // tekstura tla
		vector<sf::VertexArray> Tr; // punkty gruntu- trojkaty
		sf::VertexArray Qu; // punkty gruntu- czworokaty
		vector<sf::Vector2f> pkt; // zawiera punkty na mapie
		sf::Color kolor_gr; // kolor linii gruntu
		//
		bool TR(const vector<sf::Vector2f>::iterator pocz, const vector<sf::Vector2f>::iterator kon); // dzieli na trojkaty dany obszar
		static bool w_linii(const sf::Vector2f a, const sf::Vector2f X, const sf::Vector2f b); // sprawdza, czy X miesci sie w przedziale a i b pod wzgledem x i y
		// czolg1
		// czolg2
	public:
		// kontruktory
		mapa();
		~mapa();
		// funkcje
		void dodaj_obiekt(obiekt *_nowy); // dodaje obiekt
		bool konw_tex(); // konwertuje rysunek mapy do textury
};

#endif
