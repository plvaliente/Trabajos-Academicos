#include <vector>
#include "interfaz.h"
#include "tipos.h"

using namespace std;

vector<Hamburguesa> Hamburguesas;
vector<Bebida> Bebidas;



Combo nuevoCombo;
Pedido nuevoPedido;
Local nuevoLocal;

bool seCreoElCombo = false;
bool seCreoElPedido = false;
bool seCreoElLocal = false;


void MenuPrincipal()
{   //para que muestre true o false en vez de 0 y 1
    cout.setf(ios::boolalpha);

    bool exits = false;

    Hamburguesas = vector<Hamburguesa>();
    Hamburguesas.push_back(BigMacabra);
    Hamburguesas.push_back(McGyver);
    Hamburguesas.push_back(CukiQueFresco);
    Hamburguesas.push_back(McPato);

    Bebidas = vector<Bebida>();
    Bebidas.push_back(AguaConGags);
    Bebidas.push_back(AguaSinGags);
    Bebidas.push_back(FalsaNaranja);
    Bebidas.push_back(PestiCola);
    Bebidas.push_back(SeVeNada);

    while (!exits)
    {
        cout << endl
            << "Bienvenidos a Krustiburger" << endl
            << "1. Combo" << endl
            << "2. Pedido" << endl
            << "3. Local" << endl
            << "4. Salir" << endl;

        int opt = LeerOpcion(4);
        switch (opt)
        {
            case 1:
            {
                limpiarPantalla();
                MenuCombo();
			}
                break;
            case 2:
            {
                limpiarPantalla();
                MenuPedido();
            }
                break;
            case 3:
            {
                limpiarPantalla();
                MenuLocal();
            }
                break;
            case 4:
                limpiarPantalla();
                Salir();
                cout << endl << endl;
                exit(0);
                break;
        }
    }
}


int LeerOpcion(int maxOpcion)
{
    cout << "  Ingrese una opcion [" << 1 << "-" << maxOpcion << "]: ";
    int opt;
    bool ok = false;
    while (!ok)
    {
        cin >> opt;
        ok = (opt <= maxOpcion);

        if (!ok)
            cout << "  Opcion incorrecta. Ingrese un numero entre [" << 1 << "-" << maxOpcion << "]: ";
    }
    return opt;
}

void MenuCombo()
{
    int maxOption = 2;
    cout << "Menu Combo" << endl
            << "0. Volver al Menu Principal" << endl
            << "1. Crear" << endl
            << "2. Cargar de archivo" << endl;
    if (seCreoElCombo)
    {
        maxOption = 8;
        cout << "3. Guardar a archivo" << endl
            << "4. Mostrar" << endl
            << "5. Ver Hamburguesa" << endl
            << "6. Ver Bebida" << endl
            << "7. Ver Energia" << endl
            << "8. Volver al menu anterior" << endl;
    }

    int opt = LeerOpcion(maxOption);
    switch (opt)
    {
        case 0:
        {
            limpiarPantalla();
            MenuPrincipal();
            break;
        }
        case 1:
        {
            limpiarPantalla();
            nuevoCombo = MenuCrearCombo();
            seCreoElCombo = true;

            limpiarPantalla();
            MenuCombo();
        }
        case 2:
        {
            limpiarPantalla();
            ifstream archivoEntrada;
            LeerArchivoParaLeer(archivoEntrada);
            nuevoCombo.cargar(archivoEntrada);
            archivoEntrada.close();
            seCreoElCombo = true;
            limpiarPantalla();
            MenuCombo();
        }
            break;
        case 3:
        {
            limpiarPantalla();

            if (!seCreoElCombo)
            {
                cout << "ERROR: No se creo ningun combo aun";
                break;
            }

            ofstream archivoSalida;

            LeerArchivoParaEscribir(archivoSalida);
            nuevoCombo.guardar(archivoSalida);
            archivoSalida.close();

            limpiarPantalla();
            MenuCombo();
        }
        case 4:
        {
            limpiarPantalla();
            if (!seCreoElCombo)
            {
                cout << "ERROR: No se creo ningun combo aun";
                break;
            }
            //mostrarHamburguesasYBebidas();
            cout << "El ultimo combo creado es: "<< endl<< endl;
            nuevoCombo.mostrar(cout);
            cout << endl<< endl;
            Pausar();

            limpiarPantalla();
            MenuCombo();
        }
        case 5:
        {
            limpiarPantalla();

            if (!seCreoElCombo)
            {
                cout << "ERROR: No se creo ningun combo aun";
                break;
            }
            cout << "La hamburguesa del combo es: " << nuevoCombo.sandwichC();

            cout << endl<< endl;
            Pausar();

            limpiarPantalla();
            MenuCombo();
        }
        case 6:
        {
            limpiarPantalla();

            if (!seCreoElCombo)
            {
                cout << "ERROR: No se creo ningun combo aun";
                break;
            }
            cout << "La bebida del combo es: " << nuevoCombo.bebidaC();

            cout << endl<< endl;
            Pausar();

            limpiarPantalla();
            MenuCombo();
        }
        case 7:
        {
            limpiarPantalla();

            if (!seCreoElCombo)
            {
                cout << "ERROR: No se creo ningun combo aun";
                break;
            }
            cout << "La dificultad del combo es: " << nuevoCombo.dificultadC();

            cout << endl<< endl;
            Pausar();

            limpiarPantalla();
            MenuCombo();
        }
            break;
        case 8:
            limpiarPantalla();
            MenuPrincipal();
            break;
    }
}

