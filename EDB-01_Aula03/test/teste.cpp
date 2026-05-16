#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Lista.h"
#include <string>
#include <stdexcept>

TEST_CASE("Estado inicial da lista") {
    Lista lista;
    REQUIRE(lista.imprimir() == "{}");
    CHECK(lista.tamanho() == 0);
    CHECK_THROWS_AS(lista.primeiroElemento(), std::out_of_range);
    CHECK_THROWS_AS(lista.ultimoElemento(), std::out_of_range);
}

TEST_CASE("inserirInicio - Primeira inserção deve atualizar ponteiros 'primeiro' e 'ultimo'") {
    Lista lista;

    lista.inserirInicio("SPFC");
    REQUIRE(lista.imprimir() == "{SPFC}");
    CHECK(lista.tamanho() == 1);
    CHECK(lista.primeiroElemento() == "SPFC");
    CHECK(lista.ultimoElemento() == "SPFC");
}

TEST_CASE("inserirInicio - Sucessivas inserções no início") {
    Lista lista;

    lista.inserirInicio("C");
    REQUIRE(lista.imprimir() == "{C}");
    CHECK(lista.tamanho() == 1);
    CHECK(lista.primeiroElemento() == "C");
    CHECK(lista.ultimoElemento() == "C");

    lista.inserirInicio("F");
    REQUIRE(lista.imprimir() == "{F, C}");
    CHECK(lista.tamanho() == 2);
    CHECK(lista.primeiroElemento() == "F");
    CHECK(lista.ultimoElemento() == "C");

    lista.inserirInicio("P");
    REQUIRE(lista.imprimir() == "{P, F, C}");
    CHECK(lista.tamanho() == 3);
    CHECK(lista.primeiroElemento() == "P");
    CHECK(lista.ultimoElemento() == "C");

    lista.inserirInicio("S");
    REQUIRE(lista.imprimir() == "{S, P, F, C}");
    CHECK(lista.tamanho() == 4);
    CHECK(lista.primeiroElemento() == "S");
    CHECK(lista.ultimoElemento() == "C");
}

TEST_CASE("inserirFim - Primeira inserção deve atualizar ponteiros 'primeiro' e 'ultimo'") {
    Lista lista;

    lista.inserirFim("SPFC");
    REQUIRE(lista.imprimir() == "{SPFC}");
    CHECK(lista.tamanho() == 1);
    CHECK(lista.primeiroElemento() == "SPFC");
    CHECK(lista.ultimoElemento() == "SPFC");
}

TEST_CASE("inserirFim - Sucessivas inserções no fim") {
    Lista lista;

    lista.inserirFim("S");
    REQUIRE(lista.imprimir() == "{S}");
    CHECK(lista.tamanho() == 1);

    lista.inserirFim("P");
    REQUIRE(lista.imprimir() == "{S, P}");
    CHECK(lista.tamanho() == 2);

    lista.inserirFim("F");
    REQUIRE(lista.imprimir() == "{S, P, F}");
    CHECK(lista.tamanho() == 3);

    lista.inserirFim("C");
    REQUIRE(lista.imprimir() == "{S, P, F, C}");
    CHECK(lista.tamanho() == 4);
}

TEST_CASE("removerInicio - Remoção em lista vazia lança exceção") {
    Lista lista;
    CHECK_THROWS_AS(lista.removerInicio(), std::underflow_error);
}

TEST_CASE("removerInicio - Remoção no início após inserções no fim") {
    Lista lista;
    lista.inserirFim("S");
    lista.inserirFim("P");
    lista.inserirFim("F");
    lista.inserirFim("C");
    REQUIRE(lista.imprimir() == "{S, P, F, C}");

    CHECK(lista.removerInicio() == true);
    REQUIRE(lista.imprimir() == "{P, F, C}");
    CHECK(lista.tamanho() == 3);

    CHECK(lista.removerInicio() == true);
    REQUIRE(lista.imprimir() == "{F, C}");
    CHECK(lista.tamanho() == 2);

    CHECK(lista.removerInicio() == true);
    REQUIRE(lista.imprimir() == "{C}");
    CHECK(lista.tamanho() == 1);

    CHECK(lista.removerInicio() == true);
    REQUIRE(lista.imprimir() == "{}");
    CHECK(lista.tamanho() == 0);
}

