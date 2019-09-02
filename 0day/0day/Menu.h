#pragma once
#include <glew.h>
#include "InputManager.h"
#include "TextManager.h"
#include "GameManager.h"

enum SceneState {
	START_MENU,
	DEMO_START,
	DECK_SELECTION,
	OPTION_MENU,
	END_MENU
};

class CMenu {
public:
	CMenu();
	~CMenu();
	CMenu(std::vector<std::string> _OptVect, glm::vec2 Pos, Game* _Game);
	void IncrementMenu();
	void DecrementMenu();
	int GetCurrentOpt() { return CurrentOption; };
	void ReplaceOption(int _OptIndex, std::string _OptionText);
	void SelectOption(unsigned int _Option);
	void Process(int& _Option);
	void Render();
	
private:
	std::vector<CTextLabel> OptionVect;

	GLuint TextShader;
	int NumMenuOptions;
	int CurrentOption;
};