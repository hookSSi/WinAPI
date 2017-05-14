#pragma once
#include<memory>

/* ºô´õ */
template <typename T>
	class Builder{
	protected:
		T* product;
	public:
		Builder(){}
		virtual ~Builder(){}

		T* GetProduct() { return product; }
		void CreateNewProduct(){ product = new T(); }
	};