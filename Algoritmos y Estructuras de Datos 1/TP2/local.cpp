#include "local.h"
#include <string.h>
Local::Local(){
	_bebidas = vector <pair <Bebida,Cantidad> > ();
	_sandwiches = vector <pair <Hamburguesa,Cantidad> > ();
	_empleados = vector< pair <Empleado, Energia> >();
	_ventas = vector< Pedido > ();

	pair <Bebida, Cantidad> b1 (PestiCola, 2);
	pair <Bebida, Cantidad> b2 (FalsaNaranja, 2);
	pair <Bebida, Cantidad> b3 (SeVeNada, 2);
	pair <Bebida, Cantidad> b4 (AguaConGags, 2);
	pair <Bebida, Cantidad> b5 (AguaSinGags, 2);
	_bebidas.push_back(b1);
	_bebidas.push_back(b2);
	_bebidas.push_back(b3);
	_bebidas.push_back(b4);
	_bebidas.push_back(b5);

	pair <Hamburguesa, Cantidad> h1 (McGyver, 2);
	pair <Hamburguesa, Cantidad> h2 (CukiQueFresco, 2);
	pair <Hamburguesa, Cantidad> h3 (McPato, 2);
	pair <Hamburguesa, Cantidad> h4 (BigMacabra, 2);
	_sandwiches.push_back(h1);
	_sandwiches.push_back(h2);
	_sandwiches.push_back(h3);
	_sandwiches.push_back(h4);

	pair <Empleado, Energia> e1 ("Ronald Maconal", 100);
	pair <Empleado, Energia> e2 ("Burguer Kong", 100);
	_empleados.push_back(e1);
	_empleados.push_back(e2);

}

Local::Local(const vector< pair <Bebida,Cantidad> > bs, const vector< pair <Hamburguesa,Cantidad> > hs, const vector<Empleado> es){
	_bebidas = bs;
	_sandwiches = hs;
	unsigned int i = 0;
	_empleados = vector< pair <Empleado, Energia> >();
	while (i < es.size()) {
		pair <Empleado, Energia> e (es.at(i), 100);
		_empleados.push_back(e);
		i++;
	}
	_ventas = vector< Pedido > ();
}

Cantidad Local::stockBebidasL(const Bebida b) const{
	unsigned int i = 0;
	while (i < _bebidas.size() && _bebidas.at(i).first != b) {
		i++;
	}
	return _bebidas.at(i).second;
}

Cantidad Local::stockSandwichesL(const Hamburguesa h) const{
	unsigned int i = 0;
	while (i < _sandwiches.size() && _sandwiches.at(i).first != h) {
		i++;
	}
	return _sandwiches.at(i).second;
}

vector<Bebida> Local::bebidasDelLocalL() const{
	unsigned int i = 0;
	vector<Bebida> b = vector<Bebida>();
	while(i < _bebidas.size()){
		b.push_back(_bebidas.at(i).first);
		i++;
	}
	return b;
}

vector<Hamburguesa> Local::sandwichesDelLocalL() const{
	unsigned int i = 0;
	vector<Hamburguesa> s = vector<Hamburguesa>();
	while(i < _sandwiches.size()){
		s.push_back(_sandwiches.at(i).first);
		i++;
	}
	return s;
}


vector<Empleado> Local::empleadosL() const{
	int i = 0;
	vector<Empleado> emp = vector<Empleado>();
	while (i < _empleados.size()) {
		if(_empleados.at(i).second >= 0 ) {
			emp.push_back(_empleados.at(i).first);	
		}
		i++;
	}
	return emp;
}

vector<Empleado> Local::desempleadosL() const{
	int i = 0;
	vector<Empleado> demp = vector<Empleado>();
	
	while(i < _empleados.size()){
		if ( _empleados.at(i).second < 0) {
			demp.push_back(_empleados.at(i).first);	
		}
		i++;
	}

	return demp;
}

Energia  Local::energiaEmpleadoL(const Empleado e) const{
	int i = 0;
	while(e != _empleados.at(i).first) {
		i++;
	}
	return _empleados.at(i).second;
}

vector<Pedido> Local::ventasL() const{
	return _ventas;
}

vector<Empleado> Local::candidatosAEmpleadosDelMesL() const{
        return _candidatosAEmpleadosDelMes();
}

