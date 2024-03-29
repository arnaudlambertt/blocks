#ifndef RECTANGLE_ROTATABLE_H
#define RECTANGLE_ROTATABLE_H

#include "rectangle.h"
#include "rotatable.h"

class RectangleRotatable : public Rectangle, public Rotatable
{
public:
    RectangleRotatable(const double &width, const double &height,const std::string &basepos,
                       const std::string &refpos, const double &refposX, const double &refposY,
                       const double &rotation);

    virtual ~RectangleRotatable();

    //void dessiner(Svgfile &svgout);
};

#endif // RECTANGLE_ROTATABLE_H
