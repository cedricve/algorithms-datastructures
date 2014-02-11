#ifndef __graaf__
#define __graaf__


// wijnand.schepens@hogent.be
//
// Eenvoudige graafklasse voor gerichte of ongerichte grafen
// (representatie met burenlijsten)
//
// Alle knopen en verbindingen worden genummerd (beginnend bij 0).
// Er worden geen extra knoop- of verbindingsdata bijgehouden
// (dat kan in lijsten geindexeerd met knoop- resp. verbindingsnummers,
//  hetzij in aparte functies of klassen, hetzij in een afgeleide klasse)


#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <stdexcept>

// -------------------------------------------------------------------
// ---------------------------- interface ----------------------------
// -------------------------------------------------------------------

typedef std::map<int, int>  Knoop;	// beeldt knoopnummer (van buur) af op verbindingsnummer

// -------------------------------------------------------------------

class GraafExceptie : public std::logic_error {
public:
	GraafExceptie(const std::string &boodschap_) : std::logic_error(boodschap_) {}
};

std::ostream &operator<<(std::ostream &os, const GraafExceptie& exc)
{
	return os << exc.what();
}

// -------------------------------------------------------------------

enum GraafType { GERICHT, ONGERICHT };

// -------------------------------------------------------------------

// graaf-klasse geschikt voor ongerichte en gerichte grafen
// ongewogen
// knopen en verbindingen hebben triviale nummering (0..)
template <GraafType TYPE>
class Graaf
{
public:
    // Construeert een graaf met gegeven aantal knopen (default 0), zonder verbindingen.
    Graaf(int aantal_knopen=0);

    virtual ~Graaf() {}

    // Reset de graaf met gegeven aantal knopen (default 0), met lege knopen en zonder verbindingen.
    virtual void init(int aantal_knopen=0);

    // Voegt een nieuwe 'lege' knoop toe, d.w.z. zonder verbindingen.
    // Geeft knoopnummer van toegevoegde knoop terug (begint bij 0).
    virtual int voeg_knoop_toe();

    // Voegt verbinding toe tussen knoopnummers 'van' en 'naar'.
    // Bij ongerichte graaf wordt terugverbinding ook toegevoegd (met zelfde verbindingnummer!), tenzij van==naar.
    // Geeft verbindingsnummer van toegevoegde verbinding terug (begint bij 0).
    // Gooit GraafExceptie indien verbinding al bestaat of knoopnummers ongeldig zijn.
    // Opm. volgorde van toegevoegde verbindingen wordt niet bijgehouden!
    virtual int voeg_verbinding_toe(int van, int naar);


    // Geeft het aantal knopen van de graaf.
    int aantal_knopen() const;

    // Geeft het aantal verbindingen van de graaf.
    // Bij ongerichte graaf worden verbindingen NIET dubbel geteld!
    int aantal_verbindingen() const;

    // Toegang tot de knopen:
    const Knoop &operator[](int i) const { return knopen[i]; }

          Knoop &operator[](int i)       { return knopen[i]; }	// deze kan als lvalue gebruikt worden


    // Schrijft de gegevens van de volledige graaf naar outputstream 'os'.
    // (verbindingsnummers worden niet uitgeschreven)
    virtual void schrijf(std::ostream &os) const;

    // Construeert huidige graaf aan de hand van de gegevens gelezen uit inputstream 'is'
    // (zoals uitgeschreven door 'schrijf()').
    // Gooit GraafExceptie indien er iets niet klopt bij het inlezen.
    // Opm.:
    // - de graaf wordt eerst leeggemaakt.
    // - na uitschrijven en terug inlezen kunnen de verbindingsnummers gewijzigd zijn.
    virtual void lees(std::istream &is);

    void controleer_knoopnummer(int k) const;	// throw indien k ongeldig

    virtual void schrijf_knoop(std::ostream &os, int k) const;
    virtual void schrijf_verbinding(std::ostream &os, int van, int naar) const;
    
    virtual void lees_knoop(std::istream &is);
    virtual void lees_verbinding(std::istream &is);

    std::vector<Knoop> knopen;
    int                nverbindingen;	
};


// Uitschrijven
template <GraafType TYPE>
std::ostream &operator<<(std::ostream &os, const Graaf<TYPE> &g);


