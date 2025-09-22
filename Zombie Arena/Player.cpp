#include "Player.h"

Player::Player() : m_PlayerHealth(START_HEALTH), m_PlayerMaxHealth(START_HEALTH), m_PlayerSpeed(START_SPEED)
, m_PlayerTexture(), m_PlayerSprite(m_PlayerTexture)
{
	if (!m_PlayerTexture.loadFromFile("graphics/player.png"))
	{
		throw std::runtime_error("Failed to load player texture!");
	}
	m_PlayerSprite.setOrigin(Vector2f(25.0f, 25.0f));
}

void Player::spawn(IntRect& arena, Vector2f& screenResolution, int& tileSize)
{
	int arenaWidth  = arena.size.x;
	int arenaHeight = arena.size.y;

	// Place the player in the middle of the arena
	this->m_Position.x = arenaWidth / 2;
	this->m_Position.y = arenaHeight / 2;

	// Copy parameter arena info into player arena
	this->m_Arena.position.x = arena.position.x; // Left
	this->m_Arena.position.y = arena.position.y; // Top
	this->m_Arena.size.x     = arena.size.x;     // Width
	this->m_Arena.size.y     = arena.size.y;     // Height

	// Stores tile size
	this->m_TileSize = tileSize;

	// Store the resolution for future use

}