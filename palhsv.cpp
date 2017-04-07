#include "palhsv.h"
//
palHSV::palHSV(sf::Vector2f pozycja_wzgl_pal, const double promien_palety, sf::Color *wskaznik_na_kolor, const K_ZDARZENIE zdarzenie, sf::Color kolor_inic):kontrolka(pozycja_wzgl_pal, zdarzenie)
{
	if(promien_palety > 0)
	{
		this->kolor = wskaznik_na_kolor;
		this->r = promien_palety;
		// inicjalizacja kolorow
		double *kl = this->RGBtoHSV(kolor_inic);
		this->H = kl[0];
		this->S = kl[1];
		this->V = kl[2];
		// inicjalizacja palety
		this->pal = sf::VertexArray(sf::TrianglesFan);
		sf::Vertex vert;
		sf::Vector2f punkt;
		vert.position = this->poz;
		vert.color = this->HSVtoRGB(0, 0, this->V);
		this->pal.append(vert);
		int ilosc = round(M_PI * r);
		double kat = 360 / round(M_PI * r);
		for(int i = 0; i < ilosc; i++)
		{
			this->p_okr(punkt, this->poz, this->r, i * kat);
			vert.position = punkt;
			vert.color = this->HSVtoRGB(i * kat, 1, this->V);
			this->pal.append(vert);
		}
		this->pal.append(this->pal[1]); // dodawanie ostatniego
		// inicjalizacja suwaka
		this->suw = sf::VertexArray(sf::Quads);
		vert.position = sf::Vector2f(this->poz.x - 0.9 * r, this->poz.y + 1.16 * r);
		vert.color = this->HSVtoRGB(this->H, this->S, 0);
		this->suw.append(vert);
		vert.position.x += 1.8 * r;
		vert.color = this->HSVtoRGB(this->H, this->S, 1);
		this->suw.append(vert);
		vert.position.y += 0.33 * r;
		this->suw.append(vert);
		vert.position.x -= 1.8 * r;
		vert.color = this->HSVtoRGB(this->H, this->S, 0);
		this->suw.append(vert);
		// ustawienie wskaznika koloru
		this->p_okr(this->point_pal, this->poz, this->S * this->r, this->H);
		this->point_suw = this->suw[0].position.x + this->V * (this->suw[1].position.x - this->suw[0].position.x);
		}
}
//
palHSV::~palHSV(){}
//
bool palHSV::p_okr(sf::Vector2f &punkt, sf::Vector2f srodek_okr, double r, double kat)
{
	if(r >= 0)
	{
		kat = bch::dgrs_to_rad(kat);
		punkt = sf::Vector2f(srodek_okr.x + r * sin(kat), srodek_okr.y + r * cos(kat));
		return true;
	}
	else return false;
}
//
sf::Color palHSV::HSVtoRGB(double H, double S_100, double V_100)
{
	sf::Color k;
	H /= 60;
	double i = floor(H);
	double f = H - i;
	double p = V_100 * (1 - S_100);
	double q = V_100 * (1 - (S_100 * f));
	double t = V_100 * (1 - (S_100 * (1 - f)));
	if(i == 0)
	{
		k.r = V_100 * 255;
		k.g = t * 255;
		k.b = p * 255;
	}
	if(i == 1)
	{
		k.r = q * 255;
		k.g = V_100 * 255;
		k.b = p * 255;
	}
	if(i == 2)
	{
		k.r = p * 255;
		k.g = V_100 * 255;
		k.b = t * 255;
	}
	if(i == 3)
	{
		k.r = p * 255;
		k.g = q * 255;
		k.b = V_100 * 255;
	}
	if(i == 4)
	{
		k.r = t * 255;
		k.g = p * 255;
		k.b = V_100 * 255;
	}
	if(i == 5)
	{
		k.r = V_100 * 255;
		k.g = p * 255;
		k.b = q * 255;
	}
	return k;
}
//
double* palHSV::RGBtoHSV(sf::Color kolor)
{
	double *k = new double[3];
	double f, i;
	double rgb[3] = {static_cast<double>(kolor.r) / 255, static_cast<double>(kolor.g) / 255, static_cast<double>(kolor.b) / 255};
	double x = bch::min(rgb, 3);
	k[2] = bch::max(rgb, 3);
	if(x == k[2]) k[0] = k[1] = 0;
	else
	{
		if(x == rgb[0]) f = rgb[1] - rgb[2];
		if(x == rgb[1]) f = rgb[2] - rgb[0];
		else f = rgb[0] - rgb[1];
		if(x == rgb[0]) i = 3;
		if(x == rgb[1]) i = 5;
		else i = 1;
		k[0] = fmod((i-f/(k[2]-x))*60, 360);
		k[1] = ((k[2]-x)/k[2]);
		}
		return k;
	}
