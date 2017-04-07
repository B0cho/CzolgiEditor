#ifndef EKRAN_H
#define EKRAN_H
//
#include<SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "kontrolka.h"
#include "wlas.hpp"
//#include "e_alert.h"
class e_alert;
class ekran
{
	protected:
		std::vector<kontrolka*> kontrolki; // kontrolki ekranu
		std::vector<sf::Shape*> ksztalty; // kszta³ty na ekranie
		EKRANY id; // id ekranu; do manipulacji zdarzen
		ekran *rodzic; // ekran rodzic
		bool jest_rodzic; // czy ma rodzica
		//
		
		e_alert *alert;
	public:
		// kontruktory i destruktory
		ekran(const EKRANY _id = INNY);
		ekran(ekran *rodzic, const EKRANY _id = INNY);
		virtual ~ekran();
		// funkcje wirtualne
		virtual void rysuj(sf::RenderWindow &okno, const sf::Time c_rzecz); // rysuje dany ekran w oknie 
		virtual K_ZDARZENIE get_aktywny(sf::Event zdarzenie, sf::RenderWindow &okno, kontrolka *&wsk); // zwraca id zdarzenia na ekranie
		virtual void go_rodzic(ekran *&wsk, sf::RenderWindow &okno); // odsy³a do ekranu rodzica
		virtual void dodaj_kontrolke(kontrolka *_obiekt); // dodaje kontrolkê
		//virtual bool wPolu(sf::RenderWindow &okno) const = 0; // NIE WIEM
		// Przeci¹¿enia
		ekran* operator=(ekran* _wsk);
		// Pozosta³e
		sf::Shape *kursor; // ksztalt pokazuj¹cy siê pod kursorem na ekranie
		EKRANY get_id() const; // zwraca ID ekranu
		bool jest_alert;
		void dodaj_ksztalt(sf::Shape *_obiekt); // dodaje kszta³t na ekranie
		kontrolka* get_kontr(K_ZDARZENIE _id) const; // zwraca kontrolke przez id(pierwsza)
		std::vector<kontrolka*> get_kontr2(K_ZDARZENIE _id); // zwraca wszystkie kontrolki o
		void nowy_alert(e_alert *okno); //dodaj alert
		bool del_kontrl(K_ZDARZENIE _id);
		static sf::Vector2f centruj_w(const sf::Vector2f a, const sf::Vector2f b); // zwraca srodek w podanym kwadracie wyznaczanym przez a i b
};

#endif
