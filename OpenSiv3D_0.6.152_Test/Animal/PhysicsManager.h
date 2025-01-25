#pragma once

namespace Physics {
	constexpr double stepTime = (1.0 / 200);
	constexpr double gravity = 98;
}
class Animal;

class PhysicsManager
{
private:
	P2World world{ Physics::gravity };

public:
	PhysicsManager() {}
		~PhysicsManager() {};
	void HandleCollisions();

	void CreateBall(Animal* animal);
	void Draw();
	void AnimalReset();
	std::vector<Animal*> GetBalls(){ return balls; }

	Array<P2Body> bodys;
	P2Body ground = world.createLine(P2Static, Vec2{ 0, 0 }, Line{ -300, 0, 300, 0 });
	std::vector<Animal*> balls;
	double accumulatedTime = 0.0;
	const P2Body box = world.createPolygon(P2Static, Vec2{ 400, 400 }, LineString{ Vec2{-300, -200}, Vec2{-300, 200}, Vec2{300, 200}, {Vec2{300, -200}} }.calculateBuffer(5), P2Material{ .friction = 0.0 });

};
