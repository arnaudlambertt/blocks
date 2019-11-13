#include <iostream>
#include "src/blocs/bloc.h"
#include "rectangle.h"


int main()
{
    Svgfile svgout;
    svgout.addGrid();
    std::unique_ptr<Bloc> a = std::make_unique<Bloc>();
    Bloc b{a.get(),"bloc b",std::make_unique<Rectangle>(200,200,"tl","mc",0.25,0.25),{255,0,0},{0,0,0}};
    b.calculerAbsoluteCoords("br").afficher();
    a->dessiner(svgout);
    b.dessiner(svgout);

    return 0;
}
