#include "interface_bloc.h"
#include "../geometrie/translatable.h"
#include "../geometrie/rotatable.h"
#include <dirent.h>
#include "../util/check_arrow_key.h"
#include <windows.h>

InterfaceBloc::InterfaceBloc()
    :m_current{nullptr}, m_room{nullptr}
{
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
    //std::cout << id << " | " << ruler << std::endl;
    if (m_showId)
        m_room->displayId(svgout);
    if(m_showRuler)
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

bool InterfaceBloc::init()
{
    std::string command, file, input;
    int ignore = 0;
    std::istringstream iss;
    std::cout << "Veuillez charger un fichier rom."<< std::endl
              << "Commande : load [fichier]/[fichier.rom]" << std::endl
              << "Liste des fichiers presents dans le dossier roms/ :" << std::endl << std::endl;

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("roms/")) != NULL)
    {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL)
        {
            if(ignore >= 2)
                std::cout << " - " << ent->d_name << std::endl;
            ++ignore;
        }
        closedir (dir);
        std::cout << std::endl;
    }
    else
        std::cout << "Erreur : ouverture du dossier roms/ impossible" << std::endl;

    do
    {
        std::getline(std::cin, input);
        iss.str(input);
        iss >> command >> file;
        if(command == "load" && file != "")
            load(file);
        else if(command == "exit")
            return false;

        else
            std::cout << "Erreur : mauvaise commande" << std::endl
                      << "utilisation : load [fichier]/[fichier.rom]" << std::endl;
        iss.clear();

    }
    while(m_room == nullptr);

    std::ostringstream oss;
    m_room->sauvegarde(oss,0);
    m_store = oss.str();

    return true;
}

void InterfaceBloc::userInterface()
{
    std::string saisie, cible, cibleTemp, action = "", valeur = "";
    std::istringstream iss, iss2;
    std::vector<std::string> cibTab;

    if(init())
        do
        {
            if(m_current != nullptr)
            {
                if(m_listCurrent.size() == 1)
                    std::cout << m_current->getId() << "> ";
                else
                    std::cout << cible << "> ";
            }

            if(m_script.is_open())
            {
                if(!m_script.eof())
                {
                    Sleep(500);
                    std::getline(m_script, saisie);
                    std::cout << saisie << std::endl;
                }
                else
                {
                    m_script.close();
                    std::cout << "Fin du script" << std::endl;
                    std::getline(std::cin, saisie);
                }
            }
            else
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
                            if (i->getName() != m_listCurrent[0]->getName())
                            {
                                blindage = false;
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
                        appliquerActions(action, valeur, m_listCurrent);
                    else
                        std::cout << "Aucune fonction saisie" << std::endl;
                }
                else
                    appliquerActions(action, valeur, m_listCurrent);
            }
            dessiner();
            iss.clear();
            valeur.clear();
            action.clear();
        }
        while(saisie != "exit");
}

void InterfaceBloc::sauvegarder(std::string &saveFile)
{
    std::ofstream file_output;

    if(saveFile.size() <4 || saveFile.find(".rom") != saveFile.size()-4)
        saveFile += ".rom";

    std::string ecraser, null;


    while( std::ifstream {"roms/" + saveFile} && ecraser != "oui")
    {
        std::cout << "Le fichier " << saveFile << " existe deja, voulez-vous l'ecraser? " << std::endl << "oui / non" << std::endl;
        do
        {
            std::cin >> ecraser;
        }
        while(ecraser != "oui" && ecraser != "non");
        if(ecraser == "non")
        {
            std::cout << "Saisir le nom du nouveau fichier de sauvegarde" << std::endl;
            std::cin >> saveFile;

            if(saveFile.size() <4 || saveFile.find(".rom") != saveFile.size()-4)
                saveFile += ".rom";
        }
        std::getline(std::cin, null);
    }

    if (m_room != nullptr)
    {
        file_output = std::ofstream {"roms/" + saveFile};
        m_room->sauvegarde(file_output,0);
    }
    std::cout << "Save done : roms/"<< saveFile << std::endl << std::endl;
}

