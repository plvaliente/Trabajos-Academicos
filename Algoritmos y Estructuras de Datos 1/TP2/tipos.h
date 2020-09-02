#ifndef TIPOS_H
#define TIPOS_H

#include <vector>
#include <stdlib.h>

#include <string>
#include <iostream>

using namespace std;
typedef string Empleado;
typedef int Energia;
typedef int Cantidad;

enum Bebida{PestiCola, FalsaNaranja, SeVeNada, AguaConGags, AguaSinGags};
enum Hamburguesa{McGyver, CukiQueFresco, McPato, BigMacabra};

#define MaxH 3
#define MaxB 4

Bebida 									recuperarBebidaDeString(string b);
Hamburguesa								recuperarHamburguesaDeString(string h);

#endif /*TIPOS_H*/
