#ifndef SCENE_H
#define SCENE_H
#include "bloc.h"

class Scene
{
    public:
        Scene();
        ~Scene();

        bool init();
        void userInterface();

        void dessiner();
        void afficherHelp()const;

        void load(std::string &rom);
        void sauvegarder(std::string &saveFile);

        void store();
        void restore(const std::string &store);

        void saveState();

        void undo();
        void redo();

        void script(std::string &script);

        void appliquerActions(std::string &action, std::string &valeur, std::vector<Bloc*> &listCurrent);

        void translater(std::string valeur, std::vector<Bloc*> &listCurrent);
        void pivoter(std::string valeur, std::vector<Bloc*> &listCurrent);



    private:
        Bloc* m_current;
        std::string m_rom;
        std::unique_ptr<Bloc> m_room;
        std::vector<Bloc*> m_listCurrent;
        std::string m_store;
        std::vector<std::string> m_actions;
        std::ifstream m_script;
        size_t m_nAction = 0;
        bool m_showId = false;
        bool m_showRuler = false;
        std::vector<std::pair<Bloc*,Coords>> m_collisions;
};

#endif // SCENE_H
