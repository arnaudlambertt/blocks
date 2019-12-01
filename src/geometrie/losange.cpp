/** \brief classe losange
 *
 * \param largeur
 * \param longueur
 * \param position locale où le parent s'attache à son enfant
 * \param position locale en X où le parent s'attache à son enfant
 * \param position locale en Y où le parent s'attache à son enfant
 *
 */

#include "losange.h"
#include <iostream>
#include "../blocs/bloc.h"

Losange::Losange()
    : Losange{75,50,"tl","br",0.0,0.0}
{
    //ctor
}

Losange::Losange(const double &width, const double &height, const std::string &basepos, const std::string &refpos, const double &refposX, const double &refposY)
    : Geometrie{basepos,refpos,refposX,refposY},m_height{height}, m_width{width}
{
    m_basepos = squareposToLosangepos(m_basepos);
}

Losange::~Losange()
{
    //dtor
}

std::vector<double> Losange::getDimensions() const
{
    return std::vector<double> {m_width,m_height};
}

Coords Losange::convertRefposEnfant(const Coords &refposEnfant) const
{
    return squareposToLosangepos(refposEnfant);
}

Coords Losange::getAbsolute(const std::string &localPos) const
{
    return getAbsolute(squareposToLosangepos(Coords{pos()[localPos[1]], pos()[localPos[0]]}));
}

void Losange::dessiner(Svgfile &svgout)
{
    svgout.addLosange(getAbsolute( "ml").getX(),getAbsolute( "ml").getY(),
                      getAbsolute( "tc").getX(),getAbsolute( "tc").getY(),
                      getAbsolute( "mr").getX(),getAbsolute( "mr").getY(),
                      getAbsolute( "bc").getX(),getAbsolute( "bc").getY(),
                      m_bloc->getColor(),1,m_bloc->getBorder());
}

Coords Losange::squareposToLosangepos(const Coords &a)
{
    bool test = false;
    double m,b;
    Coords resultat = a;

    if(a.getX() < 0.0)
    {
        if(a.getY() < (-a.getX() -0.5))
        {
            test = true;
            m = -1;
            b = -0.5;
        }
        else if(a.getY() > (a.getX() +0.5))
        {
            test = true;
            m = 1;
            b = 0.5;
        }
    }

    else if (a.getX() >= 0.0)
    {

        if(a.getY() < (a.getX() -0.5))
        {
            test = true;
            m = 1;
            b = -0.5;
        }
        else if (a.getY() > (-a.getX() + 0.5))
        {
            test = true;
            m = -1;
            b = 0.5;
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
bool Losange::isIn(const Coords &point) const
{
    double area, s, t;
    Coords p2 = getAbsolute("tc"), p0 = getAbsolute("mr"), p1 = getAbsolute("ml");

    area = 0.5 *(-p1.getY()*p2.getX() + p0.getY()*(-p1.getX() + p2.getX()) + p0.getX()*(p1.getY() - p2.getY()) + p1.getX()*p2.getY());
    s = 1/(2*area)*(p0.getY()*p2.getX() - p0.getX()*p2.getY() + (p2.getY() - p0.getY())*point.getX() + (p0.getX() - p2.getX())*point.getY());
    t = 1/(2*area)*(p0.getX()*p1.getY() - p0.getY()*p1.getX() + (p0.getY() - p1.getY())*point.getX() + (p1.getX() - p0.getX())*point.getY());

    double area1, s1, t1;
    Coords p3 = getAbsolute("ml"), p5 = getAbsolute("mr"), p4 = getAbsolute("bc");

    area1 = 0.5 *(-p4.getY()*p3.getX() + p5.getY()*(-p4.getX() + p3.getX()) + p5.getX()*(p4.getY() - p3.getY()) + p4.getX()*p3.getY());
    s1 = 1/(2*area1)*(p5.getY()*p3.getX() - p5.getX()*p3.getY() + (p3.getY() - p5.getY())*point.getX() + (p5.getX() - p3.getX())*point.getY());
    t1 = 1/(2*area1)*(p5.getX()*p4.getY() - p5.getY()*p4.getX() + (p5.getY() - p4.getY())*point.getX() + (p4.getX() - p5.getX())*point.getY());

    return ((s>0 && t>0 && 1-s-t>0) || (s1>0 && t1>0 && 1-s1-t1>0));
}
