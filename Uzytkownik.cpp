#include "Uzytkownik.h"
#include <fstream>
#include <iostream>
#include <vector> // do zmiany elementow w pliku m.in. do doladowania konta
#include <ctime>
#include <unistd.h>
#include <conio.h>

using namespace std;

//szyfrowanie hasła
string Uzytkownik::hashowanie(string haslo){
    for(int i = 0; i < haslo.length(); i++)
        haslo[i] += 3;
    return haslo;
}

//funkcja dodająca 0 przed jednocyfrową liczbą w godzinie
string czas_fix(int liczba){
    string s_liczba = to_string(liczba);
    if(s_liczba.length() == 1){
        s_liczba = '0' + s_liczba;
    }
    return s_liczba;
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
            if(login == loginzklaw) {
                string linia2;
                string s_login = login + ".txt";
                fstream plik2;
                plik2.open(s_login, ios::in);
                if (plik2.good() == true) {
                    while (getline(plik2, linia2)) {
                        getline(plik2, linia2);
                        if (linia2 == "TEREN" or linia2 == "SPEED" or linia2 == "STANDARD" or linia2.empty()) {
                            continue;
                        }
                        koniec = stol(linia2);
                    }
                }
                else{
                    koniec = -1;
                }
                plik2.close();

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
        cout << "Podaj nowe hasło: ";
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

    void Uzytkownik::wypozyczenie(int czas_wyp, string typ_hul){
    time_t czas = time(0);
    cout << "Wyzpozyczanie" << endl;
    tm * gottime = localtime(&czas);
    start = czas;
    koniec = czas + czas_wyp * 60;
    czas_trwania_wyp = koniec - start;
    //godzina wypożyczenia -> lolkalny czas z komputera
    int godzina = gottime->tm_hour;
    int minuta = gottime->tm_min;
    int sekunda = gottime->tm_sec;

    //godzina końca wypożyczenia
    int minuta_k = (minuta + (czas_wyp % 60)) % 60;
    int godzina_k = (godzina + (int)(czas_wyp / 60) + (int)((minuta + (czas_wyp % 60))/60))%24;
    int sekunda_k = sekunda;

    //wyświetlanie odpowiednich godzin
    cout << "Godzina wypożyczenia: " << czas_fix(godzina) << ":"<< czas_fix(minuta) << ":" << czas_fix(sekunda)<< endl;
    cout << "Wypożyczona do godziny: " << czas_fix(godzina_k) << ":" << czas_fix(minuta_k)<<":"<<czas_fix(sekunda_k)<<endl<<endl;

    wypozyczona = true;

    string nazwa_s = login + ".txt";
    fstream plik_zapis;
    plik_zapis.open(nazwa_s, ios::out | ios::app);
    plik_zapis << endl <<czas_fix(godzina) <<':'<<czas_fix(minuta)<<':'<<czas_fix(sekunda)<<endl<<(czas_trwania_wyp/60) << endl
    << czas_fix(godzina_k)<<':'<<czas_fix(minuta_k)<<':'<<czas_fix(sekunda_k)<<endl<< typ_hul <<endl<<koniec<<endl;
    plik_zapis.close();


    cout << "Kliknij dowolny przycisk aby kontynuować";
    int wait = _getch();
    }


    void Uzytkownik::sprawdz_czas(){
        time_t a_czas = time(0);
        if(a_czas > koniec){
            wypozyczona = false;
        }
    }


    void Uzytkownik::anulowanie(){
        cout << "Wyzpozyczanie" << endl;
        cout << "Posiadasz już jedną wypożyczoną hulajnoge"<<endl;
        cout << "Czy chcesz przedwcześnie zakończyć jej wypożyczenie? Stracisz wydane pieniądze. (Y/N): " <<endl;
        char odp_wyb;
        cin >> odp_wyb;
        if(odp_wyb == 'Y' or odp_wyb == 'y'){
            cout << "Anulowanie wypożyczenia"<<endl;
            wypozyczona = false;
            start = -1;
            koniec = -1;

        }
        else if(odp_wyb == 'N' or odp_wyb == 'n'){
            cout<<"OK. Życzymy miłej jazdy!";
        }
        else{
            system("cls");
            cout << "Nie rozumiem polecenia ;(" << endl;
        }

    }
    void Uzytkownik::pokaz_historie(){
        string linia;
        string s_login = login + ".txt";
        fstream plik;
        plik.open(s_login, ios::in);
        while(getline(plik,linia)){
            cout << "=================================" << endl<<endl;
            getline(plik,linia);
            cout<<"Godzina wypożyczenia: "<<linia<<endl;
            getline(plik,linia);
            cout<<"Czas wypożyczenia: " << linia<<endl;
            getline(plik,linia);
            cout << "Godzina zakończenia wypożyczenia: " << linia<<endl;
            getline(plik,linia);
            cout << "Typ wypożyczonej hulajnogi: "<<linia<<endl;
            getline(plik,linia);
            cout <<endl<< "=================================" << endl<<endl;

        }
        plik.close();
    }

