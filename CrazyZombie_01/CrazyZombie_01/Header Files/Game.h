#ifndef GAME_H
#define GAME_H


#include "State.h"

/*
	Class that's like Game Engines
*/

class Game
{
private:

	//Time & Clock (Framrates independent system)
	sf::Clock clock;
	float dt;
	sf::Clock elapseClock;
	float elpsTime;
	float timeMultiplier;
	float dtForSpeed;

	//Windows & Events
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	
	//Mouse Position
	sf::Vector2i mousePosWindow;

	//Resource (Textures, Bullets)
	std::map<std::string , sf::Texture*> textures;
	std::vector<Bullet*> bullets; 

	//Fonts & Text
	sf::Font font_superSpace;
	sf::Text score_text;
	sf::Text hp_text;
	sf::Text enemiesKilled_text;
	

	// Score System
	float scores;

	// World & background
	sf::Sprite WorldBackground;
	sf::Texture WorldBackgroundTex;

	// Player
	Player* player;
	
	// Enemies & spawntimer
	float spawnTimerMax;
	float spawnTimer;
	std::vector<Enemy*> enemies;

	//Items
	std::vector<Items*> items_vector;


	//Initiation Functions (these functs should be inside Game() Constructor)
	void initScoreBoard();
	void initScore();
	void initFonts();
	void initGui();
	void initScoreText(); // (init in initGui() )
	void initHPText(); // (init in initGui() )
	void initEnemiesKilledText(); // (init in initGui() )
	void initTextures();
	void initVariables();
	void initWindow();
	void initEnemies();
	void initPlayer();
	void initItems();
	void initBackground();
	 
public:
	Game();
	virtual ~Game();

	//Accessors
	const bool running();

	/////////////
	//Functions//
	/////////////

	//Essentials
	void deltaTime();
	void pollEvents();
	void updatePollEvents();
	void updateInput();
	void updateElapseTime();
	void updateBoundsCollision();
	void updateMousePosition();

	// Updaters (all of these functs should be in update() )
	void updatePlayer();
	void updateEnemies();
	void updateSpawnEnemies();
	void updateSpawnItems();
	void updateBullets();
	void updateCombat();
	void updateItems();
	// Updaters Score & Text
	void updateScore(); // Scores
	void updateGui(); // Gui
	void updateScoreText(); // (updating in updateGUI()) 
	void updateHPText(); // (updating in updateGUI())
	void updateEnemiesKilledText(); // (updating in updateGUI())

	//Objects Renderers
	void renderWorld(); // World
	void renderPlayer(); // Player
	void renderEnemies(); // Enemies
	void renderBullets(); // Bullets
	void renderItems(); // Items
	void renderGui(sf::RenderTarget& target); //Gui
	
	// Actions
	void player_shoot();
	
	// Game End
	void game_ends_due_to_player_dies();
	
	//Logging
	void consolelog(bool log = true); // Change false to true for console logging

	// main Renderer & Update (Called in main)
	void update();
	void render();
};

#endif // !GAME_H
