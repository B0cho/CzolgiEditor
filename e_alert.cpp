#include "e_alert.h"
//
e_alert::e_alert(ekran *rodzic, std::vector<K_ZDARZENIE> tab):ekran(rodzic), wyl(tab)
{
	sf::VideoMode v = sf::VideoMode::getDesktopMode();	
	sf::Vector2f w;
	w.x = v.width;
	w.y = v.height;
	sf::RectangleShape *t = new sf::RectangleShape(w);
	t->setFillColor(sf::Color(0, 0, 0, 200));
	this->dodaj_ksztalt(t);
	//
	
}
e_alert::e_alert(ekran *rodzic, K_ZDARZENIE zdarzenie_wyl):ekran(rodzic)
{
	this->wyl.push_back(zdarzenie_wyl);
	sf::VideoMode v = sf::VideoMode::getDesktopMode();	
	sf::Vector2f w;
	w.x = v.width;
	w.y = v.height;
	sf::RectangleShape *t = new sf::RectangleShape(w);
	t->setFillColor(sf::Color(0, 0, 0, 200));
	this->dodaj_ksztalt(t);
	//
	
}
//
K_ZDARZENIE e_alert::get_id() const
{
	return this->id_alert;
}
//
K_ZDARZENIE e_alert::get_aktywny(sf::Event zdarzenie, sf::RenderWindow &okno)
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
	for(std::vector<kontrolka*>::const_iterator it = this->kontrolki.begin(); it != this->kontrolki.end(); it++)
	{
		if((**it).klikniety(okno)) 
		{
			K_ZDARZENIE z = (**it).get_id();
			for(std::vector<K_ZDARZENIE>::const_iterator it = this->wyl.begin(); it != this->wyl.end(); it++) 
			{
				if(z == *it) 
				{
					for(std::vector<kontrolka*>::iterator it = this->wyl_kontr.begin(); it != this->wyl_kontr.end(); it++) (**it).dis = false;
					this->rodzic->jest_alert = false;
					delete this;
				}	
			}
			return z;
		}
	}
	}
}
