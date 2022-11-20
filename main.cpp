#include <iostream>
#include <fstream>

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
    }
};
int main() {
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

            }
            else
                cout <<"Nieznany uzytkownik";
            break;
    }



}
