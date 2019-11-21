#ifndef TRIANGLE_ROTATABLE_H
#define TRIANGLE_ROTATABLE_H

#include "triangle.h"
#include "rotatable.h"

class TriangleRotatable : public Triangle, public Rotatable
{
    public:
        TriangleRotatable(const double &width, const double &height,const std::string &basepos,
                            const std::string &refpos, const double &refposX, const double &refposY,
                            const std::string &endpos, const double &rotation);

        virtual ~TriangleRotatable();

        void dessiner(const Bloc* parent, const std::string &color, const std::string &border, Svgfile &svgout);
};

#endif // TRIANGLE_ROTATABLE_H
