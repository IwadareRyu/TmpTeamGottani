#include "stdafx.h"
#include "GameManager.h"

#include "Stage.h"
#include "Animal/AnimalCat.h"
#include "Animal/AnimalCollection.h"
#include "AnimalDataBase.h";

// GameManagerのコンストラクタ
GameManager::GameManager()
	: _player(nullptr),  // プレイヤーをnullptrで初期化
	  _stage(nullptr)    // ステージをnullptrで初期化
{
}

// GameManagerのデストラクタ
GameManager::~GameManager()
{
}

void GameManager::Awake()
{
	// 初期化処理
	_collection.StartAnimals();
}

void GameManager::Start()
{
	//最初に画像フォルダのテクスチャを配列にまとめる
	FilePathView directory = U"AnimalTexture";
	for (const auto& path : FileSystem::DirectoryContents(directory)) {
		const s3d::String extension = FileSystem::Extension(path);
		if (FileSystem::IsFile(path) && extension.lowercased() == U"png") {
			textures_.emplace_back(path);
		}
	}
	AnimalDataBase::GetInstance()->Init(textures_);
	// ステージの生成
	_stage = std::make_unique<Stage>(physics_manager,ui_manager);
	// プレイヤーの初期化、ステージを渡す
	_player = std::make_unique<Player>(_stage.get(), physics_manager);
	// ステージの初期化
	_stage->Initialize();
}

void GameManager::Update()
{
	switch (scene_manager->M_Scene())
	{
	case SceneState::TitleScene:
		ui_manager->UITitleUpdate();
		if (ui_manager->m_titleStartButton.ButtonClicked())
		{
			ui_manager->ResetUI();
			physics_manager->AnimalReset();
			scene_manager->ChangeScene(SceneState::GameScene, true);
		}
		break;

	case SceneState::GameScene:
		ui_manager->UIGameUpdate();
		// プレイヤーの更新
		_player->Update();

		// 毎フレームの動物の更新処理
		_collection.UpdateAnimals();
		physics_manager->HandleCollisions();
		physics_manager->Draw();

		// ステージの更新処理
		_stage->Update();

		if (ui_manager->ChackTime())
		{
			ui_manager->UIResultInit();
			GameEnd();
		}
		break;
	case SceneState::ResultScene:
		ui_manager->UIResultUpdate();
		if (ui_manager->m_returnTitleButton.ButtonClicked())
		{
			scene_manager->ChangeScene(SceneState::TitleScene, true);
			GameTitle();
		}
	}
}

void GameManager::Draw()
{
	if (scene_manager->M_Scene() == SceneState::GameScene)
	{
		// 描画処理
		_collection.DrawAnimals();
		_player->Draw();

		// ステージの描画処理
		_stage->Draw();
	}
	scene_manager->FadeUpdate();
}

void GameManager::GameStart()
{
}

void GameManager::GameEnd()
{
	scene_manager->ChangeScene(SceneState::ResultScene, true);
}

void GameManager::GameQuit()
{
	delete _stage->animal_union;
	physics_manager->AnimalReset();
	delete physics_manager;
	delete scene_manager;
	delete ui_manager;
}

void GameManager::GameRestart()
{
}

void GameManager::GamePause()
{
}

void GameManager::GameResume()
{
}

void GameManager::GameStop()
{
}

void GameManager::GameTitle()
{
}