void InterfaceBloc::translater(std::string valeur, std::vector<Bloc*> &listCurrent)
{
    std::string::size_type sz;
    double valtranslation;
    if(valeur != "")
        valtranslation = std::stoi(valeur, &sz) *0.01;
    bool change = false;

    for(auto &i: listCurrent)
    {
        if(Translatable* t = dynamic_cast<Translatable*>(i->getGeometrie()))
        {
            if(valeur == "" )
            {
                int val = 0;
                std::cout << "Utilisez les fleches gauche et droite pour translater, une autre touche pour quitter" << std::endl;
                do
                {
                    CheckArrowKey(val);     // Lecture des touches clavier
                    if (val == 2)   // Si fleche droite
                    {
                        t->translater(-0.01 + t->getTranslation());    // Translation
                        if(i->collision(m_room->getTousEnfants()))
                        {
                            break;
                            t->translater(+0.01 + t->getTranslation());
                        }
                    }
                    if (val == 3)   // Si fleche droite
                    {
                        t->translater(+0.01 + t->getTranslation());
                        if(i->collision(m_room->getTousEnfants()))
                        {
                            break;
                            t->translater(-0.01 + t->getTranslation());
                        }
                    }
                    dessiner();
                }
                while(val == 2 || val == 3 );
            }
            else
            {
                double initiale = t->getTranslation();
                if (valeur[0] == '+' || valeur[0] == '-')
                {
                    if(valtranslation > 0)
                        for(double j = 0.01; j<= valtranslation; j+=0.01)
                        {
                            t->translater(initiale + j);

                            if(i->collision(m_room->getTousEnfants()))
                            {
                                t->translater(initiale + j-0.01);
                                break;
                            }
                            else
                                change = true;
                        }
                    else if(valtranslation < 0)
                        for(double j = -0.01; j>= valtranslation; j-=0.01)
                        {
                            t->translater(initiale + j);

                            if(i->collision(m_room->getTousEnfants()))
                            {
                                t->translater(initiale + j+0.01);
                                break;
                            }
                            else
                                change = true;
                        }
                }
                else
                {
                    if(valtranslation > initiale)
                        for(double j = initiale+0.01; j<= valtranslation; j+=0.01)
                        {
                            saveState();
                            t->translater(j);

                            if(i->collision(m_room->getTousEnfants()))
                            {
                                t->translater(j-0.01);
                                break;
                            }
                            else
                                change = true;
                        }
                    else if(valtranslation < initiale)
                        for(double j = initiale-0.01; j>= valtranslation-0.01; j-=0.01)
                        {
                            saveState();
                            t->translater(j);

                            if(i->collision(m_room->getTousEnfants()))
                            {
                                t->translater(j+0.01);
                                break;
                            }
                            else
                                change = true;
                        }
                }
            }

        }
        else
            std::cout << "Erreur: La cible " << i->getId() << " n'est pas translatable" << std::endl;
    }
    if(change)
        saveState();
}
void InterfaceBloc::pivoter(std::string valeur, std::vector<Bloc*> &listCurrent)
{
    std::string::size_type sz;
    double valrotation;
    if(valeur != "")
        valrotation = std::stod(valeur, &sz);
    bool change = false;

    for(auto &i: listCurrent)
    {
        if(dynamic_cast<Rotatable*>(i->getGeometrie()))
        {
            if(valeur == "" )
            {
                int val = 0;
                std::cout << "Utilisez les fleches gauche et droite pour tourner, une autre touche pour quitter" << std::endl;
                do
                {
                    CheckArrowKey(val);     // Lecture des touches clavier
                    if (val == 2)   // Si fleche droite
                    {
                        i->getGeometrie()->setNewRotation(i->getGeometrie()->getVraiRotation() + 2);    // Rotation
                        if(i->collision(m_room->getTousEnfants()))
                        {
                            i->getGeometrie()->setNewRotation(i->getGeometrie()->getVraiRotation() - 2);
                            break;
                        }

                        else
                            change = true;
                    }
                    if (val == 3)   // Si fleche droite
                    {
                        i->getGeometrie()->setNewRotation(i->getGeometrie()->getVraiRotation() - 2);    // Rotation
                        if(i->collision(m_room->getTousEnfants()))
                        {
                            i->getGeometrie()->setNewRotation(i->getGeometrie()->getVraiRotation() + 2);
                            break;
                        }
                        else
                            change = true;
                    }
                    dessiner();
                }
                while(val == 2 || val == 3 );
            }
            else

            {
                double initiale = i->getGeometrie()->getVraiRotation();
                if (valeur[0] == '+' || valeur[0] == '-')
                {
                    if(valrotation > 0)
                        for(double j = 1; j<= valrotation; j+=1)
                        {
                            i->getGeometrie()->setNewRotation(initiale + j);

                            if(i->collision(m_room->getTousEnfants()))
                            {
                                i->getGeometrie()->setNewRotation(initiale + j-1);
                                break;
                            }
                            else
                                change = true;
                        }
                    else if(valrotation < 0)
                        for(double j = -1; j>= valrotation; j-=1)
                        {
                            i->getGeometrie()->setNewRotation(initiale + j);

                            if(i->collision(m_room->getTousEnfants()))
                            {
                                i->getGeometrie()->setNewRotation(initiale + j+1);
                                break;
                            }
                            else
                                change = true;
                        }
                }
                else
                {
                    if(valrotation > initiale)
                        for(double j = initiale+1; j<= valrotation; j+=1)
                        {
                            saveState();
                            i->getGeometrie()->setNewRotation(j);

                            if(i->collision(m_room->getTousEnfants()))
                            {
                                i->getGeometrie()->setNewRotation(j-1);
                                break;
                            }
                            else
                                change = true;
                        }
                    else if(valrotation < initiale)
                        for(double j = initiale-1; j>= valrotation-1; j-=1)
                        {
                            saveState();
                            i->getGeometrie()->setNewRotation(j);

                            if(i->collision(m_room->getTousEnfants()))
                            {
                                i->getGeometrie()->setNewRotation(j+1);
                                break;
                            }
                            else
                                change = true;
                        }
                }
            }
        }
        else
            std::cout << "Erreur: La cible " << i->getId() << " n'est pas pivotable" << std::endl;
    }

    if(change)
        saveState();
}

