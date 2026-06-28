//
//  TesteInserir.cpp
//
//  Criado por Eiji Adachi Medeiros Barbosa
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../header/TabelaHash.h"
#include "../header/TabelaHashTestHelper.h"

using namespace std;

// Teste para inserir um único elemento em uma tabela vazia
TEST_CASE("Inserir um elemento em uma tabela vazia") {
    // Arrange
    TabelaHash tabela;
    auto c1 = "CHAVE";
    auto v1 = "Valor1";
    auto pos1 = TabelaHashTestHelper::hash(tabela, c1);

    // Act
    bool inseriu = tabela.inserir(c1, v1);

    // Assert
    CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);
    
    auto elemento = TabelaHashTestHelper::getElementoNaPosicao(tabela, pos1);

    REQUIRE(elemento.estado == Estado::OCUPADO);
    
    CHECK(elemento.chave == c1);
    CHECK(elemento.valor == v1);
    CHECK(tabela.tamanho() == 1);
    CHECK(inseriu == true);
}

// Teste para inserir dois elementos que colidem
TEST_CASE("Inserir dois elementos que colidem na tabela") {
    // Arrange
    TabelaHash tabela;
    auto c1 = "CHAVE";
    auto v1 = "Valor1";
    auto pos1 = TabelaHashTestHelper::hash(tabela, c1);

    auto c2 = "VECHA";
    auto v2 = "Valor2";
    auto pos2 = TabelaHashTestHelper::hash(tabela, c2);

    REQUIRE(pos1 == pos2); // Assegurando que as chaves vão gerar colisão

    // Act
    bool inseriu1 = tabela.inserir(c1, v1);
    bool inseriu2 = tabela.inserir(c2, v2);

    // Assert
    auto elemento1 = TabelaHashTestHelper::getElementoNaPosicao(tabela, pos1);
    auto elemento2 = TabelaHashTestHelper::getElementoNaPosicao(tabela, pos1 + 1);

    CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);

    REQUIRE(elemento1.estado == Estado::OCUPADO);
    CHECK(elemento1.chave == c1);
    CHECK(elemento1.valor == v1);

    REQUIRE(elemento2.estado == Estado::OCUPADO);
    CHECK(elemento2.chave == c2);
    CHECK(elemento2.valor == v2);

    CHECK(tabela.tamanho() == 2);
    CHECK(inseriu1 == true);
    CHECK(inseriu2 == true);
}

// Teste para atualizar um elemento existente na tabela
TEST_CASE("Atualizar um elemento existente na tabela") {
    // Arrange
    TabelaHash tabela;
    auto c1 = "CHAVE";
    auto v1 = "Valor1";
    auto pos1 = TabelaHashTestHelper::hash(tabela, c1);
    auto novoValor = "Novo";

    // Act
    bool inseriu1 = tabela.inserir(c1, v1);
    bool atualizou = tabela.inserir(c1, novoValor); // Atualiza

    // Assert
    CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);

    auto elemento = TabelaHashTestHelper::getElementoNaPosicao(tabela, pos1);
    REQUIRE(elemento.estado == Estado::OCUPADO);
    CHECK(elemento.chave == c1);
    CHECK(elemento.valor == novoValor);
    CHECK(inseriu1 == true);
    CHECK(atualizou == true);
}

// Teste para inserir em uma tabela já cheia
TEST_CASE("Inserir em uma tabela já cheia deve lançar exceção") {
     // Arrange
    TabelaHash tabela;

    TabelaHashTestHelper::preencherTabelaComOcupado(tabela);
    REQUIRE(tabela.checarConsistencia() == ConsistenciaStatus::OK);
    REQUIRE(tabela.cheia());

    // Act & Assert
    CHECK_THROWS_AS( tabela.inserir("chave", "Valor"), std::overflow_error );
    CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);
}

// Teste para atualizar um elemento em uma tabela já cheia
TEST_CASE("Atualizar valor em uma tabela com todas posições OCUPADO") {
    // Arrange
    TabelaHash tabela;
    TabelaHashTestHelper::preencherTabelaComOcupado(tabela);
    
    REQUIRE(tabela.checarConsistencia() == ConsistenciaStatus::OK);
    REQUIRE(tabela.cheia());

    auto chave = TabelaHashTestHelper::getElementoNaPosicao(tabela, 0).chave;

    // Act
    bool atualizou = tabela.inserir(chave, "Novo");

    // Assert
    CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);

    CHECK(TabelaHashTestHelper::getElementoNaPosicao(tabela, 0).chave == chave);
    CHECK(TabelaHashTestHelper::getElementoNaPosicao(tabela, 0).valor == "Novo");
    CHECK(atualizou == true);
}

