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



void InterfaceBloc::userInterface()
{
    //std::vector<std::string> tabCibles();
    std::string saisie, cible;
    std::istringstream iss;
    std::vector<std::string> cibTab;
    do
    {

        if(m_current != nullptr)
            if(m_listCurrent.size() == 1)
            std::cout << m_current->getId() << "> ";
        else
            std::cout << m_current->getName() << "> ";
        std::getline(std::cin, saisie);

        //std::cout << saisie << std::endl;


        if(saisie.find('@') != std::string::npos)
        {
            m_listCurrent.clear();
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

            if(m_listCurrent.size()==1)
                m_current = m_listCurrent[0];
            else if(m_listCurrent.size() > 1)
            {
                bool blindage = true;
                for (auto i : m_listCurrent)
                {
                //std::cout << "courant: "<< i->getId() << std::endl;
                    if (i->getName() != m_listCurrent[0]->getName())
                    {
                        blindage = false;
                        //std::cout << i->getName() << " | " << m_listCurrent[0]->getName() << std::endl;
                    }
                }
                if (blindage)
                    m_current = m_listCurrent[0];
                else
                    m_current = nullptr;

            }
            else
                m_current = nullptr;

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
    else if (m_room != nullptr)
        m_room->sauvegarde(file_output,0);
}

void InterfaceBloc::translater()
{

}
