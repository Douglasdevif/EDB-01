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
    {"CSPF", "12"},
	{"FCPS", "13"},
	{"PFCS", "14"},
	{"CFSP", "15"},
};

TEST_CASE("TabelaHash - Remover chave existente") {
	TabelaHash tabela;

	TabelaHashTestHelper::inicializar(tabela, dados);
	REQUIRE(tabela.checarConsistencia() == ConsistenciaStatus::OK);
	REQUIRE(tabela.tamanho() == dados.size());

	CHECK(tabela.remover("AAA") == true );
	CHECK(tabela.tamanho() == dados.size() - 1);
	CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);
	
	CHECK(tabela.remover("BAA") == true );
	CHECK(tabela.tamanho() == dados.size() - 2);
	CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);

	CHECK(tabela.remover("ABA") == true );
	CHECK(tabela.tamanho() == dados.size() - 3);
	CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);

	CHECK(tabela.remover("SPFC") == true );
	CHECK(tabela.tamanho() == dados.size() - 4);
	CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);

	CHECK(tabela.remover("CFSP") == true );
	CHECK(tabela.tamanho() == dados.size() - 5);
	CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);	

	CHECK(tabela.remover("FPCS") == true );
	CHECK(tabela.tamanho() == dados.size() - 6);
	CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);	
}

TEST_CASE("TabelaHash - Remover chave inexistente") {
	TabelaHash tabela;

	TabelaHashTestHelper::inicializar(tabela, dados);
	REQUIRE(tabela.checarConsistencia() == ConsistenciaStatus::OK);
	REQUIRE(tabela.tamanho() == dados.size());

	CHECK_FALSE(tabela.remover("K"));
	CHECK(tabela.tamanho() == dados.size());
	CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);	

	CHECK_FALSE(tabela.remover("L"));
	CHECK(tabela.tamanho() == dados.size());
	CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);	

	CHECK_FALSE(tabela.remover("M"));
	CHECK(tabela.tamanho() == dados.size());
	CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);	

	CHECK_FALSE(tabela.remover("N"));
	CHECK(tabela.tamanho() == dados.size());
	CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);	

	CHECK_FALSE(tabela.remover("O"));
	CHECK(tabela.tamanho() == dados.size());
	CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);	

	CHECK_FALSE(tabela.remover("P"));
	CHECK(tabela.tamanho() == dados.size());
	CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);	
}