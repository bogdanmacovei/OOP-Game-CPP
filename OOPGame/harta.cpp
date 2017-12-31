#include <bits/stdc++.h>
#include "harta.h"
#include "agent.h"

#include "arma.h"
#include "arma_cutit.h"
#include "arma_pistol.h"
#include "arma_pusca.h"

#include "armura.h"
#include "armura_primara.h"
#include "armura_secundara.h"
#include "armura_tertiara.h"

#include "functii_generale.h"

using namespace std;

/// Totul se genereaza random pe harta, dar in limita pozitiilor valide
/// orice obiect nou este generat daca inainte era un NULL
/// harta contine pointeri generici, fiind dublata si de o harta de tipuri
/// in versiunea actuala, lucrez mai mult cu map-ul tipuri, dupa realizarea clasei Bot voi lucra mai mult cu map-ul harta

/// pe harta jocului generez 15 arme, 15 armuri si 3 boti + caracterul curent

bool Harta :: veciniNuli (int x, int y)
{
    for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j)
            if (i*i + j*j != 0)
                if (tipuri[{x + i, y + j}] != " ")
                    return false;
    return true;
}

Harta :: Harta () : jocTerminat(false), modificari("Harta a fost initializata\n"), dim(25)
{
//      tipuri este alocat dinamic prin faptul ca este un map (se vede din afisarea asta ca elementele nu sunt consecutive in memorie)
//    for (int i = 0; i < dim; ++i)
//    {
//        for (int j = 0; j <= dim; ++j)
//            cout << &tipuri[{i+1, j}] - &tipuri[{i, j}] << " ";
//        cout << "\n";
//    }
//
//    system ("pause");

    for (int i = 0; i <= dim + 1; ++i)
    {
        for (int j = 0; j <= dim + 1; ++j)
        {
            if (i == 0 || j == 0 || i == dim + 1 || j == dim + 1)
                tipuri[{i, j}] = "1";

            else
                tipuri[{i, j}] = " ";
        }
    }

    for (int i = 3; i <= 8; ++i)
        tipuri[{3, i}] = "1";

    for (int i = 3; i <= 8; ++i)
        tipuri[{i, 3}] = "1";

    for (int i = dim - 3; i >= dim - 9 + 1; --i)
        tipuri[{3, i}] = "1";

    for (int i = 3; i <= 8; ++i)
        tipuri[{i, dim - 3}] = "1";

    for (int i = dim - 9 + 1; i <= dim - 3; ++i)
        tipuri[{i, 3}] = "1";

    for (int i = 3; i <= 8; ++i)
        tipuri[{dim - 3, i}] = "1";

    for (int i = dim - 9 + 1; i <= dim - 3; ++i)
        tipuri[{dim - 3, i}] = "1";

    for (int i = dim - 3; i >= dim - 9 + 1; --i)
        tipuri[{i, dim - 3}] = "1";


    /// Adaug cei 4 agenti pe harta. Ultimul agent va fi mereu jucatorul curent (setez x si y in clasa)
    ///     Obs: adaug agent doar daca pozitia este libera

    int n = 4;
    while (n)
    {
        int iPoz = random (1, dim);
        int jPoz = random (1, dim);
        if (tipuri[{iPoz, jPoz}] == " " && veciniNuli(iPoz, jPoz))
        {
            tipuri[{iPoz, jPoz}] = "L";

            n--;

            if (!n)
                x = iPoz, y = jPoz;
        }
    }

    /// Adaug armele pe harta (cutit, pistol, pusca): sunt 5 din fiecare

    n = 5;

    while (n)
    {
        int iPoz, jPoz;

        do
        {
            iPoz = random (1, dim);
            jPoz = random (1, dim);
        }
        while (tipuri[{iPoz, jPoz}] != " " && !veciniNuli(iPoz, jPoz));

        tipuri[{iPoz, jPoz}] = "C";

        do
        {
            iPoz = random (1, dim);
            jPoz = random (1, dim);
        }
        while (tipuri[{iPoz, jPoz}] != " " && !veciniNuli(iPoz, jPoz));

        tipuri[{iPoz, jPoz}] = "G";

        do
        {
            iPoz = random (1, dim);
            jPoz = random (1, dim);
        }
        while (tipuri[{iPoz, jPoz}] != " " && !veciniNuli(iPoz, jPoz));

        tipuri[{iPoz, jPoz}] = "R";

        n--;

    }

    /// Adaug pe harta armurile: sunt 5 de fiecare tip si sunt 3 tipuri

    n = 5;

    while (n)
    {
        int iPoz, jPoz;

        do
        {
            iPoz = random (1, dim);
            jPoz = random (1, dim);
        }
        while (tipuri[{iPoz, jPoz}] != " " && !veciniNuli(iPoz, jPoz));

        tipuri[{iPoz, jPoz}] = "P";


        do
        {
            iPoz = random (1, dim);
            jPoz = random (1, dim);
        }
        while (tipuri[{iPoz, jPoz}] != " " && !veciniNuli(iPoz, jPoz));

        tipuri[{iPoz, jPoz}] = "S";

        do
        {
            iPoz = random (1, dim);
            jPoz = random (1, dim);
        }
        while (tipuri[{iPoz, jPoz}] != " " && !veciniNuli(iPoz, jPoz));

        tipuri[{iPoz, jPoz}] = "T";

        n--;

    }
}

