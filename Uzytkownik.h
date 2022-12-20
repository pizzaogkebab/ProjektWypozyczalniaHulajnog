#ifndef UZYTKOWNIK_H
#define UZYTKOWNIK_H
#include <iostream>

using namespace std;

class Uzytkownik
{
public:
    string email, imie, nazwisko, login, haslo;
    void dodawanie_uzytkownika();
    bool logowanie();
    string hashowanie(string);
};
#endif //UZYTKOWNIK_H
