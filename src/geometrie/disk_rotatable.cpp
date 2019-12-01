/** \brief classe disk pivotable h�ritant de disk et rotatable
 *
 * \param rayon
 * \param position locale o� le parent s'attache � son enfant
 * \param position locale en X o� le parent s'attache � son enfant
 * \param position locale en Y o� le parent s'attache � son enfant
 * \param valeur de la rotation
 *
 */

#include "disk_rotatable.h"


DiskRotatable::DiskRotatable(const double &radius, const std::string &basepos,
                             const std::string &refpos, const double &refposX, const double &refposY,
                             const double &rotation)
    :   Disk{radius,basepos,refpos,refposX,refposY},Rotatable{}
{
    setRotation(rotation);
}

DiskRotatable::~DiskRotatable()
{
    //dtor
}
