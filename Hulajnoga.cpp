#include "Hulajnoga.h"
#include <iostream>

using namespace  std;


void Hulajnoga::dodaj_hulajnoge(string typ, int bat, float odleglosc)
{
    typ_hulajnogi = typ;
    if(typ == "standard") {
        predkosc = 30;
        waga = 100;
        stanBat = bat;
        odl = odleglosc;
    }
    else if(typ == "speed")
    {
        predkosc = 45;
        waga = 90;
        stanBat = bat;
        odl = odleglosc;
    }
    else if(typ == "teren")
    {
        predkosc = 25;
        waga = 110;
        stanBat = bat;
        odl = odleglosc;
    }


}
void Hulajnoga::pokaz_hulajnoge()
{
    cout << "========================="<<endl;
    cout << "Hulajnoga typu "<<typ_hulajnogi<<endl;
    cout << "maksymalna predkosc: "<< predkosc <<" km/h "<<endl;
    cout << "maksymalna waga pasazera: " << waga << "kg" << endl;
    cout << "Stan bateri pojazdu: " << stanBat << "%" <<endl;
    cout << "Odleglosc od ciebie: " << odl << "km" <<endl;
    cout << "========================="<<endl<<endl;
}
