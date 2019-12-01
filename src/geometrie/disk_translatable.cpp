/** \brief classe disk rotatable héritant de disk et translatable
 *
 * \param rayon
 * \param position locale où le parent s'attache à son enfant
 * \param position locale en X où le parent s'attache à son enfant
 * \param position locale en Y où le parent s'attache à son enfant
 * \param valeur de la translation
 *
 */

#include "disk_translatable.h"
#include "../blocs/bloc.h"

DiskTranslatable::DiskTranslatable(const double &radius,
                                   const std::string &basepos,
                                   const std::string &refpos, const double &refposX, const double &refposY,
                                   const std::string &endpos, double &translation)
    :   Disk{radius,basepos,refpos,refposX,refposY},Translatable{this,m_refpos,endpos,translation}
{
    translater(translation);
}

DiskTranslatable::~DiskTranslatable()
{
    //dtor
}
