#pragma once

#include "abb.hpp"
#include "nodoavl.hpp"

template <typename Key>
class AVL: public ABB<Key> {
	public:
		AVL(bool t) : ABB<Key>(), trace_(t) {}

		bool insertar(const Key& k) override {
			if (this->buscar(k)) return false;
        NodoAVL<Key>* nuevo = new NodoAVL<Key>(k, 0);
        bool crece = false;
        inserta_bal(this->raiz_, nuevo, crece); 
        return true;
		}

    // MODIFICACION
    bool eliminar(const Key& k) {
      bool decrece = false;    
      eliminar_r(this->raiz_, k, decrece);
      return decrece;
    }



		void MostrarArbol(std::ostream& os) const override {
      if (this->raiz_ == NULL) {
        os << "Árbol vacío" << std::endl;
        os << "Nivel 0: [.]" << std::endl;
        return;
      }

      std::queue<NodoB<Key>*> q;
      q.push(this->raiz_);
      int nivel = 0;

      while (!q.empty()) {
        int nodos_en_nivel = q.size();
        bool proximo_nivel_tiene_datos = false;
        
        os << "Nivel " << nivel << ": ";

        for (int i = 0; i < nodos_en_nivel; ++i) {
          NodoB<Key>* actual = q.front();
          q.pop();

          if (actual != NULL) {
              os << "[";
              // TRAZA
              if (this->trace_) {
                  NodoAVL<Key>* nodo_avl = static_cast<NodoAVL<Key>*>(actual);
                  os << nodo_avl->dato_ << "(" << nodo_avl->bal_ << ")";
              } else {
                  os << actual->dato_;
              }
              os << "] ";

              q.push(actual->izdo_);
              q.push(actual->dcho_);

              if (actual->izdo_ != NULL || actual->dcho_ != NULL) {
                  proximo_nivel_tiene_datos = true;
              }
          } else {
              os << "[.] ";
          }
        }
        os << std::endl;
        nivel++;

        if (!proximo_nivel_tiene_datos) {
          os << "Nivel " << nivel << ": ";
          int puntos_finales = q.size();
          for (int i = 0; i < puntos_finales; ++i) {
              os << "[.] ";
          }
          os << std::endl;
          break; 
        }
      }
    }

	private:
		bool trace_;

    void eliminar_r(NodoB<Key>* &nodo, int clave_dada, bool& decrece) {
      if (nodo == NULL) return;

      if (clave_dada < nodo->dato_) { // Menor que, subárbol izq
        eliminar_r(nodo->izdo_,clave_dada,decrece);
      } else if (clave_dada > nodo->dato_) { // Mayor que, subarbol der
        eliminar_r(nodo->dcho_,clave_dada,decrece);
      } else { // Igual
          bool encontrado = true;
          NodoB<Key>* nodo_eliminar = nodo;
          if (nodo->izdo_ == nullptr) {
              nodo = nodo->dcho_;
          } else if (nodo->dcho_ == nullptr) {
              nodo = nodo->izdo_;
          } else {
              NodoB<Key>* sucesor = nodo->dcho_;
              while (sucesor->izdo_ != nullptr) sucesor = sucesor->izdo_;
              nodo->dato_ = sucesor->dato_;
              bool aux;
              eliminar_r(nodo->dcho_, sucesor->dato_, aux);
              return;
          }
          delete nodo_eliminar;  
        }
      }

		void inserta_bal(NodoB<Key>* &nodo, NodoAVL<Key>* nuevo, bool &crece) {
      if (nodo == NULL) {
        nodo = nuevo;
        crece = true;
      } else if (nuevo->dato_ < nodo->dato_) {
        inserta_bal(nodo->izdo_,nuevo,crece);
        if (crece) {
            NodoAVL<Key>* &nodo_avl = reinterpret_cast<NodoAVL<Key>* &>(nodo);
            insert_re_balancea_izda(nodo_avl, crece);
        }
      } else {
          inserta_bal(nodo->dcho_,nuevo,crece);
          if (crece) {
              NodoAVL<Key>* &nodo_avl = reinterpret_cast<NodoAVL<Key>* &>(nodo);
              insert_re_balancea_dcha(nodo_avl, crece);
          }
      }
    }

		void rotacion_II(NodoAVL<Key>* &nodo) {
      if (trace_) std::cout << "Rotación II en [" << nodo->dato_ << "(" << nodo->bal_ << ")]:" << std::endl;

      NodoAVL<Key>* nodo1 = static_cast<NodoAVL<Key>*>(nodo->izdo_); 
      nodo->izdo_ = nodo1->dcho_;
      nodo1->dcho_ = nodo;
      
      if (nodo1->bal_ == 1) {
          nodo->bal_ = 0;
          nodo1->bal_ = 0;
      } else { 
          nodo->bal_ = 1;
          nodo1->bal_ = -1;
      }
      nodo = nodo1;
    }

