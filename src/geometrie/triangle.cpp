#include "triangle.h"
#include "../blocs/bloc.h"

Triangle::Triangle()
    : Triangle{50,50,"tl","br",0.0,0.0}
{
    //ctor
}

Triangle::Triangle(const double &width, const double &height, const std::string &basepos, const std::string &refpos, const double &refposX, const double &refposY)
    : Geometrie{basepos,refpos,refposX,refposY},m_width{width},m_height{height}
{
    m_basepos = squareposToTrianglepos(m_basepos);     //cpy ctor
}

Triangle::~Triangle()
{
    //dtor
}

std::vector<double> Triangle::getDimensions() const
{
    return std::vector<double> {m_width,m_height};
}

Coords Triangle::convertRefposEnfant(const Coords &refposEnfant) const
{
    return squareposToTrianglepos(refposEnfant);
}

Coords Triangle::getAbsolute(const std::string &localPos) const
{
    return getAbsolute(squareposToTrianglepos(Coords{pos()[localPos[1]], pos()[localPos[0]]}));
}

void Triangle::dessiner(Svgfile &svgout)
{
    svgout.addTriangle(getAbsolute("bl").getX(),getAbsolute("bl").getY(),
                       getAbsolute("tc").getX(),getAbsolute("tc").getY(),
                       getAbsolute("br").getX(),getAbsolute("br").getY(),
                       m_bloc->getColor(),1.25,m_bloc->getBorder());
}

Coords Triangle::squareposToTrianglepos(const Coords &a)
{
    bool test = false;
    double m,b;
    Coords resultat = a;
    if (a.getY() < 0.5)
    {
        if (a.getY() < -2*a.getX()-0.5)
        {
            test = true;
            m = -2;
            b = -0.5;
        }
        else if (a.getY() < 2*a.getX()-0.5)
        {
            test = true;
            m = 2;
            b = -0.5;
        }
    }

    if(test)
    {
        resultat.setX((a.getX()+m*a.getY()-m*b)/(1 + m*m));
        resultat.setY((m*a.getX()+m*m*a.getY()+b)/(1 + m*m));
    }

    return resultat;
}

//SOURCE : https://stackoverflow.com/questions/2049582/how-to-determine-if-a-point-is-in-a-2d-triangle
bool Triangle::isIn(const Coords &point) const
{
    double area, s, t;
    Coords p2 = getAbsolute("bl"), p0 = getAbsolute("br"), p1 = getAbsolute("tc");

    area = 0.5 *(-p1.getY()*p2.getX() + p0.getY()*(-p1.getX() + p2.getX()) + p0.getX()*(p1.getY() - p2.getY()) + p1.getX()*p2.getY());
    s = 1/(2*area)*(p0.getY()*p2.getX() - p0.getX()*p2.getY() + (p2.getY() - p0.getY())*point.getX() + (p0.getX() - p2.getX())*point.getY());
    t = 1/(2*area)*(p0.getX()*p1.getY() - p0.getY()*p1.getX() + (p0.getY() - p1.getY())*point.getX() + (p1.getX() - p0.getX())*point.getY());

    return (s>0 && t>0 && 1-s-t>0);
}
