# include <Siv3D.hpp> // Siv3D v0.6.15

#include "GameManager.h"
#include "SceneController.h"
#include "UIManager.h"

void Main()
{

	SceneController* scene_manager = new SceneController();
	UIManager* ui_manager = new UIManager();
	GameManager::GetInstance()->Start();
	while (System::Update())
	{
		GameManager::GetInstance()->Update();
		GameManager::GetInstance()->Draw();
	}

	GameManager::GetInstance()->GameQuit();
}
