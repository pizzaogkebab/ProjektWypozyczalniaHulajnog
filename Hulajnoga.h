#ifndef HULAJNOGA_H
#define HULAJNOGA_H
#include <iostream>

using namespace std;
class Hulajnoga{
public:
    string typ_hulajnogi;
    int stanBat, predkosc, waga;
    double cena;
    float odleglosc;
    virtual void pokaz_hulajnoge();
    virtual double maks_zasieg();
    virtual double koszt(int czas);

};

class Standard : public Hulajnoga{
public:
    Standard(int = 40, int = 95);
    ~Standard();
    void pokaz_hulajnoge();
    double maks_zasieg();
    double koszt(int czas);
};


class Speed : public Hulajnoga{
public:
    Speed(int = 60, int = 90);
    ~Speed();
    void pokaz_hulajnoge();
    double maks_zasieg();
    double koszt(int czas);
};

class Teren : public Hulajnoga{
public:
    Teren(int = 35, int = 100);
    ~Teren();
    void pokaz_hulajnoge();
    double maks_zasieg();
    double koszt(int czas);
};

#endif //HULAJNOGA_H