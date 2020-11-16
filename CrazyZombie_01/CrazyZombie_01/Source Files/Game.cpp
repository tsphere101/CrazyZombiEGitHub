#include "Game.h"

//Private Functions Define
void Game::initVariables()
{
	this->window = nullptr;
	
}

void Game::initWindow()
{

	
	std::ifstream ifs("Config/window.ini");

	sf::Vector2i window_bounds;

	this->videoMode.height = 1080;
	this->videoMode.width = 1920;
	std::string title = "Crazy Zombie";
	unsigned framerate_limit = 144;
	bool vertical_sync_enable = false;

	if (ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> window_bounds.x >> window_bounds.y;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enable;

		this->videoMode.width = window_bounds.x;
		this->videoMode.height = window_bounds.y;
	}
	
	
	this->window = new sf::RenderWindow (this-> videoMode, title, sf::Style::Default | sf::Style::Close);
	this->window->setFramerateLimit(framerate_limit);
}

void Game::initEnemies()
{
	this->spawnTimer = 0;
	this->spawnTimerMax = 2;

	//Manual Spawn
	this->enemies.push_back(new Enemy(1, 1500.f, 450.f));
	this->enemies.push_back(new Enemy(2, 1500.f, 450.f));


}

void Game::initScoreBoard()
{

}

void Game::initScore()
{
	this->scores = 0;
}

void Game::initFonts()
{
	if (!this->font_superSpace.loadFromFile("fonts/Superspace.ttf"))
	{
		std::cout << "ERROR::GAME::INITFONTS::Failed to load font! \n";
	}
}

void Game::initGui()
{
	this->initScoreText();
	this->initHPText();
	this->initEnemiesKilledText();
}

void Game::initScoreText()
{
	this->score_text.setFont(this->font_superSpace);
	this->score_text.setString("Score : ");
	this->score_text.setCharacterSize(24);
	this->score_text.setFillColor(sf::Color::White);
	this->score_text.setPosition(100, 100);
}

void Game::initHPText()
{
	this->hp_text.setFont(this->font_superSpace);
	this->hp_text.setString("HP : ");
	this->hp_text.setCharacterSize(30);
	this->hp_text.setFillColor(sf::Color::Green);
	
	//this->hp_text.setPosition(100, 120);
}

void Game::initEnemiesKilledText()
{
	this->enemiesKilled_text.setFont(this->font_superSpace);
	this->enemiesKilled_text.setString("Enemies Killed : ");
	this->enemiesKilled_text.setCharacterSize(24);
	this->enemiesKilled_text.setFillColor(sf::Color::White);
	this->enemiesKilled_text.setPosition(100, 150);
}



void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("textures/peanutBullet.png");

}



void Game::initPlayer()
{
	this->player = new Player(400.f,500.f);
}

void Game::initItems()
{
	this->items_vector.push_back(new Items(2, 0, 800, 300));
	this->items_vector.push_back(new Items(1, 0, 950, 300));
	this->items_vector.push_back(new Items(1, 1, 1000, 300));
	this->items_vector.push_back(new Items(1, 2, 1050, 300));
}

//Constructors // Destructors Define
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initTextures();
	this->initBackground();
	this->initEnemies();
	this->initPlayer();
	this->initItems();
	this->initScoreBoard();
	this->initScore();
	this->initFonts();
	this->initGui();

	
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	//Delete textures;
	for (auto& i : this->textures)
	{
		delete i.second;
	}
	//Delete bullets;
	for (auto* i : this->bullets)
	{
		delete i;
	}
	//Delete Enemies
	for (auto* i : this->enemies)
	{
		delete i;
	}
	
}
//Acce
const bool Game::running()
{
	return this->window->isOpen();
}





void Game::deltaTime()
{
	this->dt = clock.restart().asSeconds();
	this->timeMultiplier = 144.f;
	this->dtForSpeed = this->dt * this->timeMultiplier;
}

