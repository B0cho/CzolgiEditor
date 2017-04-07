#ifndef MENU_H
#define MENU_H
//
#include <string>
#include "wektor.h"
#include "przycisk.h"
#include "ekran.h"
#include "kontrolka.h"
#include "tekst.h"
class menu : public ekran
{
	protected:
		std::wstring tytul; // tytul okna
	public:
		//kontruktory
		menu(ekran *_rodzic, const wstring _tytul, const EKRANY _id);
		menu(const wstring _tytul, const EKRANY _id);
		~menu();
		// funkcje
		void rysuj(sf::RenderWindow &okno, const sf::Time c_rzecz); // rysuje okno
		//void go_rodzic(ekran *&wsk, sf::RenderWindow &okno); // wraca do rodzica
};

#endif
