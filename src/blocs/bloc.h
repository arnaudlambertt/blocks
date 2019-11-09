#ifndef BLOC_H
#define BLOC_H
#include <vector>
#include "../svg/svgfile.h"

class Bloc
{
    public:
        Bloc();
        virtual ~Bloc();

        Bloc* getParent() { return m_parent; }
        void setParent(Bloc* val) { m_parent = val; }
        std::vector <Bloc*> Getenfants() { return m_enfants; }
        void dessiner(Svgfile &svgout);

    protected:
        Bloc* m_parent;
        std::vector <Bloc*> m_enfants;
        std::string m_basepos;
        std::string m_refpos;
};

#endif // BLOC_H
