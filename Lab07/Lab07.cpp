#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
using namespace std;
using namespace sf;
using namespace sfp;
int main()
{
	// Create our window and world with gravity 0,1
	RenderWindow window(VideoMode(800, 600), "Bounce");
	World world(Vector2f(0, 1));
	
	// Create the ball
	PhysicsCircle ball;
	ball.setCenter(Vector2f(250, 200));
	ball.setRadius(20);
	world.AddPhysicsBody(ball);
	ball.applyImpulse(Vector2f(.3, .5));
	// Create the floor
	
	PhysicsRectangle floor;
	floor.setSize(Vector2f(760, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);
	
	//Creating Left Wall
	PhysicsRectangle Leftwall;
	Leftwall.setSize(Vector2f(20, 700));
	Leftwall.setCenter(Vector2f(10, 300));
	Leftwall.setStatic(true);
	world.AddPhysicsBody(Leftwall);
	

	//Creating Right Wall
	PhysicsRectangle Rightwall;
	Rightwall.setSize(Vector2f(20, 760));
	Rightwall.setCenter(Vector2f(790, 300));
	Rightwall.setStatic(true);
	world.AddPhysicsBody(Rightwall);
	
	
	//Creating Roof
	PhysicsRectangle Roof;
	Roof.setSize(Vector2f(760, 20));
	Roof.setCenter(Vector2f(400,10));
	Roof.setStatic(true);
	world.AddPhysicsBody(Roof);
	

	//square in the middle
	PhysicsRectangle square;
	square.setSize(Vector2f(100, 100));
	square.setCenter(Vector2f(400, 300));
	square.setStatic(true);
	world.AddPhysicsBody(square);
	int bangCount(0);
	square.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
		bangCount++;
		cout << "bang " << bangCount << endl;
		if (bangCount==3)
			{
			exit(0);
		}
	};
	//thud counts
	int thudCount(0);
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		thudCount++;
		cout << "thud " << thudCount << endl;
		};
	Leftwall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		thudCount++;
		cout << "thud " << thudCount << endl;
	};
	Rightwall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		thudCount++;
		cout << "thud " << thudCount << endl;
	};
	Roof.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		thudCount++;
		cout << "thud " << thudCount << endl;
	};

	

	Clock clock;
	Time lastTime(clock.getElapsedTime());
	while (true) {
		// calculate MS since last frame
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}
		window.clear(Color(0, 0, 0));
		window.draw(ball);
		window.draw(floor);
		window.draw(Leftwall);
		window.draw(Rightwall);
		window.draw(Roof);
		window.draw(square);
		window.display();
	}
}
