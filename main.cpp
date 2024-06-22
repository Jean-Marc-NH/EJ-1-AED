// CicrcularLinkedList.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>

using namespace std;

class node
{
public:
    int data;
    node* next;
    node(int dt, node* nxt)
    {
        data = dt;
        next = nxt;
    }
};

class CircularLinkedList
{
    node* head = NULL;
    bool one_node = false;
public:
    void add(int value)
    {
        if (!head)
        {
            head = new node(value, head);
            one_node = true;
            head->next = head;
        }
        else
        {
            node* p = head;
            node* s = NULL;
            if (head->data > value)
            {
                head->next = new node(value, head->next);
                swap(head->data, head->next->data);
            }
            else
            {
                if (one_node)
                {
                    if (p->data > value)
                    {
                        head = new node(value, head);
                        p->next = head;
                    }
                    else
                    {
                        p->next = new node(value, p->next);
                    }
                    one_node = false;
                }
                else
                {

                    do
                    {
                        s = p;
                        p = p->next;

                    } while ((p->data < value) && ((s->next) != head));

                    s->next = new node(value, s->next);
                }
            }
        }
    }

    bool find(node*& p, int value)
    {
        p = head;
        if (!one_node)
        {
            

            for (node* s = head->next; p->next != head; s = s->next, p = p->next)
            {
                if (s->data == value) return true;
            }
            if (p->next->data == value)
            {
                return true;

            }
            return false;
        }
        if (p->data == value) return true;
        else return false;
    }
    void del(int value)
    {
        node* p = head;

        if (find(p, value))
        {
            if (p->next == p) one_node = true;
            if(one_node)
            {
                delete head;
                head = NULL;
                one_node = false;
                return;
            }
            if (p->next == head)
            {
                head = head->next;
                node* tmp = p->next;
                p->next = tmp->next;
                delete tmp;
            }
            else
            {
                node* tmp = p->next;
                p->next = tmp->next;
                delete tmp;
            }
            if (p == p->next) { one_node = true; }
        }

    }

    void print()
    {
        int cont = 0;
        node* ptr = head;
        cout << "head->";
        while (head && cont < 1)
        {
            cout << ptr->data << " -> ";
            ptr = ptr->next;
            if (ptr == head) cont++;
        }
        if (head) cout << ptr->data;
        cout << " <- head \n ";

    }
};

int main()
{
    int ADD[10] = { 2,4,6,8,10,1,3,5,7,9 };
    int DEL[10] = { 9,7,5,3,1,10,8,6,4,2 };
    CircularLinkedList CLL;
    for (int i = 0; i < 10; i++)
    {
        cout << "ADD " << ADD[i] << endl;
        CLL.add(ADD[i]);
        CLL.print();
    }
    cout << "ENTRNADO AL DELETE -----<" << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << "DEL " << DEL[i] << endl;
        CLL.del(DEL[i]);
        CLL.print();
    }
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
