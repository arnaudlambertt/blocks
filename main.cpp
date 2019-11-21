#include "src/blocs/bloc.h"

int main()
{
    Svgfile svgout;
    svgout.addGrid();

    Bloc a, b{&a, "recrot",
              std::make_unique<RectangleRotatable>(200,100,"tc","br",0,0,0.25)
              ,"blue","black"}, c{&b, "diskrot2",
                                  std::make_unique<DiskRotatable>(10,"mc","mc",0,0,0.75 )
                                  ,"green","black"}
                            ,d{&c,"rectrot",
                            std::make_unique<Rectangle>(40,20,"tl","br",0,0)
              ,"yellow","black"};

    a.dessiner(svgout);
    b.dessiner(svgout);
    c.dessiner(svgout);
    d.dessiner(svgout);

//    std::vector<Bloc*> tab;
//    for(int i = 0; i<2; ++i)
//        tab.push_back(new Bloc);
//
//    for(size_t i = 1; i< tab.size(); ++i)
//        tab[i]->setParent(tab[i-1]);
//
//    for(int i = 0; i<5; ++i)
//        tab.push_back(new Bloc{tab[i+1],"rect id",std::make_unique<Losange>(),"lightgreen","black"});
//
//    for(int i = 0; i<3; ++i)
//        tab.push_back(new Bloc{tab[i+6],"diisk id",std::make_unique<Disk>(),"lightblue","black"});
//
//    for (auto &i : tab)
//        i->dessiner(svgout);
//
//    for(auto &i : tab)
//        delete i;




    return 0;
}
