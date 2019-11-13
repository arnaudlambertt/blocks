#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "geometrie.h"

class Rectangle : public Geometrie
{
    public:
        Rectangle();
        Rectangle(double width, double height,std::string basepos, std::string refpos, double refposX, double refposY);
        virtual ~Rectangle();

        std::vector<double> getDimensions() const;
        double getWeight() { return m_height; }
        void setHeight(double val) { m_height = val; }
        double getWidth() { return m_width; }
        void setWidth(double val) { m_width = val; }

        virtual void dessiner(const Bloc* parent, Couleur color, Couleur border, Svgfile &svgout);

        virtual Coords calculerAbsoluteCoords(const Bloc* parent, Coords localPos) const;
        virtual Coords calculerAbsoluteCoords(const Bloc* parent, std::string localPos) const;


    protected:
        double m_height;
        double m_width;

};

#endif // RECTANGLE_H