Harta :: ~Harta ()
{
    modificari = "";
    tipuri.clear();
}

/// stringul care va retine toate modificarile realizate asupra hartii in timpul jocului

string Harta :: getModificari () const
{
    return modificari;
}

bool Harta :: finalizat () const
{
    return jocTerminat;
}

ostream& operator << (ostream &out, Harta H)
{
    for (int i = 1; i <= H.dim; ++i)
    {
        for (int j = 1; j <= H.dim; ++j)
            out << "+---";
        out << "+\n";
        for (int j = 1; j <= H.dim; ++j)
        {
            out << "|";
            if (i == H.x && j == H.y)
                out << "YOU";
            else out << " " << H.tipuri[{i, j}] << " ";
        }
        out << "|\n";
    }
    for (int j = 1; j <= H.dim; ++j)
            out << "+---";
    out << "+\n";

    return out;
}

bool isSim = false;

void Harta :: userView ()
{
    if (isSim)
    {
        cout << "Sunteti in modul de simulare!\n\n";
        return;
    }

    cout << "\n\n\tX: " << y << ".00000" << "\n\tY: " << x << ".00000\n\n";

    for (int i = -1; i <= 1; ++i)
    {
        cout << "\t\t";

        for (int j = -1; j <= 1; ++j)
            cout << "+-------";
        cout << "+\n";

        cout << "\t\t";
        for (int j = -1; j <= 1; ++j)
            cout << "|       ";
        cout << "|\n";

        cout << "\t\t";
        for (int j = -1; j <= 1; ++j)
        {
            if (i == 0 && j == 0)
                cout << "|  " << "YOU" << "  ";
            else
            {
                cout << "|   ";
                cout << tipuri[{x+i, y+j}] << "   ";
            }
        }
        cout << "|\n";

        cout << "\t\t";
        for (int j = -1; j <= 1; ++j)
            cout << "|       ";
        cout << "|\n";
    }

    cout << "\t\t";
    for (int j = -1; j <= 1; ++j)
            cout << "+-------";
    cout << "+";
}

bool Harta :: amDuel (int xPoz, int yPoz)
{
    for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j)

            if (tipuri[{xPoz + i, yPoz + j}] == "L" && (i*i + j*j != 0))
                return true;

    return false;
}

bool Harta :: validPoz (int xPoz, int yPoz)
{
    return !(tipuri[{xPoz, yPoz}] == "1");
}

