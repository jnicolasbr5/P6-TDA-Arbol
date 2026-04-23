#include "nodob.hpp"

template <typename Key>
class AB {
  protected:
    NodoB<Key> *raiz_;

  public:
    AB() : raiz_(nullptr) {}
    AB(const Key k) : raiz_(k) {}

    bool insertar(const Key& k) {
      return insertar_rama(raiz_, k);
    }

    bool buscar(const Key& k) const {
      return buscar_rama(raiz_, k);
    }

    void inorden(NodoB<Key>* nodo=raiz_) const {
      if (nodo == NULL) return;
      inorden(nodo->izdo_);
      std::cout << nodo->getDato() << " ";
      inorden(nodo->dcho_);
    }

    void MostrarArbol(std::ostream& os) {
      
    }

  private:
    bool insertar_rama(NodoB* &nodo, const Key& key) {
      if (nodo == NULL) { // Si el nodo está vacío
        nodo = new NodoB(k);
        return true;
      } else if (k == nodo->getDato()) { // Si coincide
        return false;
      } 
      else if (k < nodo->dato_) {
        return insertar_rama(nodo->izdo_, k);
      } else {
        return insertar_rama(nodo->dcho_, k);
      }
    }

    bool buscar_rama(NodoB* &nodo, const Key& key) {
      if (nodo == NULL) { // Si no coincide
        return false;
      } else if (k == nodo->getDato()) { // Si coincide
        return true;
      } else if (k < nodo->getDato()) {
        return buscar_rama(nodo->izdo_, k);
      } else {
        return buscar_rama(nodo->dcho_, k);
      }
    }
};

std::ostream& operator<<(std::ostream& os, const AB& arbol) {
  arbol.MostrarArbol(os);
  return os;
}