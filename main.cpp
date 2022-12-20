#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <string>
#include <limits> //chyba nie trzeba
#include <typeinfo> // do testow
#include <vector> // do zmiany elementow w pliku m.in. do doladowania konta
#include "Uzytkownik.h"
#include "Hulajnoga.h"

using namespace std;

int main() {
    srand(time(0));
    cout << "1.Rejestracja nowego konta"<<endl;
    cout << "2.Logowanie"<<endl;
    int wybor_logowanie = 0;
    cin >> wybor_logowanie;
    switch(wybor_logowanie)
    {
        case 1: {
            Uzytkownik u1;
            u1.dodawanie_uzytkownika();
            cout << "Pzechodzimy do logowania" << endl;
        }

        case 2:
            cout << "Logowanie" << endl;
            Uzytkownik u1;
            if(u1.logowanie()) {
                cout << "Witamy na koncie " << u1.login << " :)" << endl;
                while (true){
                    cout << "\nWybierz co chcesz teraz zrobic" << endl;
                    cout << "1. Wypozycz hulajnoge"
                    << endl <<"2. Pokaz liste dostepnych hulajnog"
                    << endl <<"3. Pokaz historie wypozyczen"
                    << endl <<"4. Saldo konta"
                    << endl <<"5. Ustawienia"
                    << endl <<"0. Wyjscie" << endl;
                    int wybor_menu_2;
                    cin >> wybor_menu_2;
                    if (wybor_menu_2 == 1){
                        cout <<"WYBIERZ RODZAJ HULAJNOGI"<<endl;
                        cout <<"1.Hulajnogi 'STANDARD'"<<endl;
                        cout <<"2.Hulajnogi 'SPEED'"<<endl;
                        cout <<"3.Hulajnogi 'terenowe'"<<endl;
                        int wybor_hulajnogi = 0;
                        float pref_odl;
                        cin >> wybor_hulajnogi;
                        cout <<"W jakiej odległości od siebie chcesz zobaczyć hulajnogi: ";
                        cin >> pref_odl;
                        cout << "WYBRANE HULAJNOGI W TWOJEJ OKOLICY"<<endl;
                        switch(wybor_hulajnogi){
                            case 1:
                            {
                                cout<<"Hulajnogi 'STANDARD': "<<endl;
                                Hulajnoga S[10];
                                for(int i = 0; i < 10; i++)
                                {
                                    int random_1 = (rand() % 95) + 5;
                                    float random_2 = ((rand() % 50) + 0.2) / 10.0;
                                    S[i].dodaj_hulajnoge("standard", random_1, random_2);
                                    if(random_2 <= pref_odl)
                                        S[i].pokaz_hulajnoge();

                                }
                                break;
                            }
                            case 2:
                            {
                                cout<<"Hulajnogi 'SPEED': "<<endl;
                                Hulajnoga SP[10];
                                for(int i = 0; i < 10; i++)
                                {
                                    int random_1 = (rand() % 95) + 5;
                                    float random_2 = (rand() % 500) / 10.0;
                                    SP[i].dodaj_hulajnoge("speed", random_1, random_2);
                                    if(random_2 <= pref_odl)
                                        SP[i].pokaz_hulajnoge();
                                }
                                break;
                            }
                            case 3:
                            {
                                cout<<"Hulajnogi 'TERENOWA': "<<endl;
                                Hulajnoga T[10];
                                for(int i = 0; i < 10; i++)
                                {
                                    int random_1 = (rand() % 95) + 5;
                                    float random_2 = (rand() % 500) / 10.0;
                                    T[i].dodaj_hulajnoge("teren", random_1, random_2);
                                    if(random_2 <= pref_odl)
                                        T[i].pokaz_hulajnoge();
                                }
                                break;
                            }
                        }
                    }
                    if (wybor_menu_2 == 2){
                      continue;
                    }
                    if (wybor_menu_2 == 3){
                      continue;
                    }
                    if (wybor_menu_2 == 4){
                        while (true){
                            cout << "\n1. Sprawdz stan konta" << endl;
                            cout << "2. Doladuj konto" << endl;
                            cout << "9. Powrot" << endl;
                            int wybor_menu_saldo;
                            cin >> wybor_menu_saldo;
                            if (wybor_menu_saldo == 1)
                            {
                                fstream plik;
                                plik.open("uzytkownicy.txt", ios::in);

                                if (plik.good() == true){
                                    string slinia;
                                    int snrlini = 1;
                                    while(getline(plik,slinia)){
                                        if (slinia == u1.login && snrlini%7 == 4){
                                            break;
                                        }
                                        snrlini++;
                                    }
                                    getline(plik,slinia);
                                    getline(plik,slinia);
                                    cout << "Aktualne saldo to: " << slinia << endl;
                                }
                                plik.close();
                                continue;;

                            }
                            if (wybor_menu_saldo == 2)
                            {
                                double doladowanie;
                                cout << "Podaj kwote na jaka chcesz doladowac konto: ";
                                while(true){
                                    cin >> doladowanie;
                                    if (doladowanie>0){
                                        break;
                                    }
                                    cout << "Podaj kwote doladowania jeszcze raz: ";
                                }

                                fstream plik;
                                plik.open("uzytkownicy.txt", ios::in);
                                string saldos;
                                int snrlini = 1;
                                if (plik.good() == true){
                                      string slinia;
                                      while(getline(plik,slinia)){
                                          if (slinia == u1.login && snrlini%7 == 4){
                                              break;
                                          }
                                          snrlini++;
                                }
                                    getline(plik,slinia);
                                    getline(plik,slinia);
                                    snrlini ++;
                                    saldos = slinia;
                                }
                                plik.close();

                                double saldo = stod(saldos);
                                saldo += doladowanie;

                                string saldodts = to_string(saldo);

                                fstream przepisanie;

                                przepisanie.open("uzytkownicy.txt");

                                vector<string> tempplik;
                                string templinie;

                                while (getline(przepisanie,templinie)){
                                    tempplik.push_back(templinie);
                                }

                                przepisanie.close();

                                ofstream pliks;

                                pliks.open("uzytkownicy.txt");

                                for (int i = 0; i < tempplik.size(); i++) {
                                    if (i != snrlini){
                                        pliks << tempplik[i] << endl;
                                    }
                                    else
                                    {
                                        pliks << saldodts << endl;
                                    }
                                }

                                pliks.close();
                                cout << "Doladowanie konta zakonczone pomyslnie!" << endl;
                                continue;
                            }
                            if (wybor_menu_saldo == 9){
                                break;
                            }
                            else
                            {
                                continue;
                            }
                        }
                    }
                    if (wybor_menu_2 == 5){
                        continue;
                    }
                    if (wybor_menu_2 == 0){
                        break;
                    }
                }

            }
            else
                cout <<"Nieznany uzytkownik";
            break;
    }
}
