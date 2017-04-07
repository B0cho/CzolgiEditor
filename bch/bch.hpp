#ifndef BCH_HPP
#define BCH_HPP
//
#include <sstream>
#include <cmath>
#include <vector>
#include <dirent.h>
#include <string>
#include <iostream>
#define M_PI 3.141592653589793238463
using namespace std;
//
namespace bch
{
	inline bool jest_parzysta(int liczba)
	{
		bool ret = !(liczba % 2) ? true : false;
		return ret;
	}
	long long int silnia(const int n); // silnia- jesli n < 0 zwraca -1
	vector<string> path_list(string sciezka, const string format = "", bool full_path = false);
	///////////////////////////////////////////////////////////
	template<typename T>
	string to_string(const T d) // konwertuje wszystkie wartosci do stringa
	{
		stringstream strumien;
		strumien << d;
		return strumien.str();
		}
	//
	template<typename T>
	long double to_Ldouble(const T d) //zmienia liczbe w postaci string to double
	{
		stringstream strumien;
		double z;
		strumien << d;
		strumien >> z;
		return z;
		}
	//
	template<typename T>
	T sumuj_tab(T tablica[], const unsigned int koniec, unsigned int poczatek = 0) // sumuje zawartosc podanej tablicy tab do znaku koniec
	{
		T suma = 0;
		while(poczatek < koniec)
		{
			suma += tablica[poczatek];
			poczatek++;
			}
		return suma;
		}
	//
	template<typename T>
	inline T dodawanie(const T skladnik1, const T skladnik2) // dodawanie
	{
		return skladnik1 + skladnik2;
		}
	// 
	template<typename T>
	inline T odejmowanie(const T skladnik1, const T skladnik2) // odejmowanie
	{
		return skladnik1 - skladnik2;
		}
	//
	template<typename T>
	inline T mnozenie(const T skladnik1, const T skladnik2) // mnozenie
	{
		return skladnik1 * skladnik2;
		}
	//
	template<typename T>
	inline T dzielenie(const T skladnik1, const T skladnik2) // dzielenie
	{
		return skladnik1 / skladnik2;
		}
	//
	template<typename T>
	inline T dgrs_to_rad(T dgr) // przelicza stopnie na radiany
	{
       return dgr * M_PI / 180;
       }
    //
    template<typename T>
	inline T rad_to_dgrs(T rad) // przelicza radiany na stopnie
	{
	   return rad * 180 / M_PI;
       }
    //
	template<typename T>
	inline bool jest_zmiennoprzecinkowa(const T liczba) // sprawdza, czy podana liczba jest zmiennoprzecinkowa
	{
		string ciag = to_string(liczba);
		for(size_t i = 0; i < ciag.size(); i++)
		{
			if(ciag[i] == 46) return true;
			}
		return false;
		}
	//
	template<typename T>
	inline unsigned int cyfry_po_przecinku(T liczba) // sprawdza, ile liczba ma miejsc po przecinku
	{
       string ciag = to_string(liczba);
       bool kropka = false;
       unsigned int ilosc = 0;
       for(size_t i = 0; i < ciag.size(); i++)
       {
                  ilosc = (kropka) ? ilosc + 1 : ilosc;
                  if(ciag[i] == 46) kropka = true;
                  }
       return ilosc;
       }
    //
    template<typename T>
    T bzw_dgrs(T dgrs) // sprowadza stopnie w roznych postaciach do postaci 0 < kat < 360
    {
    	while(dgrs < 0 || dgrs > 360)
    	{
    		if(dgrs < 0) dgrs += 360;
    		if(dgrs > 360) dgrs -= 360;
    	}
    	return dgrs;
		}
    //
    template<typename T>
    inline T skaluj(T wartosc, float skala)
    {
    	return wartosc * skala;
    }
    //
    template<typename T>
    bool zawiera_sie_w(T a, T X, T b, bool z = true)
    {
    	if(a > b)
    	{
    		T zap = a;
    		a = b;
    		b = zap;
    	}
    	return ((a < X && X < b) || (z && (fabs(a - X) < 0.00001 || fabs(b - X) < 0.00001)));
    }
    //
    template<typename T>
    void sort_ros(vector<T> &tab)
    {
		bool mov;
		do
    	{
    		mov = false;
    		for(typename vector<T>::iterator it = tab.begin(); it < tab.end()-1; it++)
    		{
	    		if(*it > *(it+1))
    			{
    				T ob = *it;
    				*it = *(it+1);
    				*(it+1) = ob;
    				mov = true;
    				}
    		}
		}while(mov);
    } 
    //
    template<typename T>
    T max(T tablica[], const size_t rozmiar)
    {
    	T max = tablica[0];
    	for(size_t i = 1; i < rozmiar; i++) max = (tablica[i] > max) ? tablica[i] : max;
    	return max;
    }
    //
    template<typename T>
    T min(T tablica[], const size_t rozmiar)
    {
    	T min = tablica[0];
    	for(size_t i = 1; i < rozmiar; i++) min = (tablica[i] < min) ? tablica[i] : min;
    	return min;
    }
    //
    template<typename T>
    T min(vector<T> tablica)
    {
    	T min = tablica[0];
		for(size_t i = 1; i < tablica.size(); i++) min = (min > tablica[i]) ? tablica[i] : min;
    	return min;
    }
    //
    template<typename T>
    T max(vector<T> tablica)
    {
    	T max = tablica[0];
		for(size_t i = 1; i < tablica.size(); i++) max = (max < tablica[i]) ? tablica[i] : max;
    	return max;
    }
    //
    template<typename T>
    bool zawiera_sie_w(const T WART, T tablica[], const size_t rozmiar)
    {
    	for(size_t i = 0; i < rozmiar; i++) if(WART == tablica[i]) return true;
    	return false;
    }
    //
    struct p
    {
    	float x, y;
    };
    class flin
    {
    	public:
    		float a, b;
    		flin();
    		flin(const float kat, const float _b);
    		flin(float x1, const float y1, const float x2, const float y2);
    		~flin();
    		float y(const float x);
    		int i_m0(const flin f) const;
    		p operator==(const flin f);
    		static float p_odl(p x, p y);
    		};
	//
	template<typename T>
	T mod(T a, T b) // modulo liczb rzeczywistych
	{
		double m = a / b;
		if(!round(m)) return a;
		return m - floor(m);
	}
	   

}
//

#endif
