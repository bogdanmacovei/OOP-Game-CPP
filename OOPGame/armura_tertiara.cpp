#include <bits/stdc++.h>
#include "armura.h"
#include "armura_tertiara.h"

#include "functii_generale.h"

using namespace std;

Tertiara :: Tertiara () : Armura ()
{
    int randProtectie;
    int randNumb = random (2, 16);
    for (int i = 1; i < randNumb; i++)
        randProtectie = random (6, 10);

    Armura :: protectie = randProtectie;
    Armura :: numeArmura = "tertiara";
}

Tertiara :: ~Tertiara ()
{

}

int Tertiara :: getProtectie () const
{
    return protectie;
}

string Tertiara :: getNume () const
{
    return numeArmura;
}
