#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
using namespace sf;

int main()
{
	// The game will always be one of four states:
	enum class GameState{PAUSE, LEVELING_UP, GAME_OVER, PLAYING};

	// Start with the game over state
	GameState state = GameState::GAME_OVER;

	Vector2u resolution = VideoMode::getDesktopMode().size;

	// Create Window
	RenderWindow window(VideoMode::getDesktopMode(), "Zombie Arena", State::Fullscreen);
	// Will be used for creating a view for main action
	FloatRect rect({ 0.f, 0.f },
		{ static_cast<float>(resolution.x), static_cast<float>(resolution.y) });
	// Create an SFML View for the main action
	View mainView(rect);

	// Clock to time everything
	Clock clock;
	// How long has the PLAYING state been active
	Time gameTimeTotal;

	// Where is the mouse in relation to the world
	Vector2f mouseWorldPosition;
	// Where is the mouse in relation to the screen
	Vector2i mouseScreenPosition;

	Player player;
	IntRect arena;

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (Keyboard::isKeyPressed(Keyboard::Key::Enter) &&
				state == GameState::PLAYING)
			{
				state = GameState::PAUSE;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::Enter) &&
				state == GameState::PAUSE)
			{
				state = GameState::PLAYING;
				// Reset the clock so that there is no frame jump
				clock.restart();
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::Enter) &&
				state == GameState::GAME_OVER)
			{
				state = GameState::LEVELING_UP;
			}

			if (state == GameState::PLAYING)
			{

			}
		}
		// Handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
		{
			window.close();
		}
		// Handle WASD while in PLAYING state
		if (state == GameState::PLAYING)
		{
			if (Keyboard::isKeyPressed(Keyboard::Key::W))
			{
				player.playerMoveUp();
			}
			else
			{
				player.playerStopUp();
			}

			if (Keyboard::isKeyPressed(Keyboard::Key::A))
			{
				player.playerMoveLeft();
			}
			else
			{
				player.playerStopLeft();
			}

			if (Keyboard::isKeyPressed(Keyboard::Key::S))
			{
				player.playerMoveDown();
			}
			else
			{
				player.playerStopDown();
			}

			if (Keyboard::isKeyPressed(Keyboard::Key::D))
			{
				player.playerMoveRight();
			}
			else
			{
				player.playerStopRight();
			}
		}
		// Handle the leveling-up state
		if (state == GameState::LEVELING_UP)
		{
			if (Keyboard::isKeyPressed(Keyboard::Key::Num1))
			{
				state = GameState::PLAYING;
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Num2))
			{
				state = GameState::PLAYING;
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Num3))
			{
				state = GameState::PLAYING;
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Num4))
			{
				state = GameState::PLAYING;
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Num5))
			{
				state = GameState::PLAYING;
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Num6))
			{
				state = GameState::PLAYING;
			}
			if (state == GameState::PLAYING)
			{
				// Preparing the level
				arena.size.x = 500;   // Width
				arena.size.y = 500;   // Height
				arena.position.x = 0; // Left
				arena.position.y = 0; // Top

				int tileSize = 50;
				// Spawn the player in the middle of the arena
				player.spawn(arena, resolution, tileSize);
				// Reset the clock so there is no frame jump
				clock.restart();
			}
		}
		// Update the frame
		if (state == GameState::PLAYING)
		{
			// Update the delta time
			Time dt = clock.restart();
			// Update the total game time
			gameTimeTotal += dt;

			// Make a fraction of 1 from the delta time
			float dtAsSeconds = dt.asSeconds();
			// Where is the mouse pointer
			mouseScreenPosition = Mouse::getPosition(window);

			// Convert mouse coordinates to world
			// based coordinates of mainView
			mouseWorldPosition = window.mapPixelToCoords(
				mouseScreenPosition, mainView);
			
			// Update the player
			player.update(dtAsSeconds, Mouse::getPosition(window));
			// Make a note of the player's new position
			Vector2f playerPosition(player.getPlayerCenter());
		}
		// Draw the scene
		if (state == GameState::PLAYING)
		{
			window.clear();
			window.setView(mainView);
			window.draw(player.getPlayerSprite());
		}
		if (state == GameState::LEVELING_UP)
		{

		}
		if (state == GameState::PAUSE)
		{

		}
		if (state == GameState::GAME_OVER)
		{

		}

		window.display();
	}
	return 0;
}