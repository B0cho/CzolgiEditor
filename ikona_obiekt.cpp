#include "ikona_obiekt.h"

ikona_obiekt::ikona_obiekt(sf::Vector2f pozycja, K_ZDARZENIE id, unsigned rozmiar, TYP_OBIEKT typ, unsigned grubosc_ramki):kontrolka(pozycja, id), grubosc(grubosc_ramki),
ob(new skrzynia(pozycja, 0, rozmiar - 10))
{
	switch(typ)
	{
		case SKRZYNIA:
			sf::Vector2f rozmiary = this->ob->rozmiary();
			double rx = rozmiary.x / 2 + 10, ry = rozmiary.y / 2 + 10;
			this->model[0] = sf::Vector2f(pozycja.x - rx, pozycja.y - ry);
			this->model[1] = sf::Vector2f(pozycja.x + rx, pozycja.y - ry);
			this->model[2] = sf::Vector2f(pozycja.x + rx, pozycja.y + ry);
			this->model[3] = sf::Vector2f(pozycja.x - rx, pozycja.y + ry);
			break;
	}
}
//
ikona_obiekt::~ikona_obiekt()
{
}
//
void ikona_obiekt::rysuj(sf::RenderWindow &okno, sf::Time c_rzecz)
{
	this->ob->rysuj(okno);
	sf::Vector2f kursor = okno.mapPixelToCoords(sf::Mouse::getPosition(okno));
	sf::Color kolor = (flin_sf::zawiera_sie_w(this->model, 4, kursor) || this->dis) ? sf::Color(128, 128, 128) : sf::Color::White;
	for(size_t i = 0; i < 3; i++)
	{
		sf::RectangleShape l = flin_sf::linia(this->model[i], this->model[i+1], this->grubosc, kolor);
		okno.draw(l);
		if(i == 2)
		{
			l = flin_sf::linia(this->model[3], this->model[0], this->grubosc, kolor);
			okno.draw(l);
		}
	} 
	
}
//
bool ikona_obiekt::klikniety(sf::RenderWindow &okno)
{
	sf::Vector2f kursor = okno.mapPixelToCoords(sf::Mouse::getPosition(okno));
	return (flin_sf::zawiera_sie_w(this->model, 4, kursor) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->dis) ? true : false;
}
//
sf::Vector2f ikona_obiekt::rozmiary() const
{
	return this->model[1] - this->model[0] + this->model[2] - this->model[3];
}
//
void ikona_obiekt::set_poz(sf::Vector2f pozycja){} // zbedne
void ikona_obiekt::set_poz_r(sf::Vector2f pozycja){} // zbedne