//Funcs
void Game::pollEvents()
{
	while (this-> window -> pollEvent(this->ev))
	{
		switch (this-> ev.type)
		{
		case sf::Event::Closed :
			this->window->close();
			break;
		/*case sf::Event::KeyPressed:
		{
			if (this->ev.key.code == sf::Keyboard::Escape) 
				this->window->close();
			break;
			
		}*/
		}
		
		 
	}
}

void Game::updatePollEvents()
{

}

void Game::updateInput()
{
	//Keyboard Inputs
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-1.f,0.f, this->dtForSpeed);
	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(1.f, 0.f , this->dtForSpeed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(0.f, -1.f , this->dtForSpeed);
	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.f, 1.f , this->dtForSpeed);
	//Mouse Inputs
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->player_shoot();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		window->close(); // Edit here what ESC do
	}

}

void Game::updatePlayer()
{
	this->player->updateElpsTime(this->elpsTime);
	this->player->update();

	//Check if player dies
	if (this->player->getPlayerHp() <= 0)
	{
		game_ends_due_to_player_dies();
	}
}

void Game::player_shoot()
{
	if (this->player->canAttack())
	{
		this->bullets.push_back(new Bullet(this->textures["BULLET"],
			this->player->getPos().x + this->player->getBounds().width / 2.f,
			this->player->getPos().y + this->player->getBounds().height / 2.f,
			this->mousePosWindow.x,
			this->mousePosWindow.y,
			this->player->getAttackBulletSpeed(), // bullet speed
			this->player->getAttackBulletDamage() // bullet damage
		));
		this->player->updateAttackCooldown();
		
	}

}



void Game::updateGui()
{
	this->updateScoreText();
	this->updateHPText();
	this->updateEnemiesKilledText();
}

void Game::updateScore()
{
	if (this->player->getScore() < 0) //So score never below than 0
	{
		this->player->setScore(0);
	}
	this->scores = this->player->getScore();
}

void Game::renderPlayer()
{
	this->player->render(*this->window);
}



void Game::renderGui(sf::RenderTarget& target)
{
	target.draw(this->score_text);
	target.draw(this->hp_text);
	target.draw(this->enemiesKilled_text);
}

void Game::renderEnemies()
{
	for (auto* enemy : this->enemies)//Render Enemies
	{
		enemy->render(*this->window);
	}
}

void Game::renderBullets()
{
	for (auto* bullet : this->bullets) //Render Bullets
	{
		bullet->render(this->window);
	}
}

void Game::renderItems()
{
	for (int i = 0; i < this->items_vector.size(); i++)
	{
		this->items_vector[i]->render(*this->window);
	}
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update(this-> dtForSpeed); // Move the bullets

		//bullet culling top of the screen
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//Deleting bullets
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}

		++counter;
	}

}

void Game::updateSpawnEnemies()
{
	
	//spawn normal enemies
	if (this->elpsTime - this->spawnTimer >= this->spawnTimerMax)
	{
		//this->enemies.push_back(new Enemy(-500 + rand()%2000, -500 + rand() % 2000));

		int type;
		int randomType = rand() % 100;
		if (randomType >= 0 && randomType <= 25)
		{
			type = 1; // Fast Runner
		}
		else
		{
			type = 0; // Normal Zombie
		}
		int randomQuardant = rand() % 4;
		if (randomQuardant == 0)
		{
			this->enemies.push_back(new Enemy(type,1920 + rand() % 500, rand() % 1080));
		}
		else if (randomQuardant == 1)
		{
			this->enemies.push_back(new Enemy(type,rand() % 1920, -500 - (rand() % 500)));
		}
		else if (randomQuardant == 2)
		{
			this->enemies.push_back(new Enemy(type,-500 - (rand() % 500), rand() % 1080));
		}
		else if (randomQuardant == 3)
		{
			this->enemies.push_back(new Enemy(type,rand() % 1920, 1080 + (rand() % 500)));
		}

		this->spawnTimer = this->elpsTime;
		
	}
	//spawn Tank for every 50 Killed after previous tank killed
	
	
	if (this->player->getEnemmiesKilled() != 0 && (int)this->player->getEnemmiesKilled() % 50 == 0 )
	{
		int tanks_alive = 0;
		for (int i = 0; i < this->enemies.size(); i++) // Check how many tanks are alive
		{
			if (this->enemies[i]->getType() == 2)
				tanks_alive++;
				
		}
		if(tanks_alive == 0)
		this->enemies.push_back(new Enemy(2, this->window->getSize().x / 2.f, this->window->getSize().y / 2.0));
		
	}
	
}

