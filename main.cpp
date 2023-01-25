#include <iostream>
#include <cstdlib>
#include <time.h>
#include <Windows.h>
#include <unistd.h>
#include <string>
#include <limits> //chyba nie trzeba
#include <typeinfo> // do testow
#include <conio.h>
#include <fstream>
#include "Uzytkownik.h"
#include "Hulajnoga.h"

using namespace std;


float zaokraglij(float liczba)
{
    float wartosc = (int)(liczba * 100 + .5);
    return (float)wartosc / 100;

}

//funkcja sprawdzająca poprawność wprowadzonego kodu blik
bool sprawdz_blik(string &kod){

    if(kod.size() != 6)
    {
        return false;
    }
    if(kod == "000000")
    {
        return false;
    }
    for(int i = 0; i < 6; i++){
        if(int(kod[i]) < 48 or int(kod[i]) > 57)
        {
            return false;
        }
    }
    return true;
}

//funkcja symulująca ładowanie
void ladowanie(string slowo){
    cout << slowo <<", proszę czekać ";
    usleep(350000);
    for(int i= 0; i < 3; i++){
        cout << '.';
        usleep(450000);
    }
    system("cls");
}


int main() {
    fstream logs;
    logs.open("logs.txt", ios::out | ios::app);
    system("chcp 65001");// zmiana kodowania na utf-8 --> polskie znaki
    system("cls");
    srand(time(0));
    bool wylogowanie = false;
    char wybor_logowanie = '3';
    //MENU LOGOWANIA
    while(wybor_logowanie != '0'){
        cout <<"------WYPOŻYCZALNIA HULAJNÓG ELEKTRYCZNYCH SPEEDX-----"<<endl;
        cout <<"----------------REJESTRACJA/LOGOWANIE-----------------"<<endl<<endl;
        cout << "1.Rejestracja nowego konta"<<endl;
        cout << "2.Logowanie"<<endl;
        cout << "0.Zakończ"<<endl;
        cin >> wybor_logowanie;
        system("cls");
        switch(wybor_logowanie) {
            //rejestracja
            case '1': {
                cout <<"------WYPOŻYCZALNIA HULAJNÓG ELEKTRYCZNYCH SPEEDX-----"<<endl;
                cout <<"------------REJESTRACJA NOWEGO UŻYTKOWNIKA------------"<<endl<<endl;
                Uzytkownik user_rej;
                user_rej.dodawanie_uzytkownika();
                system("cls");
                cout << "Zarejestrowano pomyślnie. Pzechodzimy do logowania" << endl;
                logs << "Zarejestrowano nowego użytkownika: " << user_rej.login<<endl;
            }

            //logowanie
            case '2': {
                cout <<"------WYPOŻYCZALNIA HULAJNÓG ELEKTRYCZNYCH SPEEDX-----"<<endl;
                cout <<"------------LOGOWANIE NA KONTO UŻYTKOWNIKA------------"<<endl<<endl;
                Uzytkownik user_log;
                while (true) {
                    if (user_log.logowanie()) { //funkcja sprawdzająca poprawność logowania
                        cout << "Zalogowano pomyślnie" << endl;
                        logs << "Użytkownik: "<< user_log.login <<" zalogował sie na konto"<<endl;
                        system("cls");
                        ladowanie("Ładowanie");
                        break;
                    } else {
                        cout << "Nie istnieje taki użytkownik. Spróbuj jeszcze raz" << endl << endl;
                    }
                }
                //MENU GŁÓWNE
                while (true) {
                    system("cls");
                    cout <<"------WYPOŻYCZALNIA HULAJNÓG ELEKTRYCZNYCH SPEEDX-----"<<endl;
                    cout <<"---------------------MENU GŁÓWNE----------------------"<<endl<<endl;
                    cout << "Witamy na koncie " << user_log.login << " :)" << endl;
                    cout << "\nWybierz co chcesz teraz zrobic" << endl;
                    cout << "1. Wypożycz hulajnoge"
                         << endl << "2. Pokaż listę dostępnych hulajnog"
                         << endl << "3. Pokaż historię wypożyczeń"
                         << endl << "4. Saldo konta"
                         << endl << "5. Ustawienia"
                         << endl << "0. Wyloguj" << endl;
                    char wybor_menu_2;
                    cin >> wybor_menu_2;
                    system("cls");
                    //MENU WYBORU HULAJNOGI
                    if (wybor_menu_2 == '1') {
                        user_log.sprawdz_czas();
                        if (user_log.wypozyczona) {
                                user_log.anulowanie();
                                logs << "Użytkownik: " << user_log.login << " anuluje przedwcześnie zamowienie"<<endl;
                            ladowanie("Wracanie do głównego menu");
                        }
                        else {
                            Standard s;
                            Speed sp;
                            Teren t;
                            Hulajnoga *wsk = nullptr;
                            while (true) {
                                cout << "------WYPOŻYCZALNIA HULAJNÓG ELEKTRYCZNYCH SPEEDX-----" << endl;
                                cout << "---------MENU WYBORU HULAJNÓG ELEKTRYCZNYCH-----------" << endl << endl;
                                cout << "1.Hulajnogi 'STANDARD'" << endl;
                                cout << "2.Hulajnogi 'SPEED'" << endl;
                                cout << "3.Hulajnogi 'TEREN'" << endl;
                                char wybor_hulajnogi;
                                cin >> wybor_hulajnogi;
                                switch (wybor_hulajnogi) {
                                    case '1': {
                                        wsk = &s;
                                        break;
                                    }
                                    case '2': {
                                        wsk = &sp;
                                        break;
                                    }
                                    case '3': {
                                        wsk = &t;
                                        break;
                                    }
                                }
                                //sprawsdzneie wyboru
                                if (wsk == nullptr) {
                                    system("cls");
                                    cout << "Nie ma takiej opcji. Spróbuj jeszcze raz" << endl;
                                } else {
                                    break;
                                }
                            }
                            cout << "--- Hulajnoga wybranego typu najbliżej ciebie --- " << endl;
                            wsk->pokaz_hulajnoge();
                            cout << "Czy chcesz wypożyczyć te hulajnogę? (Y/N): ";
                            char czy_wypozyczyc;
                            cin >> czy_wypozyczyc;
                            if (czy_wypozyczyc == 'Y' or czy_wypozyczyc == 'y') {
                                cout << "Maksymalny czas wypożyczenia tej hulajnogi: ";
                                cout << zaokraglij(wsk->maks_zasieg()) << " min " << endl;
                                int czas_wypozyczenia;
                                while (true) {
                                    cout << "Wpisz czas wypożyczenia (w minutach): ";
                                    cin >> czas_wypozyczenia;
                                    if (czas_wypozyczenia <= wsk->maks_zasieg() and czas_wypozyczenia > 0) {
                                        break;
                                    } else {
                                        cout << "Nie można wypożyczyć tego modelu na taki czas" << endl;
                                        cout << "Minimalny czas wypożyczenia wynosi: 1 min"<<endl;
                                        cout << "Maksymalny czas wypożyczenia wynosi: " << wsk->maks_zasieg() << endl;
                                    }
                                }
                                double koszt_wyp = wsk->koszt(czas_wypozyczenia);
                                cout << "Koszt wypożyczenia wynosi: " << koszt_wyp << endl;
                                cout << "Porsze wpisac szesciocyfrowy kod BLIK: ";
                                string blik;
                                cin >> blik;
                                if (sprawdz_blik(blik)) {
                                    if (user_log.saldo >= koszt_wyp) {
                                        user_log.saldo -= koszt_wyp;
                                        user_log.zmiana_salda();
                                        cout << "Transakcja zakonczona pomyslnie" << endl;
                                        ladowanie("Wypożyczanie");
                                        logs << "Użytkownik: " << user_log.login << " wypożyczył hulajnoge typu: "
                                        << wsk->typ_hulajnogi << " na czas: "<< czas_wypozyczenia<< " min "<<endl;
                                        user_log.wypozyczenie(czas_wypozyczenia, wsk->typ_hulajnogi);

                                    } else {
                                        cout << "Nie posiadasz takiej kwoty na koncie. \n"
                                                "Doładuj je i spróbuj ponownie" << endl;
                                        sleep(2);
                                    }
                                } else {
                                    system("cls");
                                    cout << "Wprowadzony kod blik jest niepoprawny." << endl;
                                    ladowanie("Przerywanie transakcji");
                                }


                            } else if (czy_wypozyczyc == 'n' or czy_wypozyczyc == 'N') {
                                cout << "ok" << endl;
                            } else {
                                system("cls");
                                cout << "Nie rozumiem polecenia ;(" << endl;
                                cout << "Anulowanie zamówienia" << endl;
                                ladowanie("Wracanie do głównego menu");
                            }
                        }
                    }
                    //WYŚWIETLANIE OFERTY
                    else if (wybor_menu_2 == '2') {
                        Hulajnoga *wsk_p;
                        Standard sp;
                        Speed spp;
                        Teren tp;
                        cout <<"------WYPOŻYCZALNIA HULAJNÓG ELEKTRYCZNYCH SPEEDX-----"<<endl;
                        cout <<"---------------------NASZA OFERTA---------------------"<<endl<<endl;
                        wsk_p = &sp;
                        wsk_p->prezentacja_hulajnogi();
                        cout << "=========================" << endl << endl;
                        wsk_p = &spp;
                        wsk_p->prezentacja_hulajnogi();
                        cout << "=========================" << endl << endl;
                        wsk_p = &tp;
                        wsk_p->prezentacja_hulajnogi();
                        cout << "=========================" << endl << endl;
                        cout << "Nacisnij cokolwiek aby kontunuowac";

                        char wait = _getch(); //czeka na nacisniecie klawisza żeby przejśc do menu głównego
                        system("cls");


                    }
                    else if (wybor_menu_2 == '3') {
                        user_log.pokaz_historie();
                        cout << "Naciśnij dowolny przycisk aby kontynuować";
                        char wait;
                        wait = _getch();
                    }
                    //ZARZĄDZANIE FINANSAMI
                    else if (wybor_menu_2 == '4') {
                        while (true) {
                            system("cls");
                            cout <<"------WYPOŻYCZALNIA HULAJNÓG ELEKTRYCZNYCH SPEEDX-----"<<endl;
                            cout <<"---------------PANEL ZARZĄDZANIA SALDEM---------------"<<endl<<endl;
                            cout << "\n1. Sprawdz stan konta" << endl;
                            cout << "2. Doladuj konto" << endl;
                            cout << "9. Powrot" << endl;
                            int wybor_menu_saldo;
                            cin >> wybor_menu_saldo;
                            //sprawdzenie stanu konta
                            if (wybor_menu_saldo == 1) {
                                system("cls");
                                cout <<"------WYPOŻYCZALNIA HULAJNÓG ELEKTRYCZNYCH SPEEDX-----"<<endl;
                                cout <<"---------------PANEL ZARZĄDZANIA SALDEM---------------"<<endl<<endl;
                                user_log.stan_konta();
                                cout <<endl<<"W celu ochrony twoich danych ta wiadomość zniknie za 5 s";
                                sleep(5);

                            }
                            //doładowanie konta
                            if (wybor_menu_saldo == 2) {
                                user_log.doladowanie();
                                cout << "Doladowanie zakonczone pomyslnie";
                                logs << "Uzytkownik: " << user_log.login << " doladowuje konto"<<endl;
                                continue;
                            }
                            //wyjście do menu główngo
                            if (wybor_menu_saldo == 9) {
                                system("cls");
                                break;
                            }
                            // błędnie wprowadzony argument
                            else{
                                continue;
                            }
                        }
                    }
                    //ustawienia
                    else if (wybor_menu_2 == '5') {
                        cout <<"------WYPOŻYCZALNIA HULAJNÓG ELEKTRYCZNYCH SPEEDX-----"<<endl;
                        cout <<"----------------------USTAWIENIA----------------------"<<endl<<endl;
                        char wybor_ustawienia;
                        cout << "1.Zmien haslo" << endl;
                        cout << "9.Powrót"<<endl;
                        cin >> wybor_ustawienia;
                        switch (wybor_ustawienia) {
                            case '1': {
                                user_log.zmiana_hasla();
                                logs << "Uzytkownik: " << user_log.login << " zmienia haslo" <<endl;
                            }
                            case '9':{
                                break;
                            }
                            default:{
                                cout << "Nie rozumiem polecenia" <<endl;
                                sleep(1);
                            }

                        }
                    }
                    //wylogowanie
                    else if (wybor_menu_2 == '0') {
                        wylogowanie = true;
                        break;
                    }
                    //błędny input w menu głównym
                    else
                    {
                        cout << "Nie ma takiej opcji. Spróbuj jeszcze raz"<<endl;
                    }
                }


            }
            case'0':{
                if(wylogowanie){
                    ladowanie("Wylogowywanie");

                }
                else {
                    ladowanie("Zamykanie aplikacji");
                    cout << "Do zobaczenia." << endl;
                }
                usleep(1200000);
                break;
            }
            default:
                cout << "Nie ma takiego wyboru. Spróbuj ponownie" << endl;
            }
        }
logs.close();
}