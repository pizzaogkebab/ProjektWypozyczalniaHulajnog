#include "Uzytkownik.h"
#include <fstream>
#include <iostream>
#include <vector> // do zmiany elementow w pliku m.in. do doladowania konta

using namespace std;

string Uzytkownik::hashowanie(string haslo){
    for(int i = 0; i < haslo.length(); i++)
        haslo[i] += 3;
    return haslo;
}

bool sprawdz_doladowanie(string &kwota){
    if(kwota.length() < 1){
        return false;
    }
    for(int i = 0; i < kwota.length(); i++){
        if (int(kwota[i]) < 48 or int(kwota[i]) > 57) {
            if(int(kwota[i]) == 46){
                continue;
            }
            else {
                return false;
            }
        }
    }
    return true;
}

void Uzytkownik::dodawanie_uzytkownika()
{

    string linia;
    bool nieuzytyLogin = false;
    cout << "REJESTRACJA NOWEGO KONTA"<<endl;
    cout << "Podaj swój email: ";
    cin >> email;
    cout <<"Podaj imię: ";
    cin >> imie;
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    //wprowadzenie loginu i jednoczesne sprawdzenie czy taki użytkownik już nie występuje
    while (true){
        int licznik = 1;
        int nrlini = 1;  //indeks lini w którym znajduje się pierwszy login
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
                    cout << "Taki użytkownik już istnieje, wymyśl inny login." << endl;
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

    cout << "Ustaw hasło: ";
    cin >> haslo;

    saldo = 0;
    fstream plik_zapis;
    plik_zapis.open("uzytkownicy.txt", ios::out | ios::app);
    plik_zapis << login<< endl << hashowanie(haslo) << endl << email << endl << imie << endl << nazwisko << endl << saldo << endl << "=======" << endl;
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
        int nrlini = 1;
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
                cout << "Użytkownik: " << login<<endl;
                do{
                    cout << "Podaj hasło: ";
                    cin >> haslozklaw;
                }while(Uzytkownik::hashowanie(haslozklaw) != haslo);
                getline(plik,linia);
                email = linia;
                getline(plik,linia);
                imie = linia;
                getline(plik,linia);
                nazwisko = linia;
                getline(plik,linia);
                saldo = stod(linia);
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


void Uzytkownik::stan_konta()
{
    cout << "Aktualne saldo to: " << saldo << " zł "<<endl;
}


void Uzytkownik::zmiana_salda() {
    fstream plik;
    plik.open("uzytkownicy.txt", ios::in);
    string saldos;
    int snrlini = 1;
    if (plik.good() == true){
        string slinia;
        while(getline(plik,slinia)){
            if (slinia == login && snrlini%7 == 1){
                break;
            }
            snrlini++;
        }
        snrlini += 4;
    }
    plik.close();

    string saldodts = to_string(saldo);

    fstream przepisanie;

    przepisanie.open("uzytkownicy.txt");

    vector<string> tempplik;

    string templinie;

    while (getline(przepisanie, templinie)) {
        tempplik.push_back(templinie);
    }

    przepisanie.close();

    ofstream pliks;

    pliks.open("uzytkownicy.txt");
    string slinia;

        for (int i = 0; i < tempplik.size(); i++) {
            if (i != snrlini) {
                pliks << tempplik[i] << endl;
            } else {
                pliks << saldodts << endl;
            }
        }

        pliks.close();

    }


    void Uzytkownik::doladowanie(){
        string doladowanie;
        cout << "Podaj kwotę na jaką chcesz doładować konto: ";
        while (true) {
            cin >> doladowanie;
            if (sprawdz_doladowanie(doladowanie)) {
                break;
            }
            cout << "Podaj kwotę doładowania jeszcze raz: ";
        }
        saldo += stod(doladowanie);
        zmiana_salda();
    }

    void Uzytkownik::zmiana_hasla() {
        system("cls");
        string stare_haslo;
        string nowe_haslo;
        while(true) {
            cout << "Podaj aktualne hasło: ";
            cin >> stare_haslo;
            if(hashowanie(stare_haslo) != this -> haslo)
            {
                cout << "Podałeś niepoprawne hasło"<<endl;
            }
            else{
                cout << "Podane hasło jest poprawne"<<endl<<endl;
                break;
            }

        }
        cout << "Podaj nowe hasło:";
        cin >> nowe_haslo;

        this -> haslo = hashowanie(nowe_haslo);

        fstream plik;
        plik.open("uzytkownicy.txt", ios::in);
        string saldos;
        int snrlini = 1;
        if (plik.good() == true){
            string slinia;
            while(getline(plik,slinia)){
                if (slinia == login && snrlini%7 == 1){
                    break;
                }
                snrlini++;
            }

        }
        plik.close();

        string saldodts = haslo;

        fstream przepisanie;

        przepisanie.open("uzytkownicy.txt");

        vector<string> tempplik;

        string templinie;

        while (getline(przepisanie, templinie)) {
            tempplik.push_back(templinie);
        }

        przepisanie.close();

        ofstream pliks;

        pliks.open("uzytkownicy.txt");
        string slinia;

        for (int i = 0; i < tempplik.size(); i++) {
            if (i != snrlini) {
                pliks << tempplik[i] << endl;
            } else {
                pliks << saldodts << endl;
            }
        }

        pliks.close();

    }

