//
//  TesteRedimensionar.h
//
//  Criado por Eiji Adachi Medeiros Barbosa
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <iostream>
#include "doctest.h"
#include "../header/TabelaHash.h"
#include "../header/TabelaHashTestHelper.h"

using namespace std;

TEST_CASE("Testando método TabelaHash::redimensionar")
{
    // Arrange    
    TabelaHash tabela(17);

    vector<string> chaves = {"CHAVE1", "1CHAVE", "E1CHAV", "VE1CHA", "CHAVE7", "7CHAVE", "E7CHAV", "VE7CHA"};
    vector<string> valores= {"V1", "V2", "V3", "V4", "V5", "V6", "V7", "V8"};
    
    vector<tuple<int, string, string>> dados = {
        {TabelaHashTestHelper::hash(tabela, chaves[0])+0, chaves[0], valores[0]},
        {TabelaHashTestHelper::hash(tabela, chaves[1])+1, chaves[1], valores[1]},
        {TabelaHashTestHelper::hash(tabela, chaves[2])+2, chaves[2], valores[2]},
        {TabelaHashTestHelper::hash(tabela, chaves[3])+3, chaves[3], valores[3]},
        {TabelaHashTestHelper::hash(tabela, chaves[4])+0, chaves[4], valores[4]},
        {TabelaHashTestHelper::hash(tabela, chaves[5])+1, chaves[5], valores[5]},
        {TabelaHashTestHelper::hash(tabela, chaves[6])+2, chaves[6], valores[6]},
        {TabelaHashTestHelper::hash(tabela, chaves[7])+3, chaves[7], valores[7]},
    };    
    
    TabelaHashTestHelper::preencherTabela(tabela, dados);

    // Act
    TabelaHashTestHelper::aumentar(tabela);

    // Assert

    // Cheque que não existem chaves repetidas
    CHECK( tabela.checarConsistencia() == ConsistenciaStatus::OK );

    // Cheque que todos elementos que estavam antes na tabela, permaneceram nela após aumentar
    // Ou seja, cheque que nenhum elemento foi perdido sem querer
    CHECK( TabelaHashTestHelper::todosPermanecem(tabela, dados) );

    // Cheque que todos elementos que estão na tabela após aumentar já estavam nela anteriormente
    // Ou seja, cheque que nenhum elemento novo foi inserido na tabela sem querer
    CHECK( TabelaHashTestHelper::todosJaEstavam(tabela, dados) );       
}