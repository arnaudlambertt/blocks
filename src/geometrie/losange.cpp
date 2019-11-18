#include "losange.h"
#include <iostream>

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

Coords Losange::getAbsolute(const Bloc* parent, const std::string &localPos) const
{
    return Geometrie::getAbsolute(parent, squareposToLosangepos(Coords{pos()[localPos[1]], pos()[localPos[0]]}));
}

void Losange::dessiner(const Bloc* parent, const std::string &color, const std::string &border, Svgfile &svgout)
{
    svgout.addLosange(getAbsolute(parent, "ml").getX(),getAbsolute(parent, "ml").getY(),
                      getAbsolute(parent, "tc").getX(),getAbsolute(parent, "tc").getY(),color,1,border);
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
