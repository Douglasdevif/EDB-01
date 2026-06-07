//
//  ListaEncadeada.cpp
//
//  Created by Eiji Adachi Medeiros Barbosa
//

#include "../header/ListaEncadeada.h"
#include "../header/No.h"
#include <iostream>
#include <string>
#include <sstream>

ListaEncadeada::ListaEncadeada()
{
    this->inicio = nullptr;
}

ListaEncadeada::~ListaEncadeada()
{
    // To-Do
}

void ListaEncadeada::inserirNoInicio(int e){auto n = new No<int>(e);if( inicio == nullptr ) inicio = n;else { n->setProximo( inicio );inicio = n;}}

int ListaEncadeada::removerTodos(int val) 
{
    int removidos = 0;

    while(inicio != nullptr && inicio->valor == val){
        auto noparaDeletar = inicio;
        inicio = inicio->proximo;

        delete noparaDeletar;
        removidos++;
    }
    if(inicio == nullptr){
        return removidos;
    }
    
    auto atual = inicio;

    while(atual->proximo != nullptr){
        if(atual->proximo->valor == val){
            auto noparaDeletar = atual->proximo;
            atual->proximo = atual->proximo->proximo;

            delete noparaDeletar;
            removidos++;
        }else{
            atual = atual->proximo;
        }
    }
    return removidos;
}

No<int>* ListaEncadeada::getInicio()
{
    return this->inicio;
}

std::string ListaEncadeada::imprimir()
{
    std::stringstream resultado;
    
    auto no = this->getInicio();

    while(no != nullptr)
    {
        resultado << no->getValor() << "->" ;
        no = no->getProximo();
    }
    resultado << "null";

    return resultado.str();
}

