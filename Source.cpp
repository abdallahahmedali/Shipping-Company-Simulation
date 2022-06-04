#include <iostream>
#include "Cargos.h"
#include "NormalTruck.h"
#include "Company.h"
#include "UI.h"

using namespace std;

int main() {


	Company* cmp_ptr = new Company();
	UI* ui = new UI();
	cmp_ptr->readInputFile(ui);
	system("cls");

	ui->printMessage("Enter '1' for Interactive Mode\n");
	ui->printMessage("Enter '2' for Step By Step Mode\n");
	ui->printMessage("Enter '3' for Silent Mode\n");

	int Mode =  ui->getInteger();
	while(Mode!=1&&Mode!=2&&Mode!=3)
	{
		ui->printMessage("Please Try Again\n");
		ui->printMessage("Enter '1' for Interactive Mode\n");
		ui->printMessage("Enter '2' for Step By Step Mode\n");
		ui->printMessage("Enter '2' for Silent Mode\n");
		Mode=ui->getInteger();
	}
	cmp_ptr->simulateProgram(Mode,ui);
	if(Mode==3)
	{   
		ui->printMessage("Silent Mode \n");
		ui->printMessage("Simulation Starts ....\n");
		ui->printMessage("Simulation ends,Output file created\n");
	}
	cmp_ptr->printOutputFile(ui);

	delete cmp_ptr;
	delete ui;
	cmp_ptr = nullptr;
	ui = nullptr;

	return 0;
}