TEST_CASE("removerFim - Remoção em lista vazia lança exceção") {
    Lista lista;
    CHECK_THROWS_AS(lista.removerFim(), std::underflow_error);
}

TEST_CASE("removerFim - Remoção no fim após sucessivas inserções no fim") {
    Lista lista;
    lista.inserirFim("S");
    lista.inserirFim("P");
    lista.inserirFim("F");
    lista.inserirFim("C");

    CHECK(lista.removerFim() == true);
    REQUIRE(lista.imprimir() == "{S, P, F}");
    CHECK(lista.tamanho() == 3);

    CHECK(lista.removerFim() == true);
    REQUIRE(lista.imprimir() == "{S, P}");
    CHECK(lista.tamanho() == 2);

    CHECK(lista.removerFim() == true);
    REQUIRE(lista.imprimir() == "{S}");
    CHECK(lista.tamanho() == 1);

    CHECK(lista.removerFim() == true);
    REQUIRE(lista.imprimir() == "{}");
    CHECK(lista.tamanho() == 0);
}

TEST_CASE("inserirNaPosicao - Inserção na i-ésima posição válida") {
    Lista lista;

    CHECK(lista.inserirNaPosicao(1, "S") == true); // início
    REQUIRE(lista.imprimir() == "{S}");
    CHECK(lista.tamanho() == 1);
    
    CHECK(lista.inserirNaPosicao(2, "C") == true); // fim
    REQUIRE(lista.imprimir() == "{S, C}");
    CHECK(lista.tamanho() == 2);
    
    CHECK(lista.inserirNaPosicao(2, "P") == true); // meio
    REQUIRE(lista.imprimir() == "{S, P, C}");
    CHECK(lista.tamanho() == 3);

    CHECK(lista.inserirNaPosicao(3, "F") == true); // meio
    REQUIRE(lista.imprimir() == "{S, P, F, C}");
    CHECK(lista.tamanho() == 4);

    CHECK(lista.inserirNaPosicao(5, "!") == true); // fim
    REQUIRE(lista.imprimir() == "{S, P, F, C, !}");
    CHECK(lista.tamanho() == 5);
}

TEST_CASE("inserirNaPosicao - Inserção na i-ésima posição inválida") {
    Lista lista;

    CHECK(lista.inserirNaPosicao(1, "S") == true); // início
    CHECK(lista.inserirNaPosicao(2, "C") == true); // fim
    CHECK(lista.inserirNaPosicao(2, "P") == true); // meio
    CHECK(lista.inserirNaPosicao(3, "F") == true); // meio
    REQUIRE(lista.imprimir() == "{S, P, F, C}");

    CHECK_THROWS_AS(lista.inserirNaPosicao(-1, "X"), std::out_of_range);
    CHECK_THROWS_AS(lista.inserirNaPosicao( 0, "X"), std::out_of_range);
    CHECK_THROWS_AS(lista.inserirNaPosicao( lista.tamanho()+2, "X"), std::out_of_range);
    CHECK_THROWS_AS(lista.inserirNaPosicao( lista.tamanho()+3, "X"), std::out_of_range);
}

TEST_CASE("removerNaPosicao - Remoção na i-ésima posição em lista vazia lança exceção") {
    Lista lista;
    CHECK_THROWS_AS(lista.removerNaPosicao(1), std::underflow_error); 
}

