#ifndef DROITE_H
#define DROITE_H
#include <iostream>
using namespace std;
class Droite
{
public:
    Droite();
    Droite(float a, float b, float c);
    void print();
    float a;
    float b;
    float c;
};

#endif // DROITE_H
