#include <bits/stdc++.h>
#include "agent.h"
#include "arma.h"
#include "armura.h"
#include "arma_cutit.h"
#include "armura_primara.h"

using namespace std;

/// fiecare agent va avea, la inceputul jocului, un cutit si o armura primara

Agent :: Agent () : hp(100), xHarta(0), yHarta(0), numeAgent(" ")
{
    arma = new Cutit();
    armura = new Primara();
}

Agent :: ~Agent ()
{

}

Arma* Agent :: getArma () const
{
    return arma;
}

Armura* Agent :: getArmura () const
{
    return armura;
}

void Agent :: setArma (Arma *armaLocala)
{
    arma = armaLocala;
}

void Agent :: setArmura (Armura *armuraLocala)
{
    armura = armuraLocala;
}

int Agent :: getX () const
{
    return xHarta;
}

int Agent :: getY () const
{
    return yHarta;
}
