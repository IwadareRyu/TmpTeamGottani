#pragma once

// Stageクラスの前方宣言
class Stage;
class PhysicsManager;
#include "Animal/AnimalBase.h"
#include "AnimalDataBase.h"

class Player
{
private:
	Texture texture_{ U"example/Cursor.png" };
	Vec2 animal_pos = { 400, 100 };
	Vec2 cursor_pos = { 300, -100 };

	std::unique_ptr<Animal> current_animal_;
	Stage* stage_ = nullptr;  // Stageへのポインタ
	PhysicsManager* physics_manager;
	AnimalDataBase* animal_database = AnimalDataBase::GetInstance();
	AnimalDataBase::AnimalData current_texture = *(animal_database->animal_data[0]);

public:
	// Stageポインタを受け取るコンストラクタ
	Player(Stage* stage, PhysicsManager* physics) : stage_(stage), physics_manager(physics){}

	void Start();
	void Update();
	void Draw() const;

	// 動物をドロップする処理
	void DropAnimal();

	// 現在の動物をセット
	void SetAnimal(std::unique_ptr<Animal> animal)
	{
		current_animal_ = std::move(animal);
	}
	// プレイヤーの現在位置を取得
	const Vec2& GetPosition() const { return cursor_pos; }
};
