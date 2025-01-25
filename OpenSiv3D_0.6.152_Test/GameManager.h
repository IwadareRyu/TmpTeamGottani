#pragma once
#include "Player.h"
#include "Singleton.h"
#include "Animal/AnimalCollection.h"
#include "Animal/PhysicsManager.h"
#include "SceneController.h"
#include "UIManager.h"

class GameManager : public Singleton<GameManager>
{
public:


	GameManager();
	~GameManager();

	void Awake();
	void Start();
	void Update();
	void Draw();

	void GameStart();
	void GameEnd();
	void GameQuit();
	void GameRestart();
	void GamePause();
	void GameResume();

	void GameStop();
	void GameTitle();


private:
	std::unique_ptr<Player> _player;  // プレイヤー
	AnimalCollection _collection;     // 動物コレクション
	std::unique_ptr<Stage> _stage;    // ステージ
	PhysicsManager* physics_manager = new PhysicsManager();
	Array<Texture> textures_;
	SceneController* scene_manager = new SceneController();
	UIManager* ui_manager = new UIManager();
};
