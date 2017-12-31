#ifndef HARTA_H_
#define HARTA_H_

class Agent;

using namespace std;

class Harta
{
    const int dim;
    map <pair<int, int>, string> tipuri;
    int x, y;
    string modificari, modificariSimulare;
    bool jocTerminat;

    bool validPoz (int, int);
    void deplasareAgenti ();
    void afisareHarta ();
    bool amDuel (int, int);
    bool veciniNuli (int, int);
    void dueleaza (int, int);
    void rezolvareDuel ();
    void evaluareTip (int, int, Agent&, string);

    void mutareAgent (Agent&, Agent*, bool, int&, int&, string);

    Harta ();
    ~Harta ();
    void userView ();
    void runda (char);
    string getModificari () const;
    bool finalizat () const;
    friend ostream& operator << (ostream&, Harta);
    void simulare();

    public:

        friend class Joc;


};

#endif // HARTA_H_
