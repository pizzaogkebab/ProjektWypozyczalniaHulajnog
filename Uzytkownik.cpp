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

    string linia;
    bool nieuzytyLogin = false;
    cout << "REJESTRACJA NOWEGO KONTA"<<endl;
    cout << "Podaj swoj email: ";
    cin >> email;
    cout <<"Podaj Imie: ";
    cin >> imie;
    cout << "Podaj Nazwisko: ";
    cin >> nazwisko;
    //wprowadzenie loginu i jednoczesne sprawdzenie czy taki użytkownik już nie występuje
    while (true){
        int licznik = 1;
        int nrlini = 4;  //indeks lini w którym znajduje się pierwszy login
        cout << "Podaj login: ";
        cin >> login;
        fstream plik_odczyt;
        plik_odczyt.open("uzytkownicy.txt", ios::in);
        nieuzytyLogin = true;
        while(getline(plik_odczyt,linia))
        {
            if(licznik == nrlini)
            {
                if(login == linia)
                {
                    cout << "Taki uzytkownik juz istnieje, wymysl inny login." << endl;
                    nieuzytyLogin = false;
                    break;
                }
                else if(licznik == nrlini)
                {
                    nrlini += 7;  //indeks lini następnego loginu
                }
            }
            licznik++;
        }
        plik_odczyt.close();
        if (nieuzytyLogin)
            break;
    }

    cout << "Ustaw haslo: ";
    cin >> haslo;

    fstream plik_zapis;
    plik_zapis.open("uzytkownicy.txt", ios::out | ios::app);
    plik_zapis << email << endl << imie << endl << nazwisko << endl << login << endl << hashowanie(haslo) << endl << "0" << endl << "=======" << endl;
    plik_zapis.close();

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
