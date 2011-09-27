#ifndef DIST_H_INCLUDED
#define DIST_H_INCLUDED

/////////////////////////////////////////////////////////////////////////
//Aceasta functie preia 2 stringuri si le compara la nivel sintactic.  //
//Returneaza o valoare de tip double intre 0 si 1 in functie de cat    //
//de asemanatoare sunt cuvintele.                                      //
//Aceasta are la baza algoritmul lui Levenstein, implementarea se face //
//pe baza pseudocodului de la adresa urmatoare                         //
//http://en.wikipedia.org/wiki/Levenshtein_distance                    //
/////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;
using std::min;

double dist(string s1, string s2);

#endif // DIST_H_INCLUDED