// Teste para inserir em uma tabela com algumas posições REMOVIDO
TEST_CASE("Inserir em uma tabela com algumas posições REMOVIDO") {
    // Arrange
    TabelaHash tabela;
    
    auto c1 = "CHAVE";
    auto v1 = "Valor1";
    auto pos1 = TabelaHashTestHelper::hash(tabela, c1);
    Elemento e1;
    e1.chave = c1;
    e1.valor = v1;
    e1.estado = Estado::OCUPADO;

    auto c2 = "VECHA";
    auto v2 = "Valor2";
    Elemento e2;
    e2.chave = c2;
    e2.valor = v2;
    e2.estado = Estado::OCUPADO;
    
    auto c3 = "ECHAV";
    auto v3 = "Valor3";

    Elemento removido1;
    removido1.estado = Estado::REMOVIDO;

    Elemento removido2;
    removido2.estado = Estado::REMOVIDO;

    std::vector<pair<int, Elemento>> dados = {
        {pos1    , e1},
        {pos1 + 1, removido1},
        {pos1 + 2, removido2},
        {pos1 + 3, e2}
    };
    TabelaHashTestHelper::preencherTabela(tabela, dados);
    REQUIRE(tabela.checarConsistencia() == ConsistenciaStatus::OK);

    // Act 
    bool inseriu = tabela.inserir(c3, v3);
    // Assert
    
    CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);
    
    auto elemento = TabelaHashTestHelper::getElementoNaPosicao(tabela, pos1 + 1);
    REQUIRE(elemento.estado != Estado::REMOVIDO);
    CHECK(elemento.chave == c3);
    CHECK(elemento.valor == v3);
    CHECK(inseriu == true);
}

// Teste para atualizar um elemento após uma posição REMOVIDO
TEST_CASE("Atualizar um elemento após uma posição REMOVIDO") {
    // Arrange
    TabelaHash tabela;
    
    auto c1 = "CHAVE";
    auto v1 = "Valor1";
    auto pos1 = TabelaHashTestHelper::hash(tabela, c1);
    Elemento e1;
    e1.chave = c1;
    e1.valor = v1;
    e1.estado = Estado::OCUPADO;

    auto c2 = "VECHA";
    auto v2 = "Valor2";
    Elemento e2;
    e2.chave = c2;
    e2.valor = v2;
    e2.estado = Estado::OCUPADO;

    auto novoValor = "Novo";

    Elemento removido1;
    removido1.estado = Estado::REMOVIDO;

    Elemento removido2;
    removido2.estado = Estado::REMOVIDO;

    std::vector<std::pair<int, Elemento>> dados = {
        {pos1    , e1},
        {pos1 + 1, removido1},
        {pos1 + 2, removido2},
        {pos1 + 3, e2}
    };

    TabelaHashTestHelper::preencherTabela(tabela, dados);
    REQUIRE(tabela.checarConsistencia() == ConsistenciaStatus::OK);

    // Act
    bool atualizou = tabela.inserir(c2, novoValor);

    // Assert
    auto elemento = TabelaHashTestHelper::getElementoNaPosicao(tabela, pos1 + 3);
    REQUIRE(elemento.estado != Estado::REMOVIDO);
    CHECK(elemento.chave == c2);
    CHECK(elemento.valor == novoValor);
    CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);
    CHECK(atualizou == true);
}

// Teste para inserir em uma tabela com todas posições REMOVIDO
TEST_CASE("Inserir em uma tabela com todas posições REMOVIDO") {
    // Arrange
    TabelaHash tabela;

    auto c3 = "ECHAV";
    auto v3 = "Valor3";
    auto pos3 = TabelaHashTestHelper::hash(tabela, c3);

    TabelaHashTestHelper::preencherTabelaComRemovido(tabela);
    REQUIRE(tabela.checarConsistencia() == ConsistenciaStatus::OK);

    // Act
    bool inseriu = tabela.inserir(c3, v3);

    // Assert
    auto elemento = TabelaHashTestHelper::getElementoNaPosicao(tabela, pos3);
    REQUIRE(elemento.estado != Estado::REMOVIDO);
    CHECK(elemento.chave == c3);
    CHECK(elemento.valor == v3);
    CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);
    CHECK(tabela.tamanho() == 1);
    CHECK(inseriu == true);
}
