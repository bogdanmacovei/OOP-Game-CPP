#ifndef AGENT_H_
#define AGENT_H

#include "arma.h"
#include "armura.h"
#include "harta.h"

class Agent
{
    Arma *arma;
    Armura *armura;
    int hp;
    int xHarta, yHarta;
    std :: string numeAgent;

    public:
        Agent ();
        ~Agent ();

        Arma* getArma () const;
        Armura* getArmura () const;

        void setArma (Arma*);
        void setArmura (Armura*);

        int getX () const;
        int getY () const;

        friend class Harta;

};

#endif // AGENT_H_
