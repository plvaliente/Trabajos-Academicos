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
	string out10 = "filesExpKNN/DataFile10Fold";
	string out5 = "filesExpKNN/DataFile5Fold";

	string in = "filesExpKNN/Kfold10/outKNNb1";
	ObtenerData(out10, in);
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

	in = "filesExpKNN/Kfold5/outKNN1";
	ObtenerData(out5, in);
	in = "filesExpKNN/Kfold5/outKNN3";
	ObtenerData(out5, in);
	in = "filesExpKNN/Kfold5/outKNN5";
	ObtenerData(out5, in);
	in = "filesExpKNN/Kfold5/outKNN7";
	ObtenerData(out5, in);
	in = "filesExpKNN/Kfold5/outKNN10";
	ObtenerData(out5, in);
	in = "filesExpKNN/Kfold5/outKNN15";
	ObtenerData(out5, in);
	in = "filesExpKNN/Kfold5/outKNN20";
	ObtenerData(out5, in);
	in = "filesExpKNN/Kfold5/outKNN30";
	ObtenerData(out5, in);
	in = "filesExpKNN/Kfold5/outKNN50";
	ObtenerData(out5, in);
	return 0;
}