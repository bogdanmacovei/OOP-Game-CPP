#include <bits/stdc++.h>
#include "arma.h"
#include "arma_pistol.h"

#include "functii_generale.h"

using namespace std;

Pistol :: Pistol () : Arma ()
{
    int randDamage;
    int randNumb = random (2, 16);
    for (int i = 1; i < randNumb; i++)
        randDamage = random (14, 23);

    Arma :: damage = randDamage;
    Arma :: numeArma = "pistol";
}

Pistol :: ~Pistol ()
{

}

int Pistol :: getDamage () const
{
    return damage;
}

string Pistol :: getNume () const
{
    return numeArma;
}
