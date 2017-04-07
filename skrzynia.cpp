#include "skrzynia.h"
//
skrzynia::skrzynia(sf::Vector2f pozycja, double masa_kg, unsigned rozmiar):obiekt(pozycja, masa_kg, SKRZYNIA), rozmiar(rozmiar)
{
	this->maska.setPointCount(4); // ilosc punktow maski
	// punkty modelu
	this->model[0] = sf::Vector2f(pozycja.x - rozmiar / 2, pozycja.y - rozmiar / 2);
	this->model[1] = sf::Vector2f(pozycja.x + rozmiar / 2, pozycja.y - rozmiar / 2);
	this->model[2] = sf::Vector2f(pozycja.x + rozmiar / 2, pozycja.y + rozmiar / 2);
	this->model[3] = sf::Vector2f(pozycja.x - rozmiar / 2, pozycja.y + rozmiar / 2);
	// punkty maski
	for(int i = 0; i < 4; i++) this->maska.setPoint(i, this->model[i]);
	this->maska.setOrigin(pozycja);
	this->maska.setPosition(pozycja);
	// tekstura maski
	this->tekstura.loadFromFile("res/skrz.png");
	this->maska.setTexture(&this->tekstura);
	// pozostale
	this->srd_masy = pozycja;
	}
//
skrzynia::~skrzynia(){}
//
void skrzynia::rysuj(sf::RenderWindow &okno)
{
	okno.draw(this->maska);
}
//
void skrzynia::obroc(sf::Vector2f origin, double kat)
{
	double k;
	this->kat = bch::bzw_dgrs(this->kat + kat);
	this->maska.rotate(kat); // obracanie maski
	for(int i = 0; i < 4; i++) // obracanie punktów
	{
		k = bch::bzw_dgrs(bch::rad_to_dgrs(atan2(this->model[i].x - origin.x, this->model[i].y - origin.y)) - kat);
		palHSV::p_okr(this->model[i], origin, flin_sf::p_odl(origin, this->model[i]), k);
	}
	// obracanie wektora pozycji
	k = bch::bzw_dgrs(bch::rad_to_dgrs(atan2(this->pozycja.x - origin.x, this->pozycja.y - origin.y)) - kat);
	palHSV::p_okr(this->pozycja, origin, flin_sf::p_odl(this->pozycja, origin), k);
	this->maska.setPosition(this->pozycja);
}
//
bool skrzynia::kolizja(sf::Vector2f punkt)
{
	if(flin_sf::zawiera_sie_w(this->model, 4, punkt)) this->maska.setFillColor(sf::Color::Red); //
	else this->maska.setFillColor(sf::Color::Green); // 
	return flin_sf::zawiera_sie_w(this->model, 4, punkt);
}
//		
void skrzynia::obroc(double kat)
{
	this->kat = bch::bzw_dgrs(this->kat + kat); // ustalanie kata
	this->maska.rotate(kat); // obracanie maski
	// obracanie modelu
	for(int i = 0; i < 4; i++)
	{
		double k = bch::bzw_dgrs(bch::rad_to_dgrs(atan2(this->model[i].x - this->pozycja.x, this->model[i].y - this->pozycja.y)) - kat);
		palHSV::p_okr(this->model[i], this->pozycja, flin_sf::p_odl(this->pozycja, this->model[i]), k);
	}
}
//
void skrzynia::przesun(sf::Vector2f wektor)
{
	this->srd_masy = this->pozycja += wektor; // przesuwanie srodka masy i pozycji
	this->maska.move(wektor); // przesuwanie maski
	for(int i = 0; i < 4; i++) this->model[i] += wektor; // przesuwanie modelu
}
//
void skrzynia::ustaw(sf::Vector2f pozycja)
{
	pozycja -= this->pozycja; // ustalanie wektora przesuniecia
	this->przesun(pozycja);
}
//
sf::Vector2f skrzynia::rozmiary() const
{
	return sf::Vector2f(rozmiar, rozmiar);
}
void skrzynia::Scolor(sf::Color nowy_kolor)
{
	this->maska.setFillColor(nowy_kolor);	
}
//
list<sf::Vector2f> skrzynia::Gmodel() const
{
	list<sf::Vector2f> l;
	l.assign(this->model, this->model + 3);
	return l;
	
}