void Game::updateSpawnItems()
{
}



void Game::updateEnemies()
{
	
	//Make every enemies moving toward player
	for (auto* enemy : this->enemies)
	{
		enemy->update(); // faceright or left
		enemy->move(this->player->getPos().x, this->player->getPos().y , this->dtForSpeed);
	}

}

void Game::updateCombat()
{
	//Check if the bullets collide the enemies
	

	for (int i = 0; i < this->enemies.size(); i++)
	{
		for (int k = 0; k < this->bullets.size(); k++)
		{
			if (this->bullets[k]->getBounds().intersects(this->enemies[i]->getBounds()))//Check if the bullet hits
			{
				this->enemies[i]->enemiesInjured(this->bullets[k]->getBulletDamage());
				this->bullets.erase(this->bullets.begin() + k);
			}
		}
	}
	
	//Check if zombie dies
	for (int i = 0; i < this->enemies.size(); i++)
	{
		if (this->enemies[i]->enemyHealth() <= 0)
		{
			this->player->giveEnemiesKilled(1);
			this->player->giveScore(this->enemies[i]->enemyPoint());
			enemies.erase(this->enemies.begin() + i);
		}
	}

	//Check if zombie bite player;
	for (int i = 0; i < this->enemies.size(); i++)
	{
		if (this->enemies[i]->getBounds().intersects(this->player->getBounds()))
		{
			this->player->get_hurt(this->enemies[i]->enemyDamage(), this->enemies[i]->enemyBiteScore());
			
		}
	}
}

void Game::updateItems() 
{
	for (int i = 0; i < this->items_vector.size(); i++)
	{
		this->items_vector[i]->update();
	}

	//Check if player picks up item 
	for (int i = 0; i < this->items_vector.size(); i++)
	{
		switch (items_vector[i]->getItemID())
		{
		// Heal pick up
		case 1: 
		{// check if the player is full or not & intersect
			bool hp_is_full;
			if (this->player->getPlayerHp() == this->player->getPlayerHpMax())
				hp_is_full = true;
			else hp_is_full = false;
			// check pick up
			if (this->player->getBounds().intersects(items_vector[i]->getBounds()) & !hp_is_full)
			{
				items_vector[i]->item_picked_up();
				this->player->useItem(items_vector[i]->getItemID(), items_vector[i]->getItemEffect());
				this->items_vector.erase(this->items_vector.begin() + i);
			}
			break;
		}
		// Resistance pick up
		case 2 :
		{
			// check if player already has resistance or not
			bool has_better_resist;
			if (this->player->getResistance() > items_vector[i]->getItemEffect())
				has_better_resist = true;
			else has_better_resist = false;
			// check pick up
			if (this->player->getBounds().intersects(items_vector[i]->getBounds()) & !has_better_resist)
			{
				items_vector[i]->item_picked_up();
				this->player->useItem(items_vector[i]->getItemID(), items_vector[i]->getItemEffect());
				this->player->setResistanceCoolDown(this->player->getElpsTime()); // trigger the countdown
				this->items_vector.erase(this->items_vector.begin() + i);
			} 
			break;
		}


		default:
			break;
		}
	}
}

