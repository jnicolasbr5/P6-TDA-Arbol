#pragma once

#include <iostream>
#include <queue>

#include "nodob.hpp"

template <typename Key>
struct InfoNodo {
  NodoB<Key> *ptr;
  unsigned nivel;
};

template <typename Key>
class AB {
  protected:
    NodoB<Key> *raiz_;

  public:
    AB() : raiz_(nullptr) {}
    AB(const Key k) {
      raiz_ = new NodoB<Key>(k);
    }

    virtual bool insertar(const Key& k) = 0;

    virtual bool buscar(const Key& k) const = 0;

    void inorden() const {
      inorden(raiz_);
    }

    void MostrarArbol(std::ostream& os) const { // Por niveles
      if (raiz_ == nullptr) {
        os << "No se puede visualizar el árbol." << std::endl;
        return; 
      }
      std::queue<InfoNodo<Key>> q;
      q.push({raiz_, 0});
      unsigned nivel_actual = 0;
      while (!q.empty()) {
        InfoNodo<Key> nodo = q.front();
        q.pop();

        if (nodo.nivel > nivel_actual || nodo.nivel == 0) {
          os << "\nNivel " << nodo.nivel << ": ";
          nivel_actual = nodo.nivel;
        }

        if (nodo.ptr == NULL) {
          os << "[.] ";
        } else  {
          os << "[" << nodo.ptr->dato_ << "] ";
          q.push({nodo.ptr->izdo_, nivel_actual + 1});
          q.push({nodo.ptr->dcho_, nivel_actual + 1});
        }
      }
    }

  private: 
    void inorden(NodoB<Key>* nodo) const {
      if (nodo == NULL) return;
      inorden(nodo->izdo_);
      std::cout << nodo->dato_ << " ";
      inorden(nodo->dcho_);
    }
};

template <typename Key>
std::ostream& operator<<(std::ostream& os, const AB<Key>& arbol) {
  arbol.MostrarArbol(os);
  return os;
}