/// Functia de deplasare agenti
///     Explicatie: la fiecare runda efectuata de catre mine, un agent se poate muta random in cele 8 pozitii
///                 daca dau peste el, am de sustinut duelul
///                 daca se intalnesc intre ei, se vor lupta afisand un mesaj
///                 mutarile lor sunt strict random, nu vor alege anumite iteme din jur
///                 mutarile lor sunt simultane, cei 4 agenti (inclusiv caracterul meu) se muta in acelasi timp, apoi sunt verificarile
///                 daca se intalnesc >=2 agenti in aria de vizibilitate de 3x3, evaluarea luptelor se va face in sensul coordonatelor:
///                     (0, 0) - eu, in lupta cu (-1,-1), (-1,0), (-1,1), (0,-1), (0,1), (1,-1), (1,0), (1,1)
/// Folosesc map-ul de tipuri pentru a-i gasi, vor fi evaluate mutarile de la stanga la dreapta si de sus in jos

/// Stiu ca am doar 3 agenti externi

Agent *jucator1 = NULL, *jucator2 = NULL, *jucator3 = NULL;
Agent jucatorLocal1, jucatorLocal2, jucatorLocal3;

bool isDeadB1 = false, isDeadB2 = false, isDeadB3 = false;
int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;

void Harta :: evaluareTip (int x, int y, Agent &jucatorLocal, string nume)
{
    if (tipuri[{x, y}] == "G")
    {
        Arma *pistol = new Pistol();
        if (pistol->getDamage() > jucatorLocal.getArma()->getDamage())
            jucatorLocal.setArma(pistol), modificari += nume + " a schimbat arma in pistol\n";
        if (isSim)
            modificariSimulare += nume + " a schimbat arma in pistol\n";
    }

    else if (tipuri[{x, y}] == "C")
    {
        Arma *cutit = new Cutit();
        if (cutit->getDamage() > jucatorLocal.getArma()->getDamage())
            jucatorLocal.setArma(cutit), modificari += nume + " a schimbat arma in cutit\n";
        if (isSim)
            modificariSimulare += nume + " a schimbat arma in cutit\n";
    }

    else if (tipuri[{x, y}] == "R")
    {
        Arma *pusca = new Pusca();
        if (pusca->getDamage() > jucatorLocal.getArma()->getDamage())
            jucatorLocal.setArma(pusca), modificari += nume + " a schimbat arma in pusca\n";
        if (isSim)
            modificariSimulare += nume + " a schimbat arma in pusca\n";
    }

    else if (tipuri[{x, y}] == "P")
    {
        Armura *primara = new Primara();
        if (primara->getProtectie() > jucatorLocal.getArmura()->getProtectie())
            jucatorLocal.setArmura(primara), modificari += nume + " a schimbat armura in armura primara\n";
        if (isSim)
            modificariSimulare += nume + " a schimbat armura in armura primara\n";
    }

    else if (tipuri[{x, y}] == "S")
    {
        Armura *secundara = new Secundara();
        if (secundara->getProtectie() > jucatorLocal.getArmura()->getProtectie())
            jucatorLocal.setArmura(secundara), modificari += nume + " a schimbat armura in armura secundara\n";
        if (isSim)
            modificariSimulare += nume + " a schimbat armura in armura secundara\n";
    }

    else if (tipuri[{x, y}] == "T")
    {
        Armura *tertiara = new Tertiara();
        if (tertiara->getProtectie() > jucatorLocal.getArmura()->getProtectie())
            jucatorLocal.setArmura(tertiara), modificari += nume + " a schimbat armura in armura secundara\n";
        if (isSim)
            modificariSimulare += nume + " a schimbat armura in armura secundara\n";
    }
}

/// Deplasarea si gestionarera agentilor

/// La prima tura pe harta, botii sunt initializati, iar in restul turelor se misca in functie de aria lor de vizibilitate
///     miscarea se face strict, ei nu pot sta pe loc si nu pot accesa pozitii blocate
///     (conditiile de xRand * xRand + yRand * yRand != 0 si pozitia pe harta sa nu fie 1 - codificarea zonei blocate)
/// de fiecare data, se verifica daca pozitia pe care au ajuns contine un item, care este luat si apoi verificat
///     cu logica: daca ei au gasit un item, chiar daca nu este cel mai bun pentru ei, este luat ca sa nu-l mai pot gasi eu
///                 (pentru ca acel item putea sa fie bun pentru mine)

