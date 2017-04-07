#include "flin_sf.h"
//
flin_sf::~flin_sf(){}
flin_sf::flin_sf():flin(){}
flin_sf::flin_sf(const float kat, const float _b):flin(kat, _b){}
flin_sf::flin_sf(const sf::Vector2f x, const sf::Vector2f y):flin(x.x, x.y, y.x, y.y){}
sf::VertexArray flin_sf::rysuj(sf::RenderWindow &okno, bch::p przedzial, sf::Color kolor)
{
	sf::VertexArray ln(sf::Lines, 2);
	ln[0].position = sf::Vector2f(przedzial.x, this->y(przedzial.x));
	ln[1].position = sf::Vector2f(przedzial.y, this->y(przedzial.y));
	for(int i = 0; i < 2; i++) ln[i].color = kolor;
	okno.draw(ln);
	return ln;	
}
bool flin_sf::operator >=(const sf::Vector2f punkt)
{
	return (punkt.y >= this->y(punkt.x)) ? true : false;
	
}
bool flin_sf::operator <=(const sf::Vector2f punkt)
{
	return (punkt.y <= this->y(punkt.x)) ? true : false;
}
bool flin_sf::operator >(const sf::Vector2f punkt)
{
	return (punkt.y > this->y(punkt.x)) ? true : false;
	
}
bool flin_sf::operator <(const sf::Vector2f punkt)
{
	return (punkt.y < this->y(punkt.x)) ? true : false;
}
float flin_sf::p_odl(const sf::Vector2f x, const sf::Vector2f y)
{
	return sqrt(pow(fabs(x.x - y.x), 2) + pow(fabs(x.y - y.y), 2));
}
sf::RectangleShape flin_sf::linia(sf::Vector2f wsp1, sf::Vector2f wsp2, double grubosc_piks, sf::Color kolor)
{
	sf::RectangleShape ln;
	double len;
	wsp1.x = (wsp1.x == wsp2.x) ? wsp1.x + 0.0001 : wsp1.x;
	flin_sf f(wsp1, wsp2);
	len = sqrt(pow(wsp1.x - wsp2.x, 2) + pow(wsp1.y - wsp2.y, 2));
	ln = sf::RectangleShape(sf::Vector2f(len, grubosc_piks));
	ln.setOrigin(sf::Vector2f(0, grubosc_piks / 2));
	ln.setFillColor(kolor);
	ln.setRotation(bch::rad_to_dgrs(atan2(wsp1.y - wsp2.y, wsp1.x - wsp2.x)) + 180);
	ln.setPosition(wsp1);
	return ln;
}
sf::Vector2f flin_sf::operator==(const flin_sf f)
{
	float a1 = this->a - f.a;
	if(a1)
	{
		float b1 = (f.b - this->b)/a1;
		return sf::Vector2f(b1, this->y(b1));	
	}
}
double flin_sf::max_h(pair<sf::Vector2f, sf::Vector2f> f1, pair<sf::Vector2f, sf::Vector2f> f2)
{
	flin_sf Ff1(f1.first, f1.second), Ff2(f2.first, f2.second);
	if(Ff1.a == Ff2.a) return fabs(Ff1.b - Ff2.b);
	vector<double> t = {f1.first.x, f1.second.x, f2.first.x, f2.second.x};
	bch::sort_ros(t);
	double max1 = fabs(Ff1.y(t[1]) - Ff2.y(t[1])), max2 = fabs(Ff1.y(t[2]) - Ff2.y(t[2]));
	return (max1 >= max2) ? max1 : max2;
	
}
bool flin_sf::zawiera_sie_w(const sf::Vector2f figura[], const unsigned int r, const sf::Vector2f punkt)
{
	// wyznaczanie srodka geometrycznego
	sf::Vector2f srd_geo(0, 0);
	for(int i = 0; i < r; i++)
	{
		srd_geo.x += figura[i].x;
		srd_geo.y += figura[i].y;
	}
	srd_geo.x /= r;
	srd_geo.y /= r;
	// liczenie dla punktów
	flin_sf srd_p(srd_geo, punkt);
	for(int i = 0; i < r - 1; i++)
	{
		flin_sf f(figura[i], figura[i+1]);
		sf::Vector2f prz = f == srd_p;
		if(bch::zawiera_sie_w(round(figura[i].x), round(prz.x), round(figura[i+1].x)) && bch::zawiera_sie_w(srd_geo.x, prz.x, punkt.x)) return false;
	}
	// liczenie dla punktu ostatniego i pierwszego
	flin_sf f(figura[r-1], figura[0]);
	sf::Vector2f prz = f == srd_p;
	if(bch::zawiera_sie_w(round(figura[r-1].x), round(prz.x), round(figura[0].x)) && bch::zawiera_sie_w(srd_geo.x, prz.x, punkt.x)) return false;
	return true;
}
bool flin_sf::zawiera_sie_w(list<sf::Vector2f> obiekt, list<sf::Vector2f> figura)
{
	sf::Vector2f *f = new sf::Vector2f[figura.size()];
	auto i = figura.cbegin();
	auto y = 0;
	while(i != figura.cend())
	{
		f[y] = *i;
		i++;
		y++;
	}
	for(auto i = obiekt.cbegin(); i != obiekt.cend(); i++) if(!flin_sf::zawiera_sie_w(f, figura.size(), *i)) return false;
	return true;
}