void Local::venderL(const Pedido p){

	//Buscar Empleado que Atentio el Pedido p
	int i = 0;
	while( i < _empleados.size() && p.atendioP() != _empleados.at(i).first ){
			i++ ;
	}
	//Resta Energia
	_empleados.at(i).second -= p.dificultadP() ;
	
	if( _empleados.at(i).second >= 0 ){
	//**Empleado con Energia para atender
		//**Actualiza ventas
		_ventas.push_back(p) ;
		//**Actualiza Bebidas y Sandwiches
		i = 0 ;		
		while( i < p.combosP().size() ){
			_actualizaStockBebida( p.combosP().at(i).bebidaC() , -1 ) ;
			_actualizaStockSandwich( p.combosP().at(i).sandwichC() , -1 ) ;
			i++ ;
		}
	}		
}	

void Local::sancionL(const Empleado e, const Energia n){
	int i = 0 ;
	while( i < _empleados.size() && e != _empleados.at(i).first ){
		i++ ;
	}
	_empleados.at(i).second -= n;
	
}

void Local::anularPedidoL(int n){
	vector <Pedido> vMinN = vector <Pedido> () ;
	int i = 0 ;
	vector <Combo> combos ;
	int nro ; 
	Empleado emp ;
	while ( i < _ventas.size() ){
		if ( _ventas.at(i).numeroP() < n ){
			vMinN.push_back(_ventas.at(i)) ;
		}	
		else if ( _ventas.at(i).numeroP() == n ){
			int j = 0 ;
			while( j < _empleados.size() && _ventas.at(i).atendioP() != _empleados.at(j).first ){
				j++ ;
			}
			_empleados.at(j).second += _ventas.at(i).dificultadP() ;
			j = 0 ;
			while( j < _ventas.at(i).combosP().size() ){
				_actualizaStockBebida( _ventas.at(i).combosP().at(j).bebidaC() , 1 ) ;
				_actualizaStockSandwich( _ventas.at(i).combosP().at(j).sandwichC() , 1 ) ;
				j++ ;
			}
		}	
		else {
			emp = _ventas.at(i).atendioP() ;
			combos = _ventas.at(i).combosP() ;
			nro = _ventas.at(i).numeroP() - 1 ;
			vMinN.push_back( Pedido( nro , emp , combos ) ) ;
		}
	i++ ;
	}
	_ventas = vMinN ;
}

void Local::agregarComboAlPedidoL(const Combo c, int n){
	int i = 0 ;
	_actualizaStockBebida( c.bebidaC() , -1 ) ;
	_actualizaStockSandwich( c.sandwichC() , -1 ) ;
	while( i < _ventas.size() && _ventas.at(i).numeroP() != n ){
		i++ ;
	}
	_ventas.at(i).agregarComboP(c) ;
	int j = 0 ;
	while( j < _empleados.size() && _ventas.at(i).atendioP() != _empleados.at(j).first ){
		j++ ;
	}
	_empleados.at(j).second -= c.dificultadC() ;
}

bool Local::unaVentaCadaUnoL() const{
	int i = 0 ;
	bool ciclan = true ;
	while( i < _pedidosOrdenadosDeEmpleadosActuales().size() ){
		int imod = i % _empleadosDelCiclo().size() ;
		if ( _pedidosOrdenadosDeEmpleadosActuales().at(i).atendioP() != _pedidosOrdenadosDeEmpleadosActuales().at(imod).atendioP() ){
			ciclan = false ;
		}
	i++ ;
	}
	return ciclan ;
}

Empleado Local::elVagonetaL() const{
	int i = 0;
	vector<Empleado> emps = empleadosL();
	Empleado vagoneta;
	int max = 0;

	while(i < emps.size()) {
		int desc = _descansoMasLargo(emps.at(i));
		if (desc >= max) {
			max = desc;
			vagoneta = emps.at(i);
		}
		i++;
	}	
	return vagoneta;
}
	
void Local::guardar(std::ostream& os) const{
	os << "{ ";
	os << "L ";
	os << "[ ";
	int i = 0;
	while(i < bebidasDelLocalL().size()) {
		os << "( ";
		os << bebidasDelLocalL().at(i) << " ";
		os << stockBebidasL(bebidasDelLocalL().at(i)) << " ";
		os << ") ";
		i++;
	}
	os << "] ";
	os << "[ ";
	i = 0;
	while(i < sandwichesDelLocalL().size()) {
		os << "( ";
		os << sandwichesDelLocalL().at(i) << " ";
		os << stockSandwichesL(sandwichesDelLocalL().at(i)) << " ";
		os << ") ";
		i++;
	}
	os << "] ";
	os << "[ ";
	i = 0;
	while(i < _empleados.size()) {
		os << "( ";
		os << _empleados.at(i).first << " ";
		os << energiaEmpleadoL(_empleados.at(i).first) << " ";
		os << ") ";
		i++;
	}
	os << "] ";
	os << "[ ";
	i = 0;
	while(i < ventasL().size()) {
		ventasL().at(i).guardar(os);
		i++;
	}
	os << "] ";
	os << "}" << endl;
}	

