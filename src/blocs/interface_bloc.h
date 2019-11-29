#ifndef INTERFACEBLOC_H
#define INTERFACEBLOC_H
#include "bloc.h"

class InterfaceBloc
{
    public:
        InterfaceBloc();
        ~InterfaceBloc();

        void userInterface();

        void dessiner();
        void afficherHelp()const;
        void init();
        void load(std::string &rom);
        void sauvegarder(std::string &saveFile);


        void store();

        void appliquerActions(std::string &action, std::string &valeur, std::vector<Bloc*> &listCurrent);

        void translater(std::string valeur, std::vector<Bloc*> &listCurrent);
        void pivoter(std::string valeur, std::vector<Bloc*> &listCurrent);

    private:
        Bloc* m_current;
        std::string m_rom;
        std::unique_ptr<Bloc> m_room;
        std::vector<Bloc*> m_listCurrent;
        std::string m_store;
        std::vector<std::string> m_undo;
        bool m_showId = false;
        bool m_showRuler = false;
};

#endif // INTERFACEBLOC_H
