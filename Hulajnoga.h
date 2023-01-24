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
    virtual void prezentacja_hulajnogi();
    virtual void pokaz_hulajnoge() = 0;
    virtual double maks_zasieg() = 0;
    virtual double koszt(int czas) = 0;
};

class Standard : public Hulajnoga{
public:
    explicit Standard(int = 40, int = 95);
    ~Standard();
    void prezentacja_hulajnogi() override;
    void pokaz_hulajnoge() override;
    double maks_zasieg() override;
    double koszt(int czas) override;
};


class Speed : public Hulajnoga{
public:
    explicit Speed(int = 60, int = 90);
    ~Speed();
    void prezentacja_hulajnogi();
    void pokaz_hulajnoge();
    double maks_zasieg();
    double koszt(int czas);
};

class Teren : public Hulajnoga{
public:
    explicit Teren(int = 35, int = 100);
    ~Teren();
    void prezentacja_hulajnogi();
    void pokaz_hulajnoge();
    double maks_zasieg();
    double koszt(int czas);
};

#endif //HULAJNOGA_H