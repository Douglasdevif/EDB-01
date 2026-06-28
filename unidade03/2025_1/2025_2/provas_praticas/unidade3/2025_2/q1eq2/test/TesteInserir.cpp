#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <unordered_map>
#include "../../lib/doctest.h"
#include "../header/TabelaHash.h"
#include "../header/TabelaHashTestHelper.h"

std::unordered_map<std::string, std::string> dados = 
{
    {"AAA", "1"},
    {"BAA", "2"},
    {"ABA", "3"},
    {"AAC", "4"},
    {"AAD", "5"},
    {"ABC", "6"},
    {"ACD", "7"},
    {"ABB", "8"},
    {"CAD", "9"},
    {"SPFC", "10"},
    {"FPCS", "11"},
    {"SAB", "12"},
};

TEST_CASE("Inserir ordenado - sem atualização") 
{
    TabelaHash tabela(5);

    // Inserções para garantir colisões e encadeamento
    for (auto& [chave, valor] : dados)
    {
        tabela.inserir(chave, valor);
    }

    // Verifica se todos os buckets estão em ordem crescente pela chave
    REQUIRE(TabelaHashTestHelper::todosBucketsOrdenados(tabela));

	CHECK(tabela.tamanho() == dados.size());

	// Copia os dados para verificação posterior
    std::unordered_set<std::string> chavesInseridas;
    std::unordered_set<std::string> valoresInseridos;
    for (auto& [chave, valor] : dados)
    {
        chavesInseridas.insert(chave);
        valoresInseridos.insert(valor);
    }

    CHECK( TabelaHashTestHelper::todosJaEstavam(tabela, chavesInseridas, valoresInseridos) );
	CHECK( TabelaHashTestHelper::todosAindaEstao(tabela, chavesInseridas, valoresInseridos) );
}

TEST_CASE("Inserir ordenado - com atualização") 
{
    TabelaHash tabela(5);

    std::unordered_map<std::string, std::string> atualizacoes = 
	{
		{"ABA", "13"},
        {"AAC", "14"},
        {"AAD", "15"},
		{"ABC", "16"},
    };

	// Insere pela primeira vez, gerando colisões e encadeamento
    for (auto& [chave, valor] : dados)
    {
        tabela.inserir(chave, valor);
    }

	// Atualiza os valores, pois as chaves já existem
	for (auto& [chave, valor] : atualizacoes)
    {
        CHECK( tabela.inserir(chave, valor) == true );
        CHECK(tabela.tamanho() == dados.size());
    }

    // Verifica se todos os buckets estão em ordem crescente pela chave
    REQUIRE(TabelaHashTestHelper::todosBucketsOrdenados(tabela));

	CHECK(tabela.tamanho() == dados.size());

	std::unordered_map<std::string, std::string> dadosAtualizados = dados;

	for (auto& [chave, valor] : atualizacoes) 
	{
		dadosAtualizados[chave] = valor; // sobrescreve os valores atualizados
	}

	std::unordered_set<std::string> chavesInseridas;
	std::unordered_set<std::string> valoresInseridos;
	
	for (auto& [chave, valor] : dadosAtualizados) 
	{
		chavesInseridas.insert(chave);
		valoresInseridos.insert(valor);
	}

	CHECK( TabelaHashTestHelper::todosJaEstavam(tabela, chavesInseridas, valoresInseridos) );
	CHECK( TabelaHashTestHelper::todosAindaEstao(tabela, chavesInseridas, valoresInseridos) );
}
