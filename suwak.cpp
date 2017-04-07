#include "suwak.h"
//
template<typename T>
suwak<T>::suwak(T *wartosc, const sf::Vector2f pozycja, const float _dlugosc, const T poczatek, const T koniec, const unsigned int rozdzielczosc, const K_ZDARZENIE id):kontrolka(pozycja, id)
{
	this->inic(_dlugosc);
	this->pocz = poczatek;
	this->kon = koniec;
	this->roz = (rozdzielczosc >= 2) ? rozdzielczosc : 2;
	this->wart = wartosc;
	float wspL = _dlugosc / (this->roz - 1);
	float wspW = (koniec - poczatek) / (this->roz - 1);
	for(int i = 0; i < this->roz; i++) 
	{
		this->punkty.push_back(new sf::Vector2f(static_cast<float>(i) * wspL + pozycja.x, pozycja.y));
		this->elem.push_back(static_cast<float>(i) * wspW + poczatek);
	}
}
//
template<typename T>
suwak<T>::suwak(T *wartosc, const sf::Vector2f pozycja, const float _dlugosc, const std::vector<T> tablica, const K_ZDARZENIE id):kontrolka(pozycja, id)
{
	this->inic(_dlugosc);
	this->wart = wartosc;
	this->elem = tablica;
	this->roz = tablica.size();
	float wspL = _dlugosc / (this->roz - 1);
	for(int i = 0; i < this->roz; i++) this->punkty.push_back(new sf::Vector2f(static_cast<float>(i) *wspL + this->poz.x, this->poz.y));
	}
//
template<typename T>
suwak<T>::~suwak(){}
//
template<typename T>
void suwak<T>::rysuj(sf::RenderWindow &okno, const sf::Time c_rzecz)
{
	if(this->dis)
	{
		this->suw.setFillColor(sf::Color(127, 127, 127));
		this->linia.setFillColor(sf::Color(127, 127, 127));
	}
	else
	{
		this->suw.setFillColor(sf::Color::White);
		this->linia.setFillColor(sf::Color::White);	
	}
	sf::Rect<float> p_suw = this->suw.getGlobalBounds();
	sf::Vector2f poz = okno.mapPixelToCoords(sf::Mouse::getPosition(okno));
	if(p_suw.contains(poz.x, poz.y) && !this->dis)
	{
		this->suw.setOutlineThickness(2);
	}
	else
	{
		this->suw.setOutlineThickness(1);
	}
	
	okno.draw(this->linia);
	okno.draw(this->suw);
}
//
template<typename T>
void suwak<T>::inic(const float _dlugosc)
{
	this->dlugosc = _dlugosc;
	sf::Vector2f pozycja(this->poz.x, this->poz.y - 12.5);
	sf::Vector2f pole(_dlugosc, 25);
	this->pol = sf::Rect<float>(pozycja, pole);
	this->linia.setSize(sf::Vector2f(_dlugosc, 3));
	this->linia.setOrigin(sf::Vector2f(0, 1.5));
	this->linia.setPosition(this->poz);
	this->linia.setOutlineThickness(1);
	this->linia.setOutlineColor(sf::Color(127, 127, 127));
	this->suw.setSize(sf::Vector2f(15, 25));
	this->suw.setOrigin(sf::Vector2f(7.5, 12.5));
	this->suw.setPosition(this->poz);
	this->suw.setOutlineColor(sf::Color(127, 127, 127));
	}
//
template<typename T>
bool suwak<T>::klikniety(sf::RenderWindow &okno)
{
	sf::Vector2f p = okno.mapPixelToCoords(sf::Mouse::getPosition(okno));
	sf::CircleShape a(10);
	a.setPosition(p);
	okno.draw(a);
	unsigned int i = 0;
	if(!this->dis && sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->pol.contains(p.x, p.y))
	{
		for(std::vector<sf::Vector2f*>::const_iterator it = this->punkty.begin(); it != this->punkty.end(); it++, i++)
		{
			if((abs((**it).x - p.x)) < 5)
			{
				this->suw.setPosition(**it);
				*wart = elem[i];
			}
		} 
		return true;
	}
}
//
template<typename T>
T suwak<T>::get_pocz() const
{
	return this->pocz;
}
//
template<typename T>
T suwak<T>::get_kon() const
{
	return this->kon;
}
//
template<typename T>
sf::Vector2f suwak<T>::rozmiary() const
{
	sf::Vector2f w;
	w.x = this->pol.width;
	w.y = this->pol.height;
	return w;
}
//
template<typename T>
void suwak<T>::set_poz(sf::Vector2f pozycja)
{
}
//
template<typename T>
void suwak<T>::set_poz_r(sf::Vector2f pozycja)
{
}
//
template class suwak<float>;
template class suwak<int>;