void MenuPedido()
{
    int maxOption = 2;
    cout << "Menu Pedido" << endl
            << "0.  Volver al Menu Principal" << endl
            << "1.  Crear" << endl
            << "2.  Cargar de archivo" << endl;
    if (seCreoElPedido)
    {
        maxOption = 13;
        cout << "3.  Guardar a archivo" << endl
            << "4.  Mostrar" << endl
            << "5.  Agregar combo" << endl
            << "6.  Anular combo" << endl
            << "7.  Cambiar bebida" << endl
            << "8.  Mezclar" << endl
            << "9.  Ver quien atendio" << endl
            << "10. Ver numero de pedido" << endl
            << "11. Ver combos" << endl
            << "12. Ver dificultad del pedido" << endl
            << "13. Volver al Menu Principal" << endl;
    }

    int opt = LeerOpcion(maxOption);
    switch (opt)
    {
        case 0:
        {
            limpiarPantalla();
            MenuPrincipal();
            break;
        }
        case 1:
        {
            limpiarPantalla();
            nuevoPedido = MenuCrearPedido();
            seCreoElPedido = true;

            limpiarPantalla();
            MenuPedido();
        }
        case 2:
        {
            limpiarPantalla();
            ifstream archivoEntrada;
            LeerArchivoParaLeer(archivoEntrada);
            nuevoPedido.cargar(archivoEntrada);
            archivoEntrada.close();
            seCreoElPedido = true;
            limpiarPantalla();
            MenuPedido();
        }
            break;
        case 3:
        {
            limpiarPantalla();

            if (!seCreoElPedido)
            {
                cout << "ERROR: No se creo ningun pedido aun";
                break;
            }

            ofstream archivoSalida;

            LeerArchivoParaEscribir(archivoSalida);
            nuevoPedido.guardar(archivoSalida);
            archivoSalida.close();

            limpiarPantalla();
            MenuPedido();
        }
        case 4:
        {
            limpiarPantalla();
            if (!seCreoElPedido)
            {
                cout << "ERROR: No se creo ningun combo aun";
                break;
            }
            //mostrarHamburguesasYBebidas();
            cout << "El ultimo pedido creado es: "<< endl<< endl;
            nuevoPedido.mostrar(cout);
            cout << endl<< endl;
            Pausar();

            limpiarPantalla();
            MenuPedido();
        }
        case 5:
        {
            limpiarPantalla();

            if (!seCreoElPedido)
            {
                cout << "ERROR: No se creo ningun pedido aun";
                break;
            }
            nuevoPedido.agregarComboP(MenuCrearCombo());
            limpiarPantalla();
            MenuPedido();
        }
        case 6:
        {
            int nroCombo;
            limpiarPantalla();

            if (!seCreoElPedido)
            {
                cout << "ERROR: No se creo ningun pedido aun";
                break;
            }
            mostrarCombos(nuevoPedido.combosP());
            cout << endl;
            cout << "Ingrese el numero de combo que desea eliminar [0/" << nuevoPedido.combosP().size()-1 << "] :";
            cin >> nroCombo;
            while (nroCombo > nuevoPedido.combosP().size()-1)
            {
                cout << "Ingrese un numero de combo valido para eliminar [0/" << nuevoPedido.combosP().size()-1 << "] :";
                cin >> nroCombo;
            }
            nuevoPedido.anularComboP(nroCombo);
            limpiarPantalla();
            MenuPedido();
        }
        case 7:
        {
            int nroCombo;
            int nuevaBebida;
            limpiarPantalla();

            if (!seCreoElPedido)
            {
                cout << "ERROR: No se creo ningun combo aun";
                break;
            }
            mostrarHamburguesasYBebidas();
            mostrarCombos(nuevoPedido.combosP());
            cout << endl;
            cout << "Ingrese el numero de combo que desea cambiar la bebida [0/" << nuevoPedido.combosP().size()-1 << "] :";
            cin >> nroCombo;
            while (nroCombo > nuevoPedido.combosP().size()-1)
            {
                cout << "Ingrese un numero de combo valido para cambiar la bebida [0/" << nuevoPedido.combosP().size()-1 << "] :";
                cin >> nroCombo;
            }
            cout << "Ingrese la nueva bebida [0/" << MaxB << "] :";
            cin >> nuevaBebida;
            while (nuevaBebida > MaxB)
            {
                cout << "Ingrese un numero de bebida valido [0/" << MaxB << "] :";
                cin >> nuevaBebida;
            }
            cout << endl;
            nuevoPedido.cambiarBebidaComboP(Bebidas[nuevaBebida], nroCombo);
            limpiarPantalla();
            MenuPedido();
        }
        case 8:
        {
            string opt;
            limpiarPantalla();

            if (!seCreoElPedido)
            {
                cout << "ERROR: No se creo ningun combo aun";
                break;
            }
            mostrarCombos(nuevoPedido.combosP());
            cout << endl;
            cout << "Esta seguro que desea realizar el Mezcladito?[s/n] :";
            cin >> opt;
            cout << endl;

            if (opt == "s")
            {
                nuevoPedido.elMezcladitoP();
                cout << "Los combos se mezclaron asi:" << endl<< endl;
                mostrarCombos(nuevoPedido.combosP());
                cout << endl;
                Pausar();
            }else
            {
                cout << "Los combos siguen iguales:" << endl<< endl;
                mostrarCombos(nuevoPedido.combosP());
                cout << endl;
                Pausar();
            }
            limpiarPantalla();
            MenuPedido();
        }
        case 9:
        {
            limpiarPantalla();

            if (!seCreoElPedido)
            {
                cout << "ERROR: No se creo ningun pedido aun";
                break;
            }
            cout << "El empleado que atendio el pedido fue: " << nuevoPedido.atendioP() << endl;
            Pausar();
            limpiarPantalla();
            MenuPedido();
        }
        case 10:
        {
            limpiarPantalla();

            if (!seCreoElPedido)
            {
                cout << "ERROR: No se creo ningun pedido aun";
                break;
            }
            cout << "El numero de pedido es: " << nuevoPedido.numeroP() << endl;
            Pausar();
            limpiarPantalla();
            MenuPedido();
        }
        case 11:
        {
            limpiarPantalla();

            if (!seCreoElPedido)
            {
                cout << "ERROR: No se creo ningun pedido aun";
                break;
            }
            mostrarCombos(nuevoPedido.combosP());
            Pausar();
            limpiarPantalla();
            MenuPedido();
        }
        case 12:
        {
            limpiarPantalla();

            if (!seCreoElPedido)
            {
                cout << "ERROR: No se creo ningun pedido aun";
                break;
            }
            cout << "La dificultad del pedido es :" << nuevoPedido.dificultadP() << endl << endl;
            Pausar();
            limpiarPantalla();
            MenuPedido();
        }
            break;
        case 13:
            limpiarPantalla();
            MenuPrincipal();
            break;
    }
}

