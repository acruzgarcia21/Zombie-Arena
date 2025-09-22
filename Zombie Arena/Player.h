#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Player
{
private:
	// Starting Stats
	const float START_SPEED{ 200 };
	const float START_HEALTH{ 100 };

	// Player Stats
	int m_PlayerHealth;
	int m_PlayerMaxHealth;
	int m_PlayerSpeed;

	// Player Sprite and Texture
	Sprite m_PlayerSprite;
	Texture m_PlayerTexture;

	// When player was last hit
	Time m_PlayerLastHit;

	// Where is the player
	Vector2f m_Position;

	// Screen Resolution
	Vector2f m_Resolution;
	
	// Current Arena Size
	IntRect m_Arena;

	int m_TileSize;

	// Player Direction Booleans
	bool m_UpPressed;
	bool m_DownPressed;
	bool m_LeftPressed;
	bool m_RightPressed;

public:
	Player();

	// Prepares object for use, including putting it into starting position
	// 
	// IntRect& arena - Size and location of current level
	// Vector2f screenResolution - Contains screen resolution
	// int& - Contains size of background tile
	void spawn(IntRect&, Vector2f&, int&);

	// Resets players stats when new game is started
	void resetPlayerStats();

	// Handle the player getting hit
	bool playerHit(const Time&);

	// Getters
	Time getLastPlayerHitTime();
	FloatRect getPlayerPosition();
	Vector2f getPlayerCenter(); // Gets center of player sprite
	float getPlayerRotation(); // Gets what direction player is facing
	Sprite getPlayerSprite();
	int getPlayerHealth();

	// Player Movement Functions
	void playerMoveUp();
	void playerMoveDown();
	void playerMoveLeft();
	void playerMoveRight();

	// Player Stop Movement Functions
	void playerStopUp();
	void playerStopDown();
	void playerStopLeft();
	void playerStopRight();

	// Readies player object's data so it's ready for collision detection and drawing
	// 
	// const float& elapsedTime - Elapsed time since last frame was drawn
	// Vector2i& mousePositon - Contains what direction is the mouse facing
	void update(const float&, Vector2i&);

	// Give player speed and health
	void givePlayerSpeed();
	void givePlayerHealth();

	// Player Health Upgrade
	void upgradePlayerMaxHealth(int&);
};
