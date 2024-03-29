/** \brief classe bloc
 *
 * \param lecture de fichier
 * \param parent auquel est rattach� le bloc
 *
 */


#include "bloc.h"
#include "../geometrie/rectangle_translatable.h"
#include "../geometrie/losange_translatable.h"
#include "../geometrie/disk_translatable.h"
#include "../geometrie/triangle_translatable.h"

#include "../geometrie/rectangle_rotatable.h"
#include "../geometrie/losange_rotatable.h"
#include "../geometrie/disk_rotatable.h"
#include "../geometrie/triangle_rotatable.h"

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

    if (geometrie == "disk" && infos.find("radius") != infos.end())
        m_info.dimension1 = infos["radius"];

    else
    {
        if(infos.find("width") != infos.end())
            m_info.dimension1 = infos["width"];
        if(infos.find("height") != infos.end())
            m_info.dimension2 = infos["height"];
    }
    if(infos.find("refpos") != infos.end())
        m_info.refpos = infos["refpos"];
    if(infos.find("refposx") != infos.end())
        m_info.refposX = infos["refposx"];
    if(infos.find("refposy") != infos.end())
        m_info.refposY = infos["refposy"];
    if(translation != -1.0 && infos.find("endpos") != infos.end())
        m_info.endpos = infos["endpos"];
    if(infos.find("basepos") != infos.end())
        m_info.basepos = infos["basepos"];
    if(translation != -1.0 && infos.find("translate") != infos.end())
        m_info.translation = infos["translate"];
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

std::string Bloc::getName()
{
    bool blindage = false;
    std::string name;

    for(size_t i= m_id.size()-1; i>=0; --i)
    {
        if( blindage && ( m_id[i] < 48 || m_id[i] > 57))
        {
            name = m_id.substr(0,i+1);
            break;
        }
        else if ( m_id[i] < 48 || m_id[i] > 57)
            break;
        else
            blindage = true;
    }
    return name;
}

void Bloc::searchId(std::vector<std::string> id, std::vector<Bloc*> &listCurrent)
{
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

bool Bloc::testId(const std::string &id)
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
            return false;
        }

        if( smodulo[0] >= 48 && smodulo[0] <= 57)
            modulo = std::stoi(smodulo,&sz);

        if(modulo != -1 && reste != -1)
        {
            cpym_id = prem_id + std::to_string(numerom_id%modulo) + "%" + std::to_string(modulo);
            return (cpym_id == id);
        }
        else
            return false;
    }
    else if(idcpy.find(':') != std::string::npos)
    {
        if(numerom_id == -1)
            return false;

        std::string nom, sbornesup, pre_id;
        int borneinf = -1, bornesup = -1;
        blindage = false;

        idcpy[idcpy.find(':')] = ' ';
        iss.str(idcpy);
        iss >> nom >> sbornesup;

        for(size_t i=nom.size()-1; i>=0; --i)
        {
            if( blindage && ( nom[i] < 48 || nom[i] > 57))
            {
                borneinf = std::stoi(&nom[0]+i+1,&sz);
                pre_id = idcpy.substr(0,i+1);
                break;
            }
            else if ( nom[i] < 48 || nom[i] > 57)
                break;
            else
                blindage = true;
        }
        if(!blindage)
        {
            return false;
        }

        if( sbornesup[0] >= 48 && sbornesup[0] <= 57)
            bornesup = std::stoi(sbornesup,&sz);

        if(borneinf != -1 && borneinf!= -1)
        {
            if(borneinf>bornesup)
            {
                int temp;
                temp = borneinf;
                borneinf = bornesup;
                bornesup = temp;
            }

            if(prem_id == pre_id)
                return (borneinf <= numerom_id && numerom_id<= bornesup);
            else
                return false;
        }
        else
            return false;

    }
    else if(cpym_id.find(id) == 0)
        return true;
    else
        return false;
}

void Bloc::sauvegarde(std::ostream& ofs, int tabulation)
{
    size_t rang = 0;

    if(m_parent != nullptr)
        for(rang = 0; rang < m_parent->m_enfants.size() && m_parent->m_enfants[rang].get() != this ; ++rang)
            continue;

    if(rang > 0)
        ofs << std::endl;

    ofs << std::string (tabulation, '\t');
    if(m_id != "")
        ofs << "id=" << m_id << " ";

    if(dynamic_cast<Losange*>(m_geometrie.get()))
        ofs << "shape=losange width=" << m_info.dimension1 << " height=" << m_info.dimension2;
    else if(dynamic_cast<Triangle*>(m_geometrie.get()))
        ofs << "shape=triangle width=" << m_info.dimension1 << " height=" << m_info.dimension2;
    else if(dynamic_cast<Disk*>(m_geometrie.get()))
        ofs << "shape=disk radius=" << m_info.dimension1;
    else
        ofs << "width=" << m_info.dimension1 << " height=" << m_info.dimension2;

    ofs << " color=" << m_color;

    if(m_border != "black")
        ofs << " border=" << m_border;

    ofs << std::endl << std::string (tabulation, '\t');

    ofs << "refpos=" << m_info.refpos << " ";

    if(m_info.refposX != "")
        ofs << "refposx=" << m_info.refposX << " ";

    if(m_info.refposY != "")
        ofs << "refposy=" << m_info.refposY << " ";

    if(dynamic_cast<Translatable*>(m_geometrie.get()))
        ofs << "endpos=" << m_info.endpos << " ";

    if(m_info.basepos != "")
        ofs << "basepos=" << m_info.basepos << " ";

    if(Translatable* tr = dynamic_cast<Translatable*>(m_geometrie.get()))
        if(m_info.translation != "" || tr->getTranslation() != 0.5)
            ofs << "translate=" << tr->getTranslation() << " ";

    if(dynamic_cast<Rotatable*>(m_geometrie.get()))
        ofs << "rotate=" << m_geometrie->getVraiRotation() << " ";

    ofs << std::endl;

    if (m_enfants.size())
    {
        ofs << std::string(tabulation, '\t') << "[" << std::endl;

        for(auto &i : m_enfants)
            i->sauvegarde(ofs, tabulation+1);

        ofs << std::string(tabulation, '\t') << "]";
        if(m_parent != nullptr)
            ofs << std::endl;
    }
}

