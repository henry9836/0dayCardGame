#include "InputManager.h"

unsigned char CInputManager::KeyArray[255];
unsigned char CInputManager::KeySpecialArray[255];
unsigned int CInputManager::MouseArray[3];

CInputManager::CInputManager() {
	for (int i = 0; i < 255; ++i) {
		KeyArray[i] = KEY_RELEASED;
		KeySpecialArray[i] = KEY_RELEASED;
	}
	for (int i = 0; i < 3; ++i) MouseArray[i] = KEY_RELEASED;
}

void CInputManager::ProcessKeyInput(float _DeltaTime)
{
	for (int i = 0; i < 255; ++i) {
		if (KeyArray[i] == KEY_FIRST_PRESS) {
			KeyArray[i] = KEY_HELD;
		}
		if (KeySpecialArray[i] == KEY_FIRST_PRESS) {
			KeySpecialArray[i] = KEY_HELD;
		}
	}
	glutSpecialFunc(CInputManager::SpecialKeyDown);
	glutSpecialUpFunc(CInputManager::SpecialKeyUp);
	glutKeyboardFunc(CInputManager::NormKeyDown);
	glutKeyboardUpFunc(CInputManager::NormKeyUp);
}

void CInputManager::ProcessKeyInput()
{

	//UP KEY INPUT
	if (KeySpecialArray[GLUT_KEY_UP] == KEY_HELD) {
		//Held Stuff
	}
	else if (KeySpecialArray[GLUT_KEY_UP] == KEY_FIRST_PRESS) {
		KeySpecialArray[GLUT_KEY_UP] = KEY_HELD;
	}

	//LEFT KEY INPUT
	if (KeySpecialArray[GLUT_KEY_LEFT] == KEY_HELD) {
		//Held Stuff
	}
	else if (KeySpecialArray[GLUT_KEY_LEFT] == KEY_FIRST_PRESS) {
		KeySpecialArray[GLUT_KEY_LEFT] = KEY_HELD;
	}

	//RIGHT KEY INPUT
	if (KeySpecialArray[GLUT_KEY_RIGHT] == KEY_HELD) {
		//Held Stuff
	}
	else if (KeySpecialArray[GLUT_KEY_RIGHT] == KEY_FIRST_PRESS) {
		KeySpecialArray[GLUT_KEY_RIGHT] = KEY_HELD;
	}

	//DOWN KEY INPUT
	else if (KeySpecialArray[GLUT_KEY_DOWN] == KEY_HELD) {
		//Held Stuff
	}
	else if (KeySpecialArray[GLUT_KEY_DOWN] == KEY_FIRST_PRESS) {
		KeySpecialArray[GLUT_KEY_DOWN] = KEY_HELD;
	}

	//UP KEY INPUT
	if (KeyArray['w'] == KEY_HELD) {
		//Held Stuff
	}
	else if (KeyArray['w'] == KEY_FIRST_PRESS) {
		KeyArray['w'] = KEY_HELD;
	}

	//LEFT KEY INPUT
	else if (KeyArray['a'] == KEY_HELD) {
		//Held Stuff
	}
	else if (KeyArray['a'] == KEY_FIRST_PRESS) {
		KeyArray['a'] = KEY_HELD;
	}

	//RIGHT KEY INPUT
	else if (KeyArray['d'] == KEY_HELD) {
		//Held Stuff
	}
	else if (KeyArray['d'] == KEY_FIRST_PRESS) {
		KeyArray['d'] = KEY_HELD;
	}

	//DOWN KEY INPUT
	else if (KeyArray['s'] == KEY_HELD) {
		//Held Stuff
	}
	else if (KeyArray['s'] == KEY_FIRST_PRESS) {
		KeyArray['s'] = KEY_HELD;
	}

	//ENTER KEY INPUT
	if (KeyArray['\r'] == KEY_HELD) {

	}
	else if (KeyArray['\r'] == KEY_FIRST_PRESS) {
		KeyArray['\r'] = KEY_HELD;
	}

	//SPACE KEY INPUT
	if (KeyArray['f'] == KEY_HELD) {

	}
	else if (KeyArray['f'] == KEY_FIRST_PRESS) {
		KeyArray['f'] = KEY_HELD;
	}

	glutSpecialFunc(CInputManager::SpecialKeyDown);
	glutSpecialUpFunc(CInputManager::SpecialKeyUp);
	glutKeyboardFunc(CInputManager::NormKeyDown);
	glutKeyboardUpFunc(CInputManager::NormKeyUp);
}

void CInputManager::NormKeyDown(unsigned char key, int x, int y) {
	KeyArray[key] = KEY_FIRST_PRESS;
}

void CInputManager::NormKeyUp(unsigned char key, int x, int y) {
	KeyArray[key] = KEY_RELEASED;
}

void CInputManager::SpecialKeyDown(int key, int x, int y) {
	KeySpecialArray[key] = KEY_FIRST_PRESS;
}

void CInputManager::SpecialKeyUp(int key, int x, int y) {
	KeySpecialArray[key] = KEY_RELEASED;
}

