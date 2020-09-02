#include "nodo.hpp"
#include "HashMap.hpp"
#include "mpi.h"
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include "mpiUtils.h"
#include <string>
#include <cstring>

using namespace std;
extern bool DEBUG;

void nodo(unsigned int rank) {
    if(!DEBUG) printf("Soy un nodo. Mi rank es %d \n", rank);
    HashMap h;

    MPI_Request req;
    MPI_Status status;
    int tam_msg, tag;
    char msg [TAM_MSG];
    char palabra_msg [TAM_PALABRA];
    

    while (true) {
        MPI_Probe(CONSOLA_RANK, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_CHAR, &tam_msg);
        //cout << "Soy el nodo " << rank << ". Voy a leer un msg de tam " << tam_msg << endl;
        MPI_Recv(&msg, tam_msg, MPI_CHAR, CONSOLA_RANK, MPI_ANY_TAG, MPI_COMM_WORLD, &status); //Recibo mensaje de la consola
        tag = status.MPI_TAG;
        //cout << "El mensaje leido fue: " << msg << endl;
        switch(tag){
        	case TAG_QUIT:{
        		return;
        		break;
        	}
        	case TAG_MEMBER:{
      			
        		string key(msg, tam_msg);
        		//cout << "Soy el nodo " << rank << " en member. Voy a buscar la key: " << key << endl;
        		bool esta = h.member(key);
        		//Bloqueante??
        		trabajarArduamente();
        		MPI_Isend(&esta, 1, MPI_C_BOOL, CONSOLA_RANK, TAG_MEMBER, MPI_COMM_WORLD, &req);
        		break;
        	}
        	case TAG_ADD_START:{

        		trabajarArduamente();
        		MPI_Isend(&rank, 1, MPI_INT, CONSOLA_RANK, TAG_ADD_RECEPTOR, MPI_COMM_WORLD, &req);
        		break;
        	}
        	case TAG_ADD_WORD:{
        		string key(msg, tam_msg);
        		//cout << "Soy el nodo " << rank << " en addAndInc. Voy a agregar la key: " << key << endl;
        		h.addAndInc(key);
        		break;
        	}
        	case TAG_SKIP:{
        		//No hago nada
        		break;
        	}
        	case TAG_LOAD:{
        		string file(msg, tam_msg);
        		if(DEBUG) cout << "Node: " << rank << " Loading: " << file << endl;
        		h.load(file);
        		char ok_msg = 'k';
        		trabajarArduamente();

        		MPI_Isend(&ok_msg, 1, MPI_CHAR, CONSOLA_RANK, TAG_LOADED, MPI_COMM_WORLD, &req);
        		break;
        	}
        	case TAG_MAXIMUM_START:{
        		trabajarArduamente();
        		for(HashMap::iterator it = h.begin(); it != h.end(); it++){
        			strcpy(palabra_msg, (*it).c_str());
                    if(DEBUG) cout << "Node: " << rank << " Sending word" << endl; 
        			MPI_Isend(&palabra_msg, (*it).length(), MPI_CHAR, CONSOLA_RANK, TAG_PALABRA, MPI_COMM_WORLD, &req);
        		}
        		//Le aviso a la consola que no hay mas palabras. Mando tam 0 porque no importa le msg, solo el tag.
        		MPI_Isend(&palabra_msg, 0, MPI_CHAR, CONSOLA_RANK, TAG_MAXIMUM_END, MPI_COMM_WORLD, &req);
        		break;
      		}
        }
    }
}

void trabajarArduamente() {
    int r = rand() % 2500000 + 500000;
    usleep(r);
}
