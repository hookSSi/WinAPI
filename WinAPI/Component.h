#pragma once

class Component{
public:
	bool isActive{true}; // Active 되어 있는가?
	Component(){};
	virtual ~Component(){};
	virtual bool Update(){ return true; }; // 각 Component의 Update
};