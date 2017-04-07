#ifndef SUWAK_H
#define SUWAK_H
//
#include <vector>
#include <cmath>
#include "kontrolka.h"
template<typename T>
class suwak : public kontrolka
{
	protected:
		unsigned int roz; // rozdzielczosc suwaka- min 2
		float dlugosc; // dlugosc suwaka
		sf::RectangleShape linia; // linia suwaka
		sf::RectangleShape suw; // suwak
		sf::Rect<float> pol; // obszar suwaka
		std::vector<sf::Vector2f*> punkty; // punkty klikniec
		T pocz; // opcja przedzialu- poczatek
		T kon; // opcja przedzialu- koniec
		std::vector<T> elem; // opcja tablicy- tablica
		T* wart; // obecna wartosc suwaka
		void inic(const float _dlugosc); // inicjowanie suwaka
	public:
		// kontruktory
		suwak(T *wartosc, const sf::Vector2f pozycja, const float _dlugosc, const T poczatek, const T koniec, const unsigned int rozdzielczosc, const K_ZDARZENIE id = BRAK);
		suwak(T *wartosc, const sf::Vector2f pozycja, const float _dlugosc, const std::vector<T> tablica, const K_ZDARZENIE id = BRAK);
		~suwak();
		// funkcje
		void rysuj(sf::RenderWindow &okno, const sf::Time c_rzecz);
		bool klikniety(sf::RenderWindow &okno);
		sf::Vector2f rozmiary() const;
		T get_pocz() const; // zwraca wart poczatkowa
		T get_kon() const; // zwraca wart koncowa
		void set_poz(sf::Vector2f pozycja);
		void set_poz_r(sf::Vector2f pozycja);
		
};

#endif
