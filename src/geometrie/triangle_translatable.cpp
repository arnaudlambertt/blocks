/** \brief classe triangle translatable h�ritant de triangle et translatable
 *
 * \param largeur
 * \param longueur
 * \param position locale o� le parent s'attache � son enfant
 * \param position locale en X o� le parent s'attache � son enfant
 * \param position locale en Y o� le parent s'attache � son enfant
 * \param valeur de la translation
 *
 */

#include "triangle_translatable.h"
#include "../blocs/bloc.h"

TriangleTranslatable::TriangleTranslatable(const double &width, const double &height,
const std::string &basepos,
const std::string &refpos, const double &refposX, const double &refposY,
const std::string &endpos, double &translation)
:   Triangle{width,height,basepos,refpos,refposX,refposY},Translatable{this,m_refpos,endpos,translation}
{
    translater(translation);
}

TriangleTranslatable::~TriangleTranslatable()
{
    //dtor
}
