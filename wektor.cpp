#include "wektor.h"
//
void buduj_strzalke(sf::RenderWindow &okno, sf::ConvexShape &grot, sf::ConvexShape &strzalka, float wartosc, const sf::Vector2f p_przylozenia, float kat, sf::Text &opis, const sf::Color kolor = sf::Color::White, const bool p_wart = false)
{
	if(wartosc)
	{
	if(wartosc < 0)
	{
		kat += 180;
		wartosc = -wartosc;
	} 
	sf::Vector2f wekt;
	//
	wekt.x -= wartosc - 10;
	grot.setPoint(0, wekt);
	wekt.y -= 5;
	grot.setPoint(1, wekt);
	wekt.y += 10;
	grot.setPoint(3, wekt);
	wekt.x -= 10;
	wekt.y = 0;
	grot.setPoint(2, wekt);
	grot.setRotation(kat);
	grot.setPosition(p_przylozenia);
	//
	wekt.x = wekt.y = 0;
	strzalka.setPoint(0, wekt);
	wekt.y += 2.5;
	strzalka.setPoint(7, wekt);
	wekt.y -= 5;
	strzalka.setPoint(1, wekt);
	wekt.x -= (wartosc - 10) / 2;
	strzalka.setPoint(2, wekt);
	wekt.y += 5;
	strzalka.setPoint(6, wekt);
	wekt.x *= 2;
	strzalka.setPoint(5, wekt);
	wekt.y -= 2.5;
	strzalka.setPoint(4, wekt);
	wekt.y -= 2.5;
	strzalka.setPoint(3, wekt);
	strzalka.setRotation(kat);
	strzalka.setPosition(p_przylozenia);
	//
	if(p_wart)
	{
		sf::Font def_font;
		sf::Rect<float> r;
		def_font.loadFromFile("arial.ttf");
		opis.setString(bch::to_string(wartosc) + " N");
		opis.setFont(def_font);
		opis.scale(0.5, 0.5);
		r = opis.getGlobalBounds();
		opis.setOrigin(r.width / 2, r.height / 2);
		if(bch::bzw_dgrs(kat) > 270 && bch::bzw_dgrs(kat) < 360 || bch::bzw_dgrs(kat) >= 0 && bch::bzw_dgrs(kat) < 90)
		{
			wekt.x = p_przylozenia.x - (wartosc - 10) / 2  * cos(bch::dgrs_to_rad(kat)) + 20 * sin(bch::dgrs_to_rad(kat));
			wekt.y = p_przylozenia.y - (wartosc - 10) / 2 * sin(bch::dgrs_to_rad(kat)) - 20 * cos(bch::dgrs_to_rad(kat));
			}
			else
			{
				wekt.x = p_przylozenia.x - (wartosc - 10) / 2 * cos(bch::dgrs_to_rad(kat)) - 20 * sin(bch::dgrs_to_rad(kat));
				wekt.y = p_przylozenia.y - (wartosc - 10) / 2 * sin(bch::dgrs_to_rad(kat)) + 20 * cos(bch::dgrs_to_rad(kat));
				kat -= 180;
				}
		opis.setRotation(kat);
		opis.setPosition(wekt);
		opis.setColor(kolor);
		okno.draw(opis);
	}
	//
	strzalka.setFillColor(kolor);
	grot.setFillColor(kolor);
	okno.draw(strzalka);
	okno.draw(grot);
	}
}
wektor::wektor(const float _wartosc, const float _kat, const sf::Vector2f _punkt, const float _poziom)
{
	this->wartosc = _wartosc;
	this->kat = _kat;
	this->punkt_przylozenia = _punkt;
	this->poziom = _poziom;
}
//
wektor::wektor(const sf::Vector2f poczatek, const sf::Vector2f koniec)
{
	float x, y;
	this->punkt_przylozenia = poczatek;
	this->poziom = 0;
	x = poczatek.x - koniec.x;
    y = poczatek.y - koniec.y;
    this->wartosc = sqrt(pow(x, 2) + pow(y, 2));
    this->kat = bch::rad_to_dgrs(atan2(y, x));
}
//
wektor::wektor()
{
	this->wartosc = 0;
}
void wektor::rysuj_wektor(sf::RenderWindow &okno, const sf::Color kolor, const bool skladowe, const bool pokaz_wartosc)
{
	sf::ConvexShape grot(4), strzalka(8);
	sf::Text op;
	buduj_strzalke(okno, grot, strzalka, this->wartosc, this->punkt_przylozenia, this->kat, op, kolor, pokaz_wartosc);
	if(skladowe)
	{
		sf::ConvexShape s_grot[2], s_strzalka[2];
		sf::Text s_op[2];
		float s_wart[2];
		s_grot[0].setPointCount(4);
		s_grot[1].setPointCount(4);
		s_strzalka[0].setPointCount(8);
		s_strzalka[1].setPointCount(8);
		s_wart[0] = cos(bch::dgrs_to_rad(bch::bzw_dgrs(this->kat - this->poziom))) * this->wartosc;
		s_wart[1] = sin(bch::dgrs_to_rad(bch::bzw_dgrs(this->kat - this->poziom))) * this->wartosc;
		buduj_strzalke(okno, s_grot[0], s_strzalka[0], s_wart[0], this->punkt_przylozenia, this->poziom, s_op[0], kolor, pokaz_wartosc);
		buduj_strzalke(okno, s_grot[1], s_strzalka[1], s_wart[1], this->punkt_przylozenia, this->poziom + 90, s_op[1], kolor, pokaz_wartosc);
		}
	}
//
void wektor::set_wart(const float _wart)
{
	this->wartosc = _wart;
}
//
void wektor::set_poziom(const float _kat)
{
	this->poziom = _kat;
}
//
void wektor::set_przyl(const sf::Vector2f _punkt_przylozenia)
{
	this->punkt_przylozenia = _punkt_przylozenia;
}
//
sf::Vector2f wektor::get_kon() const
{
             sf::Vector2f kon;
             kon.x = this->punkt_przylozenia.x - cos(bch::dgrs_to_rad(this->kat)) * this->wartosc;
             kon.y = this->punkt_przylozenia.y - sin(bch::dgrs_to_rad(this->kat)) * this->wartosc;
             return kon;
}
//
float wektor::get_kat() const
{
	return this->kat;
}
//
float wektor::get_wart() const
{
	return this->wartosc;
}
//
void wektor::set_kat(const float _kat)
{
	this->kat = _kat;
}
//
wektor wektor::operator+(wektor _wekt)
{
		sf::Vector2f poc, kon;
       	float kat, wartosc;
       	poc = this->punkt_przylozenia;
       	kon = this->get_kon();
       	_wekt.punkt_przylozenia = kon;
       	kon = _wekt.get_kon();
       	return wektor(poc, kon);
}
//
wektor wektor::operator!()
{
	wektor wek;
	wek.set_kat(wek.get_kat() - 180);
	return wek;
}
vector<wektor> wektor::get_skladowe() const
{
	vector<wektor> w;
	wektor skl1(0, this->poziom, this->punkt_przylozenia, this->poziom);
	wektor skl2(0, this->poziom + 90, this->punkt_przylozenia, this->poziom);
	skl1.set_wart(cos(bch::dgrs_to_rad(bch::bzw_dgrs(this->kat - this->poziom))) * this->wartosc);
	skl2.set_wart(sin(bch::dgrs_to_rad(bch::bzw_dgrs(this->kat - this->poziom))) * this->wartosc);
	w.push_back(skl1);
	w.push_back(skl2);
	return w;
	}
