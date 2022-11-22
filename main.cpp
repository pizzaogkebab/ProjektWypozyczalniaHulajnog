#include <iostream>
#include <fstream>
#include<cstdlib>
#include <time.h>

using namespace std;

class Uzytkownik
{
    public:
    string email, imie, nazwisko, login, haslo;
    void dodawanie_uzytkownika()
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
        plik << email << endl << imie << endl << nazwisko << endl << login << endl << haslo << endl << "======="<<endl;
        plik.close();
    }
    bool logowanie()
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
                    }while(haslozklaw != haslo);
                    return true;
                }
                else
                {
                    if(licznik == nrlini)
                        nrlini +=6;
                }
                licznik++;
            }
            plik.close();
            return false;
        }
        return false;
    }
};

class Hulajnoga{
    string typ_hulajnogi;
    int predkosc, waga, stanBat;
    float odl;

public:
    void dodaj_hulajnoge(string typ, int bat, float odleglosc)
    {
        typ_hulajnogi = typ;
        if(typ == "standard") {
            predkosc = 30;
            waga = 100;
            stanBat = bat;
            odl = odleglosc;
        }
        else if(typ == "speed")
        {
            predkosc = 45;
            waga = 90;
            stanBat = bat;
            odl = odleglosc;
        }
        else if(typ == "teren")
        {
            predkosc = 25;
            waga = 110;
            stanBat = bat;
            odl = odleglosc;
        }
    }
    void pokaz_hulajnoge()
    {
        cout << "========================="<<endl;
        cout << "Hulajnoga typu "<<typ_hulajnogi<<endl;
        cout << "maksymalna predkosc: "<< predkosc <<" km/h "<<endl;
        cout << "maksymalna waga pasazera: " << waga << "kg" << endl;
        cout << "Stan bateri pojazdu: " << stanBat << "%" <<endl;
        cout << "Odleglosc od ciebie: " << odl << "km" <<endl;
        cout << "========================="<<endl<<endl;
    }

};
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
            cout << "Pzechodzimy do logowania" <<endl;
        }

        case 2:
            cout << "Logowanie"<<endl;
            Uzytkownik u1;
            if(u1.logowanie()) {
                cout << "Witamy na koncie " << u1.login << " :)" << endl;
                cout << "Wybierz co chcesz teraz zrobic" << endl;
                cout << "1. Wypozycz hulajnoge"
                << endl <<"2. Pokaz liste dostepnych hulajnog"
                << endl <<"3. Pokaz historie wypozyczen"
                << endl <<"4. Ustawienia"<<endl;
                int wybor_menu_2;
                cin >> wybor_menu_2;
                switch(wybor_menu_2){
                    case 1:
                    {
                        cout <<"WYBIERZ RODZAJ HULAJNOGI"<<endl;
                        cout <<"1.Wszystkie dotepne hulajnogi" <<endl;
                        cout <<"2.Hulajnogi 'STANDARD'"<<endl;
                        cout <<"3.Hulajnogi 'SPEED'"<<endl;
                        cout <<"4.Hulajnogi 'terenowe'"<<endl;
                        int wybor_hulajnogi = 0;
                        cin >> wybor_hulajnogi;
                        cout << "WYBRANE HULAJNOGI W TWOJEJ OKOLICY"<<endl;
                        switch(wybor_hulajnogi){
                            case 1:
                            case 2:
                            {
                                cout<<"Hulajnogi 'STANDARD': "<<endl;
                                Hulajnoga S[10];
                                for(int i = 0; i < 10; i++)
                                {
                                    int random_1 = (rand() % 95) + 5;
                                    float random_2 = (rand() % 500) / 10.0;
                                    S[i].dodaj_hulajnoge("standard", random_1, random_2);
                                    S[i].pokaz_hulajnoge();
                                }
                            }
                            case 3:
                            {
                                cout<<"Hulajnogi 'SPEED': "<<endl;
                                Hulajnoga SP[10];
                                for(int i = 0; i < 10; i++)
                                {
                                    int random_1 = (rand() % 95) + 5;
                                    float random_2 = (rand() % 500) / 10.0;
                                    SP[i].dodaj_hulajnoge("speed", random_1, random_2);
                                    SP[i].pokaz_hulajnoge();
                                }
                            }
                            case 4:
                            {
                                cout<<"Hulajnogi 'TERENOWA': "<<endl;
                                Hulajnoga T[10];
                                for(int i = 0; i < 10; i++)
                                {
                                    int random_1 = (rand() % 95) + 5;
                                    float random_2 = (rand() % 500) / 10.0;
                                    T[i].dodaj_hulajnoge("teren", random_1, random_2);
                                    T[i].pokaz_hulajnoge();
                                }
                            }
                        }
                    }
                }

            }
            else
                cout <<"Nieznany uzytkownik";
            break;
    }
}
