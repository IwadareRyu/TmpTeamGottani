#pragma once

#include "Player.h"  // Playerクラスを完全にインクルード
#include "Animal/AnimalCollection.h"
#include "AnimalUnion.h"
#include <Siv3D.hpp>

class PhysicsManager;

class Stage
{
private:
	AnimalCollection animal_container_;  // 動物を格納するコンテナ
	RectF drop_zone_;                    // プレイヤーが動物を落とせる場所
	Line border_line_;                   // ボーダーライン
	std::unique_ptr<Animal> next_animal_; // 次の動物
	//std::unique_ptr<Player> player_;      // プレイヤー

public:
	Stage(PhysicsManager* physics,UIManager* ui);

	void Initialize();
	void Update();
	void Draw() const;

	// 箱の位置とサイズを取得
	const RectF& GetDropZone() const { return drop_zone_; }

	// プレイヤーが動物をステージに追加するための関数
	void AddAnimalToStage(std::unique_ptr<Animal> animal);

	bool IsAnimalBeyondBorder(const Animal& animal) const;
	PhysicsManager* physics_manager;
	UIManager* ui_manager;
	AnimalUnion* animal_union = nullptr;
};
