#ifndef INTERFAZ_H
#define INTERFAZ_H

#include "tipos.h"
#include <vector>

#include <iostream>
#include <fstream>

#include "local.h"
#include "combo.h"
#include "pedido.h"


void MenuPrincipal();

void MenuCombo();
void MenuPedido();
void MenuLocal();

int LeerOpcion(int maxOpcion);
Combo MenuCrearCombo();

Pedido MenuCrearPedido();
Local MenuCrearLocal();


void LeerArchivoParaEscribir(ofstream &archivo);
void LeerArchivoParaLeer(ifstream &archivo);
void limpiarPantalla();
void mostrarCombos(vector<Combo> combos);
void mostrarMenuAgregacionComboAPedido(int nro, Empleado empleado, vector<Combo> combos);
vector< pair <Bebida,Cantidad> > menuAgregacionBebidasALocal();
vector< pair <Hamburguesa,Cantidad> > menuAgregacionHamburguesasALocal();
vector< Empleado > menuAgregacionEmpleadosALocal();
void mostrarStockBebidas(vector<pair < Bebida, Cantidad> > stock);
void mostrarStockHamburguesas(vector<pair < Hamburguesa, Cantidad> > stock);
void mostrarHamburguesasYBebidas();
void mostrarHamburguesasYBebidasDeLocal();
Combo MenuCrearComboAPedidoDeLocal();
Pedido MenuCrearPedidoDeLocal();
void Pausar();
void Salir();

string traducir(Bebida);
string traducir(Hamburguesa);

#endif // INTERFAZ_H
