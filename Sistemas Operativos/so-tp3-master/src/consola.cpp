#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utility>
#include <string>
#include <cstring>
#include <list>
#include <iostream>
#include <sstream>
#include "consola.hpp"
#include "HashMap.hpp"
#include "mpi.h"
#include "mpiUtils.h"

using namespace std;

#define CMD_LOAD    "load"
#define CMD_ADD     "addAndInc"
#define CMD_MEMBER  "member"
#define CMD_MAXIMUM "maximum"
#define CMD_QUIT    "quit"
#define CMD_SQUIT   "q"


static unsigned int np;
extern bool DEBUG;

/**************************** LOAD **************************/
/************************************************************/

void sleepFor(int value){
    int perderTiempo = 0;
    for (int i = 0; i < value; ++i){
        perderTiempo++;
    }
}

static void load(list<string> params) {
    uint agregados = 0;
    char archivo[TAM_ARCHIVO];
    list<string>::iterator it = params.begin();
    for (uint nodo = 1; nodo < np; nodo++, it++) {
        if(it != params.end()){
            strcpy(archivo, (*it).c_str());
            //cout << "El largo del nombre del archivo es: " << (*it).length() << endl;
            MPI_Send(&archivo, (*it).length(), MPI_CHAR, nodo, TAG_LOAD, MPI_COMM_WORLD);
        } else {
            break;
        }
    }

    MPI_Status status;
    char ok_msg;
    int nodo_libre;
    for(; it != params.end();it++){
        //Cuando cargue el archivo, el nodo envia un msg con el caracter 'k' y con TAG_LOADED.
        MPI_Recv(&ok_msg, 1, MPI_CHAR, MPI_ANY_SOURCE, TAG_LOADED, MPI_COMM_WORLD, &status);
        nodo_libre = status.MPI_SOURCE;
        if(DEBUG) cout << "Free Node: " << nodo_libre << endl; sleepFor(1000000);
        agregados++;
        if(ok_msg == 'k'){
            strcpy(archivo, (*it).c_str());
            MPI_Send(&archivo, (*it).length(), MPI_CHAR, nodo_libre, TAG_LOAD, MPI_COMM_WORLD);
        }
        //Nunca deberia entrar aca.
        //cout << "Error en el for de load" << endl;
    }
    //Pueden quedar mensajes sin recibir en la cola de mensajes. Los capturo
    while(agregados < params.size()){
        MPI_Recv(&ok_msg, 1, MPI_CHAR, MPI_ANY_SOURCE, TAG_LOADED, MPI_COMM_WORLD, &status);
        nodo_libre = status.MPI_SOURCE;
        if(DEBUG) cout << "Free Node: " << nodo_libre << endl;
        agregados++;
    }
    cout << "La listá esta procesada" << endl;
}


/***************************** QUIT *************************/
/************************************************************/


static void quit() {
    char quit_char = 'q';
    MPI_Request req;
    for(uint i = 1; i < np; i++){
        MPI_Isend(&quit_char, 1, MPI_CHAR, i, TAG_QUIT, MPI_COMM_WORLD, &req);
    }
}


/************************** ADDANDINC ***********************/
/************************************************************/

static void addAndInc(string key) {
    //cout << "Soy la consola en addAndInc, la clave recibida fue " << key << endl;
    char add_char = 'a';
    for(uint i = 1; i < np; i++){
        MPI_Send(&add_char, 1, MPI_CHAR, i, TAG_ADD_START, MPI_COMM_WORLD);
    }

    int receptor;
    MPI_Status status;
    char skip = 's';
    MPI_Request req;

    char palabra [TAM_PALABRA];

    //Espero a que algun nodo me avise que lo va a agregar
    for(uint i = 1; i < np; i++){
        //cout << "Soy la consola, estoy esperando a que un nodo responda para mandarle la palabra a agregar" << endl;
        MPI_Recv(&receptor, 1, MPI_INT, MPI_ANY_SOURCE, TAG_ADD_RECEPTOR, MPI_COMM_WORLD, &status);
        //Si es el primero que me avisa, le indico que lo agregue. Sino, que no haga nada.
        if(i == 1){
            strcpy(palabra, key.c_str());
            if(DEBUG) cout << "Adder Node: " << receptor << endl;
            MPI_Isend(&palabra, key.length(), MPI_CHAR, receptor, TAG_ADD_WORD, MPI_COMM_WORLD, &req);
        } else {
            MPI_Isend(&skip, 1, MPI_CHAR, receptor, TAG_SKIP, MPI_COMM_WORLD, &req);
        }
    }

    //Asumo que el nodo elegido agrego bien la palabra. No es necesario que avise que la agrego.
    //Si el nodo todavia no termino de agregarlo y justo le piden una funcion como member, dado que el nodo
    //es un ciclo y no tiene varios threads, va a terminar de agregar la palabra antes de responder a member.
    cout << "Agregado: " << key << endl;
}



/***************************** AUX **************************/
/************************************************************/

