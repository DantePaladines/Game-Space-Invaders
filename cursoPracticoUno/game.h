#pragma once
#include "spaceship.h"
#include <iostream>
#include "obstacule.h"
#include "alien.h"
#include "mysteryNave.h"
#include "fstream"

using namespace std;

// la clase juego debe de crear y mntener la nave espacial
class Game
{
public:
	Game();
	~Game();

	// metodos

	void Draw(); // el metodo draw dibujara todos los objetos del jeugo
	void Update(); // actualizara las posicion de todos los objetos del juego
	void HandleInput(); // maneja l entrada del jugador
	int vida;
	bool run;
	int score;
	int highscore;

	Music music;

private:
	Spaceship spaceship;
	MysteryNave mysterynave;
	std::vector<Obstacule> obstacles;
	std::vector<Alien> aliens;
	std::vector<Obstacule> CreateObstacles();// invstigar un poco mas de los vectores
	std::vector<Alien> CreateAliens();
	void DeleteInactiveLaser();
	void SaveHighScoreToFile( int highScore );

	int LoadHighScoreFromFile();

	void MoveAliens();
	void MoveDownAliens(int distance);

	int aliensDirection;

	// creamos un vector para los lacers de los aliens

	std::vector<Laser> aliensLasers;

	void AlienShootLaser();

	constexpr static float AlienLaserShooterInterval = 0.35;
	float timeLastAlienFired;

	float mysteryShipSpawnInterval;
	float timeLastSpawn;

	void CheckForCollisions();
	void GameOver();

	void Reset();

	void InitGame();

	void checkForHighScore();

	Sound explointSound;

};

Game::Game()
{

	//obstacles = CreateObstacles();
	//aliens = CreateAliens();
	//aliensDirection = 1;
	//timeLastAlienFired = 0.0;
	//mysterynave.Spawn();

	//timeLastSpawn = 0.0;

	//mysteryShipSpawnInterval = GetRandomValue(10, 2);
	//vida = 3;
	//run = true;

	music = LoadMusicStream("graphis/music.ogg");
	explointSound = LoadSound("graphis/explosion.ogg");
	PlayMusicStream(music);
	InitGame();
}

Game::~Game()
{
	Alien::UnloadImages();
	UnloadMusicStream(music);
	UnloadSound(explointSound);

}

void Game::Update() {
	// actualizamos los laser creados

	if (run)
	{

		float currenTime = GetTime();
		if (currenTime - timeLastSpawn > mysteryShipSpawnInterval)
		{
			mysterynave.Spawn();

			timeLastSpawn = GetTime();

			mysteryShipSpawnInterval = GetRandomValue(10, 2);
		}


		for (auto& laser : spaceship.lasers)
		{
			laser.Update();
		}

		MoveAliens();

		DeleteInactiveLaser();

		mysterynave.Update();

		AlienShootLaser();

		CheckForCollisions();

		for (auto& laser : aliensLasers)
		{
			laser.Update();
		}

		std::cout << "Tamanho del vector " << spaceship.lasers.size() << endl;

	}
	else
	{
		if ( IsKeyDown(KEY_ENTER) )
		{
			Reset();
			InitGame();
		}
	}
}

void Game::Draw() {
	// dibujamos los laser creados
	for ( auto& laser : spaceship.lasers )
	{
		laser.Draw();

	}
	// creamos for de rango
	for  ( auto& obstacule : obstacles )
	{
		obstacule.Draw();
	}

	// creamos un for de rango 

	for (auto& alien : aliens )
	{
		alien.Draw();
	}

	// dibijamos los laser en pantalla

	for (auto& laser : aliensLasers)
	{
		laser.Draw();
	}

	spaceship.Draw();

	mysterynave.Draw();

}

void Game::HandleInput() {

	if (run)
	{

		if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
			spaceship.MoveLeft();
		}
		else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
			spaceship.MoveRight();
		}
		else if (IsKeyDown(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			spaceship.FireLaser();
		}

	}
};

void Game::DeleteInactiveLaser() {

	for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();)
	{
		if (!it->active)
		{
			it = spaceship.lasers.erase(it);
		}
		else
		{
			++it;
		}
	}

	for (auto it = aliensLasers.begin(); it != aliensLasers.end();)
	{
		if (!it->active)
		{
			it = aliensLasers.erase(it);
		}
		else
		{
			++it;
		}
	}

};

// esta funcion nos permite crear los obstaculos

std::vector<Obstacule> Game::CreateObstacles() {

	// calculamos cuantas columnas tiene la cuadricula
	float obstacleWidth = Obstacule::grid[0].size() * 3;
	// calculamos los espacios de los cuatro bloques
	float gap = (GetScreenWidth() - (4 * obstacleWidth)) / 5;

	for (int i = 0; i < 4; i++)
	{
		// esta linea de codigo calcula la posicion de cada obstaculo agregando espacios iguales entre ellos
		float offsetx = (i + 1) * gap + i * obstacleWidth;

		obstacles.push_back(Obstacule({ offsetx, float(GetScreenHeight() - 200)}));
	}

	return obstacles;
};

// esta funcion nos permite crear los aliens 

std::vector<Alien> Game::CreateAliens() {


	for (int row = 0; row < 5; row++)
	{
		for (int column = 0; column < 11; column++)
		{
			float x = 150 + column * 55;
			float y = 110 + row * 55;

			int alienType;

			if (row == 0)
			{
				alienType = 3;
			}
			else if (row == 1 || row == 2)
			{
				alienType = 2;
			}
			else {
				alienType = 1;
			}

			aliens.push_back(Alien(alienType, { x, y }));

		}
	}

	return aliens;
}

// implementar el movimiento del los alienigenas

