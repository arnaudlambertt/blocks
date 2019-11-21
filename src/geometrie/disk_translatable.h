#ifndef DISK_TRANSLATABLE_H
#define DISK_TRANSLATABLE_H

#include "disk.h"
#include "translatable.h"

class DiskTranslatable : public Disk, public Translatable
{
    public:
        DiskTranslatable(const double &radius,const std::string &basepos,
                            const std::string &refpos, const double &refposX, const double &refposY,
                            const std::string &endpos, const double &translation);

        virtual ~DiskTranslatable();

        void dessiner(const std::string &color, const std::string &border, Svgfile &svgout);
};

#endif // DISK_TRANSLATABLE_H
