#include "disk_translatable.h"
#include "../blocs/bloc.h"

DiskTranslatable::DiskTranslatable(const double &radius,
                                   const std::string &basepos,
                                   const std::string &refpos, const double &refposX, const double &refposY,
                                   const std::string &endpos, const double &translation)
    :   Disk{radius,basepos,refpos,refposX,refposY},Translatable{m_refpos,endpos,translation}
{
    translater(translation,m_refpos);
}

DiskTranslatable::~DiskTranslatable()
{
    //dtor
}

void DiskTranslatable::dessiner(const std::string &color, const std::string &border, Svgfile& svgout)
{
    dessinerAxe(m_bloc->getParent(), svgout);
    Disk::dessiner(color, border, svgout);
}
