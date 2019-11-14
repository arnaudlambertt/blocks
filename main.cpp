#include <iostream>
#include "src/blocs/bloc.h"
#include "rectangle.h"
#include "disk.h"
#include <math.h>

int main()
{
    Svgfile svgout;
    svgout.addGrid();

    std::vector<Bloc*> tab;
    for(int i = 0; i<10; ++i)
        tab.push_back(new Bloc);

    for(size_t i = 1; i<10; ++i)
        tab[i]->setParent(tab[i-1]);

    for (auto &i : tab)
        i->dessiner(svgout);



    return 0;
}
