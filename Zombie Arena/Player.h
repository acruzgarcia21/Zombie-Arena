#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Player
{
private:
	const float START_SPEED{ 200 };
	const float START_HEALTH{ 100 };

	// Where is the player
	Vector2f m_Position;

	// Player Sprite and Texture
	Sprite m_PlayerSprite;
	Texture m_PlayerTexture;

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
	
	// How much player health has
	int m_PlayerHealth;
	// What's the max health the player can have
	int m_MaxPlayerHealth;


};