void MenuLocal()
{
    int maxOption = 2;
    cout << "Menu Local" << endl
            << "0.  Volver al Menu Principal" << endl
            << "1.  Crear" << endl
            << "2.  Cargar de archivo" << endl;
    if (seCreoElLocal)
    {
        maxOption = 19;
        cout << "3.  Guardar a archivo" << endl
            << "4.  Mostrar" << endl
            << "5.  Stock Bebidas" << endl
            << "6.  Stock Hamburguesas" << endl
            << "7.  Bebidas del local" << endl
            << "8.  Hamburguesas del local" << endl
            << "9.  Empleados" << endl
            << "10. Desempleados" << endl
            << "11. Energia de un empleado" << endl
            << "12. Ventas" << endl
            << "13. Una venta cada uno?" << endl
            << "14. Candidatos a empleados del mes" << endl
            << "15. El Vagoneta" << endl
            << "16. Vender" << endl
            << "17. Sancionar" << endl
            << "18. Anular pedido" << endl
            << "19. Agregar combo al pedido" << endl;
    }

    int opt = LeerOpcion(maxOption);
    switch (opt)
    {
        case 0:
        {
            limpiarPantalla();
            MenuPrincipal();
            break;
        }
        case 1:
        {
            limpiarPantalla();
            nuevoLocal = MenuCrearLocal();
            seCreoElLocal = true;

            limpiarPantalla();
            MenuLocal();
        }
        case 2:
        {
            limpiarPantalla();
            ifstream archivoEntrada;
            LeerArchivoParaLeer(archivoEntrada);
            nuevoLocal.cargar(archivoEntrada);
            archivoEntrada.close();
            seCreoElLocal = true;
            limpiarPantalla();
            MenuLocal();
        }
            break;
        case 3:
        {
            limpiarPantalla();

            if (!seCreoElLocal)
            {
                cout << "ERROR: No se creo ningun local aun";
                break;
            }

            ofstream archivoSalida;

            LeerArchivoParaEscribir(archivoSalida);
            nuevoLocal.guardar(archivoSalida);
            archivoSalida.close();

            limpiarPantalla();
            MenuLocal();
        }
        case 4:
        {
            limpiarPantalla();
            if (!seCreoElLocal)
            {
                cout << "ERROR: No se creo ningun local aun";
                break;
            }
            //mostrarHamburguesasYBebidas();
            cout << "El ultimo local creado es: "<< endl<< endl;
            nuevoLocal.mostrar(cout);
            cout << endl<< endl;
            Pausar();

            limpiarPantalla();
            MenuLocal();
        }
        case 5:
        {
            limpiarPantalla();
            int bebida;
            if (!seCreoElLocal)
            {
                cout << "ERROR: No se creo ningun local aun";
                break;
            }
            mostrarHamburguesasYBebidas();
            cout << "Ingrese el id de la bebida de la cual desea conocer su stock: ";
            cin >> bebida;
            limpiarPantalla();
            cout << "El Stock de " << Bebidas[bebida] << " es : " << nuevoLocal.stockBebidasL(Bebidas[bebida]) << endl;
            Pausar();
            MenuLocal();
        }
        case 6:
        {
            limpiarPantalla();
            int hamburguesa;
            if (!seCreoElLocal)
            {
                cout << "ERROR: No se creo ningun local aun";
                break;
            }
            mostrarHamburguesasYBebidas();
            cout << "Ingrese el id de la hamburguesa de la cual desea conocer su stock: ";
            cin >> hamburguesa;
            limpiarPantalla();
            cout << "El Stock de " << Hamburguesas[hamburguesa] << " es : " << nuevoLocal.stockSandwichesL(Hamburguesas[hamburguesa]) << endl;
            Pausar();
            MenuLocal();
        }
        case 7:
        {
            limpiarPantalla();

            if (!seCreoElLocal)
            {
                cout << "ERROR: No se creo ningun local aun";
                break;
            }
            cout << "Las bebidas del local son :" << endl << endl;
            for (int i = 0; i < nuevoLocal.bebidasDelLocalL().size(); i++)
            {
                cout << nuevoLocal.bebidasDelLocalL()[i] << endl;
            }
            cout << endl << endl;
            Pausar();
            limpiarPantalla();
            MenuLocal();
        }
        case 8:
        {
            limpiarPantalla();

            if (!seCreoElLocal)
            {
                cout << "ERROR: No se creo ningun local aun";
                break;
            }
            cout << "Las hamburguesas del local son :" << endl << endl;
            for (int i = 0; i < nuevoLocal.sandwichesDelLocalL().size(); i++)
            {
                cout << nuevoLocal.sandwichesDelLocalL()[i] << endl;
            }
            cout << endl << endl;
            Pausar();
            limpiarPantalla();
            MenuLocal();
        }
        case 9:
        {
            limpiarPantalla();

            if (!seCreoElLocal)
            {
                cout << "ERROR: No se creo ningun local aun";
                break;
            }
            cout << "Los empleados del local son :" << endl << endl;
            for (int i = 0; i < nuevoLocal.empleadosL().size(); i++)
            {
                cout << nuevoLocal.empleadosL()[i] << endl;
            }
            cout << endl << endl;
            Pausar();
            limpiarPantalla();
            MenuLocal();
        }
        case 10:
        {
            limpiarPantalla();

            if (!seCreoElLocal)
            {
                cout << "ERROR: No se creo ningun local aun";
                break;
            }
            cout << "Los ex-empleados del local son :" << endl << endl;
            for (int i = 0; i < nuevoLocal.desempleadosL().size(); i++)
            {
                cout << nuevoLocal.desempleadosL()[i] << endl;
            }
            cout << endl << endl;
            Pausar();
            limpiarPantalla();
            MenuLocal();
        }
        case 11:
        {
            limpiarPantalla();
            int empleado;
            if (!seCreoElLocal)
            {
                cout << "ERROR: No se creo ningun local aun";
                break;
            }
            cout << "Los empleados del local son :" << endl << endl;
            for (int i = 0; i < nuevoLocal.empleadosL().size(); i++)
            {
                cout << i << " :" << nuevoLocal.empleadosL()[i] << endl;
            }
            cout << endl << endl;

            cout << "Ingrese el numero de empleado del cual desea conocer su energia[0/" << nuevoLocal.empleadosL().size()-1 << "] :";
            cin >> empleado;

            while(empleado > nuevoLocal.empleadosL().size())
            {
                cout << "Ingrese correctamente el numero de empleado del cual desea conocer su energia[0/" << nuevoLocal.empleadosL().size()-1 << "] :";
                cin >> empleado;
            }
            limpiarPantalla();
            cout << "La energia de " << nuevoLocal.empleadosL()[empleado] << " es : " << nuevoLocal.energiaEmpleadoL(nuevoLocal.empleadosL()[empleado]) << endl;
            cout << endl;
            Pausar();
            MenuLocal();
        }
        case 12:
        {
            limpiarPantalla();

            if (!seCreoElLocal)
            {
                cout << "ERROR: No se creo ningun local aun";
                break;
            }
            cout << "Las ventas del local son :" << endl << endl;
            for (int i = 0; i < nuevoLocal.ventasL().size(); i++)
            {
                cout << nuevoLocal.ventasL()[i] << endl;
            }
            cout << endl << endl;
            Pausar();
            limpiarPantalla();
            MenuLocal();
        }
        case 13:
        {
            limpiarPantalla();

            if (!seCreoElLocal)
            {
                cout << "ERROR: No se creo ningun local aun";
                break;
            }
            cout << "Una venta cada uno? " << nuevoLocal.unaVentaCadaUnoL();
            cout << endl << endl;
            Pausar();
            limpiarPantalla();
            MenuLocal();
        }
        case 14:
        {
            limpiarPantalla();
            if (!seCreoElLocal)
            {
                cout << "ERROR: No se creo ningun local aun";
                break;
            }
            cout << "Los candidatos a empleados del mes son :" << endl << endl;
            for (int i = 0; i < nuevoLocal.candidatosAEmpleadosDelMesL().size(); i++)
            {
                cout << i << " :" << nuevoLocal.candidatosAEmpleadosDelMesL()[i] << endl;
            }
            cout << endl << endl;

            Pausar();
            MenuLocal();
        }
        case 15:
        {
            limpiarPantalla();
            if (!seCreoElLocal)
            {
                cout << "ERROR: No se creo ningun local aun";
                break;
            }
            cout << "El vagoneta es: " << nuevoLocal.elVagonetaL() << endl;
            cout << endl << endl;
            Pausar();
            MenuLocal();
        }
        case 16:
        {
            limpiarPantalla();
            if (!seCreoElLocal)
            {
                cout << "ERROR: No se creo ningun local aun";
                break;
            }
            nuevoLocal.venderL(MenuCrearPedidoDeLocal());
            MenuLocal();
        }
        case 17:
        {
            limpiarPantalla();
            int empleado;
            int sancion;
            if (!seCreoElLocal)
            {
                cout << "ERROR: No se creo ningun local aun";
                break;
            }
            cout << "Sancionando un empleado" << endl<< endl;
            cout << "Los empleados del local son :" << endl << endl;
            for (int i = 0; i < nuevoLocal.empleadosL().size(); i++)
            {
                cout << i << " :" << nuevoLocal.empleadosL()[i] << endl;
            }
            cout << endl << endl;
            cout << "Indique el numero de empleado a sancionar[0/" << nuevoLocal.empleadosL().size()-1 << "]";
            cin >> empleado;
            while(empleado > nuevoLocal.empleadosL().size()-1)
            {
                cout << "Indique correctamente el numero de empleado a sancionar[0/" << nuevoLocal.empleadosL().size()-1 << "]";
                cin >> empleado;
            }
            cout << "Indique la sancion : ";
            cin >> sancion;
            nuevoLocal.sancionL(nuevoLocal.empleadosL()[empleado], sancion);
            limpiarPantalla();
            MenuLocal();
        }
        case 18:
        {
            limpiarPantalla();
            int pedido;
            if (!seCreoElLocal)
            {
                cout << "ERROR: No se creo ningun local aun";
                break;
            }
            cout << "Anulando un pedido" << endl<< endl;
            cout << "Los pedidos del local son :" << endl << endl;
            for (int i = 0; i < nuevoLocal.ventasL().size(); i++)
            {
                cout << i << " :" << nuevoLocal.ventasL()[i] << endl;
            }
            cout << endl << endl;
            cout << "Indique el indice en la lista del pedido a anular[0/" << nuevoLocal.ventasL().size()-1 << "]";
            cin >> pedido;
            while (pedido > nuevoLocal.ventasL().size()-1)
            {
                cout << "Indique correctamente el indice en la lista del pedido a anular, de los que figuran en la lista[0/" << nuevoLocal.ventasL().size()-1 << "]";
                cin >> pedido;
            }
            nuevoLocal.anularPedidoL(nuevoLocal.ventasL()[pedido].numeroP());
            limpiarPantalla();
            MenuLocal();
        }
        case 19:
        {
            limpiarPantalla();
            int pedido;
            if (!seCreoElLocal)
            {
                cout << "ERROR: No se creo ningun local aun";
                break;
            }
            cout << "Agregando combo a un pedido" << endl<< endl;
            cout << "Los pedidos del local son :" << endl << endl;
            for (int i = 0; i < nuevoLocal.ventasL().size(); i++)
            {
                cout << i << " :" << nuevoLocal.ventasL()[i] << endl;
            }
            cout << endl << endl;
            cout << "Indique el indice en la lista del pedido al que desea agregar un combo[0/" << nuevoLocal.ventasL().size()-1 << "]";
            cin >> pedido;
            while (pedido > nuevoLocal.ventasL().size()-1)
            {
                cout << "Indique correctamente el indice en la lista del pedido al que desea agregar un combo[0/" << nuevoLocal.ventasL().size()-1 << "]";
                cin >> pedido;
            }
            nuevoLocal.agregarComboAlPedidoL(MenuCrearCombo(), nuevoLocal.ventasL()[pedido].numeroP());
            limpiarPantalla();
            MenuLocal();
        }
            break;
    }
}


