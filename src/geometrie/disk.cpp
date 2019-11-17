#include "disk.h"
#include "../blocs/bloc.h"

Disk::Disk()
: Disk{50.0,"tl","br",0.0,0.0}
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

void Disk::dessiner(const Bloc* parent, const std::string &color, const std::string &border, Svgfile &svgout)
{
    svgout.addDisk(getAbsolute(parent, "mc").getX(),getAbsolute(parent, "mc").getY(),m_radius,color,1,border);
}

Coords Disk::convertRefposEnfant(const Coords &refposEnfant) const
{
    return squareposToDiskpos(refposEnfant);
}

Coords Disk::getAbsolute(const Bloc* parent, const std::string &localPos) const
{
    return Geometrie::getAbsolute(parent, squareposToDiskpos(Coords{pos()[localPos[1]], pos()[localPos[0]]}));
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
