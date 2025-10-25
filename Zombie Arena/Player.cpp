#include "Player.h"
#include <numbers>

Player::Player() : m_PlayerHealth(START_HEALTH), m_PlayerMaxHealth(START_HEALTH),
m_PlayerSpeed(START_SPEED), m_PlayerTexture(), m_PlayerSprite(m_PlayerTexture), 
m_UpPressed(false), m_DownPressed(false), m_LeftPressed(false),
m_RightPressed(false), m_TileSize(0)
{
	if (!m_PlayerTexture.loadFromFile("graphics/player.png"))
	{
		throw std::runtime_error("Failed to load player texture!");
	}
	m_PlayerSprite.setOrigin(Vector2f(25.0f, 25.0f));
}

void Player::spawn(IntRect& arena, Vector2u& screenResolution, int& tileSize)
{
	int arenaWidth  = arena.size.x;
	int arenaHeight = arena.size.y;

	// Place the player in the middle of the arena regardless of size of sprite
	m_PlayerPosition.x = static_cast<float>(arenaWidth / 2);
	m_PlayerPosition.y = static_cast<float>(arenaHeight / 2);

	// Copy parameter arena info into player arena
	m_Arena.position.x = arena.position.x; // Left
	m_Arena.position.y = arena.position.y; // Top
	m_Arena.size.x     = arena.size.x;     // Width
	m_Arena.size.y     = arena.size.y;     // Height

	// Store the resolution for future use
	m_Resolution.x = screenResolution.x;
	m_Resolution.y = screenResolution.y;

	// Stores tile size
	m_TileSize = tileSize;
}
void Player::resetPlayerStats() // Called when player dies
{
	m_PlayerHealth    = START_HEALTH;
	m_PlayerMaxHealth = START_HEALTH;
	m_PlayerSpeed     = START_SPEED;
}
Time Player::getLastPlayerHitTime() const
{
	return m_PlayerLastHit;
}
bool Player::playerHit(const Time& timeHit)
{
	// Protects player from being hit multiple times in 1 second
	if (timeHit.asMilliseconds() - m_PlayerLastHit.asMilliseconds() > 200)
	{
		m_PlayerLastHit = timeHit;
		m_PlayerHealth -= 10;
		return true;
	}
	else
	{
		return false;
	}
}
// Getters
FloatRect Player::getPlayerPosition()
{
	return m_PlayerSprite.getGlobalBounds();
}
Vector2f Player::getPlayerCenter() const
{
	return m_PlayerPosition;
}
Angle Player::getPlayerRotation()
{
	return m_PlayerSprite.getRotation();
}
Sprite Player::getPlayerSprite()
{
	return m_PlayerSprite;
}
int Player::getPlayerHealth() const
{
	return m_PlayerHealth;
}

// Player Movement Functions
void Player::playerMoveUp()
{
	m_UpPressed = true;
}
void Player::playerMoveDown()
{
	m_DownPressed = true;
}
void Player::playerMoveLeft()
{
	m_LeftPressed = true;
}
void Player::playerMoveRight() 
{
	m_RightPressed = true;
}

// Player Stop Movement Functions
void Player::playerStopUp()
{
	m_UpPressed = false;
}
void Player::playerStopDown()
{
	m_DownPressed = false;
}
void Player::playerStopLeft()
{
	m_LeftPressed = false;
}
void Player::playerStopRight()
{
	m_RightPressed = false;
}
// position (+ or -) speed * elapsed time.
void Player::update(const float& elapsedTime, Vector2i mousePosition)
{
	// Uses the keys pressed determined with the bool values,
	// determines the player direction using speed and time so we can 
	// draw the character sprite to the screen to make it move
	if (m_UpPressed)
	{
		m_PlayerPosition.y -= m_PlayerSpeed * elapsedTime;
	}
	if (m_DownPressed)
	{
		m_PlayerPosition.y += m_PlayerSpeed * elapsedTime;
	}
	if (m_RightPressed)
	{
		m_PlayerPosition.x += m_PlayerSpeed * elapsedTime;
	}
	if (m_LeftPressed)
	{
		m_PlayerPosition.x -= m_PlayerSpeed * elapsedTime;
	}

	m_PlayerSprite.setPosition(m_PlayerPosition);

	// This will detect wether the player has reached the arena's
	// Wall and will be used to keep the player within the boundries
	// of the arena
	if (m_PlayerPosition.x > m_Arena.size.x - m_TileSize) // Width
	{
		m_PlayerPosition.x = m_Arena.size.x - m_TileSize;
	}
	if (m_PlayerPosition.x < m_Arena.position.x + m_TileSize) // Left
	{
		m_PlayerPosition.x = m_Arena.position.x + m_TileSize;
	}
	if (m_PlayerPosition.y > m_Arena.size.y - m_TileSize) // Height
	{
		m_PlayerPosition.y = m_Arena.size.y - m_TileSize;
	}
	if (m_PlayerPosition.y < m_Arena.position.y + m_TileSize) // top
	{
		m_PlayerPosition.y = m_Arena.position.y + m_TileSize;
	}

	// Calcuates the angle between the center of the screen and the 
	// Current mouse position which will be used to set the rotation
	// of the player
	float angleRads = atan2(
		mousePosition.y - (m_Resolution.y / 2.f),
		mousePosition.x - (m_Resolution.x / 2.f)
	);

	// Convert to degrees
	float angleDeg = angleRads * 180.f / std::numbers::pi_v<float>;

	m_PlayerSprite.setRotation(degrees(angleDeg));
}

void Player::upgradePlayerSpeed()
{
	// 20% speed upgrade
	m_PlayerSpeed += (START_SPEED * 0.2f);
}

void Player::upgradePlayerHealth()
{
	// 20% health upgrade
	m_PlayerMaxHealth += (START_HEALTH * 0.2f);
}

void Player::givePlayerHealth(int amount)
{
	m_PlayerHealth += amount;
	if (m_PlayerHealth > m_PlayerMaxHealth)
	{
		m_PlayerHealth = m_PlayerMaxHealth;
	}
}