#ifndef ARMA_CUTIT_H_
#define ARMA_CUTIT_H_

class Cutit : public Arma
{
    public:
        Cutit ();
        ~Cutit ();

        int getDamage () const;
        std :: string getNume () const;
};

#endif // ARMA_CUTIT_H_
