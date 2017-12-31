#ifndef ARMURA_H_
#define ARMURA_H_

class Armura
{
    protected:
        int protectie;
        std :: string numeArmura;

    public:
        Armura ();
        ~Armura ();
        virtual int getProtectie () const = 0;
        virtual std :: string getNume () const = 0;
};

#endif // ARMURA_H_