static void getHashMap(HashMap &h){
    char maximum_char = 'm';
    for(uint i = 1; i < np; i++){
        MPI_Send(&maximum_char, 1, MPI_CHAR, i, TAG_MAXIMUM_START, MPI_COMM_WORLD);
    }
    uint completados = 0;
    
    char palabra_msg [TAM_PALABRA];
    int cant_chars;
    MPI_Status status;
    while(completados < np - 1){
        MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_CHAR, &cant_chars);
        //cout << "Soy la consola en maximum, voy a leer una palabra del nodo " << status.MPI_SOURCE << " de tam " << cant_chars << endl;
        
        MPI_Recv(&palabra_msg, cant_chars, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status); //Recibo mensaje
        //Podria tomar un mensaje colgado de alguna otra funcion. ASUMO QUE NO NOS IMPORTA PERDERLO.
        //Checkeo tag
        if(status.MPI_TAG == TAG_PALABRA){
            if(DEBUG) cout << "Sender Node: " << status.MPI_SOURCE << endl; 
            //Si es agregar_palabra la agrego
            string key(palabra_msg, cant_chars);
            //cout << "Soy la consola en maximum, voy a agregar la palabra "<< key << endl;
            h.addAndInc(key);
        } else if(status.MPI_TAG == TAG_MAXIMUM_END){
            completados++;
        }
        //Descarto el mensaje 
    }
}

/*************************** MAXIMUM ************************/
/************************************************************/

static pair<string, unsigned int> maximumRET() {
    pair<string, unsigned int> result;
    HashMap h;
    getHashMap(h);
    result = h.maximum();
    return result;
}
 
static void maximum() {
    pair<string, unsigned int> result;
    result = maximumRET();
    cout << "El máximo es <" << result.first <<"," << result.second << ">" << endl;
}


/**************************** MEMBER ************************/
/************************************************************/

static bool memberRET(string key){
    bool esta = false;
    int myRank;
    MPI_Request req;
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    
    char key_buff [TAM_PALABRA];
    strcpy(key_buff, key.c_str());
    //cout << "key_buff tiene " << key_buff << endl;
    for(uint i = 1; i < np; i++){
        MPI_Isend(&key_buff, key.length(), MPI_CHAR, i, TAG_MEMBER, MPI_COMM_WORLD, &req);
    }

    bool res;
    MPI_Status status;
    for(uint i = 1; i < np; i++){
        MPI_Recv(&res, 1, MPI_C_BOOL, MPI_ANY_SOURCE, TAG_MEMBER, MPI_COMM_WORLD, &status);
        if(res){
            esta = true;
        }
    }
    return esta;        
}

static void member(string key) {
    bool esta = memberRET(key);
    cout << "El string <" << key << (esta ? ">" : "> no") << " está" << endl;
}


/* static int procesar_comandos()
La función toma comandos por consola e invoca a las funciones correspondientes
Si devuelve true, significa que el proceso consola debe terminar
Si devuelve false, significa que debe seguir recibiendo un nuevo comando
*/

static bool procesar_comandos() {

    char buffer[BUFFER_SIZE];
    size_t buffer_length;
    char *res, *first_param, *second_param;

    // Mi mamá no me deja usar gets :(
    res = fgets(buffer, sizeof(buffer), stdin);

    // Permitimos salir con EOF
    if (res==NULL)
        return true;

    buffer_length = strlen(buffer);
    // Si es un ENTER, continuamos
    if (buffer_length<=1)
        return false;

    // Sacamos último carácter
    buffer[buffer_length-1] = '\0';

    // Obtenemos el primer parámetro
    first_param = strtok(buffer, " ");

    if (strncmp(first_param, CMD_QUIT, sizeof(CMD_QUIT))==0 ||
        strncmp(first_param, CMD_SQUIT, sizeof(CMD_SQUIT))==0) {

        quit();
        return true;
    }

    if (strncmp(first_param, CMD_MAXIMUM, sizeof(CMD_MAXIMUM))==0) {
        maximum();
        return false;
    }

    // Obtenemos el segundo parámetro
    second_param = strtok(NULL, " ");
    if (strncmp(first_param, CMD_MEMBER, sizeof(CMD_MEMBER))==0) {
        if (second_param != NULL) {
            string s(second_param);
            member(s);
        }
        else {
            printf("Falta un parámetro\n");
        }
        return false;
    }

    if (strncmp(first_param, CMD_ADD, sizeof(CMD_ADD))==0) {
        if (second_param != NULL) {
            string s(second_param);
            addAndInc(s);
        }
        else {
            printf("Falta un parámetro\n");
        }
        return false;
    }

    if (strncmp(first_param, CMD_LOAD, sizeof(CMD_LOAD))==0) {
        list<string> params;
        while (second_param != NULL)
        {
            string s(second_param);
            params.push_back(s);
            second_param = strtok(NULL, " ");
        }

        load(params);
        return false;
    }

    printf("Comando no reconocido");
    return false;
}

void consola(unsigned int np_param) {
    np = np_param;
    if(!DEBUG){
        printf("Comandos disponibles:\n");
        printf("  "CMD_LOAD" <arch_1> <arch_2> ... <arch_n>\n");
        printf("  "CMD_ADD" <string>\n");
        printf("  "CMD_MEMBER" <string>\n");
        printf("  "CMD_MAXIMUM"\n");
        printf("  "CMD_SQUIT"|"CMD_QUIT"\n");
    }
    bool fin = false;
    while (!fin) {
        printf("> ");
        fflush(stdout);
        fin = procesar_comandos();
    }
}