void LeerArchivoParaLeer(ifstream &archivo)
{
    cout << "  Ingrese nombre de archivo existente: ";
    string opt;
    bool ok = false;
    while (!ok)
    {
        getline(cin, opt);
        archivo.open(opt.c_str());
        ok = archivo.good();

        if (!ok && opt.size()>1)
            cout << "  Valor incorrecto. Ingrese nombre de archivo existente: ";
    }
}


void LeerArchivoParaEscribir(ofstream &archivo)
{
    cout << "  Ingrese nombre de archivo: ";
    string opt;
    bool ok = false;
    while (!ok)
    {
        getline(cin, opt);
        archivo.open(opt.c_str());
        ok = archivo.good();
        if (!ok && opt.size()>1)
            cout << "  Valor incorrecto. Ingrese nombre de archivo: ";
    }
}



// Menus de cada tipo
// Menu Combo

Combo MenuCrearCombo()
{
	Energia energia;
	int hamburguesa;
	int bebida;

	cout << "Agregando un nuevo combo" << endl<< endl;

    mostrarHamburguesasYBebidas();

    cout << "Por favor ingrese la hamburguesa y bebida del combo: " << endl<< endl;

    cout << "Hamburguesa [0/" << MaxH << "] :";
    cin >> hamburguesa;
    while (hamburguesa > MaxH)
    {
        cout << "Por favor ingrese un valor correcto para la hamburguesa[0/" << MaxH << "] :";
        cin >> hamburguesa;
    }

    cout << endl;


    cout << "Bebida [0/" << MaxB << "] :";
    cin >> bebida;
	while (bebida > MaxB)
    {
        cout << "Por favor ingrese un valor correcto para la Bebida[0/" << MaxB << "] :";
        cin >> bebida;
    }

	cout << "Energia = ";
	cin >> energia;

	cout << endl;

    Combo combo = Combo(Bebidas[bebida],Hamburguesas[hamburguesa],energia);

    //cout << "El Combo creado es: " << endl;
    //cout << combo;

	return combo;
}

