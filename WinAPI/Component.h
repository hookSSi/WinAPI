#pragma once

class Component{
public:
	bool isActive{true}; // Active 되어 있는가?
	bool isErase{ false }; // 이 컴포넌트를 삭제할까?
	Component(){};
	virtual ~Component(){};

	virtual bool Update(){ return true; }; // 각 Component의 Update
	void DeleteSelf(){ this->isErase = true; this->isActive = false; } // 삭제하도록 셋
};