void Game::MoveAliens() {

	for ( auto& alien : aliens )
	{

		if ( alien.position.x + alien.alienImages[alien.type -1].width > GetScreenWidth() - 25)
		{
			aliensDirection = -1;
			MoveDownAliens(4);
		}
		if (alien.position.x < 25)
		{
			aliensDirection = 1;
			MoveDownAliens(4);
		}

		alien.Update(aliensDirection);
	}

}

void Game::MoveDownAliens( int distance) {

	for (auto& alien : aliens) {

		alien.position.y += distance;
	}

}

// creando el laser del extraterrestre 

void Game::AlienShootLaser() {

	double currenTime = GetTime();

	if (currenTime - timeLastAlienFired >= AlienLaserShooterInterval && !aliens.empty() )
	{
		int randomIndex = GetRandomValue(0, aliens.size() - 1);

		Alien& alien = aliens[randomIndex];

		aliensLasers.push_back(Laser({ alien.position.x + alien.alienImages[alien.type - 1].width / 2, alien.position.y + alien.alienImages[alien.type - 1].height }, 6));

		timeLastAlienFired = GetTime();
	}

}

void Game::CheckForCollisions() {

	// spaceship laser

	for ( auto& laser : spaceship.lasers )
	{
		// apunta a al comienzo del vector ed aliens
		auto it = aliens.begin();

		while (it != aliens.end() )
		{
			if ( CheckCollisionRecs(it -> getRect(), laser.getRect() ) ) {

				PlaySound(explointSound);

				if (it -> type == 1)
				{
					score += 100;
				}
				else if (it -> type == 2)
				{
					score += 200;
				}
				else if( it -> type == 3 )
				{
					score += 300;
				}
				checkForHighScore();

				it = aliens.erase(it);

				laser.active = false;

			}
			else
			{
				++it;
			}
		}

		for ( auto& obstacule : obstacles )
		{
			auto it = obstacule.blocks.begin();

			while (it != obstacule.blocks.end())
			{
				if (CheckCollisionRecs(it->getRect(), laser.getRect())) {

					it = obstacule.blocks.erase(it);

					laser.active = false;
				}
				else
				{
					++it;
				}
			}
		}

		if (CheckCollisionRecs(mysterynave.getRect(), laser.getRect() ))
		{
			mysterynave.alive = false;
			laser.active = false;

			score += 500;

			checkForHighScore();
			PlaySound(explointSound);
		}

	}

	//aliens laser

	for ( auto& laser : aliensLasers)
	{
		if(CheckCollisionRecs( laser.getRect(), spaceship.getRect() ) ){

			laser.active = false;

			vida--;

			if (vida == 0)
			{
				GameOver();
			}

			std::cout << "laser en colision" << endl;
		}

		for (auto& obstacule : obstacles)
		{
			auto it = obstacule.blocks.begin();

			while (it != obstacule.blocks.end())
			{
				if (CheckCollisionRecs(it->getRect(), laser.getRect())) {

					it = obstacule.blocks.erase(it);

					laser.active = false;
				}
				else
				{
					++it;
				}
			}
		}

	}


	// alien colision con obstaculos

	for ( auto& alien : aliens )
	{
		for ( auto& obstacule : obstacles )
		{
			auto it = obstacule.blocks.begin();

			//while (it != obstacule.blocks.end())
			{
				//if (CheckCollisionRecs(it->getRect(), alien.getRect()))
				{
					//it = obstacule.blocks.erase(it);
				}
				//else
				{
					//++it;
				}
			}

			for ( auto it = obstacule.blocks.begin(); it != obstacule.blocks.end() ;)
			{
				if ( CheckCollisionRecs(it -> getRect(), alien.getRect() ))
				{
					it = obstacule.blocks.erase(it);
				}
				else
				{
					++it;
				}
			}

		}

		if (CheckCollisionRecs( alien.getRect(), spaceship.getRect()))
		{
			GameOver();
			std::cout<< "El alien choco con la nave" << std:: endl;
		}

	}

}


void Game::GameOver() {
	
	run = false;
	
	//std::cout << "Te eliminaron" << endl;
}

void Game::InitGame() {

	obstacles = CreateObstacles();
	aliens = CreateAliens();
	aliensDirection = 1;
	timeLastAlienFired = 0.0;
	//mysterynave.Spawn();

	timeLastSpawn = 0.0;

	mysteryShipSpawnInterval = GetRandomValue(10, 2);
	vida = 3;
	run = true;
	// cargamos el juegos con la puntuacion mas alta
	highscore = LoadHighScoreFromFile();
	score = 0;

}

void Game::Reset() {

	spaceship.Reset();
	aliens.clear();
	aliensLasers.clear();
	obstacles.clear();

}

void Game::checkForHighScore() {


	if (score > highscore)
	{
		highscore = score;

		SaveHighScoreToFile(highscore);
	}
}

// implementando el puntaje alto guardando en un archivo txt

void Game::SaveHighScoreToFile(int highScore) {

	std::ofstream highScoreFile("highScore.txt");

	if (highScoreFile.is_open())
	{
		highScoreFile << highScore;

		highScoreFile.close();
	}
	else
	{
		std::cerr << "Fallo el guardado de las puntuaciones" << endl;
	}

}
// cargamos la puntuacion alta 
int Game::LoadHighScoreFromFile() {

	int loadedHighscore = 0;

	std::ifstream highScoreFile("highScore.txt");

	if (highScoreFile.is_open() )
	{
		highScoreFile >> loadedHighscore;

		highScoreFile.close();
	}
	else
	{
		std::cerr << "Fallo al cargar la puntuacion" << endl;
	}

	return loadedHighscore;
}