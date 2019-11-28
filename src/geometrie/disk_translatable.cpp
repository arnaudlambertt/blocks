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

//void DiskTranslatable::dessiner(Svgfile& svgout)
//{
//    dessinerAxe(m_bloc->getParent(), svgout);
//    Disk::dessiner(svgout);
//}