void Harta :: mutareAgent (Agent &jucatorLocal, Agent *jucator, bool isDeadB, int &a1, int &a2, string nume)
{
    if (!isDeadB)
    {
        int xRand = 0, yRand = 0;
        if (!veciniNuli (a1, a2))
        {
            for (int i = -1; i <= 1; ++i)
                for (int j = -1; j <= 1; ++j)
                    if (tipuri[{a1 + i, a2 + j}] != " " && i*i + j*j != 0 && tipuri[{a1 + i, a2 + j}] != "1" && tipuri[{a1 + i, a2 + i}] != "L")
                        xRand = i, yRand = j;
        }

        if (xRand == 0 && yRand == 0)
            do
            {
                xRand = random (-1, 1);
                yRand = random (-1, 1);
            }
            while (!validPoz(a1 + xRand, a2 + yRand) || (xRand*xRand + yRand*yRand == 0));

        a1 = a1 + xRand;
        a2 = a2 + yRand;

        /// Verific daca are de facut vreo schimbare (cod lung)

        evaluareTip (a1, a2, jucatorLocal, nume);

        tipuri[{a1, a2}] = "L";

        tipuri[{a1 - xRand, a2 - yRand}] = " ";

        modificari += nume + " s-a deplasat in punctul (" + itos(a1) + ", " + itos(a2) + ")\n";

        if (isSim)
                modificariSimulare += nume + " s-a deplasat in punctul (" + itos(a1) + ", " + itos(a2) + ")\n";

        jucatorLocal.xHarta = a1;
        jucatorLocal.yHarta = a2;

        if (jucatorLocal.hp < 100)
            jucatorLocal.hp += 3; // se reface viata dupa o batalie

        if (jucatorLocal.hp > 100)
            jucatorLocal.hp = 100;

    }

}

void Harta :: deplasareAgenti()
{
    int xRand, yRand;

    if (!jucator1 && !jucator2 && !jucator3)
    {
        int k = 0;

        for (int i = 1; i <= dim && k <= 3; ++i)
            for (int j = 1; j <= dim && k <= 3; ++j)
                if (i != x && j != y)
                    if (tipuri[{i, j}] == "L")
                    {
                        k++;

                        if (k == 1)
                        {
                            do
                            {
                                xRand = random (-1, 1);
                                yRand = random (-1, 1);
                            }
                            while (!validPoz(i + xRand, j + yRand) || (xRand*xRand + yRand*yRand == 0));

                            if (!jucator1)
                            {
                                jucator1 = &jucatorLocal1;
                                tipuri[{i + xRand, j + yRand}] = "L";
                                jucatorLocal1.numeAgent = "Bot1";
                                a1 = i + xRand, a2 = j + yRand;
                                jucatorLocal1.xHarta = a1, jucatorLocal1.yHarta = a2;

                                tipuri[{i, j}] = " ";
                            }
                        }

                        else if (k == 2)
                        {
                            do
                            {
                                xRand = random (-1, 1);
                                yRand = random (-1, 1);
                            }
                            while (!validPoz(i + xRand, j + yRand) || (xRand*xRand + yRand*yRand == 0));

                            if (!jucator2)
                            {
                                jucator2 = &jucatorLocal2;
                                tipuri[{i + xRand, j + yRand}] = "L";
                                jucatorLocal2.numeAgent = "Bot2";
                                b1 = i + xRand, b2 = j + yRand;
                                jucatorLocal2.xHarta = b1, jucatorLocal2.yHarta = b2;

                                tipuri[{i, j}] = " ";
                            }
                        }

                        else if (k == 3)
                        {
                            do
                            {
                                xRand = random (-1, 1);
                                yRand = random (-1, 1);
                            }
                            while (!validPoz(i + xRand, j + yRand) || (xRand*xRand + yRand*yRand == 0));

                            if (!jucator3)
                            {
                                jucator3 = &jucatorLocal3;
                                tipuri[{i + xRand, j + yRand}] = "L";
                                jucatorLocal3.numeAgent = "Bot3";
                                c1 = i + xRand, c2 = j + yRand;
                                jucatorLocal3.xHarta = c1, jucatorLocal3.yHarta = c2;

                                tipuri[{i, j}] = " ";
                            }
                        }
                    }
    }

    mutareAgent (jucatorLocal1, jucator1, isDeadB1, a1, a2, "Bot1");
    mutareAgent (jucatorLocal2, jucator2, isDeadB2, b1, b2, "Bot2");
    mutareAgent (jucatorLocal3, jucator3, isDeadB3, c1, c2, "Bot3");
}

