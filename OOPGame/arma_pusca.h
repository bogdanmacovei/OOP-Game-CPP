#ifndef ARMA_PUSCA_H_
#define ARMA_PUSCA_H_

class Pusca : public Arma
{
    public:
        Pusca ();
        ~Pusca ();

        int getDamage () const;
        std :: string getNume () const;
};

#endif // ARMA_PUSCA_H_
