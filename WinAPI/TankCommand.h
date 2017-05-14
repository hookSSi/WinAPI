#pragma once
#include "Tank.h"
#include "InputHandler.h"

class TankCommand : public Command
{
public:
	TankCommand() : Command(){}
	TankCommand(bool(*p_command)(Tank& tank), Tank* p_tank):command(p_command), tank(p_tank){}
	virtual ~TankCommand() {}

	virtual bool execute(){ this->command(*(this->tank)); return true; }
private:
	Tank* tank;
	TankCommand(TankCommand& other){}
	bool(*command)(Tank& tank);
};