#pragma once
#include "Singleton.h"

class AnimalDataBase: public Singleton<AnimalDataBase> {
private:
	Array<Texture> animal_textures;

public:
	struct AnimalData {
	public:
		AnimalData(Texture texture, int size, int score) :texture_(texture), size_(size), score_(score) {}
		~AnimalData() {};
		Texture texture_;
		int size_;
		int score_;
	};
	enum AnimalType {
		snake,		//ヘビ
		parrot,		//トリ
		rabbit,		//ウサギ
		penguin,	//ペンギン
		monkey,		//サル
		panda,		//パンダ
		pig,		//ブタ
		hippo,		//カバ
		giraffe,	//キリン
		elephant,	//ゾウ
	};
	AnimalDataBase() {}
	~AnimalDataBase() {};

	Array<AnimalData*> animal_data;

	void Init(Array<Texture> texture) {
		animal_textures = std::move(texture);
		animal_data = {
			new AnimalData(animal_textures[0], 2, 10),
			new AnimalData(animal_textures[1], 3, 20),
			new AnimalData(animal_textures[2], 4, 30),
			new AnimalData(animal_textures[3], 5, 40),
			new AnimalData(animal_textures[4], 6, 50),
			new AnimalData(animal_textures[5], 7, 60),
			new AnimalData(animal_textures[6], 8, 70),
			new AnimalData(animal_textures[7], 9, 80),
			new AnimalData(animal_textures[8], 10, 90),
			new AnimalData(animal_textures[9], 11, 100),
		};
	};
};
