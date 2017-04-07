#include "bch.hpp"
using namespace bch;
//
vector<string> bch::path_list(string sciezka, const string format, bool full_path) // zawraca liste plikow w danej lokacji
{
	dirent *plik;
	DIR *path;
	vector<string> tab;
	sciezka = sciezka.substr(2) + "/";
	if(path = opendir(sciezka.c_str()))
	{
		while(plik = readdir(path))
		{
			if(plik->d_name[0] != '.')
			{
				if(format != "")
				{
					if(static_cast<string>(plik->d_name).substr(static_cast<string>(plik->d_name).find_first_of(".")) == format) tab.push_back((full_path) ? sciezka + plik->d_name : plik->d_name);
				}
				else tab.push_back((full_path) ? sciezka + plik->d_name : plik->d_name);
			}
		}
		return tab;
	}
}
//
long long int silnia(const int n) // silnia- jesli n < 0 zwraca -1
{
	if(n >= 0)
	{
		long long int wynik = 1;
		for(int i = 1; i <= n; i++)
		{
			wynik *= i;
			}
		return wynik;
		}
		else
		{
			return -1;
			}
	}
	//
	/*
	long double to_Ldouble(const T d) //zmienia liczbe w postaci string to double
	{
		stringstream strumien;
		double z;
		strumien << d;
		strumien >> z;
		return z;
		} */
	flin::flin(){}
	flin::flin(const float kat, const float _b):b(_b)
	{
		if(kat != 90) this->a = tan(bch::dgrs_to_rad(kat));
		}
	flin::flin(float x1, const float y1, const float x2, const float y2)
	{
		x1 = (x2 - x1) ? x1 : x1 + 0.0001;
		float t = x2 - x1;
		this->a = (y2 - y1)/t;
		this->b = y1 - x1 * this->a;
	}
	flin::~flin(){}
	float flin::y(const float x) 
	{
		return x * this->a + b;
	}
	p flin::operator==(const flin f)
	{
		p punkt;
		punkt.x = (this->b - f.b)/(this->a - f.a);
		punkt.y = this->y(punkt.x);
		return punkt;
	}
	int flin::i_m0(const flin f) const
	{
		float a, b;
		a = this->a - f.a;
		b = f.b - this->b;
		if(!a && !b) return 2;
		if(!a && b) return 0;
		if(a && a) return 1;
		}
	float flin::p_odl(p x, p y)
	{
		return sqrt(pow(y.y - x.y, 2) + pow(y.x - x.x, 2));
	}
	
	

