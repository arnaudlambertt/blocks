#include "interface_bloc.h"

InterfaceBloc::InterfaceBloc(const std::string &rom)
    :m_current{nullptr}
{
    std::ifstream file_input{rom};
    if ( !file_input )
    {
        throw std::runtime_error( "Can't read/open " + rom );
        m_room = nullptr;
    }
    else
    {
        bool useless = true;
        m_room = std::make_unique<Bloc>(file_input, nullptr,useless);
        m_file = rom;
    }

    //ctor
}

InterfaceBloc::~InterfaceBloc()
{
    //dtor
}

void InterfaceBloc::dessiner()

{
    Svgfile::s_verbose = false;
    Svgfile svgout;
    m_room->dessiner(svgout);
}

void InterfaceBloc::afficherHelp()const
{
    std::ifstream file_input{"help.txt"};
    std::string output;
    if ( !file_input )
        throw std::runtime_error( "Can't read/open help.txt" );
    std::cout << std::endl;
    while(file_input)
    {
        if(std::getline(file_input,output))
            std::cout << output << std::endl;
    }
    std::cout << std::endl;
}

void InterfaceBloc::translater()
{

}

void InterfaceBloc::userInterface()
{
    //std::vector<std::string> tabCibles();
    std::string saisie, cible;
    std::istringstream iss;
    std::vector<std::string> cibTab;
    do
    {
        std::getline(std::cin, saisie);

        //std::cout << saisie << std::endl;


        if(saisie.find('@') != std::string::npos)
        {
            saisie[saisie.find('@')] = ' ';

        while(saisie.find('.') != std::string::npos)
            saisie[saisie.find('.')] = ' ';
            iss.str(saisie);
            while(iss >> cible)
                cibTab.push_back(cible);

//                for(auto &i : cibTab)
//                    std::cout << i << std::endl;
            m_room->searchId(cibTab, m_listCurrent);
                cibTab.clear();


            //std::cout << m_current;
        }

/// 48 -> 57



    iss.clear();
    }
    while(saisie != "exit");
}

void InterfaceBloc::sauvegarder()
{
    std::ofstream file_output{"roms/save.rom"};
    if ( !file_output )
        throw std::runtime_error( "Can't open/create roms/save.rom" );
    else
        if (m_room != nullptr)
            m_room->sauvegarde(file_output,0);
}
