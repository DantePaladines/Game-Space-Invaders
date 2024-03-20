#pragma once
#include <vector>
#include <iostream>
#include "block.h"

using namespace std;


class Obstacule
{

private:

public:

	Vector2 position;
	std::vector<Block> blocks;
	// lo colocamos en static para asi poder acceder a el sin tener que crear un objeto
	static std::vector<std::vector<int>> grid;

	Obstacule(Vector2);
	~Obstacule();
	
	// creamos metodo para dibujar el obstaculo

	void Draw();

};

std::vector<std::vector<int>> Obstacule:: grid = {
   {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
   {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
   {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
   {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1}
};

Obstacule::Obstacule(Vector2 _position)
{

	position = _position;

	// si el bloque lo queremos modificar utilizamos bucles normales 
	for (int row = 0; row < grid.size(); ++row)
	{
		// este for nos permite saber la longitud en columnas del gird
		// lo que hacemos es llamar a grid en la posicion 0 y llamar a la funcion size.
		for (int column = 0; column < grid[0].size(); ++column) {
			if ( grid[row][column] == 1)
			{	
				// calcula la coordenada x del bloque en funcion del numero de cuadricula
				// luego se multiplica por tres para determinar posicion correcta para el bloque
				float pos_x = position.x + column * 3;
				// calcula la coordenada y del bloque en funcion del numero de cuadricula
				// luego se multiplica por tres para determinar posicion correcta para el bloque
				float pos_y = position.y + row * 3;

				// la condicion cumple con lo acordado se crea un objeto de bloque 
				Block block({ pos_x, pos_y });

				blocks.push_back(block);
			}
		}
	}

}

Obstacule::~Obstacule()
{
}

void Obstacule::Draw() {
	// utilizamos el for rango para recorrer los objetos y dibujarlos en pantalla
	for (auto& block : blocks )
	{
		block.Draw();
	}

}