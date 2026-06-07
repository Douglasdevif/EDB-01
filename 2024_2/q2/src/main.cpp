#include <iostream>
#include "ListaEncadeada.h"
int main() 
{
  ListaEncadeada lista;
  
  std::cout << "Esta questão não tem main; use o comando make run-test para rodar os testes." << std::endl;
  lista.imprimir();
  lista.removerTodos(10);
  lista.imprimir();
  return 0;
}
