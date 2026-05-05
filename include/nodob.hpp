#pragma once

template <typename Key>
class NodoB {
  public: 
    Key dato_;
    NodoB<Key> *izdo_;
    NodoB<Key> *dcho_;

    NodoB(const Key k, NodoB<Key> *izq = nullptr, NodoB<Key> *der = nullptr) : 
          dato_(k), izdo_(izq), dcho_(der) {}
};