void InterfaceBloc::load(std::string &rom)
{
    m_listCurrent.clear();
    m_current = nullptr;

    if(rom.size() < 4 || rom.find(".rom") != rom.size()-4)
        rom += ".rom";

    std::ifstream file_input{"roms/" + rom};
    if ( !file_input )
    {
        std::cout << "Erreur: chargement impossible du fichier roms/" << rom << std::endl;
    }
    else
    {
        bool useless = true;
        m_room = std::make_unique<Bloc>(file_input, nullptr,useless);
        if(m_room != nullptr)
        {
            std::cout << "Chargement reussi" << std::endl;
            m_rom = rom;
            saveState();
            dessiner();
        }
        else
            std::cout << "Erreur fatale: Fichier roms/" << rom << " corrompu" << std::endl;
    }
}

void InterfaceBloc::store()
{
    std::ostringstream oss;
    m_room->sauvegarde(oss,0);
    m_store = oss.str();
    std::cout << "Store success" << std::endl;
}

void InterfaceBloc::saveState()
{
    for(size_t i = m_nAction; i< m_actions.size(); ++i)
        m_actions.erase(m_actions.begin()+i);

    std::ostringstream oss;
    m_room->sauvegarde(oss,0);
    m_actions.push_back(oss.str());
    m_nAction = m_actions.size();
}

void InterfaceBloc::undo()
{
    if(m_nAction > 1)
    {
        --m_nAction;
        restore(m_actions[m_nAction-1]);
    }
    else
        std::cout << "Aucun changement" << std::endl;

}

