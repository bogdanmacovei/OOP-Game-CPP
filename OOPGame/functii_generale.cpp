#include <bits/stdc++.h>
#include <ctime>
#include <cstdlib>

using namespace std;

/// Functiile generale sunt cele de viata si om folosite in afisarea pe consola
/// si functia itos(int), care imi transforma un int intr-un string, necesara completarii stringului de modificari

string itos (int a)
{
    ostringstream temp;
    temp << a;
    return temp.str();
}

int random (int inf, int sup)
{
//    srand(std::time(0)); // de ce nu merge?
    int random_variable = rand() + (int)&random_variable + 0xfffff + (int)&random;
    return random_variable % (sup - inf + 1) + inf;

//    srand( (unsigned)time( NULL ) );

//    int val;
//    for (int i = 0; i <= rand() % sup + inf; ++i)
//        val = rand () % (sup * sup) + inf % 10 + (sup - inf) * (sup - inf) / 3 + sup * inf;
//    val = val % (sup - inf + 1) + inf;
}

void viata (int x)
{
    int y = x;
    x /= 10;
    char z = 254;
    cout << "[";
    for (int i = 0; i <= x; ++i)
        cout << z;
    for (int i = x + 1; i <= 10; ++i)
        cout << " ";
    cout << "] " << y << "%";
}

void om (int hp1, int hp2)
{
    cout << "\n";
    cout << "        ___ ";       cout << "\t	      (*)\n";
    cout << "       | ..|";       cout << "\t	      /_\\\n";
    cout << "       |___|";       cout << "\t	    {|..|}\n";
    cout << "         |  ";       cout << "\t	     (* )\n";
    cout << "        /|\\ ";      cout << "\t               | [B] \n";
    cout << "       / | \\";      cout << "\t	      /|\\[O] \n";
    cout << "         |  ";       cout << "\t	 <==|= | [T] \n";
    cout << "        / \\ ";      cout << "\t	      / \\ \n";
    cout << "      _/   \\_";     cout << "\t	    _/   \\_ \n";

    cout << "\n        HP: ";    cout << "\t\t      HP: \n  ";

    viata(hp1);
    cout << "\t";
    viata(hp2);

    cout << "\n\n";

}
