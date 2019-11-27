#include "bloc.h"
#include "../geometrie/rectangle_translatable.h"
#include "../geometrie/losange_translatable.h"
#include "../geometrie/disk_translatable.h"
#include "../geometrie/triangle_translatable.h"

#include "../geometrie/rectangle_rotatable.h"
#include "../geometrie/losange_rotatable.h"
#include "../geometrie/disk_rotatable.h"
#include "../geometrie/triangle_rotatable.h"

Bloc::Bloc()
    : Bloc{nullptr, "emptyId", std::make_unique<RectangleRotatable>(200,100,"tl","mc",0.0,0.0,33), "orange", "black"}
{
    //ctor
}

Bloc::Bloc(std::istream& ifs, Bloc* parent, bool &child)
{
    std::string ligne, mot;
    std::istringstream iss;
    std::map<std::string, std::string> infos;

    child = true;
    m_parent = parent;

    if(std::getline(ifs, ligne))
    {
        iss.str(ligne);
        for(int i = 0; i < 2; ++i)
        {
            while(iss)
            {
                std::string raw, key, val;

                iss >> raw;

                if(raw.find('=') != std::string::npos)
                {
                    raw[raw.find('=')] = ' ';

                    std::istringstream iss2(raw);
                    iss2 >> key >> val;

                    infos.insert({key,val});
                }
            }
            if(i == 0)
            {
                iss.clear();
                std::getline(ifs,ligne);
                iss.str(ligne);
            }
        }

        initMembers(infos);

        std::getline(ifs, ligne);
        iss.clear();
        iss.str(ligne);
        iss >> mot;

        if(mot == "[") // a des enfants
        {
            do
                m_enfants.push_back(std::make_unique<Bloc>(ifs, this, child));
            while(child);

            std::getline(ifs, ligne);
            if(ligne.empty())
                child = true;
            else
            {
                iss.clear();
                iss.str(ligne);
                iss >> mot;
                if(mot == "]")
                    child = false;
            }
        }

        else if(mot == "]")
            child = false;

    }
}


Bloc::Bloc(Bloc* parent,const std::string &id, std::unique_ptr<Geometrie> geometrie, const std::string &color, const std::string &border)
    : m_parent{parent}, m_id{id}, m_color{color}, m_border{border}, m_geometrie(std::move(geometrie))
{
    m_geometrie->setBloc(this);
}

void Bloc::initMembers(std::map<std::string,std::string> &infos)
{
    std::string geometrie = "rectangle", basepos = "tr", refpos = "br", endpos = "br";
    double width = 50.0, height = 50.0, radius = 50.0, translation = -1.0, rotation = -1.0, refposX = 0.0, refposY = 0.0;

    if(infos.find("shape") != infos.end())
        geometrie = infos["shape"];

    if(infos.find("id") != infos.end())
        m_id = infos["id"];
    else
        m_id = "";

    if(infos.find("color") != infos.end())
        m_color = infos["color"];
    else
        m_color = "white";

    if(infos.find("border") != infos.end())
        m_border = infos["border"];
    else
        m_border = "black";

    if(infos.find("basepos") != infos.end())
        basepos = infos["basepos"];

    if(infos.find("refpos") != infos.end())
        refpos = infos["refpos"];

    if(infos.find("endpos") != infos.end())
        endpos = infos["endpos"];
    else
        endpos = refpos;

    if(infos.find("translate") != infos.end())
        translation = std::stod(infos["translate"]);
    else if (endpos != refpos)
        translation = 0.5;

    if(infos.find("rotate") != infos.end())
        rotation = std::stod(infos["rotate"]);

    if(infos.find("refposx") != infos.end())
    {
        if(infos["refposx"].find('%') != std::string::npos)
            refposX = std::stod(infos["refposx"])* 0.01;
        else
            refposX = std::stod(infos["refposx"])/m_parent->getDimensions()[0];
    }

    if(infos.find("refposy") != infos.end())
    {
        if(infos["refposy"].find('%') != std::string::npos)
            refposY = std::stod(infos["refposy"])* 0.01;
        else
            refposY = std::stod(infos["refposy"])/m_parent->getDimensions()[1];
    }

    if(infos.find("width") != infos.end())
    {
        if(infos["width"].find('%') != std::string::npos)
            width = m_parent->getDimensions()[0] * std::stod(infos["width"])* 0.01;
        else
            width = std::stod(infos["width"]);
    }

    if(infos.find("height") != infos.end())
    {
        if(infos["height"].find('%') != std::string::npos)
            height = m_parent->getDimensions()[1]*std::stod(infos["height"])*0.01;
        else
            height = std::stod(infos["height"]);
    }

    if(infos.find("radius") != infos.end())
    {
        if(infos["radius"].find('%') != std::string::npos)
            radius = m_parent->getDimensions()[0]*std::stod(infos["radius"])*0.01;
        else
            radius = std::stod(infos["radius"]);
    }

    if(geometrie == "triangle")
    {
        if(translation != -1.0 )
            m_geometrie = std::make_unique<TriangleTranslatable>(width,height,basepos,refpos,refposX,refposY,endpos,translation);

        else if(rotation != -1.0)
            m_geometrie = std::make_unique<TriangleRotatable>(width,height,basepos,refpos,refposX,refposY,rotation);

        else
            m_geometrie = std::make_unique<Triangle>(width,height,basepos,refpos,refposX,refposY);
    }

    else if(geometrie == "losange")
    {
        if(translation != -1.0 )
            m_geometrie = std::make_unique<LosangeTranslatable>(width,height,basepos,refpos,refposX,refposY,endpos,translation);

        else if(rotation != -1.0)
            m_geometrie = std::make_unique<LosangeRotatable>(width,height,basepos,refpos,refposX,refposY,rotation);

        else
            m_geometrie = std::make_unique<Losange>(width,height,basepos,refpos,refposX,refposY);
    }

    else if(geometrie == "disk")
    {
        if(translation != -1.0 )
            m_geometrie = std::make_unique<DiskTranslatable>(radius,basepos,refpos,refposX,refposY,endpos,translation);

        else if(rotation != -1.0)
            m_geometrie = std::make_unique<DiskRotatable>(radius,basepos,refpos,refposX,refposY,rotation);

        else
            m_geometrie = std::make_unique<Disk>(radius,basepos,refpos,refposX,refposY);
    }

    else
    {
        if(translation != -1.0 )
            m_geometrie = std::make_unique<RectangleTranslatable>(width,height,basepos,refpos,refposX,refposY,endpos,translation);

        else if(rotation != -1.0)
            m_geometrie = std::make_unique<RectangleRotatable>(width,height,basepos,refpos,refposX,refposY,rotation);

        else
            m_geometrie = std::make_unique<Rectangle>(width,height,basepos,refpos,refposX,refposY);
    }

    m_geometrie->setBloc(this);

    if(m_parent != nullptr)
        m_geometrie->setRotation(m_geometrie->getRotation() + m_parent->getGeometrie()->getRotation());
}