/// Duelul intre boti se desfasoara analog duelului meu
/// Daca doi boti se afla unul in raza de vizibilitate a celuilalt
///     atunci incepe duelul in functie de armele si armurile fiecaruia
///     hp_actual_bot = hp_vechi_bot - damage_arma_atacator + bot_protectie
///     cu mentiunea ca daca, datorita protectiei, hp_actual_bot >= 100, el ramane 100
///     duelul se desfasoara pana ce un hp ajunge <= 0, moment in care botul pierzator este sters, i se atribuie valoarea dead
///     si se afiseaza mesajul ca a murit inclusiv pentru mine

void Harta :: rezolvareDuel ()
{
    /// Pentru jucatorulLocal1

    if (!isDeadB1)
        for (int i = -1; i <= 1; ++i)
            for (int j = -1; j <= 1; ++j)
                if (i*i + j*j != 0)
                    if (tipuri[{jucatorLocal1.xHarta + i, jucatorLocal1.yHarta + j}] == "L")
                    {
                        if (jucatorLocal1.xHarta + i == jucatorLocal2.xHarta && jucatorLocal1.yHarta + j == jucatorLocal2.yHarta)
                        {
                            while (jucatorLocal1.hp >= 0 && jucatorLocal2.hp >= 0)
                            {
                                jucatorLocal1.hp = jucatorLocal1.hp - jucatorLocal2.getArma()->getDamage() + jucatorLocal1.getArmura()->getProtectie();
                                jucatorLocal2.hp = jucatorLocal2.hp - jucatorLocal1.getArma()->getDamage() + jucatorLocal2.getArmura()->getProtectie();

                                if (jucatorLocal1.hp > 100)
                                    jucatorLocal1.hp = 100;
                                if (jucatorLocal2.hp > 100)
                                    jucatorLocal2.hp = 100;

                                if (jucatorLocal1.hp < 0)
                                {
                                    isDeadB1 = true;
                                    modificari += "Bot1 a pierdut\n";

                                    if (isSim)
                                        modificariSimulare += "Bot1 a pierdut\n";

                                    tipuri[{jucatorLocal1.xHarta, jucatorLocal1.yHarta}] = " ";
                                    jucatorLocal1.hp = 0;
                                    return;
                                }

                                else if (jucatorLocal2.hp < 0)
                                {
                                    isDeadB2 = true;
                                    modificari += "Bot2 a pierdut\n";

                                    if (isSim)
                                        modificariSimulare += "Bot2 a pierdut\n";

                                    tipuri[{jucatorLocal2.xHarta, jucatorLocal2.yHarta}] = " ";
                                    jucatorLocal2.hp = 0;
                                    return;
                                }
                            }
                        }

                        else if (jucatorLocal1.xHarta + i == jucatorLocal3.xHarta && jucatorLocal1.yHarta + j == jucatorLocal3.yHarta)
                        {
                            while (jucatorLocal1.hp >= 0 && jucatorLocal2.hp >= 0)
                            {
                                jucatorLocal1.hp = jucatorLocal1.hp - jucatorLocal3.getArma()->getDamage() + jucatorLocal1.getArmura()->getProtectie();
                                jucatorLocal3.hp = jucatorLocal3.hp - jucatorLocal1.getArma()->getDamage() + jucatorLocal3.getArmura()->getProtectie();

                                if (jucatorLocal1.hp > 100)
                                    jucatorLocal1.hp = 100;
                                if (jucatorLocal3.hp > 100)
                                    jucatorLocal3.hp = 100;

                                if (jucatorLocal1.hp < 0)
                                {
                                    isDeadB1 = true;
                                    modificari += "Bot1 a pierdut\n";

                                    if (isSim)
                                        modificariSimulare += "Bot1 a pierdut\n";

                                    tipuri[{jucatorLocal1.xHarta, jucatorLocal1.yHarta}] = " ";
                                    jucatorLocal1.hp = 0;
                                    return;
                                }

                                else if (jucatorLocal3.hp < 0)
                                {
                                    isDeadB3 = true;
                                    modificari += "Bot3 a pierdut\n";

                                    if (isSim)
                                        modificariSimulare += "Bot3 a pierdut\n";

                                    tipuri[{jucatorLocal3.xHarta, jucatorLocal3.yHarta}] = " ";
                                    jucatorLocal3.hp = 0;
                                    return;
                                }
                            }
                        }
                    }

    if(!isDeadB2)
        for (int i = -1; i <= 1; ++i)
            for (int j = -1; j <= 1; ++j)
                if (i*i + j*j != 0)
                    if (tipuri[{jucatorLocal2.xHarta + i, jucatorLocal2.yHarta + j}] == "L")
                    {
                        if (jucatorLocal2.xHarta + i == jucatorLocal3.xHarta && jucatorLocal2.yHarta + j == jucatorLocal3.yHarta)
                        {
                            while (jucatorLocal2.hp >= 0 && jucatorLocal2.hp >= 0)
                            {
                                jucatorLocal2.hp = jucatorLocal2.hp - jucatorLocal3.getArma()->getDamage() + jucatorLocal2.getArmura()->getProtectie();
                                jucatorLocal3.hp = jucatorLocal3.hp - jucatorLocal2.getArma()->getDamage() + jucatorLocal3.getArmura()->getProtectie();

                                if (jucatorLocal2.hp > 100)
                                    jucatorLocal2.hp = 100;
                                if (jucatorLocal3.hp > 100)
                                    jucatorLocal3.hp = 100;

                                if (jucatorLocal2.hp < 0)
                                {
                                    isDeadB2 = true;
                                    modificari += "Bot2 a pierdut\n";

                                    if (isSim)
                                        modificariSimulare += "Bot2 a pierdut\n";

                                    tipuri[{jucatorLocal2.xHarta, jucatorLocal2.yHarta}] = " ";
                                    jucatorLocal2.hp = 0;
                                    return;
                                }

                                else if (jucatorLocal3.hp < 0)
                                {
                                    isDeadB3 = true;
                                    modificari += "Bot3 a pierdut\n";

                                    if (isSim)
                                        modificariSimulare += "Bot3 a pierdut\n";

                                    tipuri[{jucatorLocal3.xHarta, jucatorLocal3.yHarta}] = " ";
                                    jucatorLocal3.hp = 0;
                                    return;
                                }
                            }
                        }
                    }

}