// Inlezen
template <GraafType TYPE>
std::istream &operator>>(std::istream &is, Graaf<TYPE> &g);


// -------------------------------------------------------------------
// -------------------------- implementatie --------------------------
// -------------------------------------------------------------------

template <GraafType TYPE>
void Graaf<TYPE>::controleer_knoopnummer(int k) const
{
    if (k<0 || (size_t)k>=knopen.size())
            throw GraafExceptie("ongeldig knoopnummer");
}


template <GraafType TYPE>
Graaf<TYPE>::Graaf(int n)
: knopen(n), nverbindingen(0)
{}


template <GraafType TYPE>
void Graaf<TYPE>::init(int n)
{
    knopen.clear();
    knopen.resize(n);
    nverbindingen = 0;
}


template <GraafType TYPE>
int Graaf<TYPE>::voeg_knoop_toe()
{
    int n = knopen.size();
    knopen.resize(n+1);	// default constructor voor nieuwe knoop wordt opgeroepen (hier lege map)
    return n;
}


template <GraafType TYPE>
int Graaf<TYPE>::voeg_verbinding_toe(int van, int naar)
{
    controleer_knoopnummer(van);
    controleer_knoopnummer(naar);

    if (knopen[van].count(naar) > 0)
    {
        std::ostringstream out;
        out << "verbinding " << van << "-" << naar << " bestaat al";
        throw GraafExceptie(out.str());
    }
    else {
        int t = nverbindingen++;
        knopen[van][naar] = t;
        if (TYPE==ONGERICHT && van!=naar)
            knopen[naar][van] = t;
        return t;
    }
}


template <GraafType TYPE>
int Graaf<TYPE>::aantal_knopen() const
{ 
    return knopen.size();
}


template <GraafType TYPE>
int Graaf<TYPE>::aantal_verbindingen() const
{ 
    return nverbindingen;
}


template <GraafType TYPE>
void Graaf<TYPE>::schrijf(std::ostream &os) const
{
    os << (TYPE==GERICHT ? "gericht" : "ongericht") << std::endl;
    os << aantal_knopen() << std::endl;
    os << aantal_verbindingen() << std::endl;
    for (int van=0; van<aantal_knopen(); van++)
        schrijf_knoop(os, van);
    for (int van=0; van<aantal_knopen(); van++)
    {
        for (Knoop::const_iterator it=knopen[van].begin(); it!=knopen[van].end(); ++it)
        {
            int naar = it->first;
            if (TYPE==GERICHT || van<=naar )
                schrijf_verbinding(os, van, naar);
        }
    }
}


template <GraafType TYPE>
void Graaf<TYPE>::schrijf_knoop(std::ostream &os, int k) const
{
}

template <GraafType TYPE>
void Graaf<TYPE>::schrijf_verbinding(std::ostream &os, int van, int naar) const
{
    os << van << "  " << naar << std::endl;
}


template <GraafType TYPE>
void Graaf<TYPE>::lees(std::istream &is) 
{
    std::string type;
    int n, m;

    is >> type;
    if ((TYPE==GERICHT && type!="gericht") || (TYPE==ONGERICHT && type!="ongericht"))
        throw GraafExceptie("Graaftype klopt niet");
    is >> n;
    init(n);
    for (int i=0; i<n; i++)
        lees_knoop(is);
    is >> m;
    for (int j=0; j<m; j++)
        lees_verbinding(is);
    if (!is)
        throw GraafExceptie("Fout bij het inlezen");
}


template <GraafType TYPE>
void Graaf<TYPE>::lees_knoop(std::istream &is)
{
}

template <GraafType TYPE>
void Graaf<TYPE>::lees_verbinding(std::istream &is)
{
    int van, naar;
    is >> van >> naar;
    voeg_verbinding_toe(van, naar);
}

template <GraafType TYPE>
std::ostream &operator<<(std::ostream &os, const Graaf<TYPE> &g)
{ 
    g.schrijf(os);
    return os;
}

template <GraafType TYPE>
std::istream &operator>>(std::istream &is, Graaf<TYPE> &g)
{
    g.lees(is);
    return is;
}


#endif // __graaf__