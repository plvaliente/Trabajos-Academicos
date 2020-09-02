#include "ConcurrentHashMap.hpp"

typedef struct iterador_tabla{
	pthread_mutex_t max_mutex;
	pair<string, unsigned int> max;
	std::atomic<int> prox_lista;
    map<int, Lista<pair<string, unsigned int> >* >* tabla;
}iterador_tabla;

typedef struct lista_archivos_hashmap{
	ConcurrentHashMap* hashMap;
	list<string> archivos;
	pthread_mutex_t arch_mutex;
}lista_archivos_hashmap;

typedef struct hashes_archivos{
	vector<ConcurrentHashMap*> hashes;
	list<string> archivos;
	pthread_mutex_t arch_mutex;
	pthread_mutex_t hashes_mutex;
}hashes_archivos;

typedef struct merge_struct{
	vector<ConcurrentHashMap*> hashes;
	ConcurrentHashMap* h;
	std::atomic<int> prox_hash;
}merge_struct;

unsigned int char_to_pos(char i){
    return (int) (i - 97);
}

ConcurrentHashMap::ConcurrentHashMap(){
   //Inicializa las listas
   for(int i = 0; i < CANT_LETRAS ; i++){
   		tabla[i] = new Lista<pair<string, unsigned int> >();
   }
   
   //Inicializa los mutex
   for (char c = 'a'; c <= 'z'; c++){
       mutexes[c] = new pthread_mutex_t();
       int error = pthread_mutex_init(mutexes[c], NULL);
       if(error){
       		std::cout << "Hubo un error al inicializar el mutex" << std::endl;
       }
   }

}

bool ConcurrentHashMap::member(string key){
    char hash = key[0];
    auto it = tabla[char_to_pos(hash)]->CrearIt();

    while (it.HaySiguiente()){
        if (it.Siguiente().first == key){
        	return true;
        }
        it.Avanzar();
    }
    return false;
}

void ConcurrentHashMap::addAndIncN(string key, unsigned int n){
	char hash = key[0];
	pthread_mutex_lock(mutexes[hash]);
	auto it = tabla[char_to_pos(hash)]->CrearIt();
	bool esta = false;
	while (it.HaySiguiente()){
		if (it.Siguiente().first == key){
			esta = true;
			break;
		}
		it.Avanzar();
	}

	if (esta){
		it.Siguiente().second += n;
	} else {
		pair<string, int> nuevoPar(key, n);
		tabla[char_to_pos(hash)]->push_front(nuevoPar);
	}

	pthread_mutex_unlock(mutexes[hash]);
}

void ConcurrentHashMap::addAndInc(string key){
	addAndIncN(key, 1);
}


pair<string, unsigned int> dameMaximo(Lista<pair<string, unsigned int> >* lista){
	auto it = lista->CrearIt();
	pair<string, unsigned int> max("", 0);

    while (it.HaySiguiente()){
        if (it.Siguiente().second > max.second){
        	max = it.Siguiente();
        }
        it.Avanzar();
    }
    return max;
}

//Funcion para los threads. Toma un struct iterador_tabla
//y guarda en su iter.max el maximo de toda la tabla iter.tabla
void* max_lista(void* it_tabla){
	iterador_tabla* iter = (iterador_tabla*) it_tabla;
	map<int, Lista<pair<string, unsigned int> >* >& tabla = *(iter->tabla);
	int actual;
	pair<string, unsigned int> maxActual;

    while (true){
		int actual  = iter->prox_lista.fetch_add(1);

        if (actual >= 26){
			pthread_exit(NULL);
		} else {
			maxActual = dameMaximo(tabla[actual]);

			pthread_mutex_lock(&iter->max_mutex);

            if (maxActual.second > iter->max.second){
				iter->max = maxActual;
			}

            pthread_mutex_unlock(&iter->max_mutex);
		}
	}
}