Agent agentLocal;

/// Functie pentru lupta mea individuala cu agentul care se afla in aria mea de vizibilitate
/// caut pozitia agentului din jurul meu, si desfasor lupta pana cand unul dintre noi are hp <= 0
/// pentru fiecare lovitura, formula de calcul este
///     hp_nou = hp_vechi - damage_atacator + protectia_mea

void Harta :: dueleaza (int xPoz, int yPoz)
{
    /// Cautam agentul

    int xAgent = 0, yAgent = 0; // aici stochez agentul

    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            if (i*i + j*j != 0)
                if (tipuri[{xPoz + i, yPoz + j}] == "L")
                {
                    xAgent = xPoz + i, yAgent = yPoz + j;
                }

    /// Agentul vrea lupta, il identificam

//    Agent luptator = *(static_cast <Agent*> (harta[{xAgent, yAgent}]));

    Agent luptator;

    if (xAgent == jucatorLocal1.xHarta && yAgent == jucatorLocal1.yHarta)
        luptator = jucatorLocal1;

    else if (xAgent == jucatorLocal2.xHarta && yAgent == jucatorLocal2.yHarta)
        luptator = jucatorLocal2;

    else if (xAgent == jucatorLocal3.xHarta && yAgent == jucatorLocal3.yHarta)
        luptator = jucatorLocal3;

    system("cls");

    cout << "Tastati s pentru a incepe lupta: ";

    char comanda;
    do
    {
        cin >> comanda;
    } while (comanda != 's');

    /// om este o functie din functii_generale.h, deseneaza pe ecran cei doi luptatori si afiseaza hp-ul fiecaruia

    om(agentLocal.hp, luptator.hp);

    while (agentLocal.hp >= 0 && luptator.hp >= 0)
    {
        agentLocal.hp = agentLocal.hp - luptator.getArma()->getDamage() + agentLocal.getArmura()->getProtectie();
        luptator.hp = luptator.hp - agentLocal.getArma()->getDamage() + luptator.getArmura()->getProtectie();

        /// daca, datorita protectiei, se depaseste hp = 100, el va ramane la valoarea lui maxima
        ///     considerandu-se ca lovitura atacatorului nu a produs pagube

        if (agentLocal.hp > 100)
            agentLocal.hp = 100;

        if (luptator.hp > 100)
            luptator.hp = 100;

        /// prioritatea in evaluarea hp-ului o are luptatorul, pentru ca jucatorul curent sa aiba sanse mai mari de castig

        if (luptator.hp <= 0)
        {
            luptator.hp = 0;

            if (agentLocal.hp <= 0)
                agentLocal.hp = 1;

            system ("cls");

            om (agentLocal.hp, luptator.hp);

            /// parte de evaluare proasta - de refacut in functie de luptator, nu caut mereu cine este luptatorul

            if (luptator.numeAgent == "Bot1")
            {
                isDeadB1 = true, modificari += "Bot1 a pierdut\n", jucatorLocal1.hp = 0;
                tipuri[{jucatorLocal1.xHarta, jucatorLocal1.yHarta}] = " ";
            }

            if (luptator.numeAgent == "Bot2")
            {
                isDeadB2 = true, modificari += "Bot2 a pierdut\n", jucatorLocal2.hp = 0;
                tipuri[{jucatorLocal2.xHarta, jucatorLocal2.yHarta}] = " ";
            }

            if (luptator.numeAgent == "Bot3")
            {
                isDeadB3 = true, modificari += "Bot3 a pierdut\n", jucatorLocal3.hp = 0;
                tipuri[{jucatorLocal3.xHarta, jucatorLocal3.yHarta}] = " ";
            }

            cout << "\n\nAti invins!\n\n", modificari += "Ati castigat duelul\n";
            system("pause");

            /// stergem luptatorul
            tipuri[{luptator.xHarta, luptator.yHarta}] = " ";

            return;
        }

        else if (agentLocal.hp <= 0)
        {
            agentLocal.hp = 0;

            system ("cls");

            om(agentLocal.hp, luptator.hp);

            cout << "\n\nAti pierdut!\n\n", modificari += "Ati pierdut duelul\nJoc terminat\n";
            system("pause");
            jocTerminat = true;
            break;
        }

        else
        {
            cout << "\n\nTasati s pentru a continua: ";
            do
            {
                cin >> comanda;
            } while (comanda != 's');

            system("cls");

            om (agentLocal.hp, luptator.hp);
        }
    }

}

