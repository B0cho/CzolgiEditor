#include "ekran.h"
#include "e_alert.h"
//
ekran::~ekran() {}
//
K_ZDARZENIE ekran::get_aktywny(sf::Event zdarzenie, sf::RenderWindow &okno, kontrolka *&wsk)
{
	if(this->jest_alert)
	{
		e_alert *a = this->alert;
		K_ZDARZENIE z  = (*a).get_aktywny(zdarzenie, okno);
		if(z != BRAK)
		{
			return z;
		}
	}
	else
	{
	for(std::vector<kontrolka*>::const_iterator it = this->kontrolki.begin(); it < this->kontrolki.end(); it++)
	{
		if((**it).klikniety(okno)) 
		{
			wsk = *it;
			return (**it).get_id();
		}
	}
}
}
//
EKRANY ekran::get_id() const
{
	return this->id;
}
//
void ekran::dodaj_ksztalt(sf::Shape *_obiekt)
{
	this->ksztalty.push_back(_obiekt);
}
//
ekran* ekran::operator=(ekran* _wsk)
{
	delete this;
	return _wsk;
}
//
void ekran::rysuj(sf::RenderWindow &okno, const sf::Time c_rzecz)
{
	// rysuj alert- to samo w reszcie ekranow
	for(std::vector<sf::Shape*>::iterator it = this->ksztalty.begin(); it < this->ksztalty.end(); it++) okno.draw(**it);
	for(std::vector<kontrolka*>::iterator it = this->kontrolki.begin(); it < this->kontrolki.end(); it++) (**it).rysuj(okno, c_rzecz);
	//
	if(this->jest_alert)
	{
		this->alert->rysuj(okno, c_rzecz);
	}
	//
}
//
void ekran::dodaj_kontrolke(kontrolka *_obiekt)
{
	this->kontrolki.push_back(_obiekt);
}
//
void ekran::go_rodzic(ekran *&wsk, sf::RenderWindow &okno)
{
	if(this->jest_rodzic)
	{
		wsk = this->rodzic;
	}
	else
	{
		okno.close();
	}
}
//
ekran::ekran(const EKRANY _id):id(_id),jest_alert(false)
{
	this->jest_rodzic = false;
}
//
ekran::ekran(ekran *rodzic, const EKRANY _id):id(_id),rodzic(rodzic),jest_alert(false)
{
	this->jest_rodzic = true;
}
//
kontrolka* ekran::get_kontr(K_ZDARZENIE _id) const
{
	for(std::vector<kontrolka*>::const_iterator it = this->kontrolki.begin(); it != this->kontrolki.end(); it++) if((**it).get_id() == _id) return *it;
}
//
std::vector<kontrolka*> ekran::get_kontr2(K_ZDARZENIE _id)
{
	std::vector<kontrolka*> tab;
	for(std::vector<kontrolka*>::const_iterator it = this->kontrolki.begin(); it != this->kontrolki.end(); it++) if((**it).get_id() == _id) tab.push_back(*it);
	return tab;
}
//
void ekran::nowy_alert(e_alert *okno)
{
	this->jest_alert = true;
	this->alert = okno;
	for(std::vector<kontrolka*>::iterator it = this->kontrolki.begin(); it != this->kontrolki.end(); it++)
	{
		if(!(**it).dis) okno->wyl_kontr.push_back(*it);
		(**it).dis = true;
	}
}
//
sf::Vector2f ekran::centruj_w(const sf::Vector2f a, const sf::Vector2f b)
{
	sf::Vector2f wynik;
	wynik.x = (a.x + b.x)/2;
	wynik.y = (a.y + b.y)/2;
	return wynik;
}
//
bool ekran::del_kontrl(K_ZDARZENIE _id)
{
		for(std::vector<kontrolka*>::iterator it = this->kontrolki.begin(); it != this->kontrolki.end(); it++) 
		{
			if((**it).get_id() == _id)
			{
				this->kontrolki.erase(it);
				return true;
			}
		}
		return false;
}
