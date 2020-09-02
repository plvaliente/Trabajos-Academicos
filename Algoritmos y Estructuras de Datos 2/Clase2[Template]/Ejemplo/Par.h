#ifndef PAR_H
#define PAR_H

// Por tratarse de un ejemplo que quiero sea minimalista declararé todo public
// pero advierto que esto es una pésima práctica de programación.
template<typename Tizq, typename Tder>
class Par {
    
    public:
        Tizq izq;
        Tder der;
        
        Par();
        Par(Tizq izq, Tder der);
        
        class Criterio {
            public:
                bool esMejor(const Par& a, const Par& b);
        };
        
        template<typename TI, typename TD>
            friend ostream& operator<<( ostream& flujo, const Par<TI, TD>& otroPar );
    
};

template<typename Tizq, typename Tder>
Par<Tizq, Tder>::Par() {}

template<typename Tizq, typename Tder>
Par<Tizq, Tder>::Par(Tizq izq, Tder der) {
    this->izq = izq;
    this->der = der;
}

template<typename Tizq, typename Tder>
bool Par<Tizq, Tder>::Criterio::esMejor(const Par& a, const Par& b) {
    return a.izq > b.izq;
}

template<typename Tizq, typename Tder>
ostream& operator<<( ostream& flujo, const Par<Tizq, Tder>& par ) {
    flujo << "(" << par.izq << ", " << par.der << ")";
    return flujo; 
}

#endif // PAR_H
