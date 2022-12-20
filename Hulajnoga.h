#ifndef HULAJNOGA_H
#define HULAJNOGA_H
#include <iostream>

using namespace std;

class Hulajnoga {
public:
    string typ_hulajnogi;
    int predkosc, waga, stanBat;
    float odl;

    void dodaj_hulajnoge(string, int, float);
    void pokaz_hulajnoge();

};

#endif //HULAJNOGA_H