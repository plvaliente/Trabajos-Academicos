#include "pedido.h"
#include <algorithm>
Pedido::Pedido(){
	_combos = vector <Combo> ();
	_combos.push_back(Combo()) ;
	_atendio = "" ;
	_numero = 1 ;
}

Pedido::Pedido(const int nro, const Empleado e, const vector<Combo> combos){
	_combos = combos;
	_atendio = e ;
	_numero = nro ;
}

int Pedido::numeroP() const{
	int res = this->_numero ;
	return res ;
}

Empleado Pedido::atendioP() const{
	Empleado res = this->_atendio ;
	return res ;
}

vector<Combo> Pedido::combosP() const{
	vector<Combo> res = this->_combos ;
	return res ;
}

Energia Pedido::dificultadP() const{
	int i = 0 ;
	vector<Combo> p =  this->_combos ;
	int n = p.size() ;
	int suma = 0 ;
	while(i < n) {
		suma = suma + p.at(i).dificultadC() ;
		i++ ;
	}
	return suma ;
}


void  Pedido::agregarComboP(const Combo c){
	this->_combos.push_back(c) ;
}

void  Pedido::anularComboP(int i){
	int j = 0 ;
	vector<Combo> p =  this->_combos ;
	int n = p.size() ;
	vector<Combo> cs = vector <Combo> () ;
	while(j < n){
		if(j != i){
			cs.push_back(p.at(j)) ;
		}
		j++ ;
	}
	this->_combos = cs ;
}

void  Pedido::cambiarBebidaComboP(const Bebida b, int i){
	Hamburguesa ham = _combos.at(i).sandwichC() ;
	Energia dif = _combos.at(i).dificultadC() ;
	Combo ci = Combo( b , ham , dif ) ;
	_combos.at(i) = ci;
}

void  Pedido::elMezcladitoP(){
	vector< pair<Bebida, Hamburguesa> > noUsados = this->_posiblesParesNoUsados();
	int i = 0;
	int n = this->_combos.size();
	while(i < n){
		if(this->_estaRepetido(i)){
			int m = noUsados.size();
			Bebida b = noUsados.at(m - 1).first ;
			Hamburguesa h = noUsados.at(m - 1).second ;
			Energia d = this->_combos.at(i).dificultadC();
			this->_combos.at(i) = Combo(b, h, d) ;
			noUsados.pop_back() ;
		}
		i++ ;
	}

}


void Pedido::mostrar(std::ostream& os) const{
	os << "PEDIDO" << endl;
    os << "Numero: " << _numero << endl;
    os << "Empleado: " << _atendio << endl ;
    os << "Combos: " << endl ;
    os << endl ;
    for ( int i = 0 ; i < this->combosP().size() ; i++){
    	this->combosP().at(i).mostrar(os) ;
    	os << endl;
    }
}

void Pedido::guardar(std::ostream& os) const{
	os << "{ P " << numeroP() << " " <<  atendioP() << " [" ;
	for ( int i = 0 ; i < combosP().size() ; i++ ){
		combosP().at(i).guardar(os);
	}  
	os << " ] } " ;
}

void Pedido::cargar (std::istream& is){
    //{ P 1 pepe [ { C FalsaNaranja CukiQueFresco 10 } { C FalsaNaranja CukiQueFresco 12 } ] }
    
    string line;
    vector <Combo> _cs = vector <Combo> ();
    int _n;
    Empleado _e;

    //leo el {
    is >> line;
    //leo el 'P'
    is >> line;
    if (line == "P") {
        //sigo leyendo

        //leo el numero
        is >> _n;
        
        //leo el empleado
        is >> _e;

        //leo los combos

        //leo el [
        is >> line;
        
        while (true) {
            Combo _c = Combo();
            _c.cargar(is);
            _cs.push_back(_c);

            streampos pos = is.tellg();
            is >> line;
            if (line == "]") {
                break;
            } else {
                is.seekg(pos);
            }
        }
        //leo el } de pedido
        is >> line;

        this->_combos = _cs;
        this->_atendio = _e;
        this->_numero = _n;
    } 
    else {
        cout << "Archivo Invalido Pedido";
    }
}

