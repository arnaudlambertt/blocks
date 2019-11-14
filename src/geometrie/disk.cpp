#include "disk.h"
#include "../blocs/bloc.h"

Disk::Disk()
: Disk{50.0,"tl","br",0.0,0.0}
{
    //ctor
}

Disk::Disk(double radius, std::string basepos, std::string refpos, double refposX, double refposY)
: Geometrie{basepos,refpos,refposX,refposY}, m_radius{radius}
{
    //ctor
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

Coords Disk::calculerAbsoluteCoords(const Bloc* parent, Coords localPos) const
{
    Coords absolute;

    if(parent != nullptr) //calcul absolute coords de basepos
        {
            if(dynamic_cast<Disk*>(parent->getGeometrie()))
            {
                absolute.setY( parent->calculerAbsoluteCoords( parent->getBasepos() ).getY() + ( squareposToDiskpos(m_refpos).getY() - squareposToDiskpos(parent->getBasepos()).getY() )  * parent->getDimensions()[1] );
                absolute.setX( parent->calculerAbsoluteCoords( parent->getBasepos() ).getX() + ( squareposToDiskpos(m_refpos).getX() - squareposToDiskpos(parent->getBasepos()).getX() )  * parent->getDimensions()[0] );
            }
            else
            {
                absolute.setY( parent->calculerAbsoluteCoords( parent->getBasepos() ).getY() + ( m_refpos.getY() - parent->getBasepos().getY() )  * parent->getDimensions()[1] );
                absolute.setX( parent->calculerAbsoluteCoords( parent->getBasepos() ).getX() + ( m_refpos.getX() - parent->getBasepos().getX() )  * parent->getDimensions()[0] );
            }
        }

    else
        absolute = {0,0};

    if(m_basepos.getY() != localPos.getY())
        absolute.setY( absolute.getY() + (squareposToDiskpos(localPos).getY() - squareposToDiskpos(m_basepos).getY())*2* m_radius );

    if(m_basepos.getX() != localPos.getX())
        absolute.setX( absolute.getX() + (squareposToDiskpos(localPos).getX() - squareposToDiskpos(m_basepos).getX())*2* m_radius );

    return absolute;
}

Coords Disk::calculerAbsoluteCoords(const Bloc* parent, std::string localPos) const
{
    return calculerAbsoluteCoords(parent, Coords{pos()[localPos[1]], pos()[localPos[0]]});
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