/// runda imbina mare parte din functiile anterioare, efectuand urmatoarele
///     la fiecare runda, daca hp-ul meu este sub 95, creste cu 5 (dar daca era 94, ajunge la maxim 99 si ramane acolo)
///     se alege directia de mers conform instructiunilor ecranului de pornire
///     daca nu este valida pozitia aleasa, coordonatele nu se modifica
///     daca este valida, atunci vechea pozitie se sterge si, in acelasi timp
///         se muta agentii
///         si se rezolva duelurile dintre ei
///     daca m-am deplasat pe un item, il voi lua, chiar daca imi voi aplica schimbarea de item sau nu
///         logica pentru a lua un item chiar daca nu e util, este aceea de a nu lasa un bot sa mai poata lua acest item

int nrSim = 0;
void Harta :: simulare ()
{
    system ("CLS");
    cout << "\n\n\tSunteti in modul de simulare. Continuati sa tastati r.\n\n";

    if (nrSim == 0)
    {
        cout << "\tInstructiuni: Tastati r pentru a vedea modul in care rundele sunt simulate.\n";
        cout << "\tIn timpul desfasurarii rundelor, veti fi scos de pe harta, jucandu-se doar botii.\n";
        cout << "\tPentru a opri simularea, apasati tasta t\n\n";
    }

    else
    {
        modificariSimulare += "A fost runda " + itos (nrSim) + "\n\n";

        cout << modificariSimulare << "\n";
    }

    nrSim ++;
    system ("pause");
    system ("CLS");
}