bool Pedido::operator==(const Pedido& otroPedido) const{
	bool igual = true ;
	if(this->_atendio != otroPedido._atendio){
		igual = false ;
	}
	else if(this->_numero != otroPedido._numero){
		igual = false ;
		}
	else if( not this->_mismosCombos(otroPedido)){
		igual = false ;
		}
	return igual ;
}

std::ostream & operator<<(std::ostream & os,const Pedido& p){
	p.mostrar(os);
	return os ;
}

/**PARTE PRIVADA**/

vector< pair<Bebida, Hamburguesa> > Pedido::_posiblesParesNoUsados() {
	vector< pair<Bebida, Hamburguesa> > v = vector< pair<Bebida, Hamburguesa> >();
	vector<Bebida> bUsadas = this->_bebidasUsadas();
	vector<Hamburguesa> hUsadas = this->_sandwichesUsados();
	unsigned int i = 0;
	unsigned int j = 0;
	while(i < bUsadas.size()){
		j = 0 ;
		while(j < hUsadas.size()){
			pair<Bebida, Hamburguesa> par (bUsadas.at(i), hUsadas.at(j));
			v.push_back(par);
			j++;
		}
		i++;
	}
	vector< pair<Bebida, Hamburguesa> > v2 = this->_quitarUsados(v);
	return v2;
}

bool Pedido::_estaRepetido(unsigned int i) {
	bool res = false;
	unsigned int j = 0;
	vector<Combo> p = this->_combos;
	while(j < i){
		if(p.at(j).bebidaC() == p.at(i).bebidaC() && p.at(j).sandwichC() == p.at(i).sandwichC()){
			res = true;
		}
		j++;
	}
	return res;
}

vector<Bebida> Pedido::_bebidasUsadas() {
	vector<Bebida> b = vector<Bebida> () ;
	for(unsigned int i = 0 ; i < this->_combos.size() ; i++ ){
		bool tf = false;
		for(unsigned int j = 0 ; j < b.size() ; j++){
			if(b.at(j) == this->_combos.at(i).bebidaC()){
				tf = true;
			}
		}
		if(tf==false){
			b.push_back( this->_combos.at(i).bebidaC() ) ;
		}
	}
	return b;
}

vector<Hamburguesa> Pedido::_sandwichesUsados() {
	vector<Hamburguesa> h = vector<Hamburguesa> () ;
	for(unsigned int i = 0 ; i < this->_combos.size() ; i++ ){
		bool tf = false;
		for(unsigned int j = 0 ; j < h.size() ; j++){
			if(h.at(j) == this->_combos.at(i).sandwichC()){
				tf = true;
			}
		}
		if(tf==false){
			h.push_back( this->_combos.at(i).sandwichC() ) ;
		}
	}
	return h;
}
vector< pair<Bebida, Hamburguesa> > Pedido::_quitarUsados(vector< pair<Bebida, Hamburguesa> > v) {
	vector< pair<Bebida, Hamburguesa> > v2 = vector< pair<Bebida, Hamburguesa> >();
	vector<Combo> c = this->_combos ;
	int i = 0;
	int j = 0;
	int n = v.size();
	int m = c.size() ;
	while(i < n){
		bool tf = false;
		j = 0 ;
		while(j < m){
			if(v.at(i).first == c.at(j).bebidaC() && v.at(i).second == c.at(j).sandwichC() ){
				tf = true;
			}
			j++;
		}
		if(tf == false){
			v2.push_back(v.at(i));
		}
		i++;
	}
	return v2;
}


bool Pedido::_mismosCombos(const Pedido& otroPedido) const{
	bool res = true;
	if(this->_combos.size() != otroPedido._combos.size()){
		res = false;
	}
	for(unsigned int i = 0 ; i < this->_combos.size() ; i++ ){
		if(this->_cuenta(this->_combos.at(i)) != otroPedido._cuenta(this->_combos.at(i))){
			res = false;
		}
	}
	return res;
}

int Pedido::_cuenta(Combo c)const{
	int cuenta = 0;
	for(unsigned int i = 0; i < this->_combos.size() ; i++){
		if(this->_combos.at(i) == c){
			cuenta++;
		}
	}
	return cuenta;
}


