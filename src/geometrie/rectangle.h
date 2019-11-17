#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "geometrie.h"

class Rectangle : public Geometrie
{
    public:
        Rectangle();
        Rectangle(const double &width, const double &height, const std::string &basepos, const std::string &refpos, const double &refposX, const double &refposY);
        virtual ~Rectangle();

        std::vector<double> getDimensions() const;
        double getWeight() { return m_height; }
        void setHeight(double val) { m_height = val; }
        double getWidth() { return m_width; }
        void setWidth(double val) { m_width = val; }

        virtual void dessiner(const Bloc* parent, const std::string &color, const std::string &border, Svgfile &svgout);

        virtual Coords convertRefposEnfant(const Coords &refposEnfant) const;
        virtual Coords calculerAbsoluteCoords(const Bloc* parent, const std::string &localPos) const;


    protected:
        double m_height;
        double m_width;

};

#endif // RECTANGLE_H
