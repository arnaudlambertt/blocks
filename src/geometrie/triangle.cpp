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

void Triangle::dessiner(const std::string &color, const std::string &border, Svgfile &svgout)
{
    svgout.addTriangle(getAbsolute("bl").getX(),getAbsolute("bl").getY(),
                       getAbsolute("tc").getX(),getAbsolute("tc").getY(),
                       getAbsolute("br").getX(),getAbsolute("br").getY(),color,1,border);
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