Combo MenuCrearComboAPedidoDeLocal()
{
	Energia energia;
	int hamburguesa;
	int bebida;

	cout << "Agregando un nuevo combo" << endl<< endl;

    mostrarHamburguesasYBebidasDeLocal();

    cout << "Por favor ingrese la hamburguesa y bebida del combo: " << endl<< endl;

    cout << "Hamburguesa [0/" << nuevoLocal.sandwichesDelLocalL().size()-1 << "] :";
    cin >> hamburguesa;
    while (hamburguesa > MaxH)
    {
        cout << "Por favor ingrese un valor correcto para la hamburguesa[0/" << nuevoLocal.sandwichesDelLocalL().size()-1 << "] :";
        cin >> hamburguesa;
    }

    cout << endl;


    cout << "Bebida [0/" << nuevoLocal.bebidasDelLocalL().size()-1 << "] :";
    cin >> bebida;
	while (bebida > nuevoLocal.bebidasDelLocalL().size()-1)
    {
        cout << "Por favor ingrese un valor correcto para la Bebida[0/" << nuevoLocal.bebidasDelLocalL().size()-1 << "] :";
        cin >> bebida;
    }

	cout << "Energia = ";
	cin >> energia;

	cout << endl;

    Combo combo = Combo(nuevoLocal.bebidasDelLocalL()[bebida],nuevoLocal.sandwichesDelLocalL()[hamburguesa],energia);

    //cout << "El Combo creado es: " << endl;
    //cout << combo;

	return combo;
}


