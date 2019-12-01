/** \brief classe rectangle translatable héritant de rectangle et translatable
 *
 * \param largeur
 * \param longueur
 * \param position locale où le parent s'attache à son enfant
 * \param position locale en X où le parent s'attache à son enfant
 * \param position locale en Y où le parent s'attache à son enfant
 * \param valeur de la translation
 *
 */

#include "rectangle_translatable.h"
#include "../blocs/bloc.h"


RectangleTranslatable::RectangleTranslatable(const double &width, const double &height,
const std::string &basepos,
const std::string &refpos, const double &refposX, const double &refposY,
const std::string &endpos, double &translation)
:   Rectangle{width,height,basepos,refpos,refposX,refposY},Translatable{this,m_refpos,endpos,translation}
{
    translater(translation);
}

RectangleTranslatable::~RectangleTranslatable()
{
    //dtor
}

