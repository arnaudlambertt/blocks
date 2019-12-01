/** \brief classe losange pivotable h�ritant de losange et rotatable
 *
 * \param largeur
 * \param longueur
 * \param position locale o� le parent s'attache � son enfant
 * \param position locale en X o� le parent s'attache � son enfant
 * \param position locale en Y o� le parent s'attache � son enfant
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
