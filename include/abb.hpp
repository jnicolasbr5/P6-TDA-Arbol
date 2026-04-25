#pragma once

#include "ab.hpp" 

template <typename Key>
class ABB: public AB<Key> {
  public:
    bool insertar(const Key& k) override {
      return insertar_rama(this->raiz_, k);
    }

    bool buscar(const Key& k) const override {
      return buscar_rama(this->raiz_, k);
    }

  private:
    bool insertar_rama(NodoB<Key>* &nodo, const Key& k) {
      if (nodo == NULL) { // Si el nodo está vacío
        nodo = new NodoB(k);
        return true;
      } else if (k == nodo->dato_) { // Si coincide
        return false;
      } 
      else if (k < nodo->dato_) {
        return insertar_rama(nodo->izdo_, k);
      } else {
        return insertar_rama(nodo->dcho_, k);
      }
    }

    bool buscar_rama(NodoB<Key>* nodo, const Key& k) const {
      if (nodo == NULL) { // Si no coincide
        return false;
      } else if (k == nodo->dato_) { // Si coincide
        return true;
      } else if (k < nodo->dato_) {
        return buscar_rama(nodo->izdo_, k);
      } else {
        return buscar_rama(nodo->dcho_, k);
      }
    }
};