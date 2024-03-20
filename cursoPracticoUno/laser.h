#pragma once
#include "raylib.h"
#include <iostream>
#include <string>

using namespace std;

class Laser
{
private:

	Vector2 position;
	int speed;

public:
	 Laser(Vector2 position, int speed);
	~ Laser();

	void Update();
	void Draw();
	// creamos un estado de habilitacion para ver si el laser se encuentra activo o no
	bool active;
	Rectangle getRect();
};

 Laser::Laser(Vector2 _position, int _speed)
{
	 position = _position;
	 speed = _speed;
	 active = true;
}

 Laser::~Laser()
{
}

 void Laser::Draw() {
	 // dibujamos el laser junto a la posicion de en donde se encuentra

	 if (active)
	 {
		 DrawRectangle(position.x, position.y, 4, 15, { 243, 216, 63, 255 });
	 }

 }

 void Laser::Update() {

	 position.y += speed;
	 
	 if (active)
	 {

		 if (position.y > GetScreenHeight() - 100 || position.y < 25 ) {
			 active = false;

			 std::cout << "El laser esta fuera del perimetro" << endl;
		 }
	 }
 }


 Rectangle Laser::getRect() {

	 Rectangle rect;

	 rect.x = position.x;
	 rect.y = position.y;
	 rect.width = 4;
	 rect.height = 15;
	 return rect;
 }