TEST_CASE("removerNaPosicao - Remoção na i-ésima posição válida") {
    Lista lista;
    lista.inserirFim("S");
    lista.inserirFim("P");
    lista.inserirFim("F");
    lista.inserirFim("C");
    lista.inserirFim("!");
    REQUIRE(lista.imprimir() == "{S, P, F, C, !}");

    CHECK(lista.tamanho() == 5);

    CHECK(lista.removerNaPosicao(1) == true); // remove "S", permanece PFC!
    REQUIRE(lista.imprimir() == "{P, F, C, !}");
    CHECK(lista.tamanho() == 4);

    CHECK(lista.removerNaPosicao(4) == true); // remove "!", permanece PFC
    REQUIRE(lista.imprimir() == "{P, F, C}");
    CHECK(lista.tamanho() == 3);

    CHECK(lista.removerNaPosicao(2) == true); // remove "F", permanece PC
    REQUIRE(lista.imprimir() == "{P, C}");
    CHECK(lista.tamanho() == 2);

    CHECK(lista.removerNaPosicao(2) == true); // remove "C", permanece P
    REQUIRE(lista.imprimir() == "{P}");
    CHECK(lista.tamanho() == 1);

    CHECK(lista.removerNaPosicao(1) == true);  // remove "P", fica vazia
    REQUIRE(lista.imprimir() == "{}");
    CHECK(lista.tamanho() == 0);
    CHECK_THROWS_AS(lista.primeiroElemento(), std::out_of_range);
    CHECK_THROWS_AS(lista.ultimoElemento(), std::out_of_range);
}

TEST_CASE("removerNaPosicao - Remoção na i-ésima posição inválida") {
    Lista lista;
    lista.inserirFim("S");
    lista.inserirFim("P");
    lista.inserirFim("F");
    lista.inserirFim("C");
    lista.inserirFim("!");
    REQUIRE(lista.imprimir() == "{S, P, F, C, !}");

    CHECK_THROWS_AS(lista.removerNaPosicao(-1), std::out_of_range);
    CHECK_THROWS_AS(lista.removerNaPosicao( 0), std::out_of_range);
    CHECK_THROWS_AS(lista.removerNaPosicao(lista.tamanho()+1), std::out_of_range);
    CHECK_THROWS_AS(lista.removerNaPosicao(lista.tamanho()+2), std::out_of_range);
}

TEST_CASE("Acesso à i-ésima posição válida") {
    Lista lista;
    lista.inserirFim("S");
    lista.inserirFim("P");
    lista.inserirFim("F");
    lista.inserirFim("C");
    lista.inserirFim("!");
    REQUIRE(lista.imprimir() == "{S, P, F, C, !}");

    CHECK_NOTHROW(lista.elementoNaPosicao(1));
    CHECK(lista.elementoNaPosicao(1) == "S");

    CHECK_NOTHROW(lista.elementoNaPosicao(2));
    CHECK(lista.elementoNaPosicao(2) == "P");

    CHECK_NOTHROW(lista.elementoNaPosicao(3));
    CHECK(lista.elementoNaPosicao(3) == "F");

    CHECK_NOTHROW(lista.elementoNaPosicao(4));
    CHECK(lista.elementoNaPosicao(4) == "C");

    CHECK_NOTHROW(lista.elementoNaPosicao(5));
    CHECK(lista.elementoNaPosicao(5) == "!");
}

TEST_CASE("Acesso à i-ésima posição inválida") {
    Lista lista;
    lista.inserirFim("S");
    lista.inserirFim("P");
    lista.inserirFim("F");
    lista.inserirFim("C");
    lista.inserirFim("!");
    REQUIRE(lista.imprimir() == "{S, P, F, C, !}");

    CHECK_THROWS_AS(lista.elementoNaPosicao(-1), std::out_of_range);
    CHECK_THROWS_AS(lista.elementoNaPosicao( 0), std::out_of_range);
    CHECK_THROWS_AS(lista.elementoNaPosicao(lista.tamanho()+1), std::out_of_range);
    CHECK_THROWS_AS(lista.elementoNaPosicao(lista.tamanho()+2), std::out_of_range);
}

TEST_CASE("removerTodos - Remoção em lista vazia lança exceção") {
    Lista lista;
    CHECK_THROWS_AS(lista.removerTodos("a"), std::out_of_range);
}

