#include "e_mapa.h"
//
vector<sf::Texture*> e_mapa::tex_gr1;
vector<sf::Texture*> e_mapa::tex_gr2;
vector<sf::Texture*> e_mapa::tex_bg;
e_mapa::e_mapa()
{
	this->Qu = sf::VertexArray(sf::Quads);	
	this->set = false;
	this->kolor_gr = sf::Color::White;
}
//
e_mapa::~e_mapa(){}
//
void e_mapa::set_new(e_edytor *ekran_tex, sf::Shape *tex_ikony[3])
{
	sf::Texture *wsk_p;
	if(this->tex_gr1.size()) // kalibrowanie tekstur gruntu
	{
		this->tekstura_gruntI = this->tex_gr1.begin(); // ustawienie domyslnej teks
		tex_ikony[0]->setTexture(*this->tekstura_gruntI); // ustawienie ikony
		ekran_tex->get_kontr(P_TEX_GR1_POPRZ)->dis = true; // zablokowanie kontrolki POPRZ
		if(this->tex_gr1.size() == 1) ekran_tex->get_kontr(P_TEX_GR1_NAST)->dis = true; // zablokowanie kontolki NAST jesli jest tylko jedna tekstura
	} 
	if(this->tex_gr2.size()) // kalibrowanie tekstur gruntu
	{
		this->tekstura_ziemiaI = this->tex_gr2.begin();
		tex_ikony[1]->setTexture(*this->tekstura_ziemiaI);
		ekran_tex->get_kontr(P_TEX_GR2_POPRZ)->dis = true;
		if(this->tex_gr2.size() == 1) ekran_tex->get_kontr(P_TEX_GR2_NAST)->dis = true;
	} 
	if(this->tex_bg.size()) // kalibrowanie tekstur gruntu
	{
		this->tekstura_tloI = this->tex_bg.begin();
		tex_ikony[2]->setTexture(*this->tekstura_tloI);
		ekran_tex->get_kontr(P_TEX_TLO_POPRZ)->dis = true;
		if(this->tex_bg.size() == 1) ekran_tex->get_kontr(P_TEX_TLO_NAST)->dis = true;
	}
	this->set = true;
}
//
bool e_mapa::mbp(const sf::Vector2f poz)
{
	if(this->pkt.size() > 2)
	{
		float x, y, z;
		vector<sf::Vector2f>::const_iterator it = this->pkt.end() - 2;
		sf::Vector2f m, m1;
		m1 = *it;
		m = this->pkt.back();
		flin_sf lf(m, m1);
		flin_sf ln(poz, m);
		if(!round(lf.a - ln.a))
		{
			y = flin_sf::p_odl(m, poz);
			z = flin_sf::p_odl(m, m1);
			x = flin_sf::p_odl(m1, poz);
			if((y > z && !round(y - x - z)) || (y < z && !round(z - x - y)) || (y == z && !x)) return false;
		}
		for(it = this->pkt.begin(); it < this->pkt.end() - 2; it++)
		{
			lf = flin_sf(*it, *(it+1));
			if(ln.i_m0(lf) == 1)
			{
				lf = flin_sf(*it, *(it+1));
				sf::Vector2f w = ln == lf;
				x = flin_sf::p_odl(m, w);
				y = flin_sf::p_odl(poz, m);
				z = flin_sf::p_odl(poz, w);
				if(bch::zawiera_sie_w(it->x, w.x, (it+1)->x) && !round(y - x - z)) return false;
			}
		}
		return true;
	}
	else
	{
		return true;
	}
}
//
void e_mapa::dodaj_punkt(sf::RenderWindow &okno, e_edytor* wsk)
{
	if(static_cast<e_edytor*>(wsk)->wPolu(okno))
	{
		sf::Vector2f poz = okno.mapPixelToCoords(sf::Mouse::getPosition(okno));
		wsk->kursor = new sf::CircleShape(5);
		wsk->kursor->setFillColor(sf::Color::Red);
		wsk->kursor->setOrigin(sf::Vector2f(5, 5));
		wsk->kursor->setPosition(poz);
		if(this->mbp(poz) && wsk->bor_lft <= poz && wsk->bor_dwn <= poz && wsk->bor_rgh >= poz && wsk->bor_up >= poz)
		{
			wsk->kursor->setFillColor(sf::Color::Green);
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				//
				if(this->pkt.size())
				{
					if(!(this->pkt.back().x - poz.x)) poz.x += 0.00001;
				}
				if(!this->pkt.size()) this->pkt.push_back(sf::Vector2f(0, poz.y));
				if(flin_sf::p_odl(this->pkt.back(), poz) > 10) this->pkt.push_back(poz);
			}
		}
	}
	else
	{
		wsk->kursor = new sf::CircleShape(0);
	}
}
//
sf::Color* e_mapa::get_gr_kolor()
{
	return &this->kolor_gr;
}
//
void e_mapa::rysuj(sf::RenderWindow &okno, e_edytor* wsk)
{
	sf::Sprite tlo; // tlo gry
	if(this->set) // ustawienie i rozszrzeszenie tla
	{
		tlo.setTexture(**this->tekstura_tloI);
		tlo.setPosition(sf::Vector2f(0, 40));
		sf::Vector2f skala;
		skala.x = 1500 / tlo.getGlobalBounds().width;
		skala.y = 950 / tlo.getGlobalBounds().height;
		tlo.scale(skala);
	}
	switch(wsk->tryb)
	{
		case RYSOWANIE: // tryb rysowania
			if(this->set) okno.draw(tlo);
			for(vector<sf::Vector2f>::const_iterator it = this->pkt.begin(); it != this->pkt.end(); it++)
			{
				sf::CircleShape punkt(5);
				punkt.setOrigin(sf::Vector2f(5, 5));
				sf::Vector2f pocz, kon;
				punkt.setPosition(*it);
				okno.draw(punkt);
				if(it != pkt.begin())
				{
					pocz = *(it - 1);
					kon = *it;
					flin_sf f(pocz, kon);
					f.rysuj(okno, {pocz.x, kon.x});
				}
			}
			break;
		case DEF: // tryb domyslny
			if(this->set)
			{
				okno.draw(tlo);
				okno.draw(this->Qu, *this->tekstura_gruntI);
				for(int i = 0; i < this->Tr.size(); i++) okno.draw(this->Tr[i], *this->tekstura_gruntI);
				for(vector<sf::Vector2f>::const_iterator it = this->pkt.begin(); it != this->pkt.end(); it++)
				{
					sf::Vector2f pocz, kon;
					if(it != pkt.begin()) okno.draw(flin_sf::linia(*(it-1), *it, 2, this->kolor_gr));
				}
			break;
		}
		case OBIEKT: // tryb dodawania/przemieszczania obiektów
			if(this->set)
			{
				okno.draw(tlo);
				okno.draw(this->Qu, *this->tekstura_gruntI);
				for(int i = 0; i < this->Tr.size(); i++) okno.draw(this->Tr[i], *this->tekstura_gruntI);
				for(vector<sf::Vector2f>::const_iterator it = this->pkt.begin(); it != this->pkt.end(); it++)
				{
					sf::Vector2f pocz, kon;
					if(it != pkt.begin()) okno.draw(flin_sf::linia(*(it-1), *it, 2, this->kolor_gr));
				}
				//
				/*
				if(this->wsk_o->rozmiary().x / 2 + 10 > this->wsk_o->Gpos().x
				|| -this->wsk_o->rozmiary().x / 2 + 1490 < this->wsk_o->Gpos().x
				|| this->wsk_o->rozmiary().y / 2 + 500 > this->wsk_o->Gpos().y) this->wsk_o->Scolor(sf::Color::Red);
				else this->wsk_o->Scolor(sf::Color::White);
				this->wsk_o->rysuj(okno);
				*/
			// jesli zawiera siê w oknie mapy
			if(flin_sf::zawiera_sie_w(this->wsk_o->Gmodel(), {sf::Vector2f(0, 40), sf::Vector2f(1500, 40), sf::Vector2f(1500, 1000), sf::Vector2f(0, 1000)})) this->wsk_o->rysuj(okno);
			{
				if(flin_sf::zawiera_sie_w(this->wsk_o->Gmodel(), {sf::Vector2f(10, 500), sf::Vector2f(1490, 500), sf::Vector2f(1490, 990), sf::Vector2f(10, 990)})) // gdy obiekt jest w granicach
				{
					// dopasowanie obiektu do mapy lub czerwien
					this->wsk_o->Scolor(sf::Color::Green);
				}
				else
				this->wsk_o->Scolor(sf::Color::Red); // gdy obiekt jest poza granicami
			}
			break;
		}
	}
}
//
bool e_mapa::spr()
{
	if(this->pkt.size())
	{
		sf::Vector2f w;
		w.x = 1500;
		w.y = this->pkt.back().y;
		if(this->mbp(w))
		{
			this->pkt.push_back(w);
		}
		else
		{
			return false;
		}
	}
	return true;
}
//
bool e_mapa::spr_def(e_edytor* wsk, sf::Font *czcionka_alert)
{
	
	sf::Texture t;
	if(!t.loadFromFile("res/def_tex_gr1.png") || !t.loadFromFile("res/def_tex_gr2.png") || !t.loadFromFile("res/def_tex_bg.png"))
	{
		e_alert *al = new e_alert(wsk, P_OK);
		al->dodaj_kontrolke(new tekst(L"BLAD: Brak domyslnych tekstur\n\nProgram nie znalazl podstawowych tekstur do obslugi mapy-\npliki mogly zostac usuniete badz przeniesione.\nUtracone tekstury nie beda wyswietlane.", *czcionka_alert, ekran::centruj_w(sf::Vector2f(0, 0), sf::Vector2f(1980, 900)), 30));
		al->dodaj_kontrolke(new przycisk(ekran::centruj_w(sf::Vector2f(0, 0), sf::Vector2f(1600, 1080)), *czcionka_alert, P_OK, L"OK", 50));
		wsk->nowy_alert(al);
		return false;
	}
	return true;
}
//
int e_mapa::i_pkt() const
{
	return this->pkt.size();
}
//
void e_mapa::czysc()
{
	this->pkt.clear();
	this->obiekty.clear();
	this->Qu = sf::VertexArray(sf::Quads);
	this->Tr.clear();
}
//
bool e_mapa::rdy_to_save() const
{
	return (this->pkt.size());
}
