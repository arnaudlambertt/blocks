#include <iostream>
#include "src/blocs/bloc.h"

int main()
{
    Svgfile svgout;
    svgout.addGrid();
    Bloc a, b{&a,"bloc b",100.0,100.0, {255,0,0},{0,0,0} , "tl","br",0.0,0.0};
    b.calculerAbsoluteCoords("br").afficher();
    b.dessiner(svgout);
    a.dessiner(svgout); //aaaa

    return 0;
}