pair<string, unsigned int> ConcurrentHashMap::maximum(unsigned int nt){
	iterador_tabla iter;
	pthread_mutex_init(&iter.max_mutex, NULL);
	iter.max = make_pair("", 0);
	iter.prox_lista.store(0);
	iter.tabla = &tabla;

	pthread_attr_t attr;
	void* status;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);


	vector<pthread_t*> threads;
	for (int i = 0; i < nt; i++){
		pthread_t* nuevoThread = new pthread_t();
		threads.push_back(nuevoThread);
	}

	for (int i = 0; i < nt; i++){
		pthread_create(threads[i], &attr, &max_lista, (void*) &iter);
	}

	pthread_attr_destroy(&attr);

	for (int i = 0; i < nt; i++){
		pthread_join(*threads[i], &status);
	}

	for (int i = 0; i < nt; i++){
		delete threads[i];
	}

	return iter.max;
}

//Toma un puntero a ConcurrentHashMap y un archivo y le agrega todas las palabras
void add_words(ConcurrentHashMap* h, string arch){
	string palabra;

    ifstream source(arch);

    while (source >> palabra){
        h->addAndInc(palabra);
    }
}

ConcurrentHashMap ConcurrentHashMap::count_words(string arch){
    ConcurrentHashMap h;
    add_words(&h, arch);

	return h;
}

ConcurrentHashMap ConcurrentHashMap::count_words(list<string> archs){
	return ConcurrentHashMap::count_words(archs.size(), archs);
}

void* load_archs(void* _lah){ 	//Toma un struct lista_archivos_hashmap
	lista_archivos_hashmap* lah = (lista_archivos_hashmap*) _lah;
    string arch;

    while (true){
    	pthread_mutex_lock(&(lah->arch_mutex));
    	//std::cout << "Soy el thread " << (int) pthread_self() << std::endl;
        if (lah->archivos.empty()){
			pthread_mutex_unlock(&(lah->arch_mutex));
			pthread_exit(NULL);
		} else {
			arch = lah->archivos.back();
			lah->archivos.pop_back();
			//std::cout << "Soy el thread " << (int) pthread_self() << " y estoy en el archivo" << arch << std::endl;
			pthread_mutex_unlock(&(lah->arch_mutex));
			add_words(lah->hashMap, arch);
		}
	}
}


ConcurrentHashMap ConcurrentHashMap::count_words(unsigned int n, list<string> archs){
	ConcurrentHashMap h;
	lista_archivos_hashmap lah;
	lah.hashMap = &h;
	lah.archivos = archs;
	pthread_mutex_init(&lah.arch_mutex, NULL);

	int i;
	pthread_attr_t attr;
	void* status;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	vector<pthread_t*> threads;
	for (i = 0; i < n; i++){
		pthread_t* nuevoThread = new pthread_t();
		threads.push_back(nuevoThread);
	}

	for (i = 0; i < n; i++){
		pthread_create(threads[i], &attr, &load_archs, (void*) &lah);
	}

	pthread_attr_destroy(&attr);

	for (i = 0; i < n; i++){
		pthread_join(*threads[i], &status);
	}

	for (i = 0; i < n; i++){
		delete threads[i];
	}
    
    return h;
}

//Recibe un struct hashes_archivos y devuelve en ha.hashes un ConcurrentHashMap* por archivo
//con las palabras cargadas.
void* hash_archs(void* _ha){
	hashes_archivos* ha = (hashes_archivos*) _ha;
	string arch;
	while (true){
    	pthread_mutex_lock(&(ha->arch_mutex));
    	//std::cout << "Soy el thread " << (int) pthread_self() << std::endl;
        if (ha->archivos.empty()){
			pthread_mutex_unlock(&(ha->arch_mutex));
			pthread_exit(NULL);
		} else {
			arch = ha->archivos.back();
			ha->archivos.pop_back();
			//std::cout << "Soy el thread " << (int) pthread_self() << " y estoy en el archivo" << arch << std::endl;
			pthread_mutex_unlock(&(ha->arch_mutex));
			//Crea el nuevo hashMap del archivo que le toca
			ConcurrentHashMap* h = new ConcurrentHashMap();
			add_words(h, arch);
			//Lo agrega a la lista hashes
			pthread_mutex_lock(&(ha->hashes_mutex));
			ha->hashes.push_back(h);
			pthread_mutex_unlock(&(ha->hashes_mutex));
		}
	}
}

