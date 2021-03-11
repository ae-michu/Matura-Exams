#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

    //deklaracja stalych
    int iloscDanych = 1000;

    //deklaracja pliku danych
    ifstream plikDane;
    plikDane.open("dane4.txt");

    //deklaracja zmiennych
    int dane[iloscDanych];
    int najwiekszaLuka = 0;
    int najmniejszaLuka = 0;
    int ciag[iloscDanych];
    int dlugoscCiaguTemp = 2;
    int dlugoscCiagu = 0;
    int CiagOstatniaLiczbaPos;
    int CiagOstatniaLiczba;
    int krotnoscLuki = 0;
    int krotnoscLukiTemp = 0;
    vector < int > najczestszeLuki;

    //wczytywanie danych do tablicy
    for (int i = 0; i < iloscDanych; i++) {
        plikDane >> dane[i];
    }

    //szukanie najwiekszej i najmniejszej luki
    for (int i = 0; i < (iloscDanych - 1); i++) {
        if ( abs(dane[i] - dane[i+1]) > najwiekszaLuka ){
            najwiekszaLuka = abs(dane[i] - dane[i+1]);
        }
    }
    najmniejszaLuka = najwiekszaLuka;
    for (int i =  0; i < (iloscDanych - 1); i++){
        if ( abs(dane[i] - dane[i+1]) < najmniejszaLuka ){
            najmniejszaLuka = abs(dane[i] - dane[i+1]);
        }
    }

    //wypisanie wyniku luk
    cout<<"Najwieksza luka: " + to_string(najwiekszaLuka)<<endl;
    cout<<"Najmnniejsza luka: " + to_string(najmniejszaLuka)<<endl;
    cout<<endl;

    //sprawdzanie dlugosci ciagu oraz ostatniej liczby ciagu
    for (int i = 0; i < (iloscDanych - 1); i++) {
        int x1 = abs(dane[i] - dane[i+1]);
        int x2 = abs(dane[i+1] - dane[i+2]);
        if (x1 == x2){
            dlugoscCiaguTemp++;
            if(dlugoscCiaguTemp > dlugoscCiagu){
                dlugoscCiagu = dlugoscCiaguTemp;
                CiagOstatniaLiczba = dane[i+2];
                CiagOstatniaLiczbaPos = i+2;
            }
        }else{
            dlugoscCiaguTemp = 2;
        }
    }

    //wypisanie wyniku ciagu regularnego
    cout<<"Dlugosc ciagu regularnego: " + to_string(dlugoscCiagu)<<endl;
    cout<<"Pierwsza liczba ciagu regularnego: " + to_string(dane[CiagOstatniaLiczbaPos - (dlugoscCiagu-1)])<<endl;
    cout<<"Ostatnia liczba ciagu regularnego: " + to_string(CiagOstatniaLiczba)<<endl;
    cout<<endl;

    //szukanie najwiekszej krotnosci luk
    for (int i = 0; i < (iloscDanych - 1); i++) {
        int x = abs(dane[i] - dane[i+1]);
        for (int j = 0; j < (iloscDanych - 1); j++){
            if (abs(dane[j] - dane[j+1]) == x){
                krotnoscLukiTemp++;
            }
        }
        if(krotnoscLukiTemp > krotnoscLuki){
            krotnoscLuki = krotnoscLukiTemp;
        }
        krotnoscLukiTemp = 0;
    }

    //wypisanie wyniku najwiekszej krotnosci luki
    cout<<"Krotnosc najczestszej luki: " + to_string(krotnoscLuki)<<endl;

    //szukanie luk o najwiekszej krotnosci
    for (int i = 0; i < (iloscDanych - 1); i++) {
        krotnoscLukiTemp = 0;
        int x = abs(dane[i] - dane[i+1]);
        for (int j = 0; j < (iloscDanych - 1); j++){
            if (abs(dane[j] - dane[j+1]) == x){
                krotnoscLukiTemp++;
            }
        }
        if(krotnoscLukiTemp == krotnoscLuki){
            if(find(najczestszeLuki.begin(), najczestszeLuki.end(), abs(dane[i] - dane[i+1])) == najczestszeLuki.end()){
                najczestszeLuki.push_back(abs(dane[i] - dane[i+1]));
            }
        }
    }

    //wypisanie wyniku wszystkich luk o najwiekszej krotnosci
    cout<<"Luki o krotnosci rownej " + to_string(krotnoscLuki) + ": ";
    for(int i = 0; i < najczestszeLuki.size() - 1; i++){
        cout<<to_string(najczestszeLuki[i]) + ", ";
    }
    cout<<najczestszeLuki[najczestszeLuki.size() - 1]<<endl;
}