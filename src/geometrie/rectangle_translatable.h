#ifndef RECTANGLE_TRANSLATABLE_H
#define RECTANGLE_TRANSLATABLE_H

#include "rectangle.h"
#include "translatable.h"

class RectangleTranslatable : public Rectangle, public Translatable
{
    public:
        RectangleTranslatable(const double &width, const double &height,const std::string &basepos,
                            const std::string &refpos, const double &refposX, const double &refposY,
                            const std::string &endpos, const double &translation);

        virtual ~RectangleTranslatable();
};

#endif // RECTANGLE_TRANSLATABLE_H