int xRez = 0, yRez = 0; // le folosesc pentru simularea rundelor

void Harta :: runda (char ch)
{
    int xCopy = x, yCopy = y;

    if (agentLocal.hp < 100)
        agentLocal.hp += 3; // se reface viata dupa o batalie

    if (agentLocal.hp > 100)
        agentLocal.hp = 100;

    switch (ch)
    {
        case 'q': x--; y--; break;
        case 'w': x--;      break;
        case 'e': x--; y++; break;
        case 'a':      y--; break;
        case 'd':      y++; break;
        case 'z': x++; y--; break;
        case 'x': x++;      break;
        case 'c': x++; y++; break;

        case 'r': isSim = true;
                  simulare();
                  modificari += "Ati accesat modul simulare\n";
                  tipuri [{x, y}] = " ";
                  if (xRez == 0 && yRez == 0)
                    xRez = x, yRez = y;
                  x = -2, y = -2;
                  break;

        case 't': modificariSimulare = "";
                  if (isSim)
                    x = xRez, y = yRez;
                  tipuri [{x, y}] = "L";
                  nrSim = 0;
                  isSim = false;
                  break;
    }

    if (!validPoz(x, y))
    {
        x = xCopy, y = yCopy;
        userView();
    }

    else
    {
        tipuri[{xCopy, yCopy}] = " ";

        deplasareAgenti();
        rezolvareDuel();

        /// Verific daca am ales un anumit item de pe harta

        modificari += "V-ati mutat in punctul (" + itos(x) + ", " + itos(y) + ")\n";

        evaluareTip (x, y, agentLocal, "Jucatorul uman");

        /// Iau item-ul, apoi inlocuiesc pozitia acelui item cu pozitia mea

        tipuri[{x, y}] = "L";

        userView();

//        (*(static_cast<Agent*>(harta[{x,y}]))).getArma()->getDamage();

        if (isSim)
            cout << "Tastati r pentru a continua simularea sau t pentru a opri simularea";
        else
        {

            cout << "\n\n\tArma ta: " << agentLocal.getArma()->getNume();
            cout << "\n\tDamage: " << agentLocal.getArma()->getDamage();
            cout << "\n\tArmura ta: " << agentLocal.getArmura()->getNume();
            cout << "\n\tProtectie: " << agentLocal.getArmura()->getProtectie();
            cout << "\n\tHP: " << agentLocal.hp;
            if (isDeadB1)
                cout << "\n\tBot1 a pierdut";
            if (isDeadB2)
                cout << "\n\tBot2 a pierdut";
            if (isDeadB3)
                cout << "\n\tBot3 a pierdut";
        }

        if (isDeadB1 && isDeadB2 && isDeadB3)
        {
            jocTerminat = true, modificari += "Ati castigat jocul\n";
            system ("CLS");
            cout << "\n\nFelicitari, ati castigat jocul!\n\n";
        }

        if (amDuel(x, y))
        {
            modificari += "Ati intrat intr-un duel\n";

            /// Pornesc duelul

            dueleaza (x, y);

            system("CLS");

            userView();

            if (jocTerminat)
                return;
        }
    }
}
