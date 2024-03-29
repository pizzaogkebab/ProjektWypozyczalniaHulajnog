#include "Hulajnoga.h"
#include <iostream>
#include <time.h>
using namespace  std;


void Hulajnoga::prezentacja_hulajnogi() {
    cout << "========================="<<endl;
    cout << "Typ hulajnogi: " << typ_hulajnogi << endl;
    cout << "Maksymalna prędkość pojazdu: " << predkosc << " km/h" << endl;
    cout << "Maksymalna waga pasażera: " << waga << " kg" << endl;
}

void Hulajnoga::pokaz_hulajnoge()
{
    Hulajnoga::prezentacja_hulajnogi();
    cout << "Stan baterii pojazdu: " << stanBat << " %" <<endl;
    cout << "Odleglość od Ciebie: " << odleglosc << " km" <<endl;
    cout << "========================="<<endl;
}

double Hulajnoga::maks_zasieg()
{
    double wynik = (stanBat * (160.0 / predkosc));
    return wynik;
}

double Hulajnoga::koszt(int czas) {
    double koszt_calk = 2 + (czas * cena);
    return koszt_calk;
}

Standard::Standard(int pred, int w)
{

    typ_hulajnogi = "STANDARD";
    cena = 0.69;
    predkosc = pred;
    waga = w;
    srand(time(0));
    stanBat = (rand() % 95 ) + 5;
    odleglosc = ((rand() % 30) + 1) / 10.0;

}

Standard::~Standard()
{}

void Standard::prezentacja_hulajnogi()
{
    Hulajnoga::prezentacja_hulajnogi();
}

void Standard::pokaz_hulajnoge()
{
    Hulajnoga::pokaz_hulajnoge();
}

double Standard::maks_zasieg()
{
    Hulajnoga::maks_zasieg();
}

double Standard::koszt(int czas) {
    Hulajnoga::koszt(czas);
}

Speed::Speed(int pred, int w){
    typ_hulajnogi = "SPEED";
    cena = 1.1;
    predkosc = pred;
    waga = w;
    srand(time(0));
    stanBat = (rand() % 95 ) + 5;
    odleglosc = ((rand() % 30) + 1) / 10.0;

}

Speed::~Speed()
{}

void Speed::prezentacja_hulajnogi()
{
    Hulajnoga::prezentacja_hulajnogi();
}

void Speed::pokaz_hulajnoge()
{
    Hulajnoga::pokaz_hulajnoge();
}

double Speed::maks_zasieg()
{
    Hulajnoga::maks_zasieg();
}

double Speed::koszt(int czas) {
    double opust = (int)(czas / 5) * 0.4;
    double koszt_calk = Hulajnoga::koszt(czas) - opust;
    return koszt_calk;
}

Teren::Teren(int pred, int w){
    typ_hulajnogi = "TEREN";
    cena = 0.9;
    predkosc = pred;
    waga = w;
    srand(time(0));
    stanBat = (rand() % 95 ) + 5;
    odleglosc = ((rand() % 30) + 1) / 10.0;
}

Teren::~Teren()
{}

void Teren::prezentacja_hulajnogi()
{
    Hulajnoga::prezentacja_hulajnogi();
}

void Teren::pokaz_hulajnoge()
{
    Hulajnoga::pokaz_hulajnoge();
}

double Teren::maks_zasieg()
{
    Hulajnoga::maks_zasieg();
}

double Teren::koszt(int czas){
    double koszt_calk = Hulajnoga::koszt(czas) + ((int)(czas / 10));
    return koszt_calk;
}
