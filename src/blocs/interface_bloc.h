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

        void translater();


    private:
        Bloc* m_current;
        std::unique_ptr<Bloc> m_room;
        std::vector<std::string> m_history;
        std::vector<Bloc*> m_listCurrent;
};

#endif // INTERFACEBLOC_H
