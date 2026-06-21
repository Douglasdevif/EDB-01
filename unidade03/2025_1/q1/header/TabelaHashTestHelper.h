//
//  TabelaHashTestHelper.h
//
//  Criado por Eiji Adachi Medeiros Barbosa
//

#include "TabelaHash.h"
#include <unordered_set>

class TabelaHashTestHelper {
public:
    static bool todosJaEstavam(const TabelaHash& tabela, 
                           const std::unordered_set<std::string>& chavesEsperadas,
                           const std::unordered_set<std::string>& valoresEsperados)
    {
        for (int i = 0; i < tabela.capacidade; ++i)
        {
            No* atual = tabela.array[i];
            while (atual != nullptr)
            {
                if (chavesEsperadas.count(atual->chave) == 0 || valoresEsperados.count(atual->valor) == 0)
                {
                    return false;
                }
                atual = atual->proximo;
            }
        }
        return true;
    }

    static bool todosAindaEstao(const TabelaHash& tabela, 
                            const std::unordered_set<std::string>& chavesEsperadas,
                            const std::unordered_set<std::string>& valoresEsperados)
    {
        std::unordered_set<std::string> chavesEncontradas;
        std::unordered_set<std::string> valoresEncontrados;

        for (int i = 0; i < tabela.capacidade; ++i)
        {
            No* atual = tabela.array[i];
            while (atual != nullptr)
            {
                chavesEncontradas.insert(atual->chave);
                valoresEncontrados.insert(atual->valor);
                atual = atual->proximo;
            }
        }

        for (const auto& chave : chavesEsperadas)
        {
            if (chavesEncontradas.count(chave) == 0)
                return false;
        }

        for (const auto& valor : valoresEsperados)
        {
            if (valoresEncontrados.count(valor) == 0)
                return false;
        }

        return true;
    }

    static bool todosBucketsOrdenados(const TabelaHash& tabela) {
        for (int i = 0; i < tabela.capacidade; ++i) {
            No* atual = tabela.array[i];
            while (atual != nullptr && atual->proximo != nullptr) {
                if (atual->chave > atual->proximo->chave) {
                    return false;
                }
                atual = atual->proximo;
            }
        }
        return true;
    }
};
