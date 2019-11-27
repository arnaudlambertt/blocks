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
        void sauvegarder();

        void translater();


    private:
        Bloc* m_current;
        std::string m_file;
        std::unique_ptr<Bloc> m_room;
        std::vector<std::string> m_history;
        std::vector<Bloc*> m_listCurrent;
};

#endif // INTERFACEBLOC_H