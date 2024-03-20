// cursoPracticoUno.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include <raylib.h>
#include "spaceship.h"
#include "game.h"
#include "laser.h"
#include "obstacule.h"
#include "alien.h"
#include "mysteryNave.h"

using namespace std;


std::string FormatWithLeadingZeros(int number, int width) {
	std::string numberText = std::to_string(number);
	int leadingZeros = width - numberText.length();
	return numberText = std::string(leadingZeros, '0') + numberText;
}

int main()
{

	// todo obejto que se construye se debe de destruir

	// insertamos color a la pantalla de juego
	Color grey = { 29, 29, 27, 255 };
	// color amarillo para el marco
	Color yellow = { 243, 216, 63, 255 };

	// definimos el ancho y largo de la pantalla
	int offset = 50;
	int windowWith = 800;
	int windowHeight = 700;
	int fps = 120;

	// iniciamos la ventana del juego
	InitWindow(windowWith + offset, windowHeight + 2 * offset, "Mi primer juego");
	InitAudioDevice();

	// cargamos la fuente

	Font font = LoadFontEx("graphis/monogram.ttf", 64, 0, 0);
	Texture2D imgNave = LoadTexture("graphis/spaceship.png");

	// esta funcion nos permite agrgar una cantidad de fotogramas en la que correra el juego
	SetTargetFPS(fps);

	// creamos un objeto

	//Spaceship spaceship;

	Game game;

	//Alien alien = Alien( 2, {100, 100});

	//Obstacule obstacule({100, 100});

	//Laser laser({ 100, 100 }, -7);

	while (WindowShouldClose() == false)
	{

		UpdateMusicStream(game.music);

		//SetTraceLogLevel(LOG_ERROR);

		game.HandleInput();
		//laser.Update();
		game.Update();

		// nos permite crear un liezo (como si fuera una hoja en donde dibujaremos los objetos)
		BeginDrawing();

		ClearBackground(grey);
		//spaceship.Draw();
		DrawRectangleRoundedLines({ 10, 10, 830, 785 }, 0.18f, 20, 2, yellow);
		DrawLineEx({ 60, 730 }, { 775, 730 }, 3, yellow);

		if (game.run)
		{
			DrawTextEx(font, "LEVEL 01", { 570, 740 }, 34, 2, yellow);
		}
		else
		{
			DrawTextEx(font, "Game Over", { 570, 740 }, 34, 2, yellow);
		}

		// mostrar las vidas del jugador

		float x = 50.0;

		for (int i = 0; i < game.vida; i++)
		{
			DrawTextureV(imgNave, {x, 745}, WHITE);

			x += 50;
		}

		DrawTextEx(font, "SCORE", { 50, 15 }, 34, 2, yellow);
		std::string scoreText = FormatWithLeadingZeros(game.score, 5);
		DrawTextEx(font, scoreText.c_str(), { 50,40 }, 32, 4, yellow);

		// creando puntuacion alta

		DrawTextEx(font, "HIGH-SCORE", { 570,15 }, 34, 2, yellow);
		std::string highScore = FormatWithLeadingZeros(game.highscore, 5);
		DrawTextEx(font, highScore.c_str(), { 655,40 }, 34, 2, yellow);

		game.Draw();
		//laser.Draw();
		//obstacule.Draw();

		//alien.Draw();

		// finaliza el dibujo del lienzo
		EndDrawing();

	}

	// cerramos la ventana del juego
	CloseWindow();
	CloseAudioDevice();

}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
