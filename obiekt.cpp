#include "obiekt.h"
//
obiekt::obiekt(sf::Vector2f pozycja, double masa_kg, TYP_OBIEKT rodzaj):
	pozycja(pozycja),
	masa(masa_kg),
	hp(100),
	kat(0),
	rodzaj(rodzaj),
	kolor(sf::Color::White)
	{}
obiekt::~obiekt(){}
sf::Vector2f obiekt::Gpos() const
{
	return this->pozycja;
}

