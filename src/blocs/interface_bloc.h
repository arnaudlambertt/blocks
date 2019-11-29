#ifndef INTERFACEBLOC_H
#define INTERFACEBLOC_H
#include "bloc.h"

class InterfaceBloc
{
    public:
        InterfaceBloc(const std::string &rom);
        ~InterfaceBloc();

        void userInterface();

        void dessiner();
        void afficherHelp()const;
        void sauvegarder(std::string &saveFile);

        void store();

        void appliquerActions(std::string &action, std::string &valeur, std::vector<Bloc*> &listCurrent);

        void translater(std::string valeur, std::vector<Bloc*> &listCurrent);
        void pivoter(std::string valeur, std::vector<Bloc*> &listCurrent);

    private:
        Bloc* m_current;
        std::unique_ptr<Bloc> m_room;
        std::vector<Bloc*> m_listCurrent;
        std::string m_store;
        bool m_showId = false;
        bool m_showRuler = false;
};

#endif // INTERFACEBLOC_H
