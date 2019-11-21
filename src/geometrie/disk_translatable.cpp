#include "disk_translatable.h"

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

void DiskTranslatable::dessiner(const Bloc* parent, const std::string &color, const std::string &border, Svgfile& svgout)
{
    dessinerAxe(parent, svgout);
    Disk::dessiner(parent, color, border, svgout);
}
