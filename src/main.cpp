#include <fstream>
#include <iostream>
#include <vector>

#include "ab.hpp"
#include "abe.hpp"
#include "abb.hpp"
#include "nif.hpp"

#include "avl.hpp"

struct Datos {
  std::string arbol;
  std::string tipo;
  unsigned elementos = 0;
  std::string file = "";
  bool trace = false;
};

Datos LeerComandos(const std::vector<std::string>& vec) {
  Datos datos;
  for (size_t i = 1; i < vec.size(); i++) {
		if (vec[i] == "-ab") { 
			++i;
			datos.arbol = vec[i];
		}	else if (vec[i] == "-init") {
			++i;
			datos.tipo = vec[i];
      if (datos.tipo == "file" || datos.tipo == "random") {
        i++;
        datos.elementos = static_cast<unsigned int>(std::stoul(vec[i]));
        if (datos.tipo == "file") {
          i++;
          datos.file = vec[i];
        }
      }
		} else if (vec[i] == "-trace") {
      ++i;
      if (vec[i] == "y") datos.trace = true;
      else datos.trace = false; 
    }	
	}
	return datos;
}

void MostrarMenu() {
  std::cout << "\n[0] Salir\n";
  std::cout << "[1] Insertar clave\n";
  std::cout << "[2] Buscar clave\n";
  std::cout << "[3] Mostrar árbol inorden\n";
  std::cout << "[4] Mostrar recorrido por niveles\n" << std::endl;
}


// ./arbol -ab abb -init file 3 ../data/data.txt
int main(int argc, char *argv[]) {
  if (argc < 5 || argc > 9) {
    std::cerr << "Error en el n de argumentos" << std::endl;
    return 1;
  }
  std::vector<std::string> v_args(argv, argv + argc);
  Datos datos = LeerComandos(v_args);

  using Key = nif;
  nif clave;

  // Tipo de árbol
  AB<Key> *arbol = nullptr;
  if (datos.arbol == "abe") {
    arbol = new ABE<nif>();
  } else if (datos.arbol == "abb") {
    arbol = new ABB<nif>();
  } else if (datos.arbol == "avl") {
    arbol = new AVL<nif>(datos.trace);
  } else {
    std::cerr << "Error al elegir tipo de árbol." << std::endl;
    return 1;
  }

  // Opciones línea de comandos
  if (datos.tipo == "manual") {
    std::cout << "\nSe genera un árbol vácio.\n";
  } else if (datos.tipo == "random") {
    for (unsigned i = 0; i < datos.elementos; i++) {
      clave = nif();
      arbol->insertar(clave);
    }
  } else if (datos.tipo == "file") {
    std::cout << datos.file << std::endl;
    std::ifstream file(datos.file); 
    for (unsigned i = 0; i < datos.elementos; i++) {
      file >> clave;
      arbol->insertar(clave);
    }
  }

  unsigned opcion;
  while (true) {
    MostrarMenu();
    std::cout << "Opción: ";
    std::cin >> opcion;
    switch (opcion) {
      case 0:
        std::cout << "Saliendo del programa..." << std::endl;
        return 0;

      case 1:
        std::cout << "Insertar clave: ";
        std::cin >> clave;
        if (arbol->insertar(clave)) {
          std::cout << "Se introdujo la clave." << std::endl;
        } else {
          std::cout << "No se pudo insertar la clave. Ya está en el árbol" << std::endl;
        }
        break;

      case 2:
        std::cout << "Buscar clave: ";
        std::cin >> clave;
        if (arbol->buscar(clave)) {
          std::cout << "Se encontró la clave." << std::endl;
        } else {
          std::cout << "No se encontró la clave." << std::endl;
        }
        break;

      case 3: 
        arbol->inorden();
        std::cout << std::endl;
        break;

      case 4: 
        std::cout << *arbol << std::endl;
        break;

      default: 
        std::cout << "Error de selección" << std::endl;
    }
  
  }
  
  return 0;
}