#ifndef LISTA_H
#define LISTA_H

#include <string>

class Lista 
{
    public:
        Lista();
        ~Lista();
        bool inserirInicio(const std::string& elemento);
        bool inserirFim(const std::string& elemento);
        bool inserirNaPosicao(int, const std::string&);

        bool removerInicio();
        bool removerFim();
        bool removerNaPosicao(int);
        int removerTodos(const std::string&);

        const std::string& primeiroElemento() const;
        const std::string& ultimoElemento() const;
        const std::string& elementoNaPosicao(int) const;

        unsigned long tamanho() const;
        std::string imprimir() const;
   
    private:
        class No
        {
        public:
            ~No();
            
            No( std::string valor );

            std::string valor;

            No* proximo;
        };

        No* primeiro;
        No* ultimo;
        unsigned long quantidade;
};

#endif