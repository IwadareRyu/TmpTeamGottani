#include "PhysicsManager.h"
#include "AnimalBase.h"


void PhysicsManager::HandleCollisions() {
	accumulatedTime += Scene::DeltaTime();
	for (accumulatedTime += Scene::DeltaTime(); Physics::stepTime <= accumulatedTime; accumulatedTime -= Physics::stepTime)
	{
		//2D 物理演算のワールドを更新する
		world.update(Physics::stepTime);
	}
	for (size_t i = 0; i < bodys.size(); i++) {
		balls[i]->Update(bodys[i].getPos());
	}
	ground.draw(Palette::Green);
}

void PhysicsManager::CreateBall(Animal* newBall) {
	bodys << world.createCircle(P2Dynamic, newBall->GetPosition().xy(), newBall->GetSize() * 10, P2Material{2.0, 0.0, 1.0});
	balls.emplace_back(newBall);
}

void PhysicsManager::Draw() {
	for (const auto& ball : balls) {
		ball->Draw();
	}
	box.draw(ColorF{ 0.3, 0.8, 0.5 });
}
