#include <SFML/Graphics.hpp>
#include "Player.h"
using namespace sf;

int main()
{
	// The game will always be one of four states:
	enum class GameState{PAUSE, LEVELING_UP, GAME_OVER, PLAYING};

	// Start with the game over state
	GameState state = GameState::GAME_OVER;

	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().size.x; // Width
	resolution.y = VideoMode::getDesktopMode().size.y; // Height

	// Create Window
	RenderWindow window(VideoMode({ resolution.x, resolution.y }),
		"Zombie Arena", State::Fullscreen);
	// Will be used for creating a view for main action
	FloatRect rect({ 0, 0 }, { resolution.x, resolution.y });
	// Create an SFML View for the main action
	View mainView(rect);

	// Clock to time everything
	Clock clock;
	// How long has the PLAYING state been active
	Time gameTimeTotal;

	// Where is the mouse in relation to the world
	Vector2f mouseWorldPosition;
	// Where is the mouse in relation to the screen
	Vector2f mouseScreenPosition;

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
		
	}


	return 0;
}