void InterfaceBloc::redo()
{
    if(m_nAction < m_actions.size())
    {
        ++m_nAction;
        restore(m_actions[m_nAction-1]);
    }
    else
        std::cout << "Aucun changement" << std::endl;
}

void InterfaceBloc::restore(const std::string &store)
{
    m_listCurrent.clear();
    m_current = nullptr;
    std::istringstream iss{store};
    bool useless = true;
    m_room = std::make_unique<Bloc>(iss, nullptr,useless);
    if(m_room != nullptr)
        std::cout << "Success" << std::endl;
}

void InterfaceBloc::script(std::string &script)
{
    if(script.size() < 7 || script.find(".script") != script.size()-7)
        script += ".script";


    if ( !std::ifstream{"scripts/" + script} )
    {
        std::cout << "Erreur: chargement impossible du fichier scripts/" << script << std::endl;
    }
    else
    {
        m_script.open("scripts/" + script);
        if(m_script.is_open())
        {
            std::cout << "Demarrage du script " << script << std::endl;
        }
        else
            std::cout << "Erreur fatale: Fichier scripts/" << script << " corrompu" << std::endl;
    }
}

void InterfaceBloc::appliquerActions(std::string &action, std::string &valeur, std::vector<Bloc*> &listCurrent)
{
    if(action == "help")
        afficherHelp();
    else if(action == "move")
    {
        if(m_current != nullptr)
        {
            if((valeur[0] >= 48 && valeur[0] <= 57) ||
                    ((valeur[0] == '+' || valeur[0] == '-') &&
                     (valeur[1] >= 48 && valeur[1] <= 57)))
                translater(valeur, listCurrent);
            else if(valeur == "")
                translater(valeur, listCurrent);
            else
                std::cout << "Erreur de format" << std::endl;
        }
        else
            std::cout << "Pas de cible" << std::endl;
    }
    else if(action == "rotate")
    {
        if(m_current != nullptr)
        {
            if((valeur[0] >= 48 && valeur[0] <= 57) ||
                    ((valeur[0] == '+' || valeur[0] == '-') &&
                     (valeur[1] >= 48 && valeur[1] <= 57)))
                pivoter(valeur, listCurrent);
            else if(valeur == "")
                pivoter(valeur, listCurrent);

            else
                std::cout << "Erreur de format" << std::endl;
        }
        else
            std::cout << "Pas de cible" << std::endl;
    }
    else if(action == "show")
    {
        if(valeur == "ids")
            m_showId = true;

        else if(valeur == "rulers" )
            m_showRuler = true;
        else
            std::cout << "Erreur: mauvais attribut 'show'" << std::endl;

    }
    else if(action == "hide")
    {
        if(valeur == "ids")
            m_showId = false;

        else if(valeur == "rulers")
            m_showRuler = false;
        else
            std::cout << "Erreur: mauvais attribut 'hide' " << std::endl;

    }
    else if(action == "save")
    {
        if(valeur != "" )
            sauvegarder(valeur);
        else
            std::cout << "Erreur: nom du fichier vide" << std::endl;
    }
    else if (action == "load")
    {
        if(valeur != "")
            load(valeur);
        else
            std::cout << "Erreur : mauvaise commande" << std::endl
                      << "Utilisation : load [fichier]/[fichier.rom]" << std::endl;

    }
    else if (action == "store")
        store();
    else if (action == "restore")
    {
        restore(m_store);
        saveState();
    }
    else if (action == "reload")
        load(m_rom);
    else if (action == "undo")
        undo();
    else if (action == "redo")
        redo();
    else if (action == "script")
    {
        if(valeur != "")
            script(valeur);
        else
            std::cout << "Erreur : mauvaise commande" << std::endl
                      << "Utilisation : script [fichier]/[fichier.script]" << std::endl;

    }
    else if(action != "exit")
        std::cout << "Erreur: fonction inconnue" << std::endl;
}
