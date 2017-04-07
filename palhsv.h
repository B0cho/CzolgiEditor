#ifndef PALHSV_H
#define PALHSV_H
//
#include "kontrolka.h"
#include "bch/bch.hpp"
#include "flin_sf.h"
#include <math.h>
class palHSV : public kontrolka // 1.0
{
	private:
		/* dziedziczone
		sf::Vector2f poz;
		K_ZDARZENIE id;
		*/
		double H, S, V;
		double r; // promien
		sf::Vector2f point_pal; // pozycja wskaznika na palecie
		double point_suw; // pozycja wskaznika na suwaku
		sf::Color *kolor; // wskaznik  na kolor
		sf::VertexArray pal; // punkty palety
		sf::VertexArray suw; // punkty suwaka
		void reset(); //resetuje ustawienia kolorow palety i paska
		static sf::Color HSVtoRGB(double H, double S_100, double V_100); // konwersja hsv to rgb- _100, czyli od 0.0 do 1.0
		static double* RGBtoHSV(sf::Color kolor); // konwersja rgb to hsv
	public:
		/* dziedziczone
		void set_id(K_ZDARZENIE nowe_id);
		virtual void rysuj(sf::RenderWindow &okno, const sf::Time c_rzecz) = 0; // rysuje kontrolke na ekranie
		K_ZDARZENIE get_id() const; // zwraca id przycisku
		virtual bool klikniety(sf::RenderWindow &okno); // sprawdza, czy przycisk jest klikniety
		virtual sf::Vector2f rozmiary() const = 0;  // zwraca rozmiary kontrolki
		bool dis; // czy kontrolka jest wylaczona
		virtual void set_poz(sf::Vector2f pozycja) = 0;
		virtual void set_poz_r(sf::Vector2f pozycja) = 0;
		sf::Vector2f get_poz() const;
		*/
		palHSV(sf::Vector2f pozycja_wzgl_pal, const double promien_palety, sf::Color *wskaznik_na_kolor, const K_ZDARZENIE zdarzenie, sf::Color kolor_inic = sf::Color::White);
		~palHSV();
		void rysuj(sf::RenderWindow &okno, const sf::Time c_rzecz);
		bool klikniety(sf::RenderWindow &okno);
		sf::Vector2f rozmiary() const;
		void set_poz(sf::Vector2f pozycja); // nie robic
		void set_poz_r(sf::Vector2f pozycja); // nie robic
		bool setColor(sf::Color kolor); // ustawia kolor;
		sf::Color getColor() const; // zwraca kolor;
		static bool p_okr(sf::Vector2f &punkt, sf::Vector2f srodek_okr, double r, double kat); // zwraca wspolrzedne pkt na okregu
};

#endif
