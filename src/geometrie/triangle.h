#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "geometrie.h"


class Triangle : public Geometrie
{
public:
    Triangle();
    Triangle(const double &width, const double &height, const std::string &basepos, const std::string &refpos, const double &refposX, const double &refposY);
    virtual ~Triangle();

    static Coords squareposToTrianglepos(const Coords &a);

    std::vector<double> getDimensions() const;
    double Getheight()
    {
        return m_height;
    }
    void Setheight(double val)
    {
        m_height = val;
    }
    double Getwidth()
    {
        return m_width;
    }
    void Setwidth(double val)
    {
        m_width = val;
    }

    void dessiner(const Bloc* parent, const std::string &color, const std::string &border, Svgfile &svgout);


    virtual Coords convertRefposEnfant(const Coords &refposEnfant) const;
    virtual Coords getAbsolute(const Bloc* parent, const std::string &localPos) const;

protected:
    double m_width;
    double m_height;

};

#endif // TRIANGLE_H
