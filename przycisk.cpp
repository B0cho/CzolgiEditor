#include "przycisk.h"
//
przycisk::przycisk(const sf::Vector2f pozycja, const sf::Font czcionka, K_ZDARZENIE _id, const std::wstring opis, const int rozmiarTekstu, const sf::Color kolorTekstu, const sf::Color kolorTla, const float margines):kontrolka(pozycja, _id)
{
	float x, y;
	sf::Rect<float> zaw;
	this->licznik = CZAS_PRZYCISK;
	this->cz = czcionka;
	this->margin = margines;
	this->etykieta.setString(opis);
	this->etykieta.setFont(this->cz);
	this->etykieta.setColor(kolorTekstu);
	this->etykieta.setCharacterSize(rozmiarTekstu);
	this->tlo.setFillColor(kolorTla);
	this->kolorTla = kolorTla;
	zaw = etykieta.getGlobalBounds();
	x = zaw.width;
	y = zaw.height;
	this->etykieta.setOrigin(sf::Vector2f(x / 2, y - 5));
	this->tlo.setSize(sf::Vector2f(x + 2 * margines, y + 2 * margines));
	zaw = tlo.getGlobalBounds();
	x = zaw.width;
	y = zaw.height;
	this->tlo.setOrigin(sf::Vector2f(x / 2, y / 2));
	this->tlo.setOutlineThickness(3);
	}
//
void przycisk::rysuj(sf::RenderWindow &okno, const sf::Time c_rzecz)
{
	this->licznik = (this->licznik > CZAS_PRZYCISK) ? CZAS_PRZYCISK : this->licznik + c_rzecz;
	this->tlo.setPosition(this->poz);
	this->etykieta.setPosition(this->poz);
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
	okno.draw(this->etykieta);
}
//
bool przycisk::klikniety(sf::RenderWindow &okno)
{
	sf::Rect<float> zaw = tlo.getGlobalBounds();
	sf::Vector2f poz = okno.mapPixelToCoords(sf::Mouse::getPosition(okno));
	if(zaw.contains(poz.x, poz.y) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->dis && this->licznik == CZAS_PRZYCISK) return true;
	return false;
}
//
przycisk::przycisk() {}
//
sf::Vector2f przycisk::rozmiary() const
{
	sf::Vector2f w;
	sf::Rect<float> zaw = tlo.getGlobalBounds();
	w.x = zaw.width;
	w.y = zaw.height;
	return w;
}
//
void przycisk::set_etykieta(std::wstring opis)
{
	this->etykieta.setString(opis);
	float x, y;
	sf::Rect<float> zaw = etykieta.getGlobalBounds();
	x = zaw.width;
	y = zaw.height;
	this->etykieta.setOrigin(sf::Vector2f(x / 2, y - 5));
	this->tlo.setSize(sf::Vector2f(x + 2 * this->margin, y + 2 * this->margin));
	this->tlo.setOrigin(sf::Vector2f(x / 2 + this->margin, y / 2 + this->margin));
	
}

void przycisk::set_poz_r(sf::Vector2f pozycja)
{
	this->poz = pozycja;
}
void przycisk::set_poz(sf::Vector2f pozycja)
{
	sf::Rect<float> zaw = this->tlo.getGlobalBounds();
	pozycja.x += zaw.width/2;
	pozycja.y += zaw.height/2;
	this->poz = pozycja;
}
