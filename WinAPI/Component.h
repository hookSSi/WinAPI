#pragma once

class Component{
public:
	bool isActive{true}; // Active �Ǿ� �ִ°�?
	Component(){};
	virtual ~Component(){};
	virtual bool Update(){ return true; }; // �� Component�� Update
};