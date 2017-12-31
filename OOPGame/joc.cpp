#include <bits/stdc++.h>
#include "harta.h"
#include "joc.h"

using namespace std;

/// Joc este clasa pe care o vreau in main, ea preia partile importante din harta si le da utilizatorului
/// astfel ca nu se pot folosi in mod eronat functiile de runda sau de afisare modificari

void Joc :: welcomeScreen ()
{
    system("MODE 250,250");
    cout << "\n\n\t\t\t\t\t\tTHE SHOOTOUT GAME\n\n";

    cout << "\tBine ai venit, utilizator!\n\n";
    cout << "\tThe Shootout este un joc la care participa 4 jucatori (tu si 3 boti), desfasurandu-se pana cei 3 boti\n"
                << "\tsunt omorati sau pana ce tu esti omorat de un bot.\n";
    cout << "\n\tPe harta exista diferite tipuri de iteme, astfel: ";
    cout << "\n\t- C (cutit), G (pistol), R (pusca) reprezinta armele";
    cout << "\n\t- P (primar), S (secundar), T (tertiar) reprezinta tipul de armuri";
    cout << "\n\t- iar L sunt ceilalti agenti, pe care trebuie sa ii dobori";
    cout << "\n\n\tIncepereea duelului are loc automat, iar tot ceea ce ai de facut este sa apesi pe tasta s";
    cout << "\n\tIn functie de tipul de arma si de tipul de armura, vei putea sa ataci oponentul si sa te aperi de acesta";
    cout << "\n\n\tControalele deplasarii pe harta sunt urmatoarele:\n\n";
    cout << "\t\t\t\t\t\t Q W E\n\t\t\t\t\t\t A   D\n\t\t\t\t\t\t Z X C";
    cout << "\n\n\tprezentate in ordine de la coltul stanga-sus pana in coltul dreapta-jos";
    cout << "\n\n\tPentru a opri jocul, tastati p";
    cout << "\n\tpentru a vedea toata harta, tastati h (harta mare poate fi vazuta de maxim 4 ori!)";
    cout << "\n\n\tPentru a intra in modul SIMULARE, tastati r, iar pe durata simularii puteti tasta, in continuare, r";
    cout << "\n\tSimularea se opreste numai in cazul in care apasati tasta t";
    cout << "\n\n\tLa final, in fisierul info.txt veti gasi salvate toate informatiile referitoare la modificarile hartii";
    cout << "\n\n\tSucces!";
    cout << "\n\n";

    system ("pause");
    system ("cls");
}

void Joc :: shootoutGame ()
{
    H.userView ();

    char ch;

    int nrHarta = 0;

    while (ch != 'p')
    {
        if (ch == 'h')
        {
            nrHarta++;
            if (nrHarta >= 4)
                cout << "\n\n\tDin pacate nu mai aveti acces la vizualizarea hartii :(";
            else
                cout << "\n\n" << H;
        }

        if (H.finalizat())
            break;

        cout << "\n\n\tIntroduceti optiunea: ";
        cin >> ch;

        system("cls");

        H.runda(ch);
    }
}

void Joc :: showDetails ()
{
    string modif = H.getModificari();
    ofstream out ("info.txt");
    out << modif;
    out.close();
}
