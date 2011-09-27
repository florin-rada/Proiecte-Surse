/////////////////////////////////////////////////////////////////////////
//Aceasta functie preia 2 stringuri si le compara la nivel sintactic.  //
//Returneaza o valoare de tip double intre 0 si 1 in functie de cat    //
//de asemanatoare sunt cuvintele.                                      //
//Aceasta are la baza algoritmul lui Levenstein, implementarea se face //
//pe baza pseudocodului de la adresa urmatoare                         //
//http://en.wikipedia.org/wiki/Levenshtein_distance                    //
/////////////////////////////////////////////////////////////////////////

#include "dist.h"

double dist(string s1, string s2)
{
    int num1 = s1.size();
    int num2 = s2.size();

    double array[num1 + 1][num2 + 1];

    if(num1 == 0)
    {
        cout << "Primul string e gol.\n";
        cout << "Nu se poate face comparatia.\n";
        cout << endl;
    }
    else if(num2 == 0)
    {
        cout << "Al doilea string e gol.\n";
        cout << "Nu se poate face comparatia.\n";
        cout << endl;
    }
    else
    {
        for(int i = 0; i <= num1; i++)
        {
            array[i][0] = i;
        }
        for(int j = 0; j <= num2; j++)
        {
            array[0][j] = j;
        }

        for(int i = 1; i <= num1; i++)
        {
            for(int j = 1; j <= num2; j++)
            {
                if(s1[i - 1] == s2[j - 1])
                {
                    array[i][j] = array[i - 1][j - 1];
                }
                else
                {
                    array[i][j] = min(((array[i - 1][j] + 1)), (min((array[i][j - 1] + 1), (array[i - 1][j - 1] + 1))));
                }
            }
        }
    }

    return 1.0 - (array[num1][num2] / min(num1, num2));
}