Pedido MenuCrearPedido()
{
    bool otroCombo = true;
    string opt = "";

    vector<Combo> Combos;

	int nro = 0;
	Empleado empleado;

	cout << "Creando un pedido nuevo: "<< endl<< endl;

	cout << "Numero de pedido = ";
	cin >> nro;

	cout << "Empleado = ";
	cin >> empleado;

	cout << "Combos:" << endl;
	while (otroCombo)
	{
	    cout << endl;
		Combos.push_back(MenuCrearCombo());
		cout << endl;
		cout << "Agregar otro combo? [s/n]";
		cin >> opt;
		otroCombo = (opt == "s");
		limpiarPantalla();
		mostrarMenuAgregacionComboAPedido(nro, empleado, Combos);
	}

	return Pedido(nro, empleado, Combos);
}


Pedido MenuCrearPedidoDeLocal()
{
    bool otroCombo = true;
    string opt = "";

    vector<Combo> Combos;

	int nro;
	int empleado;

	cout << "Creando un pedido nuevo para el Local: "<< endl<< endl;

    cout << "La cantidad de ventas total del local es: " << nuevoLocal.ventasL().size() << endl;
	cout << "Numero de pedido = ";
	cin >> nro;

    cout << "Los empleados del local son: " << endl << endl;
    for (int i = 0; i < nuevoLocal.empleadosL().size(); i++)
    {
        cout << "| "<< i <<" | " << nuevoLocal.empleadosL()[i] << " |" << endl;
    }
	cout << "Ingrese el numero de empleado que realiza la venta[0/" << nuevoLocal.empleadosL().size() -1 << "] :";
	cin >> empleado;

    while (empleado > nuevoLocal.empleadosL().size() -1)
    {
        cout << "Ingrese correctamente el numero de empleado que realiza la venta[0/" << nuevoLocal.empleadosL().size() -1 << "] :";
        cin >> empleado;
    }

	cout << "Combos:" << endl;
	while (otroCombo)
	{
	    cout << endl;
		Combos.push_back(MenuCrearComboAPedidoDeLocal());
		cout << endl;
		cout << "Agregar otro combo? [s/n]";
		cin >> opt;
		otroCombo = (opt == "s");
		limpiarPantalla();
		mostrarMenuAgregacionComboAPedido(nro, nuevoLocal.empleadosL()[empleado], Combos);
	}

	return Pedido(nro, nuevoLocal.empleadosL()[empleado], Combos);
}

