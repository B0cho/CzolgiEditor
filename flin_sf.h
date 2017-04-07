#ifndef FLIN_SF_H
#define FLIN_SF_H
//
#include "bch/bch.hpp"
#include <SFML/Graphics.hpp>
//
#include <iostream>
#include <tuple>
#include <list>
class flin_sf : public bch::flin // klasa funkcji liniowej przystosowana dla SFML
{
	public:
		flin_sf(const float kat, const float _b = 0); // konsturktor
		flin_sf(const sf::Vector2f x, const sf::Vector2f y); // konstruktor
		flin_sf();
		sf::VertexArray rysuj(sf::RenderWindow &okno, bch::p przedzial, sf::Color kolor = sf::Color::White); // rysowanie wykresu funkcji w przedziale
		~flin_sf();
		bool operator >=(const sf::Vector2f punkt);
		bool operator <=(const sf::Vector2f punkt);
		bool operator >(const sf::Vector2f punkt);
		bool operator <(const sf::Vector2f punkt);
		static float p_odl(const sf::Vector2f x, const sf::Vector2f y); // odleglosc miedzy dwoma punktami
		static sf::RectangleShape linia(sf::Vector2f wsp1, sf::Vector2f wsp2, double grubosc_piks = 1, sf::Color kolor = sf::Color::White); // rysuje linie o dowolnej grubosci
		sf::Vector2f operator==(const flin_sf f); // zwraca punkt, w ktorym dwie funkcje sie przecinaja
		static double max_h(pair<sf::Vector2f, sf::Vector2f> f1, pair<sf::Vector2f, sf::Vector2f> f2); // zwraca maksymaln¹ odleg³osc miedzy punktami na dwoch funkcjach
		static bool zawiera_sie_w(const sf::Vector2f figura[], const unsigned int r, const sf::Vector2f punkt); // sprawdza czy punkt zawiera siê w figurze wkleslej
		static bool zawiera_sie_w(list<sf::Vector2f> obiekt, list<sf::Vector2f> figura);
};

#endif
