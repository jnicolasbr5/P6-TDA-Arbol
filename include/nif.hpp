#pragma once 

#include <iostream>
#include <random>

class nif {
	private:
		long valor_;

	public:
	// Constructor por defecto
		nif() {
			valor_ = 10000000 + std::rand() % 90000000;
		}

		// Constructor
		nif(long v) : valor_(v) {}

		// Sobrecara de comparadores
		bool operator==(const nif& other) const {
			return this->valor_ == other.valor_;
		}

		bool operator!=(const nif& other) const {
			return this->valor_ != other.valor_;
		}

		bool operator>(const nif& other) const {
			return this->valor_ > other.valor_;
		}

		// Sobrecarga cambio de tipo
		operator long() const {return valor_;}

		// Sobrecarga de entrada
		friend std::istream& operator>>(std::istream& is, nif& nif) {
			is >> nif.valor_;
			return is;
		}

		friend std::ostream& operator<<(std::ostream& os, nif& nif) {
			os << nif.valor_;
			return os;
		}
};