void mostrarMenuAgregacionComboAPedido(int nro, Empleado empleado, vector<Combo> combos)
{
    cout << "Numero de pedido = " << nro << endl;
	cout << "Empleado = " << empleado << endl;
	cout << "Combos : " << endl;

	for (int i = 0; i < combos.size(); i++)
	{
	    combos[i].mostrar(cout);
	    cout << endl;
	}
}

Local MenuCrearLocal()
{
    //Local(const vector< pair <Bebida,Cantidad> > bs, const vector< pair <Hamburguesa,Cantidad> > hs, const vector<Empleado> es);

    cout << "Creando un local" << endl << endl;
    vector< pair <Bebida,Cantidad> > bs = menuAgregacionBebidasALocal();
    vector< pair <Hamburguesa,Cantidad> > hs = menuAgregacionHamburguesasALocal();
    vector<Empleado> es = menuAgregacionEmpleadosALocal();

    return Local(bs , hs , es);
}

vector<Empleado> menuAgregacionEmpleadosALocal()
{
    vector<Empleado> empleados = vector<Empleado>();
    Empleado empleado;

    string opt = "s";
    while (opt == "s")
    {
        limpiarPantalla();
        cout << "Ingresando empleados al local" << endl << endl;
        cout << "vector de empleados :" << endl;
        for(int i = 0; i < empleados.size(); i++)
        {
            cout << empleados[i] << endl;
        }
        cout << endl;

        cout << "Ingrese el nombre del empleado que desea agregar: ";
        cin >> empleado;

        empleados.push_back(empleado);

        limpiarPantalla();
        cout << "Ingresando empleados al local" << endl << endl;
        cout << "vector de empleados :" << endl;
        for(int i = 0; i < empleados.size(); i++)
        {
            cout << empleados[i] << endl;
        }

        cout << endl;

        cout<< "Desea agregar otro empleado?[s/n]: ";
        cin >> opt;
    }

    return empleados;
}

vector< pair <Bebida,Cantidad> > menuAgregacionBebidasALocal()
{
    cout << "Ingresando stock de bebidas" << endl << endl;

    vector< pair <Bebida,Cantidad> > bebidasRetornadas = vector< pair <Bebida,Cantidad> >();

    int bebida;
    Cantidad cantidad;
    string opt = "s";

    while (opt == "s")
    {
        limpiarPantalla();
        mostrarHamburguesasYBebidas();

        mostrarStockBebidas(bebidasRetornadas);

        cout << endl << endl;
        cout << "Ingrese el numero de bebida que desea agregar al local [0/" << MaxB << "] :";
        cin >> bebida;

        while (bebida > MaxB)
        {
            cout << "Ingrese un numero correcto de bebida que desea agregar al local[0/" << MaxB << "] :";
            cin >> bebida;
        }

        cout << "Ingrese el stock inicial de " << Bebidas[bebida] << " :";
        cin >> cantidad;


        pair<Bebida,Cantidad> par = pair<Bebida,Cantidad>(Bebidas[bebida], cantidad);

        bebidasRetornadas.push_back( par );

        limpiarPantalla();
        mostrarHamburguesasYBebidas();

        mostrarStockBebidas(bebidasRetornadas);

        cout << endl << endl;
        cout << "Desea continuar agregando bebidas?[s/n] :";
        cin >> opt;
    }

    return bebidasRetornadas;
}

