#include "map.h"
//
mapa::mapa():edit(true){};
//

//
mapa::~mapa(){}
//
void mapa::dodaj_obiekt(obiekt *_nowy)
{
	this->obiekty.push_back(_nowy);
}
//
bool mapa::konw_tex()
{
	vector<vector<sf::Vector2f>::iterator> funkcje; 
	vector<vector<sf::Vector2f>::const_iterator> wyj;
	//
	for(vector<sf::Vector2f>::iterator it = this->pkt.begin() + 1; it < this->pkt.end() - 1; it++)
	{
		bool zaw = true;
		for(vector<sf::Vector2f>::iterator i = this->pkt.begin(); i < this->pkt.end() -1; i++)
		{
			if(bch::zawiera_sie_w(i->x, it->x, (i+1)->x) && it != i && it != i+1)
			{
				flin_sf f(*i, *(i+1));
				if(f.y(it->x) > it->y)
				{
					zaw = false;
					break;
				}
				funkcje.push_back(i);
				}
		}
		if(zaw)
		{
			if((it->x >= (it-1)->x && it->x > (it+1)->x) || (it->x <= (it-1)->x && it->x < (it+1)->x))
			{
				double min;
				vector<sf::Vector2f>::iterator pocz, x;
				bool us = false;
				for(vector<vector<sf::Vector2f>::iterator>::const_iterator l = funkcje.begin(); l != funkcje.end(); l++)
				{
					flin_sf f(**l, *(*l + 1));
					double wynik = it->y - f.y(it->x);
					if(!us)
					{
						min = wynik;
						us = true;
					}
					if(wynik <= min)
					{
						min = wynik;
						pocz = *l;
					}
				}
				bool ft = it->x > (it-1)->x;
				x = this->pkt.insert(pocz+1, sf::Vector2f(it->x, it->y - min));
				// sprawdza, czy punkt zostal dodany prawidlowo, a jesli nie, uruchamia funkcje od nowa
				if(pocz + 1 != x)
				{
					this->konw_tex();
					return true;
				}
				// warunek
				if(ft)
				{
					wyj.push_back(it);
					this->TR(it, x);
					it = x;
					wyj.push_back(it);
				}
				else
				{
					wyj.push_back(x);
					it++;
					wyj.push_back(it);
					this->TR(x, it);
				}				
			}
		}
		funkcje.clear();
	}
	if(!bch::jest_parzysta(wyj.size())) return false;
	if(wyj.size())bch::sort_ros(wyj);
	// usuwanie zawierajacych sie przedzialow
	for(int i = 0; i < wyj.size(); i += 2)
	{
		for(int i2 = i + 2; i2 < wyj.size() - 2; i2 += 2) 
		{
			if(bch::zawiera_sie_w(wyj[i], wyj[i2], wyj[i+1], false) || bch::zawiera_sie_w(wyj[i], wyj[i2+1], wyj[i+1], false)) wyj.erase(wyj.begin() + i2, wyj.begin() + i2 + 2);
		}
	}
	for(vector<sf::Vector2f>::const_iterator it = this->pkt.begin() + 1; it < this->pkt.end(); it++)
	{
		for(vector<vector<sf::Vector2f>::const_iterator>::const_iterator k = wyj.begin(); k != wyj.end(); k += 2)
		{
			if(it > *k && it < *(k+1) && wyj.size()) 
			{
				it = *(k+1) + 1;
				break;
			}
			}
			this->Qu.append(sf::Vertex(*(it-1), *(it-1))); // argument drugi jako tekstura- kalkulowaæ
			this->Qu.append(sf::Vertex(sf::Vector2f((it-1)->x, 1000), sf::Vector2f((it-1)->x, 1000)));
			this->Qu.append(sf::Vertex(sf::Vector2f(it->x, 1000), sf::Vector2f(it->x, 1000)));
			this->Qu.append(sf::Vertex(*it, *it));
			//
			}
}
//
bool mapa::TR(const vector<sf::Vector2f>::iterator pocz, const vector<sf::Vector2f>::iterator kon) // wersja 1.1, z b³êdami
{
	// zmienne
	vector<vector<sf::Vector2f>::const_iterator*> iter; // tablica na iteratory, pozniej do dodania;
	vector<vector<sf::Vector2f>::const_iterator> tab; // tablica skopiowanych iteratorow
	vector<sf::Vector2f>::const_iterator m, n; // iteratory(punkty) pomocnicze
	bool mov, met1; // zmienna pomocnicza dla sortowania
	vector<sf::Vector2f>::const_iterator *p_tr; // wskaznik na ostatni trojkat
	//
	// kopiowanie przedzialu iteratorow
	for(vector<sf::Vector2f>::const_iterator i = pocz + 1; i < kon; i++) tab.push_back(i); 
	// sortowanie tablicy w zale¿nosci od odleglosci od osi (pocz, kon)
	do
	{
		mov = false;
		for(vector<vector<sf::Vector2f>::const_iterator>::iterator i = tab.begin(); i < tab.end()-1; i++)
		{
			if(fabs(pocz->x - static_cast<sf::Vector2f>(**i).x) > fabs(pocz->x - static_cast<sf::Vector2f>(**(i+1)).x))
			{
				vector<sf::Vector2f>::const_iterator ob = *i;
				*i = *(i+1);
				*(i+1) = ob;
				mov = true;
			}
		}
	}while(mov);
	//
	// dzielenie na trojkaty
	for(vector<vector<sf::Vector2f>::const_iterator>::iterator i = tab.begin(); i < tab.end(); i++)
	{
		// dobieranie poczatkowych pkt
		met1 = false;
		if(!iter.size())
		{
			m = pocz;
			n = kon;
			met1 = true;
		}
		else // dobieranie kolejnego punktu
		{
			if(bch::zawiera_sie_w(bch::min(p_tr, 3), *i, bch::max(p_tr, 3)))
			{
				vector<vector<sf::Vector2f>::const_iterator> mn, wk;
				for(int k = 0; k < 3; k++)
				{
					if(p_tr[k] < *i)
					{
						mn.push_back(p_tr[k]);
					}
					else
					{
						wk.push_back(p_tr[k]);
					}
						}
						m = bch::max(mn);
						n = bch::min(wk);
						met1 = true;
				}
		}	
		//
		// pierwsza metoda
		if(met1)
		{
			flin_sf f1(**i, *m), f2(**i, *n);
			mov = true;
			for(vector<sf::Vector2f>::const_iterator l = pocz; l < kon; l++)
			{
				if(l != *i && l+1 != *i)
				{
					flin_sf fp(*l, *(l+1));
					if((f1.i_m0(fp) == 1 && this->w_linii(*l, f1 == fp, *(l+1)) && this->w_linii(**i, f1 == fp, *m)) || (f2.i_m0(fp) == 1 && this->w_linii(*l, f2 == fp, *(l+1)) && this->w_linii(**i, f2 == fp, *n)))
					{
						mov = false;
						break;
					}
				}
			}
			if(mov)
			{
				p_tr = new vector<sf::Vector2f>::const_iterator[3];
				p_tr[0] = m;
				p_tr[1] = *i;
				p_tr[2] = n;
				iter.push_back(p_tr);
				tab.erase(i);
				i = tab.begin()-1;
				continue;
			}
			//
		}
		// druga  metoda
		if(iter.size())
		{
			vector<sf::Vector2f>::const_iterator mn, wk; // iterator mniejszy i wiekszy trojkata
			vector<vector<sf::Vector2f>::const_iterator*> trk; // tablica trojkatow
			// szukanie trojkatow, w ktorych zawiera sie punkt o jeden wiekszy lub mniejszy
			for(size_t k = 0; k < iter.size(); k++)
			{
				if((bch::zawiera_sie_w(*i-1, iter[k], 3) || bch::zawiera_sie_w(*i+1, iter[k], 3)) && *i < bch::max(iter[k], 3) && *i > bch::min(iter[k], 3)) trk.push_back(iter[k]);
			}
			if(trk.size())
			{
				// petla sprawdzajaca wszystkie trojkaty, w ktorych zawieral sie poprzedni lub nastepny punkt
				for(size_t k = 0; k < trk.size(); k++)
				{
					// maxyma z mniejszych iteratorow od i i minima z wiekszych
					vector<vector<sf::Vector2f>::const_iterator> Tmn, Twk;
					for(size_t t = 0; t < 3; t++)
					{
						if(trk[k][t] < *i) Tmn.push_back(trk[k][t]);
						else Twk.push_back(trk[k][t]);
					}
					mn = bch::max(Tmn);
					wk = bch::min(Twk);
					// warunek sprawdzajacy czy punkty trojkata juz nie tworza podstaw trojkata
					if(mn != *i-1 || wk != *i+1)
					{
						flin_sf f1(**i, *mn), f2(**i, *wk); // funkcje liniowe nowego trojkata
						mov = true;
						// petla sprawdzajaca czy linie trojkata sie nie przecinaja
						for(vector<sf::Vector2f>::const_iterator l = pocz; l < kon; l++)
						{
							flin_sf fp(*l, *(l+1));
							if((f1.i_m0(fp) == 1 && this->w_linii(*l, f1 == fp, *(l+1)) && this->w_linii(**i, f1 == fp, *mn)) || (f2.i_m0(fp) == 1 && this->w_linii(*l, f2 == fp, *(l+1)) && this->w_linii(**i, f2 == fp, *wk)))
							{
								mov = false;
								break;
							}
						}
						if(mov) // jesli linie sie nie przecinaja
						{
							p_tr = new vector<sf::Vector2f>::const_iterator[3];
							p_tr[0] = mn;
							p_tr[1] = *i;
							p_tr[2] = wk;
							iter.push_back(p_tr);
							tab.erase(i);
							i = tab.begin()-1;
							break;
							
						}	
					}
					else // warunek gdy mn = i -1 i wk = i + 1
					{
						
						p_tr = new vector<sf::Vector2f>::const_iterator[3];
						p_tr[0] = mn;
						p_tr[1] = *i;
						p_tr[2] = wk;
						iter.push_back(p_tr);
						tab.erase(i);
						i = tab.begin()-1;
						break;
					}
				}
			}
		}
	}
	//
	// dodawanie trojkatow do mapy
	for(int i = 0; i < iter.size(); i++)
	{	
		sf::VertexArray trojkat(sf::Triangles, 3);
		trojkat[0].position = trojkat[0].texCoords = *(iter[i][0]);
		trojkat[1].position = trojkat[1].texCoords = *(iter[i][1]);
		trojkat[2].position = trojkat[2].texCoords = *(iter[i][2]);
		this->Tr.push_back(trojkat);
	}
}
//
bool mapa::w_linii(const sf::Vector2f a, const sf::Vector2f X, const sf::Vector2f b)
{
	int ax = round(a.x), ay = round(a.y), bx = round(b.x), by = round(b.y), Xx = round(X.x), Xy = round(X.y);
	return (bch::zawiera_sie_w(ax, Xx, bx, false) && bch::zawiera_sie_w(ay, Xy, by, false));
}


