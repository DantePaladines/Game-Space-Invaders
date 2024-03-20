#pragma once
#include "raylib.h"


class Block
{

private:

	Vector2 position;

public:
	Block(Vector2);
	~Block();

	// crear metodo para el bloque

	void Draw();

	Rectangle getRect();

};

Block::Block( Vector2 _positon )
{

	position = _positon;

}

Block::~Block()
{
}

void Block::Draw() {

	DrawRectangle( position.x, position.y, 3, 3, {243, 216, 63, 255});

}


Rectangle Block::getRect() {
	Rectangle rect;

	rect.x = position.x;
	rect.y = position.y;
	rect.width = 3;
	rect.height = 3;
	return rect;
}