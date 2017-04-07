#ifndef E_MAPA_H
#define E_MAPA_H
//
#include "map.h"
#include "e_edytor.h"
#include "e_alert.h"
#include "obiekt.h"
//
#include <iostream>
#include <math.h>
class e_mapa : public mapa
{
	friend obiekt;
	private:
		bool mbp(const sf::Vector2f poz); // sprawdza, czy mo¿na dodaæ punkt do mapy
		bool set;	
		/* dziedziczone
		bool edit; // czy mapa jest edytowalna
		float destr; // wspolczynnik zniszczalnosci gruntu
		vector<obiekt*> obiekty; // tablica obiektow
		sf::Texture tekstura_grunt; // tekstura gruntu
		sf::Texture tekstura_ziemia; // tekstura ziemii
		sf::Texture tekstura_tlo; // tekstura tla
		sf::VertexArray Tr; // punkty gruntu- trojkaty
		sf::VectexArray Qu; // punkty gruntu- czworokaty
		vector<sf::Vector2f> pkt; // zawiera punkty na mapie
		
		bool TR(const vector<sf::Vector2f>::iterator pocz, const vector<sf::Vector2f>::iterator kon); // dzieli na trojkaty dany obszar
		static bool w_linii(const sf::Vector2f a, const sf::Vector2f X, const sf::Vector2f b); // sprawdza, czy X miesci sie w przedziale a i b pod wzgledem x i y
		*/
	public:
		e_mapa();
		~e_mapa();
		void set_new(e_edytor *ekran_tex, sf::Shape *tex_ikony[3]); // kalibrowanie nowej mapy(tekstury itd)
		void dodaj_punkt(sf::RenderWindow &okno, e_edytor* wsk); // dodaje punkt do mapy
		void rysuj(sf::RenderWindow &okno, e_edytor* wsk); // odpowiada za rysowanie mapy
		sf::Color* get_gr_kolor(); // zwraca wskaŸnik do wspó³czynnika znisczalnosci terenu
		static bool spr_def(e_edytor* wsk, sf::Font *czcionka_alert); // sprawdza, czy dostepne sa domyslne czcionki
		bool spr(); // sprawdza, czy wszystkie punkty zosta³y dobrze umiejscowione
		int i_pkt() const; // zwraca ilosc punktow w tablicy
		void czysc(); // czysci dana mape
		bool rdy_to_save() const; // sprawdza, czy mape mozna zapisac
		static vector<sf::Texture*> tex_gr1, tex_gr2, tex_bg; // tekstury, wspólne dla wszystkich obiektów klasy
		vector<sf::Texture*>::const_iterator tekstura_gruntI, tekstura_ziemiaI, tekstura_tloI; // tekstury
		obiekt *wsk_o; // wskaznik na przetrzymywany obiekt
		/* dziedziczone
		bool konw_tex(); // konwertuje do textury
		*/
};

#endif
