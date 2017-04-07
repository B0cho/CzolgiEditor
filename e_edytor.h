#ifndef E_EDYTOR_H
#define E_EDYTOR_H
//
#include "tekst.h"
#include "menu.h"
#include "e_alert.h"
#include "flin_sf.h"
//#include "e_mapa.h"
#include <vector>
#include <list>
class e_mapa;
enum E_EDYTOR_TRYB // tryby ekranu
{
	DEF,
	RYSOWANIE,
	OBIEKT
};
class e_edytor : public menu
{
	friend class e_mapa; // klasa zaprzyjazniona
	protected:
		sf::Rect<float> rys; //
		sf::Vector2f rys1,  rys2;
		flin_sf bor_up, bor_dwn, bor_lft, bor_rgh; // granice na ekranie
		// id
		//kontroki
	public:
		E_EDYTOR_TRYB tryb; // tryb ekranu
		e_edytor(const wstring _tytul, const EKRANY _id); // konstruktor - tytul ekranu i jego ID
		~e_edytor();
		void rysuj(sf::RenderWindow &okno, const sf::Time c_rzecz); // rysuje ekran
		bool wPolu(sf::RenderWindow &okno) const;
		void dis(list<K_ZDARZENIE> lista, bool s = true);
		//get_id
		//go_rodzice
		static void set_tex(ekran *wsk, sf::Font &czcionka_alert, vector<sf::Texture*> &tex_gr1, vector<sf::Texture*> &tex_gr2, vector<sf::Texture*> &tex_bg); // ustawia tekstury
};

#endif
