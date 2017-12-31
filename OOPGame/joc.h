#ifndef JOC_H_
#define JOC_H_

#include "harta.h"

class Joc
{
    Harta H;

    public:
        Joc () {};
        ~Joc () {};

        void welcomeScreen ();
        void shootoutGame ();
        void showDetails ();
};

#endif // JOC_H_
