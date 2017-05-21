#pragma once

class Component{
public:
	bool isActive{true}; // Active �Ǿ� �ִ°�?
	bool isErase{ false }; // �� ������Ʈ�� �����ұ�?
	Component(){};
	virtual ~Component(){};

	virtual bool Update(){ return true; }; // �� Component�� Update
	void DeleteSelf(){ this->isErase = true; this->isActive = false; } // �����ϵ��� ��
};