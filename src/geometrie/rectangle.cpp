/** \brief classe rectangle
 *
 * \param largeur
 * \param longueur
 * \param position locale où le parent s'attache à son enfant
 * \param position locale en X où le parent s'attache à son enfant
 * \param position locale en Y où le parent s'attache à son enfant
 *
 */

#include "rectangle.h"
#include "../blocs/bloc.h"
#include "disk.h"

Rectangle::Rectangle()
: Rectangle{100.0,100.0,"tl","br",0.0,0.0}
{
    //ctor
}

Rectangle::Rectangle(const double &width, const double &height,const std::string &basepos, const std::string &refpos, const double &refposX, const double &refposY)
:   Geometrie{basepos,refpos,refposX,refposY},m_height{height}, m_width{width}
{
    //ctor
}

Rectangle::~Rectangle()
{
    //dtor
}

std::vector<double> Rectangle::getDimensions() const
{
    return std::vector<double> {m_width,m_height};
}

Coords Rectangle::convertRefposEnfant(const Coords &refposEnfant) const
{
    return refposEnfant;
}

Coords Rectangle::getAbsolute(const std::string &localPos) const
{
    return getAbsolute(Coords{ pos()[localPos[1]], pos()[localPos[0]]});
}

void Rectangle::dessiner(Svgfile &svgout)
{
    svgout.addRectangle(getAbsolute("tl").getX(),getAbsolute("tl").getY(),
                        getAbsolute("tr").getX(),getAbsolute("tr").getY(),
                        getAbsolute("br").getX(),getAbsolute("br").getY(),
                        getAbsolute("bl").getX(),getAbsolute("bl").getY(),
                        m_bloc->getColor(),1.25,m_bloc->getBorder());
}

//source : https://math.stackexchange.com/questions/190111/how-to-check-if-a-point-is-inside-a-rectangle
bool Rectangle::isIn(const Coords &point) const
{
    Coords a = getAbsolute("tl"), b = getAbsolute("tr"), d = getAbsolute("bl");
    Coords am = point - a, ab = b - a, ad = d - a;

    return (0 < am*ab && am*ab < ab*ab && 0 < am*ad && am*ad < ad*ad);
}

