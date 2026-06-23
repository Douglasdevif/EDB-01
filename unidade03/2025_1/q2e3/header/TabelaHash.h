//
//  TabelaHash.h
//
//  Created by Eiji Adachi Medeiros Barbosa
//
#define CHECK_STATUS
#ifndef TABELA_HASH_H
#define TABELA_HASH_H

#include <string>
#include <unordered_set>
#include <iostream>

enum class Estado 
{ 
    LIVRE = 0, 
    OCUPADO, 
    REMOVIDO 
};

struct Elemento 
{
    std::string chave;
    std::string valor;
    Estado estado = Estado::LIVRE;
};

enum class ConsistenciaStatus {
    OK = 0,
    QUANTIDADE_INCORRETA,
    CHAVE_DUPLICADA,
};

class TabelaHash 
{
    friend class TabelaHashTestHelper;

private:
    Elemento* array;
    int capacidade;
    int quantidade;    
    
    static constexpr int CAPACIDADE_PADRAO = 17;
    static constexpr float CARGA_LIMITE_INFERIOR = 0.125f;
    static constexpr float CARGA_LIMITE_SUPERIOR = 0.5f;

    size_t valorHash(const std::string& chave) const 
    {
        size_t valorHash = 0;
		for (char c : chave) {
			valorHash += static_cast<unsigned int>(c);
		}
        return valorHash;
    }

    int hash(const std::string& chave) const 
    {
        return this->valorHash(chave) % this->capacidade; 
    }

    float fatorDeCarga() 
    {
        return static_cast<float>(quantidade) / static_cast<float>(capacidade);
    }

    void aumentar()
    {
        redimensionar(this->capacidade * 2 + 1);
    }











    void redimensionar(size_t novaCapacidade)                                                                                                                                                                               // EAMB 1.0
    {
        Elemento* arrayNovo = new Elemento[novaCapacidade];
        Elemento* arrayVelho = this->array;

        auto capacidadeVelha = this->capacidade;
        this->capacidade = novaCapacidade;
        this->array = arrayNovo;

        for(int i = 0; i < capacidadeVelha; i++){
            Elemento& elemento = arrayVelho[i];

            if(elemento.estado == Estado::OCUPADO){
                int h = this->hash(elemento.chave);
                for(int delta = 0; delta < novaCapacidade; delta ++){
                    auto indice = (h + delta)%novaCapacidade;

                    if(arrayNovo[indice].estado == Estado::LIVRE){

                        arrayNovo[indice].chave = elemento.chave;
                        arrayNovo[indice].valor = elemento.valor;
                        arrayNovo[indice].estado = Estado::OCUPADO;
                        break;
                    }
                }
            }
        }
        delete [] arrayVelho;
    }









public:
    TabelaHash(int capacidadeInicial = CAPACIDADE_PADRAO) : capacidade(capacidadeInicial) , quantidade(0)
    {
        this->array = new Elemento[this->capacidade];
    }

    ~TabelaHash()
    {
        delete [] this->array;
    }








    

    bool inserir(const std::string& chave, const std::string& valor)
    {
        
    int posRemovido = -1;
    int h = hash(chave);

    for(int delta = 0; delta < this->capacidade; delta++){
        int indice = (h + delta) % capacidade;
        Elemento& elemento = this->array[indice];

        if(elemento.estado == Estado::LIVRE){
            int posInsercao;

            if(posRemovido != -1){
                posInsercao = posRemovido;
            } else{
                posInsercao = indice;
            }

            this->array[posInsercao].chave = chave;
            this->array[posInsercao].valor = valor;
            this->array[posInsercao].estado = Estado::OCUPADO;
            this->quantidade++;
            return true;
        }
        else if(elemento.estado == Estado::OCUPADO && elemento.chave == chave){

            elemento.valor = valor;
            return true;
        }
        else if(elemento.estado == Estado::REMOVIDO && posRemovido == -1){ 
            posRemovido = indice;
        }
    }
    if(posRemovido != -1){
        this->array[posRemovido].chave = chave;
        this->array[posRemovido].valor = valor;
        this->array[posRemovido].estado = Estado::OCUPADO;
        this->quantidade++;
        return true;
    } else{
        throw std::overflow_error ("Tabela cheia.");
    }
		
	}


























































    ConsistenciaStatus checarConsistencia() const
    {
        int contador = 0;
        std::unordered_set<std::string> chaves;

        for (int i = 0; i < this->capacidade; ++i)
        {
            const Elemento& e = this->array[i];

            if (e.estado == Estado::OCUPADO)
            {
                contador++;

                // Verifica duplicatas
                if (chaves.count(e.chave) > 0)
                {
                    return ConsistenciaStatus::CHAVE_DUPLICADA;
                }
                chaves.insert(e.chave);
            }
        }

        if (contador != this->quantidade)
        {
            return ConsistenciaStatus::QUANTIDADE_INCORRETA;
        }

        return ConsistenciaStatus::OK;
    }

    int tamanho() const 
    {
        return quantidade;
    }

    bool vazia() const
    {
        return this->quantidade == 0;
    }

    bool cheia() const 
    {
        return this->capacidade == this->quantidade;
    }

    void imprimir() const
    {
        for (int i = 0; i < this->capacidade; ++i)
        {
            const Elemento& e = this->array[i];

            std::cout << "[" << i << "]: ";

            switch (e.estado)
            {
                case Estado::LIVRE:
                    std::cout << "LIVRE";
                    break;
                case Estado::REMOVIDO:
                    std::cout << "REMOVIDO";
                    break;
                case Estado::OCUPADO:
                    std::cout << "OCUPADO (" << e.chave << ", " << e.valor << ")";
                    break;
            }

            std::cout << std::endl;
        }
    }
};

#endif /* TABELA_HASH_H */
