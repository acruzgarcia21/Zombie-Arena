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

	RenderWindow window(VideoMode({ resolution.x, resolution.y }),
		"Zombie Arena", State::Fullscreen);
	return 0;
}