std::vector<Bloc*> Bloc::getEnfants()
{
    std::vector<Bloc*> enfants;
    for(auto &i : m_enfants)
        enfants.push_back(i.get());
    return enfants;
}

void Bloc::displayId(Svgfile &svgout)
{
    dessinerId(svgout);
    for(auto &i: m_enfants)
    {
        i->displayId(svgout);
    }
}

void Bloc::displayRuler(Svgfile &svgout)
{
    if(Translatable* t = dynamic_cast<Translatable*>(getGeometrie()))
        t->dessinerAxe(m_parent, svgout);
    else if(Rotatable* r = dynamic_cast<Rotatable*>(getGeometrie()))
        r->dessinerAxe(this, svgout);

    for(auto &i: m_enfants)
    {
        i->displayRuler(svgout);
    }
}

void Bloc::dessinerId(Svgfile &svgout)
{
    svgout.addText(getAbsolute("ml").getX()-1, getAbsolute("ml").getY()-1, m_id, "yellow");
    svgout.addText(getAbsolute("ml").getX()-1, getAbsolute("ml").getY(), m_id, "yellow");
    svgout.addText(getAbsolute("ml").getX()-1, getAbsolute("ml").getY()+1, m_id, "yellow");
    svgout.addText(getAbsolute("ml").getX(), getAbsolute("ml").getY()-1, m_id, "yellow");
    svgout.addText(getAbsolute("ml").getX(), getAbsolute("ml").getY()+1, m_id, "yellow");
    svgout.addText(getAbsolute("ml").getX()+1, getAbsolute("ml").getY()-1, m_id, "yellow");
    svgout.addText(getAbsolute("ml").getX()+1, getAbsolute("ml").getY(), m_id, "yellow");
    svgout.addText(getAbsolute("ml").getX()+1, getAbsolute("ml").getY()+1, m_id, "yellow");
    svgout.addText(getAbsolute("ml").getX(),getAbsolute("ml").getY(), m_id, "black");
}

Bloc * Bloc::getFirstMovableParent()
{
    if(dynamic_cast<Translatable*>(m_geometrie.get()) || dynamic_cast<Rotatable*>(m_geometrie.get()))
    {
        if(m_parent != nullptr && m_parent->getFirstMovableParent() != nullptr)
            return m_parent->getFirstMovableParent();
        else
            return this;
    }
    else if(m_parent != nullptr)
        return m_parent->getFirstMovableParent();
    else
        return nullptr;
}

std::list<Bloc*> Bloc::getTousEnfants()
{
    std::list<Bloc*> mesEnfants;

    for(auto &i : getEnfants())
    {
        mesEnfants.push_back(i);
        for(auto &j : i->getTousEnfants())
            mesEnfants.push_back(j);
    }

    return mesEnfants;
}

bool Bloc::collision(std::list<Bloc*> tousEnfants, std::vector<std::pair<Bloc*,Coords>> &colltab)
{
    Bloc* firstMovableParent = getFirstMovableParent();
    bool test = false;

    for(auto &i : tousEnfants)
    {
        if(i->getFirstMovableParent() == nullptr || firstMovableParent != i->getFirstMovableParent()) // pas de parent movable commun
        {
            for(double j = -0.5; j <= 0.5 ; j+=0.5)//LATANCE IMPORTANTE
            {
                for(double k = -0.5; k <= 0.5 ; k+=0.5)//LATENCE IMPORTANTE
                    if(k == 0 && j ==0)
                        continue;
                    else if( i->getGeometrie()->isIn( getAbsolute(convertRefposEnfant(Coords{j,k})) ) )
                    {
                        test = true;
                        colltab.push_back({this,Coords{j,k}});
                    }
            }
            if (test)
                return true;
        }
    }

    for (auto &i : m_enfants)
    {
        if(i->collision((tousEnfants),colltab))
            return true;
    }
    return test;
}


