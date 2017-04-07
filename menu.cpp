#include "menu.h"
//
menu::menu(ekran *_rodzic, const wstring _tytul, const EKRANY _id)
{
	this->id = _id;
	this->rodzic = _rodzic;
	this->jest_rodzic = true;
	this->tytul = _tytul;	
}
//
menu::menu(const wstring _tytul, const EKRANY _id)
{
	this->id = _id;
	this->jest_rodzic = false;
	this->tytul = _tytul;
}
//
menu::~menu() {}
//
void menu::rysuj(sf::RenderWindow &okno, const sf::Time c_rzecz)
{
	sf::Font czcionka_tytul;
	czcionka_tytul.loadFromFile("arial.ttf");
	tekst tytul(this->tytul, czcionka_tytul, sf::Vector2f(65, 10), 20);
	tytul.rysuj(okno, c_rzecz);
	sf::RectangleShape linia(sf::Vector2f(1500, 3));
	linia.setPosition(sf::Vector2f(0, 40));
	okno.draw(linia);
	for(vector<kontrolka*>::iterator it = this->kontrolki.begin(); it != this->kontrolki.end(); it++) (**it).rysuj(okno, c_rzecz);
}
//

//




