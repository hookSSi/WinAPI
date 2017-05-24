#include "EventManager.h"
#include "Tank.h"
#include "Game.h"

void EventManager::onNotify(const Tank& object, EVENT event)
{
	switch (event)
	{
	case EVENT::PLAYER_DEAD:
		if (Game::GetInstance()->player1_tank == &object)
		{
			/*Game::GetInstance()->player1_tank->collision.isCollision = false;
			Game::GetInstance()->player1_tank->collision.isActive = true;*/
			ScoreUp(2);
			flag = true;
		}
		if (Game::GetInstance()->player2_tank == &object)
		{
			/*Game::GetInstance()->player2_tank->collision.isCollision = false;
			Game::GetInstance()->player2_tank->collision.isActive = true;*/
			ScoreUp(1);
			flag = true;
		}
		break;
	}
}

void EventManager::ScoreUp(int player)
{
	switch (player)
	{
	case 1:
		Game::GetInstance()->player1_score++;
		break;
	case 2:
		Game::GetInstance()->player2_score++;
		break;
	}
	
}