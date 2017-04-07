#include "tekst.h"
/*
tekst::tekst(const std::wstring opis, const sf::Font _czcionka, const sf::Vector2f pozycja, const int rozmiarTekstu, const sf::Color kolorTekstu):kontrolka(pozycja, BRAK)
{
//	this->poz = pozycja;
	this->czcionka = _czcionka;
	this->t = sf::Text(sf::String(opis), this->czcionka, rozmiarTekstu);
	this->t.setColor(kolorTekstu);
	sf::Vector2f origin = this->t.getOrigin();
	sf::Rect<float> rect = this->t.getGlobalBounds();
	//this->t.setOrigin(sf::Vector2f(rect.width / 2, rect.height / 2));
}
*/
//
void tekst::rysuj(sf::RenderWindow &okno, const sf::Time c_rzecz)
{
	this->t.setPosition(this->poz);
	okno.draw(this->t);
}
//
sf::Vector2f tekst::rozmiary() const
{
	sf::Vector2f w;
	sf::Rect<float> r = this->t.getGlobalBounds();
	w.x = r.width;
	w.y = r.height;
	return w;
}
// test
tekst::tekst(const std::wstring opis, const sf::Font _czcionka, const sf::Vector2f pozycja, const int rozmiarTekstu, const sf::Color kolorTekstu):kontrolka(pozycja, BRAK)
{
	this->czcionka = _czcionka;
	this->t = sf::Text(sf::String(opis), this->czcionka, rozmiarTekstu);
	this->t.setColor(kolorTekstu);
}
void tekst::set_poz(sf::Vector2f pozycja)
{
	this->poz = pozycja;
}
void tekst::set_poz_r(sf::Vector2f pozycja)
{
	sf::Rect<float> zaw = this->t.getGlobalBounds();
	pozycja.x -= zaw.width/2;
	pozycja.y -= zaw.height/2;
	this->poz = pozycja;
}

