#include "Factory.hpp"

Factory::~Factory()
{
    std::map<int,planeLayout *>::iterator it;
    for(it=m_map.begin();it!=m_map.end();it++)
    {
        delete (*it).second;
    }
}

int Factory::loadLayout(const char* Filename)
{
    int nbr=0;
    std::string bFileName;
    TiXmlDocument doc(Filename);
    if( !doc.LoadFile()) return 0;
    TiXmlHandle hDoc(&doc);
    TiXmlElement* pElem;
    TiXmlHandle hRoot(0);

    pElem=hDoc.FirstChildElement().Element();
    // should always have a valid root but handle gracefully if it does
    if (!pElem) return 0;
    hRoot=TiXmlHandle(pElem);

    pElem=hRoot.Element();
    pElem->QueryIntAttribute("NbrofFiles", &nbr);

    pElem=hRoot.FirstChild("pLayout").Element();
    for( int i=0;i<nbr;i++)
    {
        planeLayout * ptrCurrentL = new planeLayout;
        if(!pElem)  return 0;
        bFileName = pElem->Attribute("file");
        ptrCurrentL->LoadFromXml(bFileName.c_str());
        Register(ptrCurrentL->GetKey(),ptrCurrentL);
		pElem=pElem->NextSiblingElement();
    }
    return 1;

}

void Factory::Register(int key,planeLayout* obj)
{
    //si la clé n'est pas déjà présente
    if(m_map.find(key)==m_map.end())
    {
        //on ajoute l'objet dans la map
        m_map[key]=obj;
    }
}

PlaneE* Factory::Create(int key,sf::Image &Img) const
{
    PlaneE* ptrPlane = new PlaneE;
    ptrPlane->SetImage(Img);    //must be set before other clip parameter
    std::map<int,planeLayout *>::const_iterator it=m_map.find(key);
    //si l'itérateur ne vaut pas map.end(), cela signifie que que la clé à été trouvée
    if(it!=m_map.end())
    {
        //(*it).second->Print();
        (*it).second->SetToPlane(ptrPlane);
        return ptrPlane;
    }
    else
    {
        delete ptrPlane;
        return NULL;
    }
}
