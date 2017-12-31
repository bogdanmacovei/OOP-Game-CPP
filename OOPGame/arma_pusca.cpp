#include <bits/stdc++.h>
#include "arma.h"
#include "arma_pusca.h"

#include "functii_generale.h"

using namespace std;

Pusca :: Pusca () : Arma ()
{
    int randDamage;
    int randNumb = random (2, 16);
    for (int i = 1; i < randNumb; i++)
        randDamage = random (20, 27);

    Arma :: damage = randDamage;
    Arma :: numeArma = "pusca";
}

Pusca :: ~Pusca ()
{

}

int Pusca :: getDamage () const
{
    return damage;
}

string Pusca :: getNume () const
{
    return numeArma;
}
