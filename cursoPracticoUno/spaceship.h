#pragma once
#include <raylib.h>
#include "laser.h"
#include <vector>

class Spaceship
{
private:
	// es una estructura de datos que representa una imagen (lo que es graficos)
	Texture2D image;
	// nos sirve para psosicionar el objeto en pantalla
	Vector2 position;
	double ultimoDisparo; 
	Sound laserSound;


public:
	Spaceship(); // este es un constructor
	~Spaceship(); // este es un destructor

	void Draw();
	void MoveLeft();
	void MoveRight();
	void FireLaser();
	// guardamos objetos laser al vector para luego ser utilizado
	std::vector<Laser> lasers;

	Rectangle getRect();

	void Reset();

};

Spaceship::Spaceship()
{
	// esta funcion nois permite cargar la imagen del objeto
	image = LoadTexture("graphis/spaceship.png");
	position.x = (GetScreenWidth() - image.width) / 2; // calculamos el valor de la posicion x 
	position.y = GetScreenHeight() - image.height - 100; // calculamos el valor de la posicion y 
	ultimoDisparo = 0.0;

	laserSound = LoadSound("graphis/laser.ogg");

}

Spaceship::~Spaceship()
{
	// esta funcion nos permite descargar (eliminar de la memoria de espacio) la imagen del objeto
	UnloadTexture(image);
	UnloadSound(laserSound);

}

void Spaceship::Draw() {
	// nos permite dibujar la textura en una posicion especifica utilizando vector2
	DrawTextureV(image, position, WHITE);

}

void Spaceship::MoveLeft() {
	position.x -= 7;
	
	// agregamos una condicion de si llega a cero el objeto se detendra en esa posicion que se cumplio
	if (position.x < 25)
	{
		position.x = 25;
	}
}

void Spaceship::MoveRight() {
	position.x += 7;

	// agregamos una condicion de si llega a cero el objeto se detendra en esa posicion que se cumplio
	if (position.x > GetScreenWidth() - image.width - 25)
	{
		position.x = GetScreenWidth() - image.width - 25;
	}
}


void Spaceship::FireLaser() {

	if ( GetTime() - ultimoDisparo >= 0.35 )
	{
		// creamos objetos laser y lo almacenamos en un vector de tipo lasers teniendo sus posiciones y velocidad
		lasers.push_back(Laser({ position.x + image.width / 2 - 2,position.y }, -6));

		ultimoDisparo = GetTime();

		PlaySound(laserSound);
	}

}

Rectangle Spaceship::getRect() {

	return { position.x, position.y, float(image.width), float(image.height) };
}


void Spaceship::Reset() {

	position.x = (GetScreenWidth() - image.width) / 2.0;
	position.y = GetScreenHeight() - image.height - 100;
	
	lasers.clear();
}

