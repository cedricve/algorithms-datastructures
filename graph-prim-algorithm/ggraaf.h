/* 
 * File:   ggraaf.h
 * Author: Wijnand
 *
 * Created on 9 mei 2010, 21:32
 */

#ifndef _GGRAAF_H
#define	_GGRAAF_H

#include <vector>
#include "graaf.h"


template <GraafType TYPE, typename T>
class GewogenGraaf : public Graaf<TYPE>
{
public:
    GewogenGraaf(int n=0) : Graaf<TYPE>(n), gewichten(n) {}

    virtual ~GewogenGraaf() {}

    T gewicht(int i) const
    {
        return gewichten[i];
    }

    T &gewicht(int i)
    {
        return gewichten[i];
    }

    // override
    virtual void init(int aantal_knopen=0)
    {
        Graaf<TYPE>::init(aantal_knopen);
        gewichten.resize(0);
    }
    
    // (geen override)
    virtual int voeg_verbinding_toe(int van, int naar, T w)
    {
        int t = Graaf<TYPE>::voeg_verbinding_toe(van, naar);	// throws
        // assert t==gewicht.size()
        gewichten.push_back(w);
        return t;
    }

    // override
    virtual void schrijf_verbinding(std::ostream &os, int van, int naar) const
    {
        int v = this->knopen[van].find(naar)->second;
        os << van << " " << naar << " " << gewichten[v] << std::endl;
    }

    // override
    virtual void lees_verbinding(std::istream &is)
    {
        int van, naar;
        T gewicht;
        is >> van >> naar >> gewicht;
        voeg_verbinding_toe(van, naar, gewicht);
    }

protected:
    std::vector<T> gewichten;

};



#endif	/* _GGRAAF_H */

