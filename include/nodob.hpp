#pragma once

template <typename Key>
class NodoB {
  public: 
    Key dato_;
    NodoB<Key> *izdo_;
    NodoB<Key> *dcho_;

    NodoB(const Key k) : dato_(k), izdo_(nullptr), dcho_(nullptr) {}
};