void Game::updateBoundsCollision()
{
	//Check left window bound
	if (this->player->getPos().x < 0)
	{
		this->player->setPos(0, this->player->getPos().y);
	}
	//check right
	else if(this->player->getPos().x > this->window->getSize().x - this->player->getBounds().width)
	{
		this->player->setPos(this->window->getSize().x - this->player->getBounds().width, this->player->getPos().y);
	}
	//check upper
	if (this->player->getPos().y < 0)
	{
		this->player->setPos(this->player->getPos().x , 0);
	}
	//check bottom
	else if (this->player->getBounds().top + this->player->getBounds().height > this->window->getSize().y)
	{
		this->player->setPos( this->player->getPos().x , this->window->getSize().y - this->player->getBounds().height);
	}
}

void Game::updateMousePosition()
{
	//Mouse position relative to window
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->player->getMousePosWindow(mousePosWindow.x, mousePosWindow.y);
}

void Game::initBackground()
{
	if (!this->WorldBackgroundTex.loadFromFile("Xtextures/grass.png"))
	{
		std::cout << "INITBACKGROUND::WorldBackgroundTexture LOAD FROM FILE ERROR\n";
	}
	this->WorldBackground.setTexture(this->WorldBackgroundTex);
}

void Game::consolelog(bool log)
{
	if (log)
	{
		//std::cout << "dt: " << this->dt << " " <<
		//	"\t elps: " << this->player->getElpsTime() << std::endl;
		std::cout << "hp : " << this->player->getPlayerHp()<< "\t score : " << this->player->getScore() <<" Killed : " << this->player->getEnemmiesKilled()<< std::endl;
		
	}
}

void Game::game_ends_due_to_player_dies()
{
	this->window->close();
	//End
	
}

void Game::updateScoreText()
{
	std::stringstream _text;
	_text << "Score : " << this->scores;
	this->score_text.setString(_text.str());
	
}

void Game::updateHPText()
{
	if (this->player->lowHealth())
	{
		this->hp_text.setFillColor(sf::Color::Red);
	}
	else this->hp_text.setFillColor(sf::Color::White);
	this->hp_text.setPosition(this->player->getPos().x, this->player->getPos().y + 70.f);
	std::stringstream _text;
	_text << "HP : " << this->player->getPlayerHp();
	this->hp_text.setString(_text.str());
	
}

void Game::updateEnemiesKilledText()
{
	std::stringstream _text;
	
	_text << "Killed : " << this->player->getEnemmiesKilled();
	this->enemiesKilled_text.setString(_text.str());
}



void Game::renderWorld()
{
	this->window->draw(this->WorldBackground);
}

//Functions Define
void Game::update()
{ 
	this->deltaTime();

	this->pollEvents();

	this->updatePollEvents();

	this->updateInput();

	this->updatePlayer();

	this->updateBullets();

	this->updateItems();

	this->updateBoundsCollision();
	
	this->updateSpawnEnemies();

	this->updateEnemies();

	this->updateCombat();

	this->updateScore();

	this->updateGui();

	this->updateMousePosition();

	/*sf::RectangleShape player(sf::Vector2f(100.0f, 100.0f));
	player.setFillColor(sf::Color::Yellow);
	player.setOrigin(50.0f, 50.0f);
	player.setPosition(100.f, 100.f);
	/*
	std::cout << "Mouse Pos X : " << sf::Mouse::getPosition().x 
		<< "  Mouse Pos Y : " << sf::Mouse::getPosition().y << std::endl;
	*/
	/*
	std::cout << "Mouse Pos X : " << sf::Mouse::getPosition(*this->window).x
		<< "  Mouse Pos Y : " << sf::Mouse::getPosition(*this->window).y << std::endl; //to make it reference to window use *this->window
	*/
	
	this->updateElapseTime();

	this->consolelog();

}

void Game::render()
{
	
	this->window->clear(sf::Color::Black); // Window Clear

	//Render Game Objects
	this->renderWorld();//Render background
	this->renderEnemies(); // Render Enemies
	this->renderBullets(); // Render Bullets
	this->renderPlayer(); //Render Player
	this->renderItems(); // Render Items
	this->renderGui(*this->window); // Render Gui

	//Display
	this->window->display();

}

void Game::updateElapseTime()
{
	this->elpsTime = elapseClock.getElapsedTime().asSeconds();

}
