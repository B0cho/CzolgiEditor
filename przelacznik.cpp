#include "przelacznik.h"
//
przelacznik::~przelacznik()
{
}
//
przelacznik::przelacznik(const sf::Vector2f pozycja, const K_ZDARZENIE _id, const float _kat, const float rozmiar,  const sf::Color kolorTla):kontrolka(pozycja, _id)
{
	this->tlo.setFillColor(kolorTla);
	this->kolorTla = kolorTla;
	this->tlo.setOrigin(this->poz);
	this->tlo.setPointCount(4);
	this->tlo.setPoint(0, this->poz);
	sf::Vector2f wekt = this->poz;
	wekt.x -= rozmiar / 2;
	this->tlo.setPoint(2, wekt);
	wekt = this->poz;
	wekt.y -= rozmiar / 2;
	this->tlo.setPoint(1, wekt);
	wekt.y += rozmiar;
	this->tlo.setPoint(3, wekt);
	this->tlo.setRotation(_kat); 
	this->tlo.setOutlineThickness(3);
	this->tlo.setPosition(this->poz);
}
//
bool przelacznik::klikniety(sf::RenderWindow &okno)
{
	sf::Rect<float> zaw = tlo.getGlobalBounds();
	sf::Vector2f poz = okno.mapPixelToCoords(sf::Mouse::getPosition(okno));
	if(zaw.contains(poz.x, poz.y) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->dis && this->licznik == CZAS_PRZYCISK) return true;
	return false;
}
//
void przelacznik::rysuj(sf::RenderWindow &okno, const sf::Time c_rzecz)
{
	this->licznik = (this->licznik > CZAS_PRZYCISK) ? CZAS_PRZYCISK : this->licznik + c_rzecz;
	this->tlo.setPosition(this->poz);
	sf::Rect<float> zaw = tlo.getGlobalBounds();
	sf::Vector2f poz = okno.mapPixelToCoords(sf::Mouse::getPosition(okno));
	if(zaw.contains(poz.x, poz.y) && !this->dis)
	{
		this->tlo.setOutlineColor(sf::Color(127, 127, 127));
	}
	else
	{
		this->tlo.setOutlineColor(this->tlo.getFillColor());
	}
	if(this->dis)
	{
		this->tlo.setFillColor(sf::Color(127, 127, 127));
	}
	else
	{
		this->tlo.setFillColor(this->kolorTla);
	} 
	okno.draw(this->tlo);
}
//

void przelacznik::set_poz(sf::Vector2f pozycja)
{
	this->poz = pozycja;
}
void przelacznik::set_poz_r(sf::Vector2f pozycja)
{
	sf::Rect<float> zaw = this->tlo.getGlobalBounds();
	pozycja.x -= zaw.width/2;
	pozycja.y -= zaw.height/2;
	this->poz = pozycja;
}
sf::Vector2f przelacznik::rozmiary() const
{
	sf::Vector2f w;
	sf::Rect<float> zaw = this->tlo.getGlobalBounds();
	w.x = zaw.width;
	w.y = zaw.height;
	return w;
}
