#include "disk.h"
#include "../blocs/bloc.h"

Disk::Disk()
: Disk{50.0,"tl","mc",util::alea(-0.5,0.5),util::alea(-0.5,0.5)}
{
    //ctor
}

Disk::Disk(double radius, std::string basepos, std::string refpos, double refposX, double refposY)
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

void Disk::dessiner(const Bloc* parent, Couleur color, Couleur border, Svgfile &svgout)
{
    svgout.addDisk(calculerAbsoluteCoords(parent, "mc").getX(),calculerAbsoluteCoords(parent, "mc").getY(),m_radius,color,1,border);
}

Coords Disk::calculerAbsoluteCoords(const Bloc* parent, std::string localPos) const
{
    return Geometrie::calculerAbsoluteCoords(parent, squareposToDiskpos(Coords{pos()[localPos[1]], pos()[localPos[0]]}));
}

double abs(double a)
{
    return (sqrt(a*a));
}

double signe(double a)
{
    return a>=0.0?1:-1;
}

Coords squareposToDiskpos(const Coords &a)
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
