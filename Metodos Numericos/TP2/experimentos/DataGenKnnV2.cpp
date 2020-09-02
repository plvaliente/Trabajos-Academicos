#include "../entrega/Metodos.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std::chrono;
using namespace std;

int main(){
	string out5 = "DataFile10F-KnnV2";

	string in = "outKNNV2-k1";
	ObtenerData(out5, in);
	in = "outKNNV2-k3";
	ObtenerData(out5, in);
	in = "outKNNV2-k5";
	ObtenerData(out5, in);
	in = "outKNNV2-k7";
	ObtenerData(out5, in);
	in = "outKNNV2-k10";
	ObtenerData(out5, in);
	in = "outKNNV2-k15";
	ObtenerData(out5, in);
	in = "outKNNV2-k20";
	ObtenerData(out5, in);
	in = "outKNNV2-k30";
	ObtenerData(out5, in);
	in = "outKNNV2-k50";
	ObtenerData(out5, in);
	/*ObtenerData(out10, in);
	in = "filesExpKNN/Kfold10/outKNNb3";
	ObtenerData(out10, in);
	in = "filesExpKNN/Kfold10/outKNNb5";
	ObtenerData(out10, in);
	in = "filesExpKNN/Kfold10/outKNNb7";
	ObtenerData(out10, in);
	in = "filesExpKNN/Kfold10/outKNNb10";
	ObtenerData(out10, in);
	in = "filesExpKNN/Kfold10/outKNNb15";
	ObtenerData(out10, in);
	in = "filesExpKNN/Kfold10/outKNNb20";
	ObtenerData(out10, in);
	in = "filesExpKNN/Kfold10/outKNNb30";
	ObtenerData(out10, in);
	in = "filesExpKNN/Kfold10/outKNNb50";
	ObtenerData(out10, in);
*/
	
	return 0;
}