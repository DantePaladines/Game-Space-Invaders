#pragma once
#include <vector>
#include "raylib.h"

class Alien
{
public:
	Alien( int, Vector2);
	~Alien();

	void Draw();
	void Update( int direction);
	int GetType();
	static Texture2D alienImages[3];

	static void UnloadImages();

	Vector2 position;
	int type;
	Rectangle getRect();

private:

	//Texture2D image;



};

Texture2D Alien::alienImages[3] = {};

Alien::Alien(int _type, Vector2 _position)
{	

	position = _position;
	type = _type;

	if (alienImages[type -1].id == 0)
	{

		switch (type)
		{
		case 1:
			alienImages[0] = LoadTexture("graphis/alien_1.png");

			break;

		case 2:
			alienImages[1] = LoadTexture("graphis/alien_2.png");

			break;

		case 3:
			alienImages[2] = LoadTexture("graphis/alien_3.png");

			break;
		default:
			alienImages[0] = LoadTexture("graphis/alien_1.png");
			break;
		}


	}


	// estas posiciones nos sirve para colocar el personaje en medio
	//position.x = (GetScreenWidth() - image.width) / 2;
	//position.y = GetScreenHeight() - image.height;
}

Alien::~Alien()
{

	//UnloadTexture(image);

}

void Alien::Draw() 
{
	DrawTextureV(alienImages[type -1], position, WHITE);
}

int Alien::GetType() 
{
	return type;
}

void Alien::UnloadImages() {

	for (int i = 0; i < 4; i++)
	{
		UnloadTexture(alienImages[i]);
	}

}

void Alien::Update(int direction) {
	position.x += direction;
}

Rectangle Alien::getRect() {
	return {
		position.x,
		position.y,
		float(alienImages[type - 1].width),
		float(alienImages[type - 1].height)
	};
}