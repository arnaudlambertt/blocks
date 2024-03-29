#ifndef LOSANGE_TRANSLATABLE_H
#define LOSANGE_TRANSLATABLE_H

#include "losange.h"
#include "translatable.h"

class LosangeTranslatable : public Losange, public Translatable
{
    public:
        LosangeTranslatable(const double &width, const double &height,const std::string &basepos,
                            const std::string &refpos, const double &refposX, const double &refposY,
                            const std::string &endpos, double &translation);

        virtual ~LosangeTranslatable();

        //void dessiner(Svgfile &svgout);
};

#endif // LOSANGE_TRANSLATABLE_H
