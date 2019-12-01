/** \brief classe rectangle pivotable héritant de rectangle et rotatable
 *
 * \param largeur
 * \param longueur
 * \param position locale où le parent s'attache à son enfant
 * \param position locale en X où le parent s'attache à son enfant
 * \param position locale en Y où le parent s'attache à son enfant
 * \param valeur de la rotation
 *
 */

#include "rectangle_rotatable.h"


RectangleRotatable::RectangleRotatable(const double &width, const double &height,
                                       const std::string &basepos,
                                       const std::string &refpos, const double &refposX, const double &refposY,
                                       const double &rotation)
    :   Rectangle{width,height,basepos,refpos,refposX,refposY},Rotatable{}
{
    setRotation(rotation);
}

RectangleRotatable::~RectangleRotatable()
{
    //dtor
}