//
void palHSV::rysuj(sf::RenderWindow &okno, const sf::Time c_rzecz)
{
	okno.draw(this->pal); // paleta
	okno.draw(this->suw); // suwak
	for(short i = 0; i < round(M_PI * 7); i++) // wskaznik palety
	{
		sf::Vector2f wsp1, wsp2;
		this->p_okr(wsp1, this->point_pal, 7, i * 360 / round(M_PI * 7));
		this->p_okr(wsp2, this->point_pal, 7, (i+1) * 360 / round(M_PI * 7));
		okno.draw(flin_sf::linia(wsp1, wsp2, 2.5, sf::Color(195, 195, 195)));
	}
	sf::RectangleShape border;
	double kat = 360 / round(M_PI * this->r);
	double x = 1.2; // polowa grubosci obwodki
	for(short i = 1; i < this->pal.getVertexCount() - 1; i++) // obwodka palety
	{
		sf::Vector2f wsp1, wsp2;
		this->p_okr(wsp1, this->poz, this->r + x, (i-1) * kat);
		this->p_okr(wsp2, this->poz, this->r + x, i * kat);
		border = flin_sf::linia(wsp1, wsp2, 2 * x, sf::Color(195, 195, 195));		
		okno.draw(border);
	}
	for(short i = 0; i < 4; i++) // obwodka paska
	{
		border = flin_sf::linia(this->suw[i].position, (i != 3) ? this->suw[i+1].position : this->suw[0].position, 2 * x, sf::Color(195, 195, 195));
		okno.draw(border);
	}
	// wskaznik suwaka
	sf::VertexArray point_suw(sf::Triangles, 6);
	sf::Vector2f p(this->point_suw, this->poz.y + 1.3316 * this->r);
	point_suw[0].position = sf::Vector2f(p.x, p.y + 0.055 * this->r);
	point_suw[3].position = sf::Vector2f(p.x, p.y - 0.055 * this->r);
	point_suw[1].position = sf::Vector2f(p.x + 0.055 * this->r, p.y + 0.17 * this->r);
	point_suw[4].position = sf::Vector2f(p.x + 0.055 * this->r, p.y - 0.18 * this->r);
	point_suw[2].position = sf::Vector2f(p.x - 0.055 * this->r, p.y + 0.17 * this->r);
	point_suw[5].position = sf::Vector2f(p.x - 0.055 * this->r, p.y - 0.18 * this->r);
	point_suw[0].color = point_suw[3].color = sf::Color(195, 195, 195);
	point_suw[1].color = point_suw[2].color = point_suw[4].color = point_suw[5].color = sf::Color(128, 128, 128);
	okno.draw(point_suw);
	if(this->dis) // dla trybu zablokowanego
	{
		sf::CircleShape pal_dis(this->r);
		pal_dis.setFillColor(sf::Color(128, 128, 128, 0.8 * 255));
		pal_dis.setPosition(sf::Vector2f(this->poz.x - this->r, this->poz.y - this->r));
		sf::RectangleShape suw_dis(sf::Vector2f(1.8 * this->r, 0.33 * this->r));
		suw_dis.setFillColor(sf::Color(128, 128, 128, 0.8 * 255));
		suw_dis.setPosition(this->suw[0].position);
		okno.draw(pal_dis);
		okno.draw(suw_dis);
	}	
}
//
bool palHSV::klikniety(sf::RenderWindow &okno)
{
	sf::Vector2f kursor = okno.mapPixelToCoords(sf::Mouse::getPosition(okno));
	if(!this->dis && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if(flin_sf::p_odl(this->poz, kursor) <= this->r) // reakcja na klikniecie palety
		{
			this->point_pal = kursor;
			this->S = flin_sf::p_odl(kursor, this->poz) / this->r;
			this->H = bch::bzw_dgrs(bch::rad_to_dgrs(atan2(kursor.x - this->poz.x, kursor.y - this->poz.y)));
			this->reset();
			return true;
		}
		if(kursor.x > this->suw[0].position.x && kursor.y > this->suw[0].position.y && kursor.x < this->suw[2].position.x && kursor.y < this->suw[2].position.y) // reakcja na klikniecie suwaka
		{
			this->point_suw = kursor.x;
			this->V = (kursor.x - this->suw[0].position.x) / (this->suw[1].position.x - this->suw[0].position.x);
			this->reset();
			return true;
		}
	}
	return false;
}
//
sf::Vector2f palHSV::rozmiary() const
{
	return sf::Vector2f(2 * this->r, 2.83 * this->r);
}
//
void palHSV::set_poz(sf::Vector2f pozycja){}
//
void palHSV::set_poz_r(sf::Vector2f pozycja){}
//
bool palHSV::setColor(sf::Color kolor)
{
	*this->kolor = kolor;
	double *k = this->RGBtoHSV(kolor);
	this->H = k[0];
	this->S = k[1];
	this->V = k[2];
	this->reset();
}
//
sf::Color palHSV::getColor() const
{
	return this->HSVtoRGB(this->H, this->S, this->V);
}
//
void palHSV::reset()
{
	this->pal[0].color = this->HSVtoRGB(0, 0, this->V);
	double kat = 360 / round(M_PI * this->r);
	for(short i = 0; i < this->pal.getVertexCount() - 1 ; i++) this->pal[i+1].color = this->HSVtoRGB(i * kat, 1, this->V);
	this->pal[this->pal.getVertexCount() - 1].color = this->pal[1].color;
	this->suw[0].color = this->suw[3].color = this->HSVtoRGB(this->H, this->S, 0);
	this->suw[1].color = this->suw[2].color = this->HSVtoRGB(this->H, this->S, 1);
	*this->kolor = this->getColor();
}
