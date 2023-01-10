#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>
#include <limits> //chyba nie trzeba
#include <typeinfo> // do testow
#include "Uzytkownik.h"
#include "Hulajnoga.h"

using namespace std;


float zaokraglij(float liczba)
{
    float wartosc = (int)(liczba * 100 + .5);
    return (float)wartosc / 100;
}

bool sprawdz_blik(int kod){
    if(kod > 999999){
        return false;
    }
    string kods = to_string(kod);
    if(kods.size() != 6)
    {
        return false;
    }
    if(kods == "000000")
    {
        return false;
    }
    return true;
}



int main() {
    srand(time(0));
    cout << "1.Rejestracja nowego konta"<<endl;
    cout << "2.Logowanie"<<endl;
    int wybor_logowanie = 0;
    cin >> wybor_logowanie;
    system("cls");
    switch(wybor_logowanie)

    {
        //rejestracja
        case 1: {
            Uzytkownik user1;
            user1.dodawanie_uzytkownika();
            system("cls");
            cout << "Zarejestrowano pomyślnie. Pzechodzimy do logowania" << endl;
        }

        //logowanie
        case 2: {
            cout << "Logowanie" << endl;
            Uzytkownik user_log;
            if(user_log.logowanie()) {
                system("cls");
                cout << "Witamy na koncie " << user_log.login << " :)" << endl;
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
                    system("cls");
                    if (wybor_menu_2 == 1){
                        cout <<"WYBIERZ RODZAJ HULAJNOGI"<<endl;
                        cout <<"1.Hulajnogi 'STANDARD'"<<endl;
                        cout <<"2.Hulajnogi 'SPEED'"<<endl;
                        cout <<"3.Hulajnogi 'TEREN'"<<endl;
                        int wybor_hulajnogi;
                        cin >> wybor_hulajnogi;
                        cout << "WYBRANE HULAJNOGI W TWOJEJ OKOLICY"<<endl;
                        Standard s;
                        Speed sp;
                        Teren t;
                        Hulajnoga *wsk;
                        switch(wybor_hulajnogi){
                            case 1:
                            {
                                wsk = &s;
                                break;
                            }
                            case 2:
                            {
                                wsk = &sp;
                                break;
                            }
                            case 3:
                            {
                                wsk = &t;
                                break;
                            }
                            default:
                                cout << "Nie ma takiej opcji" << endl;

                        }
                        cout << "--- Hulajnoga wybranego typu najbliżej ciebie --- "<< endl;
                        wsk -> pokaz_hulajnoge();
                        cout << "Czy chcesz wypożyczyć te hulajnoge? (Y/N): ";
                        char czy_wypozyczyc;
                        cin >> czy_wypozyczyc;
                        if(czy_wypozyczyc == 'Y' or czy_wypozyczyc == 'y')
                        {
                            cout << "Maksymalny czas wypozyczenia tej hulajnogi: ";
                            cout << zaokraglij(wsk->maks_zasieg()) << " min " << endl;
                            cout << "Wypozyczanie..." << endl;
                            cout << "Wpisz czas wypożyczenia (w minutach): ";
                            int czas_wypozyczenia;
                            cin >> czas_wypozyczenia;
                            double koszt_wyp = wsk -> koszt(czas_wypozyczenia);
                            cout << "Koszt wypożyczenia wynosi: " << koszt_wyp << endl;
                            cout << "Porsze wpisac szesciocyfrowy numer BLIK: ";
                            int blik;
                            cin >> blik;
                            if(sprawdz_blik(blik))
                            {
                                user_log.saldo -= koszt_wyp;
                                user_log.zmiana_salda();
                                cout << "Transakcja zakonczona pomyslnie" << endl;
                            }

                        }
                        else if (czy_wypozyczyc == 'n' or czy_wypozyczyc == 'N')
                        {
                            cout << "ok" << endl;
                        }
                        else
                        {
                           cout << "nie rozumiem polecenia ;(";
                        }
                    }
                    if (wybor_menu_2 == 2){
                        cout << "------- NASZA OFERTA -------" << endl << endl;

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
                                user_log.stan_konta();
                            }
                            if (wybor_menu_saldo == 2)
                            {
                                user_log.doladowanie();
                                cout << "Doladowanie zakonczone pomyslnie";
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
        default:
        cout << "Nie ma takiego wyboru" << endl;

    }

}
