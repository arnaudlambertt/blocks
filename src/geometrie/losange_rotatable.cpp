/** \brief classe losange pivotable héritant de losange et rotatable
 *
 * \param largeur
 * \param longueur
 * \param position locale où le parent s'attache à son enfant
 * \param position locale en X où le parent s'attache à son enfant
 * \param position locale en Y où le parent s'attache à son enfant
 * \param valeur de la rotation
 *
 */

#include "losange_rotatable.h"


LosangeRotatable::LosangeRotatable(const double &width, const double &height,
                                   const std::string &basepos,
                                   const std::string &refpos, const double &refposX, const double &refposY,
                                   const double &rotation)
    :   Losange{width,height,basepos,refpos,refposX,refposY},Rotatable{}
{
    setRotation(rotation);
}

LosangeRotatable::~LosangeRotatable()
{
    //dtor
}
