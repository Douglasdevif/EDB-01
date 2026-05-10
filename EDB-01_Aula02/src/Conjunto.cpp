#include "Conjunto.h"
#include <iostream>
using namespace std;

Conjunto::Conjunto(const int capacidade)
{
}

Conjunto::~Conjunto()
{
}

bool Conjunto::contem(int elemento) const
{
    for(int i = 0; i < this->quantidade; i++){
        if(this->elementos[i] == elemento){
            return true;
        }
    }
    return false;
}

bool Conjunto::inserir(int elemento)
{
    if(this->quantidade == this->capacidade){
        return false;
    }
    for(int i = 0; i < quantidade; i++){
        auto elementoAtual = this->elementos[i];

        if(elementoAtual == elemento){
            return false;
        } 
    }
    //O elemento não existe no conjunto
    //Estou pronto para inserir
    this->elementos[quantidade] = elemento;
    quantidade++;
    return true;
    
}

bool Conjunto::remover(int elemento)
{
    for(int i = 0; i < this->quantidade; i++){
        auto elementoAtual = this->elementos[i];

        if(elementoAtual == elemento){
            //Efetivar a remoção
            for(int j = i; j < this->quantidade; j++){
                this->elementos[j] = this->elementos[j+1];
            }
            --this->quantidade;
            return true;
        }
    }
    return false;
}

int Conjunto::tamanho() const
{
    return this->quantidade;
}

void Conjunto::imprimir() const
{
    std::cout << "{ ";
    for(int i = 0; i < quantidade; ++i)
    {
        std::cout << this->elementos[i] << " ";
    }
    std::cout << "}" << std::endl;
}
