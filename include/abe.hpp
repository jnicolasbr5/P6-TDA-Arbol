#pragma once 

#include "ab.hpp"

template <typename Key>
class ABE: public AB<Key> {
  public:
    bool insertar(const Key& k) override {
      if (buscar(k)) {
        return false;
      }

      if (this->raiz_ == NULL) {
        this->raiz_ = new NodoB<Key>(k);
        return true;
      }
      else {
        return insertar_rama(this->raiz_, k);
      } 
    }

    bool buscar(const Key& k) const override {
      return buscar_rama(this->raiz_, k);
    }


  private: 
    bool insertar_rama(NodoB<Key>* nodo, const Key& key) {
      if (TamRama(nodo->izdo_) <= TamRama(nodo->dcho_)) {
        if (nodo->izdo_ != NULL) {
          return insertar_rama(nodo->izdo_, key);
        } else {
          nodo->izdo_ = new NodoB<Key>(key);
          return true;
        }
      } else {
        if (nodo->dcho_ != NULL)  {
          return insertar_rama(nodo->dcho_, key);
        } else {
          nodo->dcho_ = new NodoB(key);
          return true;
        }
      }
    } 

    bool buscar_rama(NodoB<Key>* nodo, const Key& key) const {
      if (nodo == NULL) { // Si no coincide
        return false;
      } else if (key == nodo->dato_) { // Si coincide
        return true;
      } 
      
      return buscar_rama(nodo->izdo_, key) || buscar_rama(nodo->dcho_, key);
    }

    const int TamRama(NodoB<Key>* nodo) {
      if (nodo == NULL) return 0;
        return (1 + TamRama(nodo->izdo_) + TamRama(nodo->dcho_));
    }

};