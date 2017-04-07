#include "e_edytor.h"
//
e_edytor::e_edytor(const wstring _tytul, const EKRANY _id):menu(_tytul, _id)
{
	this->rys1 = sf::Vector2f(0, 40);
	this->rys2 = sf::Vector2f(1500, 960);
	this->rys = sf::Rect<float>(this->rys1, this->rys2);
	this->kursor = new sf::CircleShape(0);
	this->tryb = DEF;
	this->bor_dwn = flin_sf(0, 990);
	this->bor_up = flin_sf(0, 500);
	this->bor_lft = flin_sf(sf::Vector2f(10, 42), sf::Vector2f(10.001, 1000));
	this->bor_rgh = flin_sf(sf::Vector2f(1490, 45), sf::Vector2f(1490.01, 1002));
}
//
e_edytor::~e_edytor()
{
}
//
void e_edytor::rysuj(sf::RenderWindow &okno, const sf::Time c_rzecz)
{
	sf::VideoMode pulpit = sf::VideoMode::getDesktopMode();
	sf::RectangleShape linia[3];
	linia[0].setSize(sf::Vector2f(pulpit.width, 3));
	linia[0].setPosition(sf::Vector2f(0, 40));
	linia[1].setSize(sf::Vector2f(3, pulpit.height - 40));
	linia[1].setPosition(sf::Vector2f(1500, 40));
	linia[2].setSize(sf::Vector2f(1500, 3));
	linia[2].setPosition(sf::Vector2f(0, 1000));
	sf::Font czcionka_tytul;
	czcionka_tytul.loadFromFile("arial.ttf");
	tekst tytul(this->tytul, czcionka_tytul, sf::Vector2f(10, 6), 20);
	tytul.rysuj(okno, c_rzecz);
	tekst wersja(WERSJA, czcionka_tytul, sf::Vector2f(10, 1020), 20);
	wersja.rysuj(okno, c_rzecz);
	okno.draw(*(this->kursor));
	for(size_t i = 0; i <= 2; i++) okno.draw(linia[i]);
	if(this->tryb == RYSOWANIE || this->tryb == OBIEKT)
	{
		this->bor_dwn.rysuj(okno, {0, 1500}, sf::Color::Blue);
		this->bor_lft.rysuj(okno, {10, 10.001}, sf::Color::Blue);
		this->bor_rgh.rysuj(okno, {1490, 1490.01}, sf::Color::Blue);
		this->bor_up.rysuj(okno, {0, 1500}, sf::Color(127, 127, 127));
		
	}
	for(std::vector<sf::Shape*>::iterator it = this->ksztalty.begin(); it != this->ksztalty.end(); it++) okno.draw(**it);
	for(std::vector<kontrolka*>::iterator it = this->kontrolki.begin(); it != this->kontrolki.end(); it++) (**it).rysuj(okno, c_rzecz);
	if(this->jest_alert)
	{
		this->alert->rysuj(okno, c_rzecz);
	}
	}
//
bool e_edytor::wPolu(sf::RenderWindow &okno) const
{
	bool rezultat = this->rys.contains(okno.mapPixelToCoords(sf::Mouse::getPosition(okno)));
	return rezultat;
}
//
void e_edytor::set_tex(ekran *wsk, sf::Font &czcionka_alert, vector<sf::Texture*> &tex_gr1, vector<sf::Texture*> &tex_gr2, vector<sf::Texture*> &tex_bg)
{
	vector<string> gr1 = bch::path_list("./maps/TEXgr1", ".png", true), gr2 = bch::path_list("./maps/TEXgr2", ".png", true), bg = bch::path_list("./maps/TEXbg", ".png", true); // lokalizacje tekstur
	bool err = false; // bool errora
	string gr1_df = "", gr2_df = "", bg_df = ""; // string pomocniczy
	size_t i;
	sf::Texture *tex;
	if(bch::path_list("./res", ".png").size()) // sprawdzanie rozmiaru tekstur w pliku
	{
		vector<string> res = bch::path_list("./res", ".png"); // tablica tekstur dom
		for(size_t i = 0; i < res.size(); i++) // dodawanie poszczegolnych tekstur do lokalizacji
		{
			res[i] = "res/" + res[i];
			if(res[i] == TEX_GR1_PTH) gr1_df = res[i]; //gr1.push_back(res[i]);
			if(res[i] == TEX_GR2_PTH) gr2_df = res[i]; //.push_back(res[i]);
			if(res[i] == TEX_BG_PTH) bg_df = res[i]; //]bg.push_back(res[i]);
			}
	}
	else err = true; // wyjatek gdy nie istnieje ¿aden plik
	// sprawdzanie, czy istnieja domyslne pliki
	if(gr1_df != "") gr1.insert(gr1.begin(), gr1_df);
	else err = true;
	if(gr2_df != "") gr2.insert(gr2.begin(), gr2_df);
	else err = true;
	if(bg_df != "") bg.insert(bg.begin(), bg_df);
	else err = true;
	// reakcja na blad
	if(err)
	{
		e_alert *al = new e_alert(wsk, P_OK);
		al->dodaj_kontrolke(new tekst(L"BLAD: Brak domyslnych tekstur\n\nProgram nie znalazl podstawowych tekstur do obslugi mapy-\npliki mogly zostac usuniete badz przeniesione.\nUtracone tekstury nie beda wyswietlane.", czcionka_alert, ekran::centruj_w(sf::Vector2f(0, 0), sf::Vector2f(1980, 900)), 30));
		al->dodaj_kontrolke(new przycisk(ekran::centruj_w(sf::Vector2f(0, 0), sf::Vector2f(1600, 1080)), czcionka_alert, P_OK, L"OK", 50));
		wsk->nowy_alert(al);
	}
	//
	// dodawanie tekstur do tablic
	for(size_t i = 0; i < gr1.size(); i++)
	{
		tex = new sf::Texture;
		tex->loadFromFile(gr1[i]);
		tex->setRepeated(true);
		tex_gr1.push_back(tex);
	}
	for(size_t i = 0; i < gr2.size(); i++)
	{
		tex = new sf::Texture;
		tex->loadFromFile(gr2[i]);
		tex->setRepeated(true);
		tex_gr2.push_back(tex);
	}
	for(size_t i = 0; i < bg.size(); i++)
	{
		tex = new sf::Texture;
		tex->loadFromFile(bg[i]);
		tex->setRepeated(true);
		tex_bg.push_back(tex);
	}
}
//
void e_edytor::dis(list<K_ZDARZENIE> lista, bool s)
{
	for(auto i = lista.begin(); i != lista.end(); i++) this->get_kontr(*i)->dis = s;
}
