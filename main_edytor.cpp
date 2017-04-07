#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "bch/bch.hpp"
#include "obiekt.h"
#include "przycisk.h"
#include "tekst.h"
#include "menu.h"
#include "ekran.h"
#include "przelacznik.h"
#include "e_edytor.h"
#include "suwak.h"
#include "e_mapa.h"
#include "e_alert.h"
#include "flin_sf.h"
#include "palhsv.h"
//#include "skrzynia.h"
#include "ikona_obiekt.h"
int main()
{
	//// Okno
	sf::VideoMode pulpit = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(pulpit, "Czolgi EDYTOR MAP");
    sf::Clock zegar;
    sf::Font def_font;
    e_mapa mapa;
    sf::Shape *tex_ikony[3]; // ikony tekstur
    //vector<string> tex_gr1, tex_gr2, tex_tlo; // tekstury gruntu i tla
    //vector<sf::Texture> tex_gr1, tex_gr2, tex_bg; // tekstury gruntu i tla
    //// Czcionki
    
    def_font.loadFromFile("arial.ttf");
    //// Ekrany
    ekran *wsk; // wskaznik ekranu
    e_edytor start(L"Edytor", E_START);
    e_edytor nowy_t(L"Edytor- NOWA MAPA", E_NOWY_TEREN);
    e_edytor nowy_t2(L"Edytor- NOWA MAPA", E_NOWY_TEREN2);
    e_edytor nowy_o(L"Edytor- NOWA MAPA", E_NOWY_OBIEKTY);
    
 	wsk = &start; // ustawienie ekranu poczatkowego
 	//// Kontrolki
 	kontrolka *a;
 	sf::Shape *k;
 	sf::Vector2f w;
 	// ekrant start
 	start.dodaj_kontrolke(new przycisk(sf::Vector2f(1710, 1040), def_font, P_WYJSCIE, L"WYJSCIE", 40));
 	start.dodaj_kontrolke(new przycisk(sf::Vector2f(1050, 1040), def_font, P_NOWY, L"NOWY", 40));
 	start.dodaj_kontrolke(new przycisk(sf::Vector2f(1300, 1040), def_font, P_OTWORZ, L"OTWORZ", 40));
 	start.dodaj_kontrolke(new tekst(L"Utworz\nlub\nedytuj\nistniejaca mape!", def_font, sf::Vector2f(1530, 60), 50));
 	// ekran obiekty i teren1
 	a = new przycisk(sf::Vector2f(1710, 1040), def_font, P_WYJSCIE, L"WYJSCIE", 40);
 	nowy_t.dodaj_kontrolke(a);
 	nowy_o.dodaj_kontrolke(a);
 	a = new przycisk(sf::Vector2f(820, 1040), def_font, P_ZAPISZ, L"ZAPISZ", 40);
 	nowy_t.dodaj_kontrolke(a);
 	nowy_o.dodaj_kontrolke(a);
 	a = new przycisk(sf::Vector2f(1050, 1040), def_font, P_NOWY, L"NOWY", 40);
 	nowy_t.dodaj_kontrolke(a);
 	nowy_o.dodaj_kontrolke(a);
 	a = new przycisk(sf::Vector2f(1300, 1040), def_font, P_OTWORZ, L"OTWORZ", 40);
 	nowy_t.dodaj_kontrolke(a);
 	nowy_o.dodaj_kontrolke(a);
 	a = new przycisk(sf::Vector2f(1700, 100), def_font, BRAK, L"TEREN", 40, sf::Color::White);
 	a->dis = true;
 	nowy_t.dodaj_kontrolke(a);
 	a = new przycisk(sf::Vector2f(1700, 100), def_font, BRAK, L"OBIEKTY", 40, sf::Color::White);
 	a->dis = true;
 	nowy_o.dodaj_kontrolke(a);
 	nowy_t.dodaj_kontrolke(new przelacznik(sf::Vector2f(1550, 100), P_POPRZ));
 	nowy_t.dodaj_kontrolke(new przelacznik(sf::Vector2f(1850, 100), P_NAST, 180));
 	nowy_o.dodaj_kontrolke(new przelacznik(sf::Vector2f(1550, 100), P_POPRZ));
 	nowy_o.dodaj_kontrolke(new przelacznik(sf::Vector2f(1850, 100), P_NAST, 180));
 	a = nowy_t.get_kontr(P_ZAPISZ);
 	a->dis = true;
 	a = nowy_t.get_kontr(P_POPRZ);
	a->dis = true;
	a = nowy_o.get_kontr(P_NAST);
	a->dis = true;
	//
	sf::Vector2f m1(1500, 160);
	sf::Vector2f m2(1900, 160);
	k = new sf::RectangleShape(sf::Vector2f(400, 1));
	k->setPosition(ekran::centruj_w(m1, sf::Vector2f(1540, m1.y)));
	nowy_t.dodaj_ksztalt(k);
	m1.y += 10;
	m2.y += 10;
	nowy_t.dodaj_kontrolke(new tekst(L"Rysuj teren", def_font, ekran::centruj_w(m1, sf::Vector2f(1540, m1.y)), 25));
	m1.y += 50;
	m2.y += 100;
	nowy_t.dodaj_kontrolke(new przycisk(ekran::centruj_w(m1, m2), def_font, P_RYSUJ, L"Rysuj", 40));
	nowy_t.dodaj_kontrolke(new przycisk(ekran::centruj_w(sf::Vector2f(1800, 220), sf::Vector2f(1900, 270)), def_font, P_POMRYS, L"?", 40));
	m1.y += 70;
	m2.y += 70;
	k = new sf::RectangleShape(sf::Vector2f(400, 1));
	k->setPosition(ekran::centruj_w(m1, sf::Vector2f(1540, m1.y)));
	nowy_t.dodaj_ksztalt(k);
	m1.y += 10;
	m2.y += 10;
	nowy_t.dodaj_kontrolke(new tekst(L"Tekstura gruntu", def_font, ekran::centruj_w(m1, sf::Vector2f(1540, m1.y)), 25)); // naglowek tekstury gruntu
	nowy_t.dodaj_kontrolke(new przelacznik(sf::Vector2f(1540, 400), P_TEX_GR1_POPRZ, 0, 20)); // przycisk poprzedni tekstury gruntu
	nowy_t.dodaj_kontrolke(new przelacznik(sf::Vector2f(1890, 400), P_TEX_GR1_NAST, 180, 20)); // przycisk nastepny tekstury gruntu
	tex_ikony[0] = new sf::RectangleShape(sf::Vector2f(300, 100)); // ikona gruntu
	tex_ikony[0]->setPosition(sf::Vector2f(1565, 350));
	k = new sf::RectangleShape(sf::Vector2f(400, 1)); // linia miedzy tekstura gruntu1 a gruntu 2;
	k->setPosition(sf::Vector2f(1520, 470));
	nowy_t.dodaj_ksztalt(k);
	nowy_t.dodaj_kontrolke(new tekst(L"Tekstura gruntu- ziemia", def_font, sf::Vector2f(1520, 480), 25)); // naglowek tekstury gruntu-ziemii
	nowy_t.dodaj_kontrolke(new przelacznik(sf::Vector2f(1540, 570), P_TEX_GR2_POPRZ, 0, 20)); // przycisk poprzedni tekstury gruntu
	nowy_t.dodaj_kontrolke(new przelacznik(sf::Vector2f(1890, 570), P_TEX_GR2_NAST, 180, 20)); // przycisk nastepny tekstury gruntu
	tex_ikony[1] = new sf::RectangleShape(sf::Vector2f(300, 100)); // ikona gruntu-ziemii
	tex_ikony[1]->setPosition(sf::Vector2f(1565, 520));
	k = new sf::RectangleShape(sf::Vector2f(400, 1)); // linia miedzy tekstura gruntu 2 a tlo
	k->setPosition(sf::Vector2f(1520, 640));
	nowy_t.dodaj_ksztalt(k);
	nowy_t.dodaj_kontrolke(new tekst(L"Tekstura tla", def_font, sf::Vector2f(1520, 650), 25));
	nowy_t.dodaj_kontrolke(new przelacznik(sf::Vector2f(1600, 960), P_TEX_TLO_POPRZ, 0, 20)); // przycisk poprzedni tekstury gruntu
	nowy_t.dodaj_kontrolke(new przelacznik(sf::Vector2f(1830, 960), P_TEX_TLO_NAST, 180, 20)); // przycisk nastepny tekstury gruntu
	tex_ikony[2] = new sf::RectangleShape(sf::Vector2f(385, 230));
	tex_ikony[2]->setPosition(sf::Vector2f(1520, 700));
	for(int licznik = 0; licznik < 3; licznik++) nowy_t.dodaj_ksztalt(tex_ikony[licznik]); // dodawanie ikon
	// ekran2 
	nowy_t2.dodaj_kontrolke(new przycisk(sf::Vector2f(1710, 1040), def_font, P_WYJSCIE, L"WYJSCIE", 40));
 	nowy_t2.dodaj_kontrolke(new przycisk(sf::Vector2f(1050, 1040), def_font, P_NOWY, L"NOWY", 40));
 	nowy_t2.dodaj_kontrolke(new przycisk(sf::Vector2f(1300, 1040), def_font, P_OTWORZ, L"OTWORZ", 40));
 	nowy_t2.dodaj_kontrolke(new przycisk(sf::Vector2f(820, 1040), def_font, P_ZAPISZ, L"ZAPISZ", 40));
 	nowy_t2.dodaj_kontrolke(new przelacznik(sf::Vector2f(1550, 100), P_POPRZ));
 	nowy_t2.dodaj_kontrolke(new przelacznik(sf::Vector2f(1850, 100), P_NAST, 180));
 	a = new przycisk(sf::Vector2f(1700, 100), def_font, BRAK, L"KOLORY", 40, sf::Color::White);
 	a->dis = true;
 	nowy_t2.dodaj_kontrolke(a);
 	k = new sf::RectangleShape(sf::Vector2f(400, 1));
 	k->setPosition(sf::Vector2f(1520, 160));
 	nowy_t2.dodaj_ksztalt(k);
 	nowy_t2.dodaj_kontrolke(new tekst(L"Krawedz gruntu", def_font, sf::Vector2f(1520, 170), 25));
 	nowy_t2.dodaj_kontrolke(new palHSV(sf::Vector2f(1720, 380), 150, mapa.get_gr_kolor(), BRAK)); // paleta HSV
 	//obiekty
 	nowy_o.dodaj_ksztalt(k);
	nowy_o.dodaj_kontrolke(new tekst(L"Obiekty- gracze", def_font, sf::Vector2f(1520, 170), 25));
	nowy_o.dodaj_kontrolke(new ikona_obiekt(sf::Vector2f(1620, 300), P_SKRZYNIA, 100, SKRZYNIA));
	// inicjalizacja tekstur
	e_edytor::set_tex(wsk, def_font, mapa.tex_gr1, mapa.tex_gr2, mapa.tex_bg);
 	//// petla
	while (window.isOpen())
    {
		sf::Event event;
		//
        K_ZDARZENIE zdarzenie; // zmienna zdarzenia
        kontrolka *kontrl; // wskaznik do aktywnej kontrolki
        sf::Time czas_petla = zegar.restart(); // czas wykonania petli
        //
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            // zdarzenia wlasne
            zdarzenie = (*wsk).get_aktywny(event, window, kontrl);
            // ZDARZENIA OGO£NE
            if(wsk->get_id() == E_NOWY_TEREN || wsk->get_id() == E_NOWY_TEREN2 || wsk->get_id() == E_NOWY_OBIEKTY) if(static_cast<e_edytor*>(wsk)->tryb == DEF) wsk->get_kontr(P_ZAPISZ)->dis = (mapa.rdy_to_save()) ? false : true; // warunek dla ktorego p_zapisz ma byc wlaczony
            if(!mapa.i_pkt() || static_cast<e_edytor*>(wsk)->tryb == OBIEKT) nowy_o.dis({P_SKRZYNIA}); else nowy_o.dis({P_SKRZYNIA}, false); // blokowanie ikon w zaleznosci od ikon mapy
			switch((*wsk).get_id())
            {
            	case E_START: // zdarzenia w menu glownym
            		if(zdarzenie == P_WYJSCIE) window.close(); // klikniecie WYJSCIE
            		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) (*wsk).go_rodzic(wsk, window);
            		if(zdarzenie == P_NOWY)
					{
						mapa.set_new(&nowy_t, tex_ikony);// setting dla nowej mapy
						wsk = &nowy_t; // kliniecie NOWY
						break;
					} 
            		if(zdarzenie == P_OTWORZ); // klikniecie OTWORZ
            		break;
            	case E_NOWY_TEREN: // zdarzenia w ekranie nowej mapy
            		
            		if(zdarzenie == P_WYJSCIE) // klikniecie WYJSCIE
            		{
            			//
            		}
            		if(zdarzenie == P_NAST) // klikniecie NASTEPNY
            		{
            			wsk = &nowy_t2;
						//kontrl = wsk->get_kontr(BRAK);
						//static_cast<przycisk*>(kontrl)->set_etykieta(L"OBIEKTY");
						break;
            		}
            		if(zdarzenie == P_POMRYS) // KLIKNIECIE NA POMOC RYSOWANIA
            		{
            			e_alert *al = new e_alert(wsk, P_OK);
            			kontrl = new przycisk(ekran::centruj_w(sf::Vector2f(0, 0), sf::Vector2f(1920, 1500)), def_font, P_OK, L"OK", 40);
            			// tekst do kontrolki
            			al->dodaj_kontrolke(kontrl);
            			wsk->nowy_alert(al);
            		}
            		if(zdarzenie == P_GOTOW && static_cast<e_edytor*>(wsk)->tryb == RYSOWANIE) // klikniecie na GOTOWE w trybie RYSOWANIE
					{
            			#define wc1 sf::Vector2f(0,0)
						#define wc2 1600
						#define mg 100
            			if(!mapa.spr())
            			{
            				vector<K_ZDARZENIE> k_zd;
            				k_zd.push_back(P_OK);
            				k_zd.push_back(P_CZYSC);
							e_alert *komunikat = new e_alert(wsk, k_zd);
            				komunikat->dodaj_kontrolke(new tekst(L"Cos musisz poprawic...", def_font, ekran::centruj_w(wc1, sf::Vector2f(wc2, 500)), 50));
            				komunikat->dodaj_kontrolke(new tekst(L"Zadna z linii terenu nie moze sie przecinac.\nOstatni punkt musi byc najbardziej wysuniety na prawo, aby zamknac mape!", def_font, ekran::centruj_w(wc1, sf::Vector2f(wc2, 700)), 30));
            				komunikat->dodaj_kontrolke(new przycisk(ekran::centruj_w(wc1, sf::Vector2f(wc2 - 300, 600)), def_font, P_OK, L"OK", 50));
            				komunikat->dodaj_kontrolke(new przycisk(ekran::centruj_w(wc1, sf::Vector2f(wc2 - 300, 750)), def_font, P_CZYSC, L"Wyczysc", 50));
            				wsk->nowy_alert(komunikat);
            			}
            			else
            			{
            				static_cast<e_edytor*>(wsk)->tryb = DEF;
            				wsk->del_kontrl(P_GOTOW);
            				kontrl = wsk->get_kontr(P_CZYSC);
            				std::wstring et = L"Rysuj";
            				K_ZDARZENIE kzd = P_RYSUJ;
							if(mapa.i_pkt()) 
							{
								et = L"Wyczysc";
								kzd = P_CZYSC;
								mapa.konw_tex();
							}
							static_cast<przycisk*>(kontrl)->set_etykieta(et);
							kontrl->set_id(kzd);
            				kontrl->dis = false;
            				sf::Vector2f poz = kontrl->get_poz();
							kontrl->set_poz_r(sf::Vector2f(poz.x - mg + 45, poz.y));
							static_cast<przycisk*>(wsk->get_kontr(P_ZAPISZ))->dis = false;
							static_cast<przycisk*>(wsk->get_kontr(P_NAST))->dis = false;
            			}
					}
            		if(zdarzenie == P_RYSUJ && static_cast<e_edytor*>(wsk)->tryb == DEF)// klikniecie na RYSUJ w trybie DOMYSLNYM
            		{
            			static_cast<e_edytor*>(wsk)->tryb = RYSOWANIE;
            			kontrl = wsk->get_kontr(P_RYSUJ);
            			przycisk *psk = static_cast<przycisk*>(kontrl);
            			psk->set_etykieta(L"Gotowe");
            			psk->set_id(P_GOTOW);
            			sf::Vector2f poz = psk->get_poz();
            			psk->set_poz_r(sf::Vector2f(poz.x - mg, poz.y));
            			psk = new przycisk(sf::Vector2f(poz.x + mg - 45, poz.y), def_font, P_CZYSC, L"Czysc", 40);
            			psk->dis = true;
            			wsk->dodaj_kontrolke(psk);
            			static_cast<przycisk*>(wsk->get_kontr(P_ZAPISZ))->dis = true;
            			static_cast<przycisk*>(wsk->get_kontr(P_NAST))->dis = true;
            		}
            		if(static_cast<e_edytor*>(wsk)->tryb == RYSOWANIE && !wsk->jest_alert) // instrukcje dla trybu RYSOWANIA i braku ALERTU
            		{
            			mapa.dodaj_punkt(window, static_cast<e_edytor*>(wsk));
            			wsk->get_kontr(P_CZYSC)->dis = (mapa.i_pkt()) ? false : true;
            		}
					if(zdarzenie == P_CZYSC) // klikniecie na CZYSC
					{
						mapa.czysc();
						if(static_cast<e_edytor*>(wsk)->tryb == DEF)
						{
								kontrl = wsk->get_kontr(P_CZYSC);
								kontrl->set_id(P_RYSUJ);
								static_cast<przycisk*>(kontrl)->set_etykieta(L"Rysuj");
						}
					}
					if(zdarzenie == P_TEX_GR1_POPRZ) // klikniecie na poprzedni tekstury gruntu
					{
						if(--mapa.tekstura_gruntI == e_mapa::tex_gr1.begin()) wsk->get_kontr(P_TEX_GR1_POPRZ)->dis = true;
						if(mapa.tekstura_gruntI != e_mapa::tex_gr1.end() - 1) wsk->get_kontr(P_TEX_GR1_NAST)->dis = false;
						tex_ikony[0]->setTexture(*mapa.tekstura_gruntI, true);
					}
					if(zdarzenie == P_TEX_GR1_NAST) // klikniecie na nastepny tekstury gruntu
					{
						if(++mapa.tekstura_gruntI == e_mapa::tex_gr1.end() - 1) wsk->get_kontr(P_TEX_GR1_NAST)->dis = true;
						if(mapa.tekstura_gruntI != e_mapa::tex_gr1.begin()) wsk->get_kontr(P_TEX_GR1_POPRZ)->dis = false;
						tex_ikony[0]->setTexture(*mapa.tekstura_gruntI, true);
					}
					if(zdarzenie == P_TEX_GR2_POPRZ) // klikniecie na poprzedni tekstury ziemii
					{
						if(--mapa.tekstura_ziemiaI == e_mapa::tex_gr2.begin()) wsk->get_kontr(P_TEX_GR2_POPRZ)->dis = true;
						if(mapa.tekstura_ziemiaI != e_mapa::tex_gr2.end() - 1) wsk->get_kontr(P_TEX_GR2_NAST)->dis = false;
						tex_ikony[1]->setTexture(*mapa.tekstura_ziemiaI, true);
					}
					if(zdarzenie == P_TEX_GR2_NAST) // klikniecie na nastepny tekstury gruntu
					{
						if(++mapa.tekstura_ziemiaI == e_mapa::tex_gr2.end() - 1) wsk->get_kontr(P_TEX_GR2_NAST)->dis = true;
						if(mapa.tekstura_ziemiaI != e_mapa::tex_gr2.begin()) wsk->get_kontr(P_TEX_GR2_POPRZ)->dis = false;
						tex_ikony[1]->setTexture(*mapa.tekstura_ziemiaI, true);
					}
					if(zdarzenie == P_TEX_TLO_POPRZ) // klikniecie na poprzedni tekstury ziemii
					{
						if(--mapa.tekstura_tloI == e_mapa::tex_bg.begin()) wsk->get_kontr(P_TEX_TLO_POPRZ)->dis = true;
						if(mapa.tekstura_tloI != e_mapa::tex_bg.end() - 1) wsk->get_kontr(P_TEX_TLO_NAST)->dis = false;
						tex_ikony[2]->setTexture(*mapa.tekstura_tloI, true);
					}
					if(zdarzenie == P_TEX_TLO_NAST) // klikniecie na nastepny tekstury gruntu
					{
						if(++mapa.tekstura_tloI == e_mapa::tex_bg.end() - 1) wsk->get_kontr(P_TEX_TLO_NAST)->dis = true;
						if(mapa.tekstura_tloI != e_mapa::tex_bg.begin()) wsk->get_kontr(P_TEX_TLO_POPRZ)->dis = false;
						tex_ikony[2]->setTexture(*mapa.tekstura_tloI, true);
					}
					
					
					// 
					//e_edytor em();
					//if(stati)
			//wsk->get_kontr(P_CZYSC)->dis = (mapa.i_pkt()) ? false : true; // COS TU JEST NIE TAK
					
					
					break;
				case E_NOWY_TEREN2:
					if(zdarzenie == P_POPRZ) wsk = &nowy_t;
					if(zdarzenie == P_NAST) wsk = &nowy_o;
					//if(static_cast<e_edytor*>(wsk)->tryb == DEF) wsk->get_kontr(P_ZAPISZ)->dis = (mapa.rdy_to_save()) ? false : true; // warunek dla ktorego p_zapisz ma byc wlaczony
					
				
					break;
            	case E_NOWY_OBIEKTY:
            		if(zdarzenie == P_POPRZ) wsk = &nowy_t2;
            		if(zdarzenie == P_SKRZYNIA)
					{
						static_cast<e_edytor*>(wsk)->tryb = OBIEKT;
						static_cast<e_edytor*>(wsk)->dis({P_NAST, P_POPRZ});
						mapa.wsk_o = new skrzynia(sf::Vector2f(0, 0), 100, 75);
						
					}
					if(static_cast<e_edytor*>(wsk)->tryb == OBIEKT && !wsk->jest_alert) // instrukcje dla trybu OBIEKT i braku ALERTU
            		{
            			mapa.wsk_o->ustaw(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
            			//mapa.wsk_o->rysuj(window);
            		} 
            
            		break;
            }
        }
        window.clear();
		//
		mapa.rysuj(window, static_cast<e_edytor*>(wsk)); // rysowanie mapy
		wsk->rysuj(window, czas_petla); // rysowanie poszcegolnego ekranu
		
		//
		window.display();
    }
    return 0;
}
