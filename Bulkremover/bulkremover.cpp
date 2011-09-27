/*Applicatie facuta de catre Rada Florin
Strict pentru uz personal
Acest program este eliberat fara nici o garantie sub licenta GPL
Programul v-a cauta prin fisierele din directorul dat dupa text-ul dat
si il va sterge
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <boost/filesystem.hpp>
#include <ctime>
#include <stdio.h>

using namespace std;
using namespace boost::filesystem;

typedef vector<path> vec;

// Functie pentru creerea unor fisiere random unde sa fie depozitata adresa temporara a fisierelor din fiecare folder
string randFisier()
{
    char alfabet[25] = {'a', 'b', 'c', 'd', 'f', 'g', 'h', 'i', 'j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    string randFisierOutput;
    srand(time(0));
    for(int i = 0; i < 5;i++)
    {
        int randLetter = rand() & 25;
        randFisierOutput += alfabet[randLetter];
    }
    randFisierOutput.append(".txt");
    return randFisierOutput;
}

//scoate new line-urile de dinaintea si de dupa stringul nostru
string removeNewLines(string linie)
{
    string temp = linie;
    if((temp[0] == '\n') || (temp[0] == '\r'))
    {
        temp.erase(0);
    }
    if((temp[(temp.size() - 1)] == '\n') || (temp[(temp.size() - 1)] == '\r'))
    {
        temp.erase((temp.size() - 1));
    }
    return temp;
}

//Functia ce va manipula fiecare fisier in parte
void removeFromFile(string numeFisier, char* adresaFisierTextDeScos)
{
    string fisierBuffer;
    string linieDeSters;
    string linie; // va tine linia temporara inainte sa fie prelucrata (scoaterea lui \n sau \r de la inceput si sfarsit;
    string fisierParte1;
    string fisierParte2;
    string temp;
    int length = 0;
    char* buffer;
    size_t found;
    size_t found2;
    ifstream fIn;
    fIn.open(numeFisier.c_str(), ios::binary);
    if(fIn.is_open())
    {
        fIn.seekg(0, ios::end);
        length = fIn.tellg();
        //cout << length << endl;
        fIn.seekg(0, ios::beg);
        buffer = new char[length + 1];
        fIn.read(buffer, length);
        buffer[length] = '\0';
        fisierBuffer = buffer;
    }
    else
    {
        cout << numeFisier << " nu a putut fi deschis pentru citire" << endl;
    }
    fIn.close();
    ifstream fIn2;
    fIn2.open(adresaFisierTextDeScos, ios::binary);
    if(fIn2.is_open())
    {
        while(fIn2.good())
        {
            getline(fIn2, linieDeSters);
            if((linieDeSters[(linieDeSters.size() - 1)] == '\n') || (linieDeSters[(linieDeSters.size() - 1)] == '\r'))
            {
                linieDeSters.erase((linieDeSters.size() - 1));
                cout << "\nAm sters semnul \\n sau \\r din textul de cautat" << endl;
                cout << "Linia de sters este acum : " << linieDeSters << " asd";
            }
            found = fisierBuffer.find(linieDeSters);
            while(found != string::npos)
            {
                if((fisierBuffer[(found - 1)] == '\n') || (fisierBuffer[(found - 1)] == '\r'))
                {
                    temp = fisierBuffer.substr(0, (found - 1));
                    fisierParte1 = removeNewLines(temp);
                }
                //fisierParte1 = fisierBuffer.substr(0, found);
                if((fisierBuffer[(found + linieDeSters.size())] == '\r') || fisierBuffer[(found + linieDeSters.size())] == '\n')
                {
                    found2 = found + linieDeSters.size() + 1;
                }
                else
                {
                    found2 = found + linieDeSters.size();
                }
                fisierParte2 = fisierBuffer.substr(found2);
                fisierBuffer.erase(fisierBuffer.begin(), fisierBuffer.end());
                fisierBuffer = fisierParte1 + fisierParte2;
                found = fisierBuffer.find(linieDeSters);
            }
        }
    }
    else
    {
        cout << adresaFisierTextDeScos << " nu a putut fi deschis pentru citire" << endl;
    }
    fIn2.close();
    ofstream fOut(numeFisier.c_str());
    if(fOut.is_open())
    {
        fOut << fisierBuffer;
    }
    else
    {
        cout << numeFisier << " nu a putut fi deschis pentru scriere." << endl;

    }
}

//functia ce va itera prin fiecare folder si va cauta fiecare fisier de acolo
//In momentul in care functia gaseste un fisier executa removeFromFile
void checkFolder(path director, char* adresaFisierTextDeScos)
{
    string adresaFisierDeEditat; // va tine adresa fisierului de editat
    path tempPath = director; // copiem adresa in variabila tempPath
    int vectorIterator = 0; // necesar pentru a putea returna valorile din interiorul vectorului tempPathvector.
    vec tempPathVector; // va tine adresele folderului nostru
    if(is_regular_file(tempPath))
    {
        string adresa;
        string temp = randFisier();
        ofstream fisierOutput(temp.c_str());
        if(fisierOutput.is_open())
        {
            fisierOutput << tempPath;
        }
        fisierOutput.close();
        ifstream fisierInput(temp.c_str());
        if(fisierInput.is_open())
        {
            getline(fisierInput, adresa);
        }
        fisierInput.close();
        for(int i = 0; i < 100; i++) // doar ceva care sa tina programul ocupat un pic.
        {

        }
        remove(temp.c_str()); // stergem fisierul temporar creat
        removeFromFile(adresa, adresaFisierTextDeScos);
    }
    else if(is_directory(tempPath))
    {
        copy(directory_iterator(tempPath), directory_iterator(), back_inserter(tempPathVector)); // copiem adresele in vector
        for(vec::const_iterator tempIt(tempPathVector.begin()); tempIt != tempPathVector.end(); ++tempIt) // loop pentru a trece prin fiecare adresa
        {
            if(is_directory(*tempIt)) // verificam daca adresa curenta e director
            {
                checkFolder(*tempIt, adresaFisierTextDeScos); // daca este executam din nou functia pentru directorul respectiv
            }
            else if(is_regular_file(*tempIt)) // daca in schimb e fisier ne apucam sa cautam si sa stergem ce avem de sters
            {
                fstream fisierDeEditat; // fisierul ce va fi editat
                // improvizatie pentru a putea lua adresa fisierului de editat.
                // luat adresa fisierului din tempIt si o salvam in fisierul random creat(fisierOutput)
                // dupa care deschidem fisierul si copiem adresa intr-un string nou
                string temp = randFisier();
                ofstream fisierOutput(temp.c_str());
                if(fisierOutput.is_open())
                {
                    fisierOutput << *tempIt;
                }
                fisierOutput.close();
                ifstream fisierInput(temp.c_str());
                if(fisierInput.is_open())
                {
                    getline(fisierInput, adresaFisierDeEditat);
                }
                removeFromFile(adresaFisierDeEditat, adresaFisierTextDeScos);

                fisierInput.close();
                remove(temp);
                fisierDeEditat.close();
            }
            vectorIterator++;
        }
    }
}

int main(int argv, char* argc[])
{
    if(argv == 1)
    {
        cout << "Utilizare: bulkremover fisier_text_de_sters director_cu_fisierele_de_sters.\n";
    }
    else if(argv > 1)
    {
        path p = argc[2];
        checkFolder(p, argc[1]);
        cout << "Am terminat." << endl;
    }


    return 0;
}
