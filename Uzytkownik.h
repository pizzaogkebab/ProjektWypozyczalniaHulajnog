#ifndef UZYTKOWNIK_H
#define UZYTKOWNIK_H
#include <iostream>

using namespace std;

class Uzytkownik
{
public:
    string email, imie, nazwisko, login, haslo;
    double saldo;
    void dodawanie_uzytkownika();
    bool logowanie();
    string hashowanie(string);
    void stan_konta();
    void doladowanie();
    void zmiana_salda();
};
#endif //UZYTKOWNIK_H
