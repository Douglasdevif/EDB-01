//
//  TabelaHash.h
//
//  Created by Eiji Adachi Medeiros Barbosa
//
#define CHECK_STATUS
#ifndef TABELA_HASH_H
#define TABELA_HASH_H

#include <string>
#include <iostream>
#include <optional>
#include <unordered_set>

struct No {
	std::string chave;
	std::string valor;
	No* proximo;

	No(const std::string& c, const std::string& v) : chave(c), valor(v), proximo(nullptr) {}
};

enum class ConsistenciaStatus {
    OK = 0,
    PONTEIRO_INVALIDO,
    CICLO_DETECTADO,
    DESALINHAMENTO_HASH_INDICE,
    QUANTIDADE_INCORRETA,
	CHAVE_DUPLICADA
};

class TabelaHash {
friend class TabelaHashTestHelper;

private:
	No** array;
	int capacidade;
	int quantidade;

	static constexpr int CAPACIDADE_MINIMA = 17;
	static constexpr float FATOR_CARGA_MAX = 2.0f;
	static constexpr float FATOR_CARGA_MIN = 0.25f;

	unsigned int valorHash(const std::string& chave) const {
		unsigned int valorHash = 0;
		for (char c : chave) {
			valorHash += static_cast<unsigned int>(c);
		}
		return valorHash;
	}

	int hash(const std::string& chave) const {
		return this->valorHash(chave) % capacidade;
	}

public:
	TabelaHash(int cap = CAPACIDADE_MINIMA) : capacidade(cap), quantidade(0) {
		array = new No*[capacidade];		
		for (int i = 0; i < capacidade; ++i) {
			array[i] = nullptr;
		}
	}

	~TabelaHash() {
		for (int i = 0; i < capacidade; ++i) {
			No* no = array[i];
			while (no != nullptr) {
				No* temp = no;
				no = no->proximo;
				delete temp;
			}
		}
		delete[] array;
	}









	

	bool inserir(const std::string& chave, const std::string& valor)                                                                                                                                                                                // EAMB 1.0
	{


	auto indice = hash(chave);
    No* no = this->array[indice];
    No* anterior = nullptr;

    while (no != nullptr && no->chave < chave) {
        anterior = no;
        no = no->proximo;
    }
    if (no != nullptr && no->chave == chave) {
        no->valor = valor;
        return true;
    }
    No* novo = new No(chave, valor);

    if (anterior == nullptr) {
        novo->proximo = this->array[indice];
        this->array[indice] = novo;
    } else {
        novo->proximo = no;
        anterior->proximo = novo;
    }
    this->quantidade++;
    return true;

		// inserir ordenado
		//auto indice = hash(chave);
		//No* no = array[indice];
		//No* anterior = nullptr;

		//while (no != nullptr && no->chave < chave) {
		//	anterior = no;
			//no = no->proximo;
		//}

	}

	bool remover(const std::string& chave)                                                                                                                                                                                                          // EAMB 1.0 
	{
		auto indice = hash(chave);
    
    No* atual = this->array[indice];
    No* anterior = nullptr;

    while (atual != nullptr) {
        if (atual->chave == chave) {

            if (anterior == nullptr) {
                this->array[indice] = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }

            delete atual;
            this->quantidade--;
            return true;
        }
        
        anterior = atual;
        atual = atual->proximo;
    }

    return false;
	}



















































	int tamanho() const {
		return quantidade;
	}

	void imprimir() const {
		for (int i = 0; i < capacidade; ++i) {
			std::cout << "[" << i << "]: ";
			No* no = array[i];
			while (no != nullptr) {
				std::cout << "(" << no->chave << ", " << no->valor << ") → ";
				no = no->proximo;
			}
			std::cout << "nullptr\n";
		}
	}

	ConsistenciaStatus checarConsistencia() const {
		int contadorTotal = 0;
		std::unordered_set<std::string> chavesVisitadas;

		for (int i = 0; i < capacidade; ++i) {
			if(array[i] == nullptr){
				continue;
			}

			No* lento = array[i];
			No* rapido = array[i];

			// Detecta ciclos com algoritmo do Floyd
			while (rapido != nullptr && rapido->proximo != nullptr) {
				rapido = rapido->proximo->proximo;
				lento = lento->proximo;

				if (rapido == lento) {
					return ConsistenciaStatus::CICLO_DETECTADO;
				}
			}

			No* no = array[i];
			while (no != nullptr) {
				// Todos pares no mesmo encadeamento devem possuir o mesmo hash
				if (hash(no->chave) != i) {
					return ConsistenciaStatus::DESALINHAMENTO_HASH_INDICE;
				}
				// Chaves não podem se repetir
				if (chavesVisitadas.count(no->chave)) {
					return ConsistenciaStatus::CHAVE_DUPLICADA;
				}
				chavesVisitadas.insert(no->chave);
				contadorTotal++;
				no = no->proximo;
			}
		}

		if (contadorTotal != quantidade) {
			return ConsistenciaStatus::QUANTIDADE_INCORRETA;
		}

		return ConsistenciaStatus::OK;
	}
};

#endif