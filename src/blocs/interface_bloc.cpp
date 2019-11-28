#include "interface_bloc.h"
#include "../geometrie/translatable.h"
#include "../geometrie/rotatable.h"

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

void InterfaceBloc::dessiner(bool &id, bool &ruler, std::vector<Bloc*> &listCurrent)

{
    Svgfile::s_verbose = false;
    Svgfile svgout;
    m_room->dessiner(svgout);
    //std::cout << id << " | " << ruler << std::endl;
    if (id)
        m_room->displayId(svgout);
    if(ruler)
        m_room->displayRuler(svgout);
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
    std::string saisie, cible, cibleTemp, action = "", valeur = "";
    std::istringstream iss, iss2;
    std::vector<std::string> cibTab;
    bool id = false, ruler = false;
    dessiner(id, ruler, m_listCurrent);
    do
    {
        if(m_current != nullptr)
        {
            if(m_listCurrent.size() == 1)
                std::cout << m_current->getId() << "> ";
            else
                std::cout << cible << "> ";
        }

        std::getline(std::cin, saisie);
        if(saisie == "@")
            std::cout << "erreur de format" << std::endl;
        else
        {
            iss.str(saisie);



            if(saisie.find('@') != std::string::npos)
            {
                iss >> cibleTemp;
                m_listCurrent.clear();
                cibleTemp[cibleTemp.find('@')] = ' ';

                while(cibleTemp.find('.') != std::string::npos)
                    cibleTemp[cibleTemp.find('.')] = ' ';
                iss2.str(cibleTemp);
                while(iss2 >> cible)
                    cibTab.push_back(cible);
                iss2.clear();


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
            if(iss)
                iss >> action;
            if(iss)
                iss >> valeur;
            if(m_current != nullptr)
            {
                if(action != "")
                    appliquerActions(action, valeur, m_listCurrent, id, ruler);
                else
                    std::cout << "Aucune fonction saisie" << std::endl;
            }
            else
                appliquerActions(action, valeur, m_listCurrent, id, ruler);
        }
        iss.clear();
        valeur.clear();
        action.clear();
        dessiner(id,ruler, m_listCurrent);
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

void InterfaceBloc::translater(std::string valeur, std::vector<Bloc*> &listCurrent)
{
    std::string::size_type sz;
    double valtranslation = std::stod(valeur, &sz) *0.01;
    for(auto &i: listCurrent)
    {
        if(Translatable* t = dynamic_cast<Translatable*>(i->getGeometrie()))
        {
            if (valeur[0] == '+' || valeur[0] == '-')
                t->translater(valtranslation + t->getTranslation());
            else
                t->translater(valtranslation);
        }
        else
            std::cout << "La cible " << i->getId() << " n'est pas translatable" << std::endl;
    }
}

void InterfaceBloc::pivoter(std::string valeur, std::vector<Bloc*> &listCurrent)
{
    std::string::size_type sz;
    double valrotation = std::stod(valeur, &sz);
    for(auto &i: listCurrent)
    {
        if(dynamic_cast<Rotatable*>(i->getGeometrie()))
        {
            if (valeur[0] == '+' || valeur[0] == '-')
                i->getGeometrie()->setNewRotation(i->getGeometrie()->getVraiRotation() + valrotation);
            else
                i->getGeometrie()->setNewRotation(valrotation);
        }
        else
            std::cout << "La cible " << i->getId() << " n'est pas pivotable" << std::endl;
    }
}

void InterfaceBloc::store()
{
    std::ostringstream os (m_store);
    m_room->sauvegarde(os,0);
}

void InterfaceBloc::appliquerActions(std::string action, std::string valeur, std::vector<Bloc*> &listCurrent, bool &id, bool &ruler)
{
    if(action == "help")
        afficherHelp();
    else if(action == "move")
    {
        if((valeur[0] >= 48 && valeur[0] <= 57) ||
                ((valeur[0] == '+' || valeur[0] == '-') &&
                 (valeur[1] >= 48 && valeur[1] <= 57)))
            translater(valeur, listCurrent);
        else
            std::cout << "Erreur de format" << std::endl;
    }
    else if(action == "rotate")
    {
        if((valeur[0] >= 48 && valeur[0] <= 57) ||
                ((valeur[0] == '+' || valeur[0] == '-') &&
                 (valeur[1] >= 48 && valeur[1] <= 57)))
            pivoter(valeur, listCurrent);
    }
    else if(action == "display")
    {
        if(valeur == "ids" && id == false)
        {
            id = true;
        }
        else if(valeur == "rulers" && ruler == false)
        {
            ruler = true;
        }
        else
            std::cout << "Fonction inconnue" << std::endl;
    }
    else if(action == "hide")
    {
        if(valeur == "ids" && id)
        {
            id = false;
        }
        else if(valeur == "rulers" && ruler)
        {
            ruler = false;
        }
        else
            std::cout << "Fonction inconnue" << std::endl;
    }


    else if(action != "exit")
        std::cout << "Fonction inconnue" << std::endl;
}
