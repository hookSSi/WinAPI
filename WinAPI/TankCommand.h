#pragma once
#include "Tank.h"
#include "InputHandler.h"

class MoveCommand : public Command
{
public:
	MoveCommand() : Command(){}
	MoveCommand(Vector2D& p_vel) : Command(){ velocity = p_vel; }
	virtual ~MoveCommand() {}

	virtual void execute(Tank& tank){ tank.Move(velocity); }
private:
	Vector2D velocity;
};

class FireDegreeCommand : public Command
{
public:
	FireDegreeCommand() : Command(), scale(0){}
	FireDegreeCommand(float p_scale) : Command(), scale(p_scale){}
	virtual ~FireDegreeCommand(){}

	virtual void execute(Tank& tank){ tank.ControlDegree(scale); }
private:
	float scale;
};

class JumpCommand :public Command
{
public:
	JumpCommand() : Command(),scale(0){}
	JumpCommand(float p_scale) : Command(),scale(p_scale){}
	virtual ~JumpCommand(){}

	virtual void execute(Tank& tank){ tank.Jump(scale); }
private:
	float scale;

};

class FireCommand : public Command
{
public:
	FireCommand() : Command(), master(1){}
	FireCommand(int p_master) : Command(),master(p_master){}
	virtual ~FireCommand() {}

	virtual void execute(Tank& tank){ tank.Fire(master); }
private:
	int master;
};