#pragma once
#include "raylib.h"


class MysteryNave
{
public:
	MysteryNave();
	~MysteryNave();

	void Draw();
	void Update();
	void Spawn();

	bool alive;

	Rectangle getRect();

private:

	Texture2D image;
	Vector2 position;
	int speed;

};

MysteryNave::MysteryNave()
{

	image = LoadTexture("graphis/mystery.png");
	//position.x = (GetScreenWidth() - image.width) / 2; // calculamos el valor de la posicion x 
	//position.y = GetScreenHeight() - image.height; // calculamos el valor de la posicion y 
	alive = false;
}

MysteryNave::~MysteryNave()
{

	UnloadTexture(image);

}

void MysteryNave::Spawn() {
	position.y = 90;

	// punto de partida aleatorio

	int side = GetRandomValue(0, 1);

	if (side == 0)
	{
		position.x = 25;

		speed = 2;
	}
	else
	{
		position.x = GetScreenWidth() - image.width - 25;
		speed = -2;
	}

	alive = true;

}

void MysteryNave::Update() {
	if (alive)
	{
		position.x += speed;

		if (position.x > GetScreenWidth() - image.width - 25 || position.x < 25 )
		{
			alive = false;
		}
	}
}

void MysteryNave::Draw() {

	if (alive)
	{
		DrawTextureV(image, position, WHITE);
	}

}

Rectangle MysteryNave::getRect() {

	if (alive)
	{
		return {
			position.x,
			position.y,
			float(image.width),
			float(image.height)
		};
	}
	else
	{
		return { position.x, position.y, 0,0 };
	}

}