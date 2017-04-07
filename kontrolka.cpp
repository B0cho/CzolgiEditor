#include "kontrolka.h"
//
kontrolka::kontrolka(const sf::Vector2f pozycja, K_ZDARZENIE _id)
{
	this->dis = false;
	this->poz = pozycja;
	this->id = _id;
}
//
kontrolka::kontrolka(){}
//
K_ZDARZENIE kontrolka::get_id() const
{
	return this->id;
}
//
kontrolka::~kontrolka(){}
//
//
bool kontrolka::klikniety(sf::RenderWindow &okno)
{
	return false;
}
//
void kontrolka::set_id(K_ZDARZENIE nowe_id)
{
	this->id = nowe_id;
}
//
sf::Vector2f kontrolka::get_poz() const
{
	return this->poz;
}
