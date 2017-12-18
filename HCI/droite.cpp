#include "droite.h"

Droite::Droite(){

}

Droite::Droite(float a, float b, float c)
{
    this->a=a;
    this->b=b;
    this->c=c;
}

void Droite::print(){
    cout << "a: " << a << " b: " << b << " c: " << c << endl;
}
