#include <time.h>
#include "Util.h"
#include "GameManager.h"


int main(int argc, char** argv) {

	//Initalise Console Controller
	Banner();
	srand((unsigned int)time(NULL));

	//Start Game
	Start(argc, argv);

	system("pause");

	return 0;

}