Coords Bloc::convertRefposEnfant(const Coords &refposEnfant) const
{
    return m_geometrie->convertRefposEnfant(refposEnfant);
}

Coords Bloc::getAbsolute(const Coords &localPos) const
{
    return m_geometrie->getAbsolute(localPos);
}

Coords Bloc::getAbsolute(const std::string &localPos) const
{
    return m_geometrie->getAbsolute(localPos);
}

void Bloc::dessiner(Svgfile &svgout)
{
    m_geometrie->dessiner(svgout);

    for(auto &i : m_enfants)
        i->dessiner(svgout);
}

void Bloc::searchId(std::vector<std::string> id, std::vector<Bloc*> &listCurrent)
{
    //std::cout << "search id" << std::endl;
    if(testId(id[0]))
    {
        if(id.size() == 1)
            listCurrent.push_back(this);
        id.erase(id.begin());
        std::cout << m_id << " FOUND" << std::endl;
    }

    if(id.size())
        for(auto &i: m_enfants)
            i->searchId(id, listCurrent);

}

bool Bloc::testId(const std::string &id)   /// : range | [ specific ]| % modulo | ? random
{
    std::string::size_type sz;

    std::istringstream iss;
    std::string idcpy = id;

    std::string cpym_id = m_id, prem_id;
    int numerom_id = -1;
    bool blindage = false;

    for(size_t i= cpym_id.size()-1; i>=0; --i)
    {
        if( blindage && ( cpym_id[i] < 48 || cpym_id[i] > 57))
        {
            numerom_id = std::stoi(&cpym_id[0]+i+1,&sz);
            prem_id = cpym_id.substr(0,i+1);
            break;
        }
        else if ( cpym_id[i] < 48 || cpym_id[i] > 57)
            break;
        else
            blindage = true;
    }

    if(idcpy.find('%') != std::string::npos)
    {
        if(numerom_id == -1)
            return false;

        std::string nom, smodulo;
        int reste = -1, modulo =-1;
        blindage = false;

        idcpy[idcpy.find('%')] = ' ';
        iss.str(idcpy);
        iss >> nom >> smodulo;

        for(size_t i=nom.size()-1; i>=0; --i)
        {
            if( blindage && ( nom[i] < 48 || nom[i] > 57))
            {
                reste = std::stoi(&nom[0]+i+1,&sz);
                break;
            }
            else if ( nom[i] < 48 || nom[i] > 57)
                break;
            else
                blindage = true;
        }
        if(!blindage)
        {
            std::cout << "erreur de format" << std::endl;
            return false;
        }

        if( smodulo[0] >= 48 && smodulo[0] <= 57)
            modulo = std::stoi(smodulo,&sz);
        else
            std::cout <<"erreur de format" << std::endl;

        if(modulo != -1 && reste != -1)
        {
            cpym_id = prem_id + std::to_string(numerom_id%modulo) + "%" + std::to_string(modulo);
            return (cpym_id == id);
        }
        else
            return false;
    }

    return false;
}

void Bloc::sauvegarde(std::ostream& ofs, int tabulation)
{
    size_t rang = 0;

    if(m_parent != nullptr)
        for(rang = 0; rang < m_parent->m_enfants.size() && m_parent->m_enfants[rang].get() != this ; ++rang)
            continue;

    if(rang > 0)
        ofs << "\n";

    ofs << std::string (tabulation, '\t') << "id=" << m_id << "\n\n" ;
    if (m_enfants.size())
    {
        ofs << std::string(tabulation, '\t') << "[\n";

        for(auto &i : m_enfants)
            i->sauvegarde(ofs, tabulation+1);

        ofs << std::string(tabulation, '\t') << "]\n";
    }
}

