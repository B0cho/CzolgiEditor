#ifndef WEKTOR_H
#define WEKTOR_H
//
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include "bch/bch.hpp"
#include "wlas.hpp"
class wektor
{
	private:
		float wartosc; // wartosc wektora
		float kat; // kat pod jakim wektor dziala (w stosunku do ekr)
		float poziom; // kat skladowej F1 (w stosunku do ekr)
		sf::Vector2f punkt_przylozenia; // punkt przylozenia
	public:
		// konstruktory i destruktory
		wektor(const float _wartosc, const float _kat, const sf::Vector2f _punkt, const float _poziom = 0); // konstruktor
		wektor(const sf::Vector2f poczatek, const sf::Vector2f koniec); // konstruktor
		wektor();
		// settingi
		void set_wart(const float _wart); // setting wartosci
		void set_poziom(const float _kat); // setting poziomu
		void set_przyl(const sf::Vector2f _punkt_przylozenia); // setting punktu
		void set_kat(const float _kat); // setting kata
		// klucze
		sf::Vector2f get_kon() const; // klucz do punkt koncowego
		float get_kat() const;
		float get_wart() const;
		// operatory
		wektor operator+(wektor _wekt); // dodawanie wektorow o tym samym poziomie
		wektor operator!(); // tworzenie wektora przeciwnego
		// pozostale
		void rysuj_wektor(sf::RenderWindow &okno, const sf::Color kolor = sf::Color::White, const bool skladowe = false, const bool pokaz_wartosc = false); // rysuje dany wektor z wypisanymi wartosciami lub ze skladowymu
		vector<wektor> get_skladowe() const; // zwraca dwie skladowe wg poziomu
		
};

#endif
