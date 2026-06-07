//
//  ListaDuplamenteEncadeada.h
//
//  Criado por Eiji Adachi Medeiros Barbosa
//

#ifndef __ListaDuplamenteEncadeada__
#define __ListaDuplamenteEncadeada__

#include "No.h"
#include <string>

typedef enum {
    OK ,
    CABECA_NULA,
    CAUDA_NULA,
    CABECA_ANTERIOR,
    CABECA_PROXIMO_NULO,
    CAUDA_PROXIMO,
    CAUDA_ANTERIOR_NULO,
    CABECA_CAUDA,
    ENCADEAMENTO_INCORRETO
} StatusDaLista ;

class ListaDuplamenteEncadeada {
private:
    No<std::string>* cabeca;
    No<std::string>* cauda;
    void init();
    
public:
    int quantidade;
    ListaDuplamenteEncadeada(void);
    ListaDuplamenteEncadeada(std::string);
    ~ListaDuplamenteEncadeada(void);

    No<std::string>* getCabeca(void);
    No<std::string>* getCauda(void);
    
    bool inserirAntes( std::string, std::string );

    StatusDaLista checarConsistencia(void);
    
    std::string imprimir(void);
    
    bool vazia(void);
    int tamanho(void);
};

#endif 
