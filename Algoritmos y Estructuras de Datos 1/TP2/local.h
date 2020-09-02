#ifndef LOCAL_H_INCLUDED
#define LOCAL_H_INCLUDED

#include <vector>
#include "pedido.h"

class Local{
    
    public:

        Local();
        Local(const vector< pair <Bebida,Cantidad> > bs, const vector< pair <Hamburguesa,Cantidad> > hs, const vector<Empleado> es);

        Cantidad                stockBebidasL(const Bebida b) const;
        Cantidad                stockSandwichesL(const Hamburguesa h) const;
        vector<Bebida>          bebidasDelLocalL() const;
        vector<Hamburguesa>     sandwichesDelLocalL() const;
        vector<Empleado>        empleadosL() const;
        vector<Empleado>        desempleadosL() const;
        Energia                 energiaEmpleadoL(const Empleado e) const;
        vector<Pedido>          ventasL() const;
        bool                    unaVentaCadaUnoL() const;
        void                    venderL(const Pedido p);
        vector<Empleado>        candidatosAEmpleadosDelMesL() const;
        void                    sancionL(const Empleado e, const Energia n);
        Empleado                elVagonetaL() const;
        void                    anularPedidoL(int n);
        void                    agregarComboAlPedidoL(const Combo c, int n);
        void                    mostrar(std::ostream& os) const;
        void                    guardar(std::ostream& os) const;
        void                    cargar (std::istream& is);

    private:

        enum {ENCABEZADO_ARCHIVO = 'L'};
        vector< pair <Hamburguesa,Cantidad> >   _sandwiches;
        vector< pair <Bebida,Cantidad> >        _bebidas;
        vector< pair <Empleado, Energia> >      _empleados;
        vector< Pedido >                        _ventas;
        vector < Empleado >                     _candidatosAEmpleadosDelMes() const;
        vector < Empleado >                     _empleadosConMasCombos(const vector <Empleado> empleados) const;
        vector < Empleado >                     _empleadosConMasVentas(const vector <Empleado> empleados) const;
        vector < Pedido >                       _ventasDelEmpleado(const Empleado e) const;
        vector < Combo >                        _combosVendidosPorElEmpleado(const Empleado e) const;
        int                                     _minNroPedido(const vector <Pedido> ps) const;
        int                                     _maxNroPedido(const vector <Pedido> ps) const;
        Pedido                                  _pedidoPorNro(const int n) const;
        vector < Pedido >                       _pedidosOrdenados() const;
        vector < Pedido >                       _pedidosOrdenadosDeEmpleado(const Empleado e) const;
        int                                     _descansoMasLargo(const Empleado e) const;
        vector < int >                          _descansos(const Empleado e) const;
        vector<Pedido>                          _pedidosOrdenadosDeEmpleadosActuales() const;
        vector<Empleado>                        _empleadosDelCiclo() const;
        void                                    _actualizaStockBebida(const Bebida b , const int n );
        void                                    _actualizaStockSandwich(const Hamburguesa h , const int n );
};
#endif // LOCAL_H_INCLUDED
std::ostream & operator<<(std::ostream & os,const Local & c);
