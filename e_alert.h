#ifndef E_ALERT_H
#define E_ALERT_H
//
#include<SFML/Graphics.hpp>
#include <vector>
#include "ekran.h"
#include "wlas.hpp"
//
class e_alert : public ekran
{
	protected:
		K_ZDARZENIE id_alert; // id zwracane przez alert
		std::vector<K_ZDARZENIE> wyl;// tablica zdarzen wylaczajacych alert
	public:
		std::vector<kontrolka*> wyl_kontr;
		e_alert(ekran *rodzic, std::vector<K_ZDARZENIE> tab);
		e_alert(ekran *rodzic, K_ZDARZENIE zdarzenie_wyl);
		K_ZDARZENIE get_id() const;
		K_ZDARZENIE get_aktywny(sf::Event zdarzenie, sf::RenderWindow &okno);
		
		
};
//
#endif
