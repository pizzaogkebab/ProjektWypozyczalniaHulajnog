#include "Uzytkownik.h"
#include <fstream>
#include <iostream>

using namespace std;


string Uzytkownik::hashowanie(string haslo){
    for(int i = 0; i < haslo.length(); i++)
        haslo[i] += 3;
    return haslo;
}


void Uzytkownik::dodawanie_uzytkownika()
{
    cout << "REJESTRACJA NOWEGO KONTA"<<endl;
    cout << "Podaj swoj email: ";
    cin >> email;
    cout <<"Podaj Imie: ";
    cin >> imie;
    cout << "Podaj Nazwisko: ";
    cin >> nazwisko;
    cout << "Podaj login: ";
    cin >> login;
    cout << "Ustaw haslo: ";
    cin >> haslo;

    fstream plik;
    plik.open("uzytkownicy.txt", ios::out | ios::app);
    plik << email << endl << imie << endl << nazwisko << endl << login << endl << hashowanie(haslo) << endl << "0" << endl << "=======" << endl;
    plik.close();

}


bool Uzytkownik::logowanie()
{
    string loginzklaw;
    string haslozklaw;


    fstream plik;
    plik.open("uzytkownicy.txt", ios::in);

    if (plik.good() == true){
        string linia;
        int licznik = 1;
        int nrlini = 4;
        cout << "Podaj login: ";
        cin >> loginzklaw;
        while(getline(plik,linia))
        {
            if(licznik == nrlini)
            {
                login = linia;
            }
            if(login == loginzklaw)
            {
                getline(plik,linia);
                haslo = linia;
                cout << "Uzytkownik: " << login<<endl;
                do{
                    cout << "Podaj haslo: ";
                    cin >> haslozklaw;
                }while(Uzytkownik::hashowanie(haslozklaw) != haslo);
                return true;
            }
            else
            {
                if(licznik == nrlini)
                    nrlini +=7;
            }
            licznik++;
        }
        plik.close();
        return false;
    }
    return false;
}