vector< pair <Hamburguesa,Cantidad> > menuAgregacionHamburguesasALocal()
{

    cout << "Ingresando stock de hamburguesas" << endl << endl;
    vector< pair <Hamburguesa,Cantidad> > hamburguesasRetornadas = vector< pair <Hamburguesa,Cantidad> >();

    int hamburguesa;
    Cantidad cantidad;
    string opt = "s";

    while (opt == "s")
    {
        limpiarPantalla();
        mostrarHamburguesasYBebidas();

        mostrarStockHamburguesas(hamburguesasRetornadas);

        cout << endl << endl;
        cout << "Ingrese el numero de hamburguesa que desea agregar al local[0/" << MaxH << "] :";
        cin >> hamburguesa;

        while (hamburguesa > MaxH)
        {
            cout << "Ingrese un numero correcto de hamburguesa que desea agregar al local[0/" << MaxH << "] :";
            cin >> hamburguesa;
        }

        cout << "Ingrese el stock inicial de " << Hamburguesas[hamburguesa] << " :";
        cin >> cantidad;


        pair<Hamburguesa,Cantidad> par = pair<Hamburguesa,Cantidad>(Hamburguesas[hamburguesa], cantidad);

        hamburguesasRetornadas.push_back( par );

        limpiarPantalla();
        mostrarHamburguesasYBebidas();

        mostrarStockHamburguesas(hamburguesasRetornadas);

        cout << endl << endl;
        cout << "Desea continuar agregando hamburguesas?[s/n] :";
        cin >> opt;
    }

    return hamburguesasRetornadas;
}

void mostrarStockHamburguesas(vector< pair <Hamburguesa,Cantidad> > stock)
{
    cout << "Stock de hamburguesas: " << endl << endl;
    cout << "Hamburguesa" << "\t\tCantidad" << endl;
    for (int i = 0; i < stock.size(); i++)
    {
        cout << stock[i].first << "\t" << stock[i].second << endl;
    }
}

void mostrarStockBebidas(vector< pair <Bebida,Cantidad> > stock)
{
    cout << "Stock de bebidas: " << endl << endl;
    cout << "Bebida" << "\t\tCantidad" << endl;
    for (int i = 0; i < stock.size(); i++)
    {
        cout << stock[i].first << "\t" << stock[i].second << endl;
    }
}

void mostrarHamburguesasYBebidas()
{
    cout << "vector de Bebidas : \t |\tvector de Hamburguesas" << endl; cout << " \t\t\t |" << endl;
    for (int i = 0; i < Bebidas.size(); i++)
    {
        cout << i << ":" << traducir(Bebidas[i]) << "\t\t |\t";
        if (i < Hamburguesas.size()) cout << i << " :" << traducir(Hamburguesas[i]) << endl;
    }
    cout << endl<< endl;
}

void mostrarHamburguesasYBebidasDeLocal( )
{
    if (nuevoLocal.bebidasDelLocalL().size() > nuevoLocal.sandwichesDelLocalL().size())
    {
        cout << "vector de Bebidas : \t |\tvector de Hamburguesas" << endl; cout << " \t\t\t |" << endl;
        for (int i = 0; i < nuevoLocal.bebidasDelLocalL().size(); i++)
        {
            cout << i << ":" << traducir(nuevoLocal.bebidasDelLocalL()[i]) << "\t\t |\t";
            if (i < nuevoLocal.sandwichesDelLocalL().size()) cout << i << " :" << traducir(nuevoLocal.sandwichesDelLocalL()[i]) << endl;
        }
        cout << endl<< endl;
    }else
    {
        cout << "vector de Hamburguesas : \t |\tvector de Bebidas" << endl; cout << " \t\t\t |" << endl;
        for (int i = 0; i < nuevoLocal.sandwichesDelLocalL().size(); i++)
        {
            cout << i << ":" << traducir(nuevoLocal.sandwichesDelLocalL()[i]) << "\t\t |\t";
            if (i < nuevoLocal.bebidasDelLocalL().size()) cout << i << " :" << traducir(nuevoLocal.bebidasDelLocalL()[i]) << endl;
        }
        cout << endl<< endl;
    }

}


void mostrarCombos(vector<Combo> combos)
{
    cout << "Los combos del pedido son: " << endl<< endl;
    for(int i = 0; i < combos.size(); i++)
    {
        cout << i << ":"; combos[i].mostrar(cout); cout << endl;
    }
}

void Salir()
{
    cout << "Gracias, Vuelvan prontos!" << endl;
}

void Pausar()
{
    string opt = "n";
#ifdef WIN32
    system("Pause");
#else
    while (opt != "s")
    {
        cout << "Desea continuar?[s/n]";
        cin >> opt;
    }
#endif

}

void limpiarPantalla()
{
#ifdef WIN32
    system("cls");
#else
    system("clear");
#endif
}


string traducir(Bebida b){

    switch(b){

        case PestiCola: return "PestiCola"; break;
        case FalsaNaranja: return "FalsaNaranja"; break;
        case SeVeNada: return "SeVeNada"; break;
        case AguaConGags: return "AguaConGags"; break;
        case AguaSinGags: return "AguaSinGags"; break;
        default: return "Otra bebida invalida";
    }
    return "";

}

//enum Hamburguesa{McGyver, CukiQueFresco, McPato, BigMacabra};
string traducir(Hamburguesa h){

    switch(h){

        case McGyver: return "McGyver"; break;
        case CukiQueFresco: return "CukiQueFresco"; break;
        case McPato: return "McPato"; break;
        case BigMacabra: return "BigMacabra"; break;

        default: return "Otra hamburg invalida";
    }
    return "";

}
