#pragma once

#include "ab.hpp"
#include "abe.hpp"
#include "avl.hpp"
#include "nif.hpp"

template <typename Key>
class Test {
    public:
    Test(bool trace) : trace_(trace) {}

    void testear() {
        AB<Key> *arbol = nullptr;
        arbol = new AVL<Key>(trace_);

        // Inserto del 1 al 10
        int num_nodos = 10;
        for (int i = 1; i <= num_nodos; i++) {
            arbol->insertar(nif(i));
        }
        std::cout << "Árbol con todos los nodos: \n";
        std::cout << *arbol << std::endl;
        
        // Elimino los valores pares
        int nodos_eliminados = 0;
        AVL<Key>* avl_arbol = static_cast<AVL<Key>*>(arbol);
        for (int i = 2; i <= num_nodos; i++) {
            if (avl_arbol->eliminar(nif(i))) {
                nodos_eliminados++;
            }
        }

        // Muestro el árbol restante
        std::cout << "Árbol con los nodos restantes\n";
        std::cout << *arbol << std::endl;

        int nodos_arbol = arbol->TamRama(arbol->raiz_);
        if (nodos_arbol == (num_nodos - nodos_eliminados)) {
            std::cout << "Test completado." << std::endl;
        }   else {
            std::cout << "Test fallado." << std::endl;
        }

        delete arbol;
    }

    private:
        bool trace_;

};