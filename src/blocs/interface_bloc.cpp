#include "interface_bloc.h"

InterfaceBloc::InterfaceBloc(const std::string &rom)
    :m_current{nullptr}
{
    std::ifstream file_input{rom};
    if ( !file_input )
    {
        throw std::runtime_error( "Can't read/open data.txt" );
        m_room = nullptr;
    }
    else
        m_room = std::make_unique<Bloc>(file_input, nullptr);

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
    do
    {


        //std::cin.ignore();
        std::getline(std::cin, saisie);



        if(saisie.find('@') != std::string::npos)
        {
            saisie[saisie.find('@')] = ' ';
            std::istringstream iss(saisie);
            iss >> cible;
            std::cout << cible << std::endl;
            m_current = m_room->searchId(cible);
            std::cout << m_current;
            if(saisie.find('%') != std::string::npos)
                saisie[saisie.find('%')] = ' ';




        }


    }
    while(saisie != "exit");
}
