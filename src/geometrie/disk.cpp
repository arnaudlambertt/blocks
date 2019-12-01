#include "disk.h"
#include "../blocs/bloc.h"

Disk::Disk()
: Disk{50.0,"bl","tr",0.0,0.0}
{
    //ctor
}

Disk::Disk(const double &radius, const std::string &basepos, const std::string &refpos, const double &refposX, const double &refposY)
: Geometrie{basepos,refpos,refposX,refposY}, m_radius{radius}
{
    m_basepos = squareposToDiskpos(m_basepos);
}

Disk::~Disk()
{
    //dtor
}

std::vector<double> Disk::getDimensions() const
{
    return std::vector<double> {2*m_radius,2*m_radius};
}

void Disk::dessiner(Svgfile &svgout)
{
    svgout.addDisk(getAbsolute("mc").getX(),getAbsolute("mc").getY(),
                   m_radius,m_bloc->getColor(),1.25,m_bloc->getBorder());
}

Coords Disk::convertRefposEnfant(const Coords &refposEnfant) const
{
    return squareposToDiskpos(refposEnfant);
}

Coords Disk::getAbsolute(const std::string &localPos) const
{
    return getAbsolute(squareposToDiskpos(Coords{pos()[localPos[1]], pos()[localPos[0]]}));
}

double Disk::abs(double a)
{
    return (sqrt(a*a));
}

double Disk::signe(double a)
{
    return a>=0.0?1:-1;
}

Coords Disk::squareposToDiskpos(const Coords &a)
{
    double angle = 2*atan2(a.getY(),a.getX() + sqrt(a.getX()*a.getX() + a.getY()*a.getY()) );
    double radius = sqrt(a.getX()*a.getX() + a.getY()*a.getY());
    if (radius > 0.5)
        radius = 0.5;

    return Coords {
        radius*signe(a.getX())*abs(cos(angle)),
        radius*signe(a.getY())*abs(sin(angle))
        };

}

bool Disk::isIn(const Coords &point) const
{
    Coords o = getAbsolute("mc");

    return (m_radius > sqrt( pow(point.getX()-o.getX(),2) + pow(point.getY()-o.getY(),2)));
}
