#include <iostream>
#include "src/blocs/bloc.h"

int main()
{
    Bloc a, b{&a,"bloc b",100.0,100.0, {0,0,0},{0,0,0} , "tl","br",0.0,0.0};
    b.absoluteCoords("br").afficher();

    return 0;
}
