#ifndef TIRANGLE_TRANSLATABLE_H
#define TRIANGLE_TRANSLATABLE_H

#include "triangle.h"
#include "translatable.h"

class TriangleTranslatable : public Triangle, public Translatable
{
    public:
        TriangleTranslatable(const double &width, const double &height,const std::string &basepos,
                            const std::string &refpos, const double &refposX, const double &refposY,
                            const std::string &endpos, const double &translation);

        virtual ~TriangleTranslatable();

        void dessiner(const Bloc* parent, const std::string &color, const std::string &border, Svgfile &svgout);
};

#endif // TRIANGLE_TRANSLATABLE_H