TEST_CASE("removerTodos - remove com sucesso de lista com um só elemento") {
    Lista lista;
    lista.inserirFim("S");
    REQUIRE(lista.imprimir() == "{S}");
    CHECK(lista.tamanho() == 1);

    int removidos = lista.removerTodos("S");
    CHECK(removidos == 1);
    CHECK(lista.tamanho() == 0);
    REQUIRE(lista.imprimir() == "{}");
    REQUIRE_THROWS_AS(lista.primeiroElemento(), std::out_of_range);
    REQUIRE_THROWS_AS(lista.ultimoElemento(), std::out_of_range);
}

TEST_CASE("removerTodos - tenta remover elemento que não existe de lista com um só elemento") {
    Lista lista;
    lista.inserirFim("S");
    REQUIRE(lista.imprimir() == "{S}");
    CHECK(lista.tamanho() == 1);

    int removidos = lista.removerTodos("X");
    CHECK(removidos == 0);
    CHECK(lista.tamanho() == 1);
    REQUIRE(lista.imprimir() == "{S}");
    REQUIRE(lista.primeiroElemento() == "S");
    REQUIRE(lista.ultimoElemento() == "S");
}

TEST_CASE("removerTodos - tenta remover elemento que não existe de lista com múltiplos elementos") {
    Lista lista;
    lista.inserirFim("S");
    lista.inserirFim("S");
    lista.inserirFim("P");
    lista.inserirFim("P");
    lista.inserirFim("F");
    lista.inserirFim("F");
    lista.inserirFim("C");
    lista.inserirFim("C");
    REQUIRE(lista.imprimir() == "{S, S, P, P, F, F, C, C}");
    CHECK(lista.tamanho() == 8);

    int removidos = lista.removerTodos("X");
    CHECK(removidos == 0);
    CHECK(lista.tamanho() == 8);
    REQUIRE(lista.imprimir() == "{S, S, P, P, F, F, C, C}");
    REQUIRE(lista.primeiroElemento() == "S");
    REQUIRE(lista.ultimoElemento() == "C");
}

TEST_CASE("removerTodos - remove todos elementos de lista que tem múltiplos elementos iguais entre si") {
    Lista lista;
    lista.inserirFim("S");
    lista.inserirFim("S");
    lista.inserirFim("S");
    lista.inserirFim("S");
    lista.inserirFim("S");
    lista.inserirFim("S");
    lista.inserirFim("S");
    lista.inserirFim("S");
    REQUIRE(lista.imprimir() == "{S, S, S, S, S, S, S, S}");
    CHECK(lista.tamanho() == 8);

    int removidos = lista.removerTodos("S");
    CHECK(removidos == 8);
    CHECK(lista.tamanho() == 0);
    REQUIRE(lista.imprimir() == "{}");
    REQUIRE_THROWS_AS(lista.primeiroElemento(), std::out_of_range);
    REQUIRE_THROWS_AS(lista.ultimoElemento(), std::out_of_range);
}

TEST_CASE("removerTodos - remove elementos que estão no fim e lista permanece com elementos") {
    Lista lista;
    lista.inserirFim("S");
    lista.inserirFim("S");
    lista.inserirFim("P");
    lista.inserirFim("P");
    lista.inserirFim("F");
    lista.inserirFim("F");
    lista.inserirFim("C");
    lista.inserirFim("C");
    REQUIRE(lista.imprimir() == "{S, S, P, P, F, F, C, C}");
    CHECK(lista.tamanho() == 8);

    int removidos = lista.removerTodos("C");
    CHECK(removidos == 2);
    CHECK(lista.tamanho() == 6);
    REQUIRE(lista.imprimir() == "{S, S, P, P, F, F}");
    REQUIRE(lista.primeiroElemento() == "S");
    REQUIRE(lista.ultimoElemento() == "F");
}

TEST_CASE("removerTodos - remove elementos que estão no início e lista permanece com elementos") {
    Lista lista;
    lista.inserirFim("S");
    lista.inserirFim("S");
    lista.inserirFim("P");
    lista.inserirFim("P");
    lista.inserirFim("F");
    lista.inserirFim("F");
    lista.inserirFim("C");
    lista.inserirFim("C");
    REQUIRE(lista.imprimir() == "{S, S, P, P, F, F, C, C}");
    CHECK(lista.tamanho() == 8);

    int removidos = lista.removerTodos("S");
    CHECK(removidos == 2);
    CHECK(lista.tamanho() == 6);
    REQUIRE(lista.imprimir() == "{P, P, F, F, C, C}");
    REQUIRE(lista.primeiroElemento() == "P");
    REQUIRE(lista.ultimoElemento() == "C");
}

