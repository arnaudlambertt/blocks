#include <iostream>
#include "src/blocs/bloc.h"
#include "rectangle.h"
#include "disk.h"
#include <math.h>

int main()
{
    Svgfile svgout;
    svgout.addGrid();

    Bloc a,c{&a,"bloc c",std::make_unique<Disk>(50,"tl","br",0.0,0.0),Couleur{0,0,255},Couleur{0,0,0}},
     b{&c,"bloc b",std::make_unique<Rectangle>(200,100,"tl","bc",0.0,0.0),Couleur{255,0,0},Couleur{0,0,0}},
     d{&b,"bloc d",std::make_unique<Disk>(35,"tl","br",0,0.0),Couleur{255,255,255},Couleur{0,0,0}};
    a.dessiner(svgout);
    c.dessiner(svgout);
    b.dessiner(svgout);
    d.dessiner(svgout);


    return 0;
}