void Local::mostrar(std::ostream& os) const{
	os << "Local" << endl;
	os << endl;
     os << "Bebidas : " << endl;
    	for (int i = 0; i < bebidasDelLocalL().size(); i++)
    	{
			os << bebidasDelLocalL().at(i) << " | Cantidad: " << stockBebidasL(bebidasDelLocalL().at(i)) << endl;
    	}
    	os << endl;
    	os << "Hamburguesas : " << endl;
    	for (int i = 0; i < sandwichesDelLocalL().size(); i++)
    	{
			os << sandwichesDelLocalL().at(i) << " | Cantidad: " << stockSandwichesL(sandwichesDelLocalL().at(i)) << endl;
    	}
    	os << endl;
    	os << "Empleados : " << endl;
    	for (int i = 0; i < empleadosL().size(); i++)
    	{
			os << empleadosL().at(i) << " | Energia: " << energiaEmpleadoL(empleadosL().at(i)) << endl;
    	}
    	os << endl;
    	os << "Desempleados : " << endl;
    	for (int i = 0; i < desempleadosL().size(); i++)
    	{
			os << desempleadosL().at(i) << endl;
    	}
	os << endl;
    	os << "Cantidatos a Empleados del Mes : " << endl;
    	for (int i = 0; i < candidatosAEmpleadosDelMesL().size(); i++)
    	{
		os << candidatosAEmpleadosDelMesL().at(i) << endl;
    	}
    	os << endl;
    	os << "El Vagoneta : " << elVagonetaL() << endl;

	os << endl;
    	os << "Ventas : " << endl;
    	os << endl;
    	for (int i = 0; i < ventasL().size(); i++)
    	{
		ventasL().at(i).mostrar(os);
    	os << endl;		
    	}

}

void Local::cargar (std::istream& is){

	string line;
	vector <pair <Bebida,Cantidad> > _bs = vector <pair <Bebida,Cantidad> > ();
	vector <pair <Hamburguesa,Cantidad> > _hs = vector <pair <Hamburguesa,Cantidad> > ();
	vector< pair <Empleado, Energia> > _es = vector< pair <Empleado, Energia> > ();
	vector< pair <Empleado, Energia> > _ds = vector< pair <Empleado, Energia> > ();
	vector< Pedido > _vs = vector< Pedido > ();

	//leo {
	is >> line;

	//leo L
	is >> line;

	//cargo stock y empleados;
	//[ ( AguaConGags 7 ) ] [ ( CukiQueFresco 7 ) ] [ ( pepe 56 ) ( juan 88 ) ]

	//cargo stock y empleados;
	//[ ( AguaConGags 7 ) ( AguaConGags 7 ) ] [ ( CukiQueFresco 7 ) ] [ ( pepe 56 ) ( juan 88 ) ]
	
	//leo [
	is >> line;

	while(true) {
		
		//leo (
		is >> line;
		
		//leo AguaConGags
		is >> line;
		Bebida b = recuperarBebidaDeString(line);

		Cantidad c;
		is >> c;	

		pair <Bebida, Cantidad> bc = pair<Bebida, Cantidad> (b, c);
		_bs.push_back(bc);
		//leo )
		is >> line;	

		streampos pos = is.tellg();
        is >> line;
        if (line == "]") {
            break;
        } else {
            is.seekg(pos);
        }
	}


	//leo [
	is >> line;

	

	while(true) {
		//leo (
		is >> line;
		
		//leo Hamburguesa
		is >> line;
		Hamburguesa h = recuperarHamburguesaDeString(line);

		Cantidad c;
		is >> c;	

		pair <Hamburguesa, Cantidad> hc = pair<Hamburguesa, Cantidad> (h, c);
		_hs.push_back(hc);
		//leo )
		is >> line;	

		streampos pos = is.tellg();
        is >> line;
        if (line == "]") {
            break;
        } else {
            is.seekg(pos);
        }
	}

	
	//[ ( pepe 56 ) ( juan 88 ) ]
	//leo [
	is >> line;

	while(true) {
		//leo (
		is >> line;

		is >> line;
		Empleado e = line;

		Energia c;
		is >> c;	

		pair <Empleado, Energia> ee = pair<Empleado, Energia> (e, c);
		_es.push_back(ee);
		//leo )
		is >> line;	

		streampos pos = is.tellg();
        is >> line;
        if (line == "]") {
            break;
        } else {
            is.seekg(pos);
        }
	}


	//leer las ventas;
	//leo [
	is >> line;

	//me fijo si hay pedidos. Si fuera [ ] Entonces no entro al While
	streampos pos = is.tellg();
    is >> line;
    
	if (line != "]") {
        is.seekg(pos);
		while(true) {

			Pedido _p = Pedido();
	        _p.cargar(is);
			_vs.push_back(_p);

			streampos pos = is.tellg();
	        is >> line;
	        if (line == "]") {
	            break;
	        } else {
	            is.seekg(pos);
	        }
		}
	}


	this->_bebidas = _bs;
	this->_sandwiches = _hs;
	this->_empleados = _es;
	this->_ventas = _vs;

}

