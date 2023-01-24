#ifndef UZYTKOWNIK_H
#define UZYTKOWNIK_H
#include <iostream>

using namespace std;

class Uzytkownik
{
public:
    string email, imie, nazwisko, login, haslo;
    double saldo;
    long czas_trwania_wyp, start, koniec;
    bool wypozyczona = true;
    void dodawanie_uzytkownika();
    bool logowanie();
    string hashowanie(string);
    void stan_konta();
    void doladowanie();
    void zmiana_salda();
    void zmiana_hasla();
    void wypozyczenie(int, string);
    void anulowanie();
    void sprawdz_czas();
    void pokaz_historie();
};
#endif //UZYTKOWNIK_H
