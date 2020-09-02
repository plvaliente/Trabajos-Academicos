#include "ConcurrentHashMap.hpp"
#include <cassert>

using namespace std;

typedef struct ag_int{
	Lista<int>* l;
	int nums[3];
}ag_int;

typedef struct s_addMember{
	ConcurrentHashMap* h;
	int caso;
}s_addMember;

bool buscar(Lista<int>* l, int n){
	auto it = l->CrearIt();
	while (it.HaySiguiente()){
        if (it.Siguiente() == n){
        	return true;
        }
        it.Avanzar();
    }
    return false;
}

void* agregarLista(void* s_n){
	ag_int* s = (ag_int*) s_n;
	for(int i = 0; i < 3; i++){
		s->l->push_front(s->nums[i]);
		assert(buscar(s->l, s->nums[i]));
	}
	pthread_exit(NULL);
}


void test_push_front(int rep){
	for(int j = 0; j < rep; j++){	
		Lista<int> l;
		assert(!buscar(&l, 0));
		assert(!buscar(&l, 1));
		assert(!buscar(&l, 2));
		assert(!buscar(&l, 3));

		pthread_t threads[2];
		ag_int s_uno;
		s_uno.l = &l;
		s_uno.nums[0] = 0;
		s_uno.nums[1] = 2;
		s_uno.nums[2] = 4;
		
		ag_int s_cero;
		s_cero.l = &l;
		s_cero.nums[0] = 1;
		s_cero.nums[1] = 3;
		s_cero.nums[2] = 5;

		pthread_attr_t attr;
		void* status;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
		pthread_create(&threads[0], &attr, &agregarLista, (void*) &s_cero);
		pthread_create(&threads[1], &attr, &agregarLista, (void*) &s_uno);

		pthread_join(threads[0], &status);
		pthread_join(threads[1], &status);

		for(int i = 0; i < 6; i++){
			assert(buscar(&l, i));
		}
	}	
	cout << "test_push_front OK!" << endl;
}

void* aux_add_member_1(void* _h){
	ConcurrentHashMap* h = (ConcurrentHashMap*) _h;
	h->addAndInc("chau");
	assert(h->member("chau"));
	h->addAndInc("hello");
	assert(h->member("hello"));
	h->addAndInc("danke");
	assert(h->member("danke"));

}

void* aux_add_member_2(void* _h){
	ConcurrentHashMap* h = (ConcurrentHashMap*) _h;
	h->addAndInc("chau");
	assert(h->member("chau"));
	h->addAndInc("hi");
	assert(h->member("hi"));
	h->addAndInc("bonjour");
	assert(h->member("bonjour"));

}

void* aux_add_member_3(void* _h){
	ConcurrentHashMap* h = (ConcurrentHashMap*) _h;
	h->addAndInc("sistemas");
	assert(h->member("sistemas"));
	h->addAndInc("sistemas");
	assert(h->member("sistemas"));
	h->addAndInc("nadieMiraEstosTests");
	assert(h->member("nadieMiraEstosTests"));
	h->addAndInc("sistemas");
	assert(h->member("sistemas"));
	h->addAndInc("nadieMiraEstosTests");
	assert(h->member("nadieMiraEstosTests"));

}

void test_hashMap(int rep){
	for(int j = 0; j < rep; j++){
		ConcurrentHashMap h;
		h.addAndInc("hola");

		assert(h.member("hola"));
		assert(!h.member("chau"));
		assert(!h.member("hello"));
		assert(!h.member("danke"));
		assert(!h.member("hi"));
		assert(!h.member("bonjour"));
		assert(!h.member("nadieMiraEstosTests"));
		assert(!h.member("sistemas"));
		pthread_t threads[3];

		pthread_attr_t attr;
		void* status;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

		pthread_create(&threads[0], &attr, &aux_add_member_1, (void*) &h);
		pthread_create(&threads[1], &attr, &aux_add_member_2, (void*) &h);
		pthread_create(&threads[2], &attr, &aux_add_member_3, (void*) &h);

		pthread_join(threads[0], &status);
		pthread_join(threads[1], &status);
		pthread_join(threads[2], &status);

		assert(h.member("chau"));
		assert(h.member("hello"));
		assert(h.member("danke"));
		assert(h.member("hi"));
		assert(h.member("bonjour"));
		assert(h.member("nadieMiraEstosTests"));
		assert(h.member("sistemas"));

		pair<string, unsigned int> maxInicial("sistemas", 3);
		for (int i = 1; i <= 10; ++i){
			assert(maxInicial == h.maximum(i));	
		}
		
		h.addAndInc("nadieMiraEstosTests");
		h.addAndInc("nadieMiraEstosTests");
		
		pair<string, unsigned int> maxFinal("nadieMiraEstosTests", 4);
		for (int i = 1; i <= 10; ++i){
			assert(maxFinal == h.maximum(i));	
		}
	}
	cout << "test_hashMap OK!" << endl;
}