std::ostream & operator<<(std::ostream & os,const Local & l){
	l.mostrar(os);
	return os;
}



/**Parte Privada**/


vector <Empleado> Local::_candidatosAEmpleadosDelMes() const{
	return _empleadosConMasCombos(_empleadosConMasVentas(empleadosL()));
}

vector < Empleado > Local::_empleadosConMasCombos(const vector <Empleado> empleados) const{
	int i = 0;
	vector < Empleado > emp = vector < Empleado >();

	//**Busco el maximo de Combos vendidos por todos los empleados.
	int maxCombos = 0;
	while (i < empleados.size()) {



		if ( _combosVendidosPorElEmpleado(empleados.at(i)).size() > maxCombos) {
			maxCombos = _combosVendidosPorElEmpleado(empleados.at(i)).size(); 			
		}
		i++;
	}

	//**Me quedo con los empleados que hayan vendido al menos maxCombo de combos
	i=0;
	while (i < empleados.size()) {
		if ( _combosVendidosPorElEmpleado(empleados.at(i)).size() >= maxCombos) {
			emp.push_back(empleados.at(i));
		}
		i++;
	}
	return emp;

}
vector < Empleado > Local::_empleadosConMasVentas(const vector <Empleado> empleados) const{
	int i = 0;
	vector < Empleado > emp = vector < Empleado >();

	//**Busco el maximo de Combos vendidos por todos los empleados.
	int maxVentas = 0;
	while (i < empleados.size()) {
		if ( _ventasDelEmpleado(empleados.at(i)).size() > maxVentas) {
			maxVentas = _ventasDelEmpleado(empleados.at(i)).size();
		}
		i++;
	}


	//**Me quedo con los empleados que hayan vendido al menos maxCombo de combos
	i=0;
	while (i < empleados.size()) {
		if ( _ventasDelEmpleado(empleados.at(i)).size() >= maxVentas) {
			emp.push_back(empleados.at(i));
		}
		i++;
	}
	return emp;

}

vector < Pedido > Local::_ventasDelEmpleado(const Empleado e) const{
	vector <Pedido> ventas = vector <Pedido>();
	int i = 0;
	while(i < ventasL().size()) {
		if (ventasL().at(i).atendioP() == e) {
			ventas.push_back(ventasL().at(i));
		}
		i++;
	}
	return ventas;

}
vector < Combo >  Local::_combosVendidosPorElEmpleado(const Empleado e) const{
	vector <Combo> combos = vector <Combo>();
	int i = 0;
	while(i < ventasL().size()) {
		if (ventasL().at(i).atendioP() == e) {
			int j = 0;
			while (j < ventasL().at(i).combosP().size()) {
				combos.push_back(ventasL().at(i).combosP().at(j));
				j++;
			}
		}
		i++;
	}
	return combos;
}

Pedido Local::_pedidoPorNro(const int n) const {
	vector <Pedido> ventas = vector <Pedido>();
	int i = 0;
	while(i < ventasL().size() && ventasL().at(i).numeroP() != n) {
		i++;
	}
	return ventasL().at(i);
}

int Local::_minNroPedido(const vector <Pedido> ps) const {
	int min = 0;
	int i = 0;
	if (ps.size() == 0) {
		return 0;
	} else {
		min = ps.at(i).numeroP();
	}
	while( i < ps.size()) {
		if (ps.at(i).numeroP() < min) {
			min = ps.at(i).numeroP();
		}
		i++;
	}
	return min;
}
int Local::_maxNroPedido(const vector <Pedido> ps) const {
	int max = 0;
	int i = 0;
	while( i < ps.size()) {
		if (ps.at(i).numeroP() > max) {
			max = ps.at(i).numeroP();
		}
		i++;
	}
	return max;
}

