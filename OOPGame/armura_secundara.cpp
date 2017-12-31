#include <bits/stdc++.h>
#include "armura.h"
#include "armura_secundara.h"

#include "functii_generale.h"

using namespace std;

Secundara :: Secundara () : Armura ()
{
    int randProtectie;
    int randNumb = random (2, 16);
    for (int i = 1; i < randNumb; i++)
        randProtectie = random (3, 8);

    Armura :: protectie = randProtectie;
    Armura :: numeArmura = "secundara";
}

Secundara :: ~Secundara ()
{

}

int Secundara :: getProtectie () const
{
    return protectie;
}

string Secundara :: getNume () const
{
    return numeArmura;
}
