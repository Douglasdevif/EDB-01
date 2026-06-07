#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "ListaDuplamenteEncadeada.h"
#include <iostream>
using namespace std;

TEST_CASE("'Referência' já existe na lista, por isso insere elemento e retorna true") 
{
    ListaDuplamenteEncadeada lista("A");

    CHECK( lista.imprimir() == "A" );
    CHECK( lista.checarConsistencia() == OK );
    CHECK( lista.tamanho() == 1 );

    bool inseriu = lista.inserirAntes("B", "A");

    CHECK( inseriu == true );
    CHECK( lista.imprimir() == "B<->A" );
    CHECK( lista.checarConsistencia() == OK );
    CHECK( lista.tamanho() == 2 );

    inseriu = lista.inserirAntes("B", "A");

    CHECK( inseriu == true );
    CHECK( lista.imprimir() == "B<->B<->A" );
    CHECK( lista.checarConsistencia() == OK );
    CHECK( lista.tamanho() == 3 );

    inseriu = lista.inserirAntes("C", "A");

    CHECK( inseriu == true );
    CHECK( lista.imprimir() == "B<->B<->C<->A" );
    CHECK( lista.checarConsistencia() == OK );
    CHECK( lista.tamanho() == 4 );

    inseriu = lista.inserirAntes("C", "B");

    CHECK( inseriu == true );
    CHECK( lista.imprimir() == "C<->B<->B<->C<->A" );
    CHECK( lista.checarConsistencia() == OK );
    CHECK( lista.tamanho() == 5 );

    inseriu = lista.inserirAntes("D", "C");

    CHECK( inseriu == true );
    CHECK( lista.imprimir() == "D<->C<->B<->B<->C<->A" );
    CHECK( lista.checarConsistencia() == OK );
    CHECK( lista.tamanho() == 6 );
}

TEST_CASE("'Referência' não existe na lista, por isso não insere elemento e retorna false") 
{
    ListaDuplamenteEncadeada lista("A");
    lista.inserirAntes("B", "A");
    lista.inserirAntes("B", "A");
    lista.inserirAntes("C", "A");

    REQUIRE( lista.imprimir() == "B<->B<->C<->A" );
    REQUIRE( lista.checarConsistencia() == OK );
    REQUIRE( lista.tamanho() == 4 );

    bool inseriu = lista.inserirAntes("C", "F");

    CHECK( inseriu == false );
    CHECK( lista.imprimir() == "B<->B<->C<->A" );
    CHECK( lista.checarConsistencia() == OK );
    CHECK( lista.tamanho() == 4 );

    inseriu = lista.inserirAntes("B", "X");

    CHECK( inseriu == false );
    CHECK( lista.imprimir() == "B<->B<->C<->A" );
    CHECK( lista.checarConsistencia() == OK );
    CHECK( lista.tamanho() == 4 );

    inseriu = lista.inserirAntes("A", "Z");

    CHECK( inseriu == false );
    CHECK( lista.imprimir() == "B<->B<->C<->A" );
    CHECK( lista.checarConsistencia() == OK );
    CHECK( lista.tamanho() == 4 );
}
