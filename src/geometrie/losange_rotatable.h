#ifndef LOSANGE_ROTATABLE_H
#define LOSANGE_ROTATABLE_H

#include "losange.h"
#include "rotatable.h"

class LosangeRotatable : public Losange, public Rotatable
{
public:
    LosangeRotatable(const double &width, const double &height,const std::string &basepos,
                     const std::string &refpos, const double &refposX, const double &refposY,
                     const double &rotation);

    virtual ~LosangeRotatable();

    //void dessiner(Svgfile &svgout);
};

#endif // LOSANGE_ROTATABLE_H
