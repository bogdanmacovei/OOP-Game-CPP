#ifndef ARMA_PISTOL_H_
#define ARMA_PISTOL_H_

class Pistol : public Arma
{
    public:
        Pistol ();
        ~Pistol ();

        int getDamage () const;
        std :: string getNume () const;
};

#endif // ARMA_PISTOL_H_