vector < Pedido > Local::_pedidosOrdenados() const{
	//declaro
	int min = 0;
	int max = 0;
	int i = 0;
	vector <Pedido> pedidos = vector < Pedido >();
	//inicializo
	min = _minNroPedido(ventasL());
	max = _maxNroPedido(ventasL());
	i = min;

	while(i <= max) {
		pedidos.push_back(_pedidoPorNro(i));
		//uso invariante...el numero de las ventas son consecutivos!!!!
		i++;
	}

	return pedidos;


}
vector < Pedido > Local::_pedidosOrdenadosDeEmpleado(const Empleado e) const {
	int i = 0;
	vector <Pedido> pedidos = vector < Pedido >();
	vector <Pedido> pedidosOrdenados = _pedidosOrdenados();

	while (i < pedidosOrdenados.size()) {
		if (pedidosOrdenados.at(i).atendioP() == e) {
			pedidos.push_back(pedidosOrdenados.at(i));
		}
		i++;
	}
	return pedidos;
}
int Local::_descansoMasLargo(const Empleado e) const {
	int i = 0;
	int max = 0;
	vector < int > descansos = _descansos(e);
	while(i < descansos.size()) { 
		if ( descansos.at(i) > max) {
			max = descansos.at(i);
		}
		i++;
	}
	return max;
}
vector < int > Local::_descansos(const Empleado e) const {
	vector <int> descansos = vector<int>();
	if (_ventasDelEmpleado(e).size() == 0) {
		descansos.push_back(ventasL().size());
	} else {
		//primer descanso
		vector <Pedido> pedidosOrdenadosEmp = _pedidosOrdenadosDeEmpleado(e);
		int min = _minNroPedido(ventasL());
		descansos.push_back(pedidosOrdenadosEmp.at(0).numeroP() - min);

		//descansos intermedios.
		int  i = 0;
		while (i < pedidosOrdenadosEmp.size() - 1) {
			descansos.push_back(pedidosOrdenadosEmp.at(i+1).numeroP() - pedidosOrdenadosEmp.at(i).numeroP());
			i++;
		}

		//ultimo descanso
		int max = _maxNroPedido(ventasL());
		descansos.push_back(max - pedidosOrdenadosEmp.at(pedidosOrdenadosEmp.size()-1).numeroP());
	}
	return descansos;
}

void Local::_actualizaStockBebida(const Bebida b , const int n ) {
	unsigned int i = 0;
	while (i < _bebidas.size() && _bebidas.at(i).first != b) {
		i++;
	}
	_bebidas.at(i).second += n ;

}	
void Local::_actualizaStockSandwich(const Hamburguesa h , const int n ) {
	unsigned int i = 0;
	while (i < _sandwiches.size() && _sandwiches.at(i).first != h) {
		i++;
	}
	_sandwiches.at(i).second += n ;
}	

vector<Pedido> Local::_pedidosOrdenadosDeEmpleadosActuales() const{
	//declaro
	int min = 0;
	int max = 0;
	int i = 0;
	vector <Pedido> pedidos = vector < Pedido >();
	//inicializo
	min = _minNroPedido(ventasL());
	max = _maxNroPedido(ventasL());
	i = min;

	while(i <= max) {
		bool in = false ;
		for(int j = 0 ; j < empleadosL().size() ; j++){
			if( _pedidoPorNro(i).atendioP() == empleadosL().at(j) ){
				in = true ;
			}
		}
		if(in == true){
			pedidos.push_back(_pedidoPorNro(i)) ;
		//Numero ventas es consecutivo
		}
		i++;
	}

	return pedidos;
}	

vector<Empleado> Local::_empleadosDelCiclo() const{
	unsigned int i = 0;
	vector < Empleado > emp = vector < Empleado >() ;
	while( i < _pedidosOrdenadosDeEmpleadosActuales().size() ){
		bool yaEsta = false ;
		for(int j = 0 ; j < emp.size() ; j++){
			if( _pedidosOrdenadosDeEmpleadosActuales().at(i).atendioP() == emp.at(j) ){
				yaEsta = true ;
			}
		}
		if( yaEsta == false ){
			emp.push_back(_pedidosOrdenadosDeEmpleadosActuales().at(i).atendioP()) ;
		}
		i++ ;
	}
	return emp ;
}