vector<string> hashToVec(ConcurrentHashMap* h){
	std::vector<string> v;
	for(int i=0; i < 26; i++){
		auto it = h->tabla[i]->CrearIt();
		while (it.HaySiguiente()){
			string s = it.Siguiente().first + to_string(it.Siguiente().second);
			v.push_back(s);
			it.Avanzar();
		}	
	}
	sort(v.begin(), v.end());
	return v;
}

void test_count_words(int rep){
	for(int j = 0; j < rep; j++){
		list<string> archs6 = { "pal6_0.txt", "pal6_1.txt", "pal6_2.txt", "pal6_3.txt", "pal6_4.txt" };
		list<string> archs10 = { "pal10_0.txt", "pal10_1.txt", "pal10_2.txt"};
		string arch30 = "palabrasTest.txt";

		ConcurrentHashMap h1 = ConcurrentHashMap::count_words(arch30);
		ConcurrentHashMap h2 = ConcurrentHashMap::count_words(archs6);
		ConcurrentHashMap h3 = ConcurrentHashMap::count_words(archs10);
		
		vector<string> v1 = hashToVec(&h1);
		vector<string> v2 = hashToVec(&h2);
		vector<string> v3 = hashToVec(&h3);
		
		assert(v1 == v2);
		assert(v1 == v3);

		vector<string> v_i_1;
		vector<string> v_i_2;
		for(int i = 1; i <= 10; i++){
			ConcurrentHashMap h_i_1 = ConcurrentHashMap::count_words(i, archs6);
			ConcurrentHashMap h_i_2 = ConcurrentHashMap::count_words(i, archs10);
		
			v_i_1 = hashToVec(&h_i_1);
			v_i_2 = hashToVec(&h_i_2);

			assert(v1 == v_i_1);
			assert(v1 == v_i_2);
		}
	}
	cout << "test_count_words OK!" << endl;
}

void test_maximum(int rep){
	for (int k = 0; k < rep; ++k){
		string arch30 = "palabrasTest.txt";
		list<string> archs6 = { "pal6_0.txt", "pal6_1.txt", "pal6_2.txt", "pal6_3.txt", "pal6_4.txt" };
		list<string> archs10 = { "pal10_0.txt", "pal10_1.txt", "pal10_2.txt"};
		
		ConcurrentHashMap h = ConcurrentHashMap::count_words(arch30);
		
		pair<string, unsigned int> maxInicial("duck", 4);
		for (int i = 1; i <= 10; ++i){
			assert(maxInicial == h.maximum(i));
		}

		for(int i = 1; i <= 10; i++){
			for(int j = 1; j <= 10; j++){
				assert(maxInicial == ConcurrentHashMap::maximum(i, j, archs6));
				assert(maxInicial == ConcurrentHashMap::maximum(i, j, archs10));
				assert(maxInicial == ConcurrentHashMap::maximum_concurrente(i, j, archs6));
				assert(maxInicial == ConcurrentHashMap::maximum_concurrente(i, j, archs10));
			}
		}
	}	
	cout << "test_maximum OK!" << endl;
}

int main(){
	int rep = 50;
	test_push_front(rep);
	test_hashMap(rep);
	test_count_words(rep);
	test_maximum(rep);
	return 0;

}