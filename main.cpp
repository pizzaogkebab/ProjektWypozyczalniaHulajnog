#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <string>
#include <limits> //chyba nie trzeba
#include <typeinfo> // do testow
#include <vector> // do zmiany elementow w pliku m.in. do doladowania konta

using namespace std;

string hashowanie(string haslo){
    for(int i = 0; i < haslo.length(); i++)
        haslo[i] += 3;
    return haslo;
}

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
        plik << email << endl << imie << endl << nazwisko << endl << login << endl << hashowanie(haslo) << endl << "0" << endl << "=======" << endl;
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
                    }while(hashowanie(haslozklaw) != haslo);
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
};

class Hulajnoga{

public:
    string typ_hulajnogi;
    int predkosc, waga, stanBat;
    float odl;

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
    void pokaz_hulajnoge() const
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
                        while(getline(plik,slinia)){
                          if (slinia == u1.login){
                            break;
                          }
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
                      while (true){
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
                          if (slinia == u1.login){
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
                        } else {
                          pliks << saldodts << endl;
                        }
                      }
                      
                      pliks.close();
                      cout << "Doladowanie konta zakonczone pomyslnie!" << endl;
                      continue;
                    }
                    if (wybor_menu_saldo == 9){
                      break;
                    } else {
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