		void rotacion_DD(NodoAVL<Key>* &nodo) {
      if (trace_) std::cout << "Rotación DD en [" << nodo->dato_ << "(" << nodo->bal_ << ")]:" << std::endl;

      NodoAVL<Key>* nodo1 = static_cast<NodoAVL<Key>*>(nodo->dcho_);
      nodo->dcho_ = nodo1->izdo_;
      nodo1->izdo_ = nodo;
      
      if (nodo1->bal_ == -1) {
          nodo->bal_ = 0;
          nodo1->bal_ = 0;
      } else {
          nodo->bal_ = -1;
          nodo1->bal_ = 1;
      }
      nodo = nodo1;
    }

		void rotacion_ID(NodoAVL<Key>* &nodo) {
      if (trace_) std::cout << "Rotación ID en [" << nodo->dato_ << "(" << nodo->bal_ << ")]:" << std::endl;

      NodoAVL<Key>* nodo1 = static_cast<NodoAVL<Key>*>(nodo->izdo_);
      NodoAVL<Key>* nodo2 = static_cast<NodoAVL<Key>*>(nodo1->dcho_);

      nodo->izdo_ = nodo2->dcho_;
      nodo2->dcho_ = nodo;
      nodo1->dcho_ = nodo2->izdo_;
      nodo2->izdo_ = nodo1;

      if (nodo2->bal_ == -1) 
          nodo1->bal_ = 1; 
      else 
          nodo1->bal_ = 0;

      if (nodo2->bal_ == 1) 
          nodo->bal_ = -1; 
      else 
          nodo->bal_ = 0;

      nodo2->bal_ = 0;
      nodo = nodo2; 
    }

		void rotacion_DI(NodoAVL<Key>* &nodo) {
      if (trace_) std::cout << "Rotación DI en [" << nodo->dato_ << "(" << nodo->bal_ << ")]:" << std::endl;

      NodoAVL<Key>* nodo1 = static_cast<NodoAVL<Key>*>(nodo->dcho_);
      NodoAVL<Key>* nodo2 = static_cast<NodoAVL<Key>*>(nodo1->izdo_);

      // Reestructuración de punteros
      nodo->dcho_ = nodo2->izdo_;
      nodo2->izdo_ = nodo;
      nodo1->izdo_ = nodo2->dcho_;
      nodo2->dcho_ = nodo1;

      if (nodo2->bal_ == 1) 
          nodo1->bal_ = -1; 
      else 
          nodo1->bal_ = 0;

      if (nodo2->bal_ == -1) 
          nodo->bal_ = 1; 
      else 
          nodo->bal_ = 0;

      nodo2->bal_ = 0;
      nodo = nodo2;
    }

		void insert_re_balancea_izda(NodoAVL<Key>* &nodo, bool &crece) {
      switch (nodo->bal_) {
        case -1: 
          nodo->bal_ = 0;
          crece = false;
          break;
        case 0: 
          nodo->bal_ = 1;
          crece = true;
          break;
        case 1: 
          if (trace_) {
              nodo->bal_ = 2; 
              std::cout << "Desbalanceo:" << std::endl;
              std::cout << *this << std::endl;
          }

          NodoAVL<Key>* nodo1 = static_cast<NodoAVL<Key>*>(nodo->izdo_);
          if (nodo1->bal_ == 1) 
              rotacion_II(nodo); 
          else 
              rotacion_ID(nodo); 
          crece = false;
          break;
      }
    }

		void insert_re_balancea_dcha(NodoAVL<Key>* &nodo, bool &crece) {
      switch (nodo->bal_) {
        case 1: 
          nodo->bal_ = 0;
          crece = false;
          break;
        case 0: 
          nodo->bal_ = -1;
          crece = true;
          break;
        case -1: 
          if (trace_) {
              nodo->bal_ = -2; 
              std::cout << "Desbalanceo:" << std::endl;
              std::cout << *this << std::endl;
          }

          NodoAVL<Key>* nodo1 = static_cast<NodoAVL<Key>*>(nodo->dcho_);
          if (nodo1->bal_ == -1) {
              rotacion_DD(nodo); 
          } else {
              rotacion_DI(nodo); 
          }
          crece = false; 
          break;
      }
    }

};