#include "ConcurrentHashMap.hpp"
#include <chrono>

#define LARGO_LST 10
#define REP 30

using namespace std;
using namespace std::chrono;


void tester(list<string> lst){
auto tStart = high_resolution_clock::now();
auto tEnd = high_resolution_clock::now();
auto acumT = high_resolution_clock::now();
auto acTime1 = chrono::duration_cast<std::chrono::microseconds>(tStart-tStart);
auto acTime2 = chrono::duration_cast<std::chrono::microseconds>(tStart-tStart);
auto aux = chrono::duration_cast<std::chrono::microseconds>(tEnd-tStart);

tStart = high_resolution_clock::now();
	for(int i = 1; i <= 10; i++){
			acTime1 = chrono::duration_cast<std::chrono::microseconds>(tStart-tStart);
			acTime2 = chrono::duration_cast<std::chrono::microseconds>(tStart-tStart);
			for(int j = 1; j <= REP; j++){
				tStart = high_resolution_clock::now();
				ConcurrentHashMap::maximum(i, LARGO_LST, lst);
				tEnd = high_resolution_clock::now();
				aux = chrono::duration_cast<std::chrono::microseconds>(tEnd-tStart);
				acTime1 = acTime1 + aux;

				tStart = high_resolution_clock::now();
				ConcurrentHashMap::maximum_concurrente(i, LARGO_LST, lst);
				tEnd = high_resolution_clock::now();
				aux = chrono::duration_cast<std::chrono::microseconds>(tEnd-tStart);
				acTime2 = acTime2 + aux;
			}
			cout << chrono::duration_cast<std::chrono::microseconds>(acTime1).count() / REP
			<< ", " << chrono::duration_cast<std::chrono::microseconds>(acTime2).count() / REP << endl;
		}
}

int	main(){
	list<string> l_I_10 = { "INs/iguales10", "INs/iguales10", "INs/iguales10", "INs/iguales10", "INs/iguales10", "INs/iguales10", "INs/iguales10", "INs/iguales10", "INs/iguales10", "INs/iguales10"};			
	list<string> l_I_100 = { "INs/iguales100", "INs/iguales100", "INs/iguales100", "INs/iguales100", "INs/iguales100", "INs/iguales100", "INs/iguales100", "INs/iguales100", "INs/iguales100", "INs/iguales100"};			
	list<string> l_I_1000 = { "INs/iguales1000", "INs/iguales1000", "INs/iguales1000", "INs/iguales1000", "INs/iguales1000", "INs/iguales1000", "INs/iguales1000", "INs/iguales1000", "INs/iguales1000", "INs/iguales1000"};			
	
	list<string> l_Rnd_10 = { "INs/rnd10_0", "INs/rnd10_1", "INs/rnd10_2", "INs/rnd10_3", "INs/rnd10_4", "INs/rnd10_5", "INs/rnd10_6", "INs/rnd10_7", "INs/rnd10_8", "INs/rnd10_9" };
	list<string> l_Rnd_100 = { "INs/rnd100_0", "INs/rnd100_1", "INs/rnd100_2", "INs/rnd100_3", "INs/rnd100_4", "INs/rnd100_5", "INs/rnd100_6", "INs/rnd100_7", "INs/rnd100_8", "INs/rnd100_9" };
	list<string> l_Rnd_1000 = { "INs/rnd1000_0", "INs/rnd1000_1", "INs/rnd1000_2", "INs/rnd1000_3", "INs/rnd1000_4", "INs/rnd1000_5", "INs/rnd1000_6", "INs/rnd1000_7", "INs/rnd1000_8", "INs/rnd1000_9" };


	cout << "ig10" << endl;
	tester(l_I_10);

	cout << "ig100" << endl;
	tester(l_I_100);

	cout << "ig1000" << endl;
	tester(l_I_1000);

	cout << "rnd10" << endl;
	tester(l_Rnd_10);

	cout << "rnd100" << endl;
	tester(l_Rnd_100);

	cout << "rnd1000" << endl;
	tester(l_Rnd_1000);

}
