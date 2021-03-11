#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//funkcja do znalezienia kolejnej liczby pierwszej w stosunku do liczby podanej
int ZnajdzNastepnaPierwsza(int x){
    bool CzyPierwsza = false;
    while (CzyPierwsza != true){
        CzyPierwsza = true;
        x++;
        if (x == 0 || x == 1){
            CzyPierwsza = false;
        }else{
            for (int i = 2; i <= x/2; i++){
                if (x%i == 0) {
                    CzyPierwsza = false;
                    break;
                }
            }
        }
    }
    return x;
}

int main() {
    
    //deklaracja stałych
    int iloscDanych = 100;

    //deklaracja pliku danych
    ifstream plikDane;
    plikDane.open("pary.txt");

    //deklaracja zmiennych
    int liczby[iloscDanych];
    string slowa[iloscDanych];
    int najmniejszaPara;
    bool pierwszaPara = false;

    //wczytanie danych do tablic
    for (int i  = 0; i < iloscDanych; i++){
        plikDane >> liczby[i];
        plikDane >> slowa[i];
    }

    //Wypisanie liczb parzystych w postacii dwoch liczb pierwszych nieparzystych w kolejnosci niemalejacej
    cout<<"Wszystkie liczby parzyste w postacii sumy liczb nieparzystych [format: liczba  suma]"<<endl;
    for (int i  = 0; i < iloscDanych; i++){
        if (liczby[i]%2 == 0){
            cout<<to_string(liczby[i]) + " ";
            int x = 2;
            int y = 2;
            while (x+y != liczby[i]){
                if (ZnajdzNastepnaPierwsza(y) < liczby[i]){
                    y = ZnajdzNastepnaPierwsza(y);
                }else{
                    y = 2;
                    x = ZnajdzNastepnaPierwsza(x);
                }
            }
            if (x < y){
                cout<<to_string(x) + " " + to_string(y)<<endl;
            }else{
                cout<<to_string(y) + " " + to_string(x)<<endl;
            }
        }
    }
    cout<<endl;

    //Znalezienie najdluzszego ciagu takich samych znakow w slowie oraz wypisanie jego dlugosci wraz ze znakami
    cout<<"Najdluzsze ciagi takich samych znakow wraz z ich dlugoscia"<<endl;
    for (int i = 0; i < iloscDanych; i++){
        int n = 1;
        int ntemp = 1;
        string slowo = slowa[i];
        string znak;
        for (int j = 0; j < slowo.length()-1; j++){
            if (slowo[j] == slowo[j+1]){
                ntemp++;
            }else{
                ntemp = 1;
            }
            if (ntemp > n){
                n = ntemp;
                znak = slowo[j];
            }
        }
        if (n > 1){
            for(int k = 0; k < n; k++){
                cout<<znak;
            }
        }else{
            cout<<slowo[0];
        }
        cout<<" " + to_string(n)<<endl;
    }
    cout<<endl;

    //Znalezienie najmniejszej pary sposrod wszystkich par, ktorych dlugosc slowa jest rowna liczbie
    for (int i = 0; i < iloscDanych; i++){
        if (slowa[i].length() == liczby[i]){
            if (pierwszaPara == true){
                if (liczby[i] <= liczby[najmniejszaPara]){
                    najmniejszaPara = i;
                }
            }else{
                najmniejszaPara = i;
                pierwszaPara = true;
            }
        }
    }
    cout<<"Najmniejsza para poprzedzona liczba odpowiadajaca liczbie znakow"<<endl;
    cout<<to_string(liczby[najmniejszaPara]) + " " + slowa[najmniejszaPara]<<endl;
}