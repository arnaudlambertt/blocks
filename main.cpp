#include <iostream>
#include "src/blocs/bloc.h"

int main()
{
    Bloc a, b{&a,100.0,100.0,"tl","bl"};
    b.getBaseCoords().afficher();

    return 0;
}
