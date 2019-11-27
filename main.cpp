#include "src/blocs/interface_bloc.h"
#include "../geometrie/rectangle_translatable.h"
#include "../geometrie/losange_translatable.h"
#include "../geometrie/disk_translatable.h"
#include "../geometrie/triangle_translatable.h"

#include "../geometrie/rectangle_rotatable.h"
#include "../geometrie/losange_rotatable.h"
#include "../geometrie/disk_rotatable.h"
#include "../geometrie/triangle_rotatable.h"

int main()
{
    InterfaceBloc ib("roms/simplebot.rom");
    ib.afficherHelp();
    ib.userInterface();
//
///    std::string test = "dzqzq6RG%d",temp;
///    temp = test.substr(test.find('6'));
///    std::cout << temp;


//    Svgfile::s_verbose = false;
//    Svgfile svgout;
//    svgout.addGrid();
//
//
//    std::ifstream file_input{"roms/simplebot.rom"};
//    if ( !file_input ) throw std::runtime_error( "Can't read/open data.txt" );
//
//    std::unique_ptr<Bloc> room = std::make_unique<Bloc>(file_input, nullptr);
//    room->dessiner(svgout);

//    Bloc a, b{&a, "recrot",
//              std::make_unique<RectangleRotatable>(200,100,"tc","br",0,0,75)
//              ,"blue","black"}
//                            ,c{&b,"rectrot",
//                            std::make_unique<RectangleTranslatable>(80,40,"tl","bc",0,0,"br",0.5)
//              ,"yellow","black"}
//              ,d{&c,"rectrot2",
//                            std::make_unique<RectangleRotatable>(40,20,"tl","br",0,0,45)
//              ,"lightgreen","black"};
//    a.dessiner(svgout);
//    b.dessiner(svgout);
//    c.dessiner(svgout);
//    d.dessiner(svgout);


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