//Toma un struct merge_struct y pone en mh.h el merge de los hashMaps de mh.hashes
void* merge_hashes(void* _ms){
	merge_struct* ms = (merge_struct*) _ms;
	int actual;
    while (true){
		//Dos threads nunca procesan el mismo archivo
		actual = ms->prox_hash.fetch_add(1);
	    if (actual >= ms->hashes.size() || actual < 0){
			pthread_exit(NULL);
		} else {
			ConcurrentHashMap* hashMap = ms->hashes[actual];
			//Cada thread recorre las listas en distinto orden (random), para mejorar concurrencia
			vector<int> orden(CANT_LETRAS);
			std::iota(orden.begin(), orden.end(), 0); //Llena el vector con 0, 1, ..., CANT_LETRAS
			auto engine = std::default_random_engine{};
			std::shuffle(orden.begin(), orden.end(), engine);
			
			//Recorre todas las listas en orden random y agrega los elementos a *h.
			for(int i = 0; i < orden.size(); i++){
				Lista<pair<string, unsigned int> >* lista = hashMap->tabla[orden[i]];
				for(auto it = lista->CrearIt(); it.HaySiguiente(); it.Avanzar()){
					pair<string, unsigned int>& sig = it.Siguiente();
					ms->h->addAndIncN(sig.first, sig.second);
				}
			}
			
		}
	}
}

pair<string, unsigned int> ConcurrentHashMap::maximum(unsigned int p_archivos,
													 unsigned int p_maximos, list<string> archs){
	hashes_archivos ha;
	//Inicializa el struct para construir el hashMap de cada archivo
	ha.archivos = archs;
	pthread_mutex_init(&ha.arch_mutex, NULL);
	pthread_mutex_init(&ha.hashes_mutex, NULL);

	int i;
	pthread_attr_t attr;
	void* status;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    //Crea p_archivos threads para crear los hashMaps
	vector<pthread_t*> threads;
	for (i = 0; i < p_archivos; i++){
		pthread_t* nuevoThread = new pthread_t();
		threads.push_back(nuevoThread);
	}

	for (i = 0; i < p_archivos; i++){
		pthread_create(threads[i], &attr, &hash_archs, (void*) &ha);
	}

	for (i = 0; i < p_archivos; i++){
		pthread_join(*threads[i], &status);
	}

	for (i = 0; i < p_archivos; i++){
		delete threads[i];
	}

	//Ya tengo en ha todos los hashMap de los archivos
	//Hago merge de los hashMaps
	
	ConcurrentHashMap mergeHash;	//Guarda el merge de los hashMaps
	//Inicializa el struct para mergear los hashMaps
	merge_struct ms;
	ms.h = &mergeHash;
	ms.hashes = ha.hashes;
	ms.prox_hash.store(0);

	for (i = 0; i < p_archivos; i++){
		pthread_t* nuevoThread = new pthread_t();
		threads[i] = nuevoThread;
	}

	for (i = 0; i < p_archivos; i++){
		pthread_create(threads[i], &attr, &merge_hashes, (void*) &ms);
	}

	pthread_attr_destroy(&attr);

	for (i = 0; i < p_archivos; i++){
		pthread_join(*threads[i], &status);
	}

	for (i = 0; i < p_archivos; i++){
		delete threads[i];
	}

	for(int i = 0; i < ha.hashes.size(); i++){
		delete ms.hashes[i];
	}

	//mergeHash ya tiene la suma todos los elementos de todos los hashMaps creados de archs.
	return mergeHash.maximum(p_maximos);
}

pair<string, unsigned int> ConcurrentHashMap::maximum_concurrente(unsigned int p_archivos,
													 unsigned int p_maximos, list<string> archs){
	ConcurrentHashMap hashMax = count_words(p_archivos, archs);
	return hashMax.maximum(p_maximos);
}

unsigned int ConcurrentHashMap::search(string key){
	char hash = key[0];
    auto it = tabla[char_to_pos(hash)]->CrearIt();

    while (it.HaySiguiente()){
        if (it.Siguiente().first == key){
        	return it.Siguiente().second;
        }
        it.Avanzar();
    }
    return -1;
}