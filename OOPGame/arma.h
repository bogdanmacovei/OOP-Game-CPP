#ifndef ARMA_H_
#define ARMA_H_

class Arma
{
    protected:
        int damage;                 // cat de mult poate lovi
        std :: string numeArma;     // vreau acces direct la nume

    public:
        Arma ();
        ~Arma ();
        virtual int getDamage () const = 0;
        virtual std :: string getNume () const = 0;
};

#endif // ARMA_H_
