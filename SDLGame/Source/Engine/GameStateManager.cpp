#include "GameStateManager.h"


GameStateManager::GameStateManager()
{

}

GameStateManager::~GameStateManager()
{

}

void GameStateManager::PushState(StateRef State, bool isReplacing)
{
	if(states.top)
		states.top->OnExit(); 

	if(isReplacing)
		states.pop;

	states.push(State); 
	states.top->OnEnter(); 
}

void GameStateManager::PopState()
{
	if (states.top)
	{
		states.top->OnExit(); 
		states.pop; 
	}
}

void GameStateManager::HandleInput()
{
	if(states.top)
		states.top->HandleInput(); 
}

void GameStateManager::Update()
{
	if (states.top)
		states.top->Update(); 
}

void GameStateManager::Draw()
{
	if (states.top)
		states.top->Draw(); 
}
StateRef GameStateManager::getCurrentState() const
{
	if (!states.empty)
		return states.top;
	else
		return nullptr; 
}