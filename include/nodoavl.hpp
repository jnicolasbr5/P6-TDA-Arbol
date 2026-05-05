#pragma once

#include "nodob.hpp"

template <typename Key>
class NodoAVL: public NodoB<Key> {
	public:

	NodoAVL(const Key k, int bal=1, NodoB<Key> *izq=nullptr, NodoB<Key>  *der = nullptr) :
					NodoB<Key>(k, izq, der), bal_(bal) {}


	int bal_;
	
};