TEST_CASE("removerTodos - remove elementos consecutivos que estão no meio e lista permanece com elementos") {
    Lista lista;
    lista.inserirFim("S");
    lista.inserirFim("S");
    lista.inserirFim("P");
    lista.inserirFim("P");
    lista.inserirFim("F");
    lista.inserirFim("F");
    lista.inserirFim("C");
    lista.inserirFim("C");
    REQUIRE(lista.imprimir() == "{S, S, P, P, F, F, C, C}");
    CHECK(lista.tamanho() == 8);

    int removidos = lista.removerTodos("P");
    CHECK(removidos == 2);
    CHECK(lista.tamanho() == 6);
    REQUIRE(lista.imprimir() == "{S, S, F, F, C, C}");
    REQUIRE(lista.primeiroElemento() == "S");
    REQUIRE(lista.ultimoElemento() == "C");
}

TEST_CASE("removerTodos - remove elementos não-consecutivos que estão no meio e lista permanece com elementos") {
    Lista lista;
    lista.inserirFim("S");
    lista.inserirFim("S");
    lista.inserirFim("P");
    lista.inserirFim("F");
    lista.inserirFim("P");
    lista.inserirFim("F");
    lista.inserirFim("C");
    lista.inserirFim("C");
    REQUIRE(lista.imprimir() == "{S, S, P, F, P, F, C, C}");
    CHECK(lista.tamanho() == 8);

    int removidos = lista.removerTodos("P");
    CHECK(removidos == 2);
    CHECK(lista.tamanho() == 6);
    REQUIRE(lista.imprimir() == "{S, S, F, F, C, C}");
    REQUIRE(lista.primeiroElemento() == "S");
    REQUIRE(lista.ultimoElemento() == "C");
}

TEST_CASE("removerTodos - remove elementos até lista ficar vazia") {
    Lista lista;
    lista.inserirFim("S");
    lista.inserirFim("S");
    lista.inserirFim("P");
    lista.inserirFim("F");
    lista.inserirFim("P");
    lista.inserirFim("F");
    lista.inserirFim("C");
    lista.inserirFim("C");
    REQUIRE(lista.imprimir() == "{S, S, P, F, P, F, C, C}");
    CHECK(lista.tamanho() == 8);

    // Remove do meio
    int removidos = lista.removerTodos("P");
    CHECK(removidos == 2);
    CHECK(lista.tamanho() == 6);
    REQUIRE(lista.imprimir() == "{S, S, F, F, C, C}");
    REQUIRE(lista.primeiroElemento() == "S");
    REQUIRE(lista.ultimoElemento() == "C");

    // Remove do fim
    removidos = lista.removerTodos("C");
    CHECK(removidos == 2);
    CHECK(lista.tamanho() == 4);
    REQUIRE(lista.imprimir() == "{S, S, F, F}");
    REQUIRE(lista.primeiroElemento() == "S");
    REQUIRE(lista.ultimoElemento() == "F");

    // Remove do início
    removidos = lista.removerTodos("S");
    CHECK(removidos == 2);
    CHECK(lista.tamanho() == 2);
    REQUIRE(lista.imprimir() == "{F, F}");
    REQUIRE(lista.primeiroElemento() == "F");
    REQUIRE(lista.ultimoElemento() == "F");

    // Remove do início
    removidos = lista.removerTodos("F");
    CHECK(removidos == 2);
    CHECK(lista.tamanho() == 0);
    REQUIRE(lista.imprimir() == "{}");
    REQUIRE_THROWS_AS(lista.primeiroElemento(), std::out_of_range);
    REQUIRE_THROWS_AS(lista.ultimoElemento(), std::out_of_range);
}