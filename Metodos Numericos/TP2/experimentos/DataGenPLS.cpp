#include "../entrega/Metodos.h"
#include <iostream>
#include <fstream>
#include <ostream>

using namespace std;

int main(){
	string out10k1 = "filesPLS/DataPLSk1F10";
	string out10k3 = "filesPLS/DataPLSk3F10";
	string out10k5 = "filesPLS/DataPLSk5F10";
	string out5k1 = "filesPLS/DataPLSk1F5";
	string out5k3 = "filesPLS/DataPLSk3F5";
	string out5k5 = "filesPLS/DataPLSk5F5";

	string in = "filesPLS/out10FoldsK1gamma1";
	ObtenerData(out10k1, in);
	in = "filesPLS/out10FoldsK1gamma5";
	ObtenerData(out10k1, in);
	in = "filesPLS/out10FoldsK1gamma10";
	ObtenerData(out10k1, in);
	in = "filesPLS/out10FoldsK1gamma20";
	ObtenerData(out10k1, in);
	in = "filesPLS/out10FoldsK1gamma30";
	ObtenerData(out10k1, in);
	in = "filesPLS/out10FoldsK1gamma40";
	ObtenerData(out10k1, in);
	in = "filesPLS/out10FoldsK1gamma50";
	ObtenerData(out10k1, in);

	in = "filesPLS/out10FoldsK3gamma1";
	ObtenerData(out10k3, in);
	in = "filesPLS/out10FoldsK3gamma5";
	ObtenerData(out10k3, in);
	in = "filesPLS/out10FoldsK3gamma10";
	ObtenerData(out10k3, in);
	in = "filesPLS/out10FoldsK3gamma20";
	ObtenerData(out10k3, in);
	in = "filesPLS/out10FoldsK3gamma30";
	ObtenerData(out10k3, in);
	in = "filesPLS/out10FoldsK3gamma40";
	ObtenerData(out10k3, in);
	in = "filesPLS/out10FoldsK3gamma50";
	ObtenerData(out10k3, in);
	
	in = "filesPLS/out10FoldsK5gamma1";
	ObtenerData(out10k5, in);
	in = "filesPLS/out10FoldsK5gamma5";
	ObtenerData(out10k5, in);
	in = "filesPLS/out10FoldsK5gamma10";
	ObtenerData(out10k5, in);
	in = "filesPLS/out10FoldsK5gamma20";
	ObtenerData(out10k5, in);
	in = "filesPLS/out10FoldsK5gamma30";
	ObtenerData(out10k5, in);
	in = "filesPLS/out10FoldsK5gamma40";
	ObtenerData(out10k5, in);
	in = "filesPLS/out10FoldsK5gamma50";
	ObtenerData(out10k5, in);

	in = "filesPLS/out5FoldsK1gamma1";
	ObtenerData(out5k1, in);
	in = "filesPLS/out5FoldsK1gamma5";
	ObtenerData(out5k1, in);
	in = "filesPLS/out5FoldsK1gamma10";
	ObtenerData(out5k1, in);
	in = "filesPLS/out5FoldsK1gamma20";
	ObtenerData(out5k1, in);
	in = "filesPLS/out5FoldsK1gamma30";
	ObtenerData(out5k1, in);
	in = "filesPLS/out5FoldsK1gamma40";
	ObtenerData(out5k1, in);
	in = "filesPLS/out5FoldsK1gamma50";
	ObtenerData(out5k1, in);

	in = "filesPLS/out5FoldsK3gamma1";
	ObtenerData(out5k3, in);
	in = "filesPLS/out5FoldsK3gamma5";
	ObtenerData(out5k3, in);
	in = "filesPLS/out5FoldsK3gamma10";
	ObtenerData(out5k3, in);
	in = "filesPLS/out5FoldsK3gamma20";
	ObtenerData(out5k3, in);
	in = "filesPLS/out5FoldsK3gamma30";
	ObtenerData(out5k3, in);
	in = "filesPLS/out5FoldsK3gamma40";
	ObtenerData(out5k3, in);
	in = "filesPLS/out5FoldsK3gamma50";
	ObtenerData(out5k3, in);
	
	in = "filesPLS/out5FoldsK5gamma1";
	ObtenerData(out5k5, in);
	in = "filesPLS/out5FoldsK5gamma5";
	ObtenerData(out5k5, in);
	in = "filesPLS/out5FoldsK5gamma10";
	ObtenerData(out5k5, in);
	in = "filesPLS/out5FoldsK5gamma20";
	ObtenerData(out5k5, in);
	in = "filesPLS/out5FoldsK5gamma30";
	ObtenerData(out5k5, in);
	in = "filesPLS/out5FoldsK5gamma40";
	ObtenerData(out5k5, in);
	in = "filesPLS/out5FoldsK5gamma50";
	ObtenerData(out5k5, in);


	return 0;
}