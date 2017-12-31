#include <bits/stdc++.h>
#include "arma.h"
#include "arma_cutit.h"

#include "functii_generale.h"

using namespace std;

/// Analog pentru arma_pistol si arma_pusca,
///     generez random un damage, folosesc si un randNumb pentru ca in C++ randomul functioneaza aiurea
///     si mereu prima valoare pe care mi-o lua la randDamage era 4

Cutit :: Cutit () : Arma ()
{
    int randDamage;
    int randNumb = random (2, 16);
    for (int i = 1; i < randNumb; i++)
        randDamage = random (6, 14);

    Arma :: damage = randDamage;
    Arma :: numeArma = "cutit";
}

Cutit :: ~Cutit ()
{

}

int Cutit :: getDamage () const
{
    return damage;
}

string Cutit :: getNume () const
{
    return numeArma;
}
