#ifndef INTERFACEBLOC_H
#define INTERFACEBLOC_H
#include "bloc.h"

class InterfaceBloc
{
    public:
        InterfaceBloc(const std::string &rom);
        ~InterfaceBloc();

        void userInterface();

        void dessiner(bool &id, bool &ruler, std::vector<Bloc*> &listCurrent);
        void afficherHelp()const;
        void sauvegarder(std::string &saveFile);

        void store();

        void appliquerActions(std::string action, std::string valeur, std::vector<Bloc*> &listCurrent, bool &id, bool &ruler);

        void translater(std::string valeur, std::vector<Bloc*> &listCurrent);
        void pivoter(std::string valeur, std::vector<Bloc*> &listCurrent);

    private:
        Bloc* m_current;
        std::unique_ptr<Bloc> m_room;
        std::vector<Bloc*> m_listCurrent;
        std::string m_store;
};

#endif // INTERFACEBLOC_H
