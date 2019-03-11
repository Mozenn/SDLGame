#pragma once


class GameState
{
public:

	GameState();

	~GameState();

	virtual void OnEntered() = 0;

	virtual void OnExit() = 0; 

	virtual void HandleInput() = 0 ; 

	virtual void Update() = 0 ; 

	virtual void Draw() = 0 ; 


};