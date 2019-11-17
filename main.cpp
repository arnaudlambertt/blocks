#include <iostream>
#include "src/blocs/bloc.h"
#include "rectangle.h"
#include "disk.h"
#include "losange.h"
#include <math.h>

int main()
{
     Svgfile svgout;
    svgout.addGrid();

    std::vector<Bloc*> tab;
    for(int i = 0; i<4; ++i)
        tab.push_back(new Bloc);

    for(size_t i = 1; i< tab.size(); ++i)
        tab[i]->setParent(tab[i-1]);

    for(int i = 0; i<5; ++i)
        tab.push_back(new Bloc{tab[i+3],"rect id",std::make_unique<Losange>(),"lightgreen","black"});

    for (auto &i : tab)
        i->dessiner(svgout);

    for(size_t i = 0; i<4; ++i)
        delete tab[i];




    return 0;
}
