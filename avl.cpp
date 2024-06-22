#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

// Estructura del nodo
struct Nodo {
    int valor;
    Nodo* l; // Nodo izquierdo
    Nodo* r; // Nodo derecho
    int altura;

    Nodo(int val) : valor(val), l(nullptr), r(nullptr), altura(1) {}
};

// Estructura del árbol AVL
struct AVL {
    Nodo* raiz;

    AVL() : raiz(nullptr) {}

    // Obtener la altura de un nodo
    int obtenerAltura(Nodo* n) {
        return n ? n->altura : 0;
    }

    // Obtener el factor de balance de un nodo
    int balance(Nodo* n) {
        return n ? obtenerAltura(n->l) - obtenerAltura(n->r) : 0;
    }

    // Rotación a la derecha
    Nodo* rotarDerecha(Nodo* y) {
        Nodo* x = y->l;
        Nodo* T2 = x->r;

        x->r = y;
        y->l = T2;

        y->altura = max(obtenerAltura(y->l), obtenerAltura(y->r)) + 1;
        x->altura = max(obtenerAltura(x->l), obtenerAltura(x->r)) + 1;

        return x;
    }

    // Rotación a la izquierda
    Nodo* rotarIzquierda(Nodo* x) {
        Nodo* y = x->r;
        Nodo* T2 = y->l;

        y->l = x;
        x->r = T2;

        x->altura = max(obtenerAltura(x->l), obtenerAltura(x->r)) + 1;
        y->altura = max(obtenerAltura(y->l), obtenerAltura(y->r)) + 1;

        return y;
    }

    // Inserción en el árbol AVL
    Nodo* insertar(Nodo* nodo, int valor) {
        if (!nodo) return new Nodo(valor);

        if (valor < nodo->valor)
            nodo->l = insertar(nodo->l, valor);
        else if (valor > nodo->valor)
            nodo->r = insertar(nodo->r, valor);
        else
            return nodo; // Los valores duplicados no están permitidos

        nodo->altura = 1 + max(obtenerAltura(nodo->l), obtenerAltura(nodo->r));

        int bal = balance(nodo);

        // Rotaciones para balancear el árbol
        // Caso izquierda-izquierda
        if (bal > 1 && valor < nodo->l->valor)
            return rotarDerecha(nodo);

        // Caso derecha-derecha
        if (bal < -1 && valor > nodo->r->valor)
            return rotarIzquierda(nodo);

        // Caso izquierda-derecha
        if (bal > 1 && valor > nodo->l->valor) {
            nodo->l = rotarIzquierda(nodo->l);
            return rotarDerecha(nodo);
        }

        // Caso derecha-izquierda
        if (bal < -1 && valor < nodo->r->valor) {
            nodo->r = rotarDerecha(nodo->r);
            return rotarIzquierda(nodo);
        }

        return nodo;
    }

    // Función pública para insertar un valor
    void insertar(int valor) {
        raiz = insertar(raiz, valor);
    }

    // Función para obtener los valores en orden
    void inorder(Nodo* nodo, vector<int>& resultado) {
        if (nodo) {
            inorder(nodo->l, resultado);
            resultado.push_back(nodo->valor);
            inorder(nodo->r, resultado);
        }
    }

    // Función pública para obtener los valores en orden
    vector<int> inorder() {
        vector<int> resultado;
        inorder(raiz, resultado);
        return resultado;
    }

    // Función para obtener los valores en preorden
    void preorder(Nodo* nodo, vector<int>& resultado) {
        if (nodo) {
            resultado.push_back(nodo->valor);
            preorder(nodo->l, resultado);
            preorder(nodo->r, resultado);
        }
    }

    // Función pública para obtener los valores en preorden
    vector<int> preorder() {
        vector<int> resultado;
        preorder(raiz, resultado);
        return resultado;
    }

    // Función para imprimir el árbol como matriz
    void imprimirMatriz() {
        vector<int> in = inorder();
        vector<int> pre = preorder();

        int filas = pre.size();
        int columnas = in.size();

        // Crear matriz con dimensiones apropiadas
        vector<vector<string>> matriz(filas, vector<string>(columnas, " "));

        // Llenar la matriz con los valores de preorden e inorder
        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                if (pre[i] == in[j]) {
                    matriz[i][j] = to_string(pre[i]);
                }
            }
        }

        // Imprimir la matriz
        for (const auto& fila : matriz) {
            for (const auto& elemento : fila) {
                cout << setw(4) << elemento;
            }
            cout << endl;
        }
    }
};

int main() {
    AVL arbol;
    arbol.insertar(10);
    arbol.insertar(20);
    arbol.insertar(30);
    arbol.insertar(40);
    arbol.insertar(50);
    arbol.insertar(55);
    arbol.insertar(32);
    arbol.insertar(12);
    arbol.insertar(233);

    cout << "Arbol AVL:\n";
    arbol.imprimirMatriz();

    return 0;
}
