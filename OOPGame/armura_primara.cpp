#include <bits/stdc++.h>
#include "armura.h"
#include "armura_primara.h"

#include "functii_generale.h"

using namespace std;

/// Descriere si pentru armura_secundara si armura_tertiara

/// Analog prezentarii din arma_pistol, generez random o protectie, dupa un randNumb ture
///     pentru ca prima utilizare randProtectie dadea mereu acelasi rezultat

Primara :: Primara () : Armura ()
{
    int randProtectie;
    int randNumb = random (2, 16);
    for (int i = 1; i < randNumb; i++)
        randProtectie = random (1, 4);
        /// am impartit la 3 pentru ca era o protectie mult prea mare, ajungeau lupte infinite (la ambii hp >= 100)

    Armura :: protectie = randProtectie;
    Armura :: numeArmura = "primara";
}

Primara :: ~Primara ()
{

}

int Primara :: getProtectie () const
{
    return protectie;
}

string Primara :: getNume () const
{
    return numeArmura;
}
