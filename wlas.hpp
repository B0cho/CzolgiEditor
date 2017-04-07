#ifndef WLAS
#define WLAS
#include<SFML/Graphics.hpp>
#include <string>
//
const float G = 10; // przyps graw[m^2/s]
const float METR = 5; // metr w pikselach
const std::wstring WERSJA= L"v. ALFA\nby Bochniarz >.<";
const sf::Time CZAS_PRZYCISK = sf::seconds(0.5); // czas reakcji przycisku
// sciezki
const std::string TEX_GR1_PTH = "res/def_tex_gr1.png"; // domyslna gruntu
const std::string TEX_GR2_PTH = "res/def_tex_gr2.png"; // domyslna gruntu2
const std::string TEX_BG_PTH = "res/def_tex_bg.png"; // domyslna tla

//
enum EKRANY
{
	INNY, // domyslny, bezwartosciowy ekran
	// GRA
	M_GLOWNE, // menu glowne gry
	M_PAUZA, // menu pauzy gry
	// EDYTOR
	E_START, // ekran startowy edytora
	E_NOWY_TEREN, // ekran tworzenia nowej mapy- teren
	E_NOWY_TEREN2, // ekran tworzenia nowej mapy- kolory
	E_NOWY_OBIEKTY,
	E_POTW 
	
};
//
enum K_ZDARZENIE
{
	BRAK, // brak przypisanego zdarzenia
	P_WYJSCIE, // przycisk wyjscia
	// GRA
	
	//EDYTOR
	P_NOWY, // przycisk nowy
	P_OTWORZ, // przycisk otworz
	P_ZAPISZ,
	P_NAST,
	P_POPRZ,
	P_RYSUJ,
	P_GOTOW,
	P_POMRYS,
	S_WYTRZ,
	T_WYTRZ,
	P_OK,
	P_CZYSC,
	P_TEX_GR1_POPRZ, // przycisk poprzedni przy teksturze gruntu
	P_TEX_GR1_NAST, // przycisk nastepny przy teksturze gruntu
	P_TEX_GR2_POPRZ, // przycisk poprzedni przy teksturze gruntu- ziemii
	P_TEX_GR2_NAST, // przycisk nastepny przy teksturze gruntu
	P_TEX_TLO_POPRZ, // przycisk poprzedni przy teksturze tla
	P_TEX_TLO_NAST, // przycisk nastepny przy teksturze tla
	P_SKRZYNIA // ikona skrzyni
};
//
#endif
