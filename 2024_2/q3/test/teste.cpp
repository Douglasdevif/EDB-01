#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "palindromo.h"
#include <string>
#include <stack>

using namespace std;

TEST_CASE("Strings que são palíndromo - Sem espaço em branco") 
{
    CHECK( ehPalindromo("ana") == true);
    CHECK( ehPalindromo("arara") == true);
    CHECK( ehPalindromo("racecar") == true);
    CHECK( ehPalindromo("rotor") == true);
    CHECK( ehPalindromo("civic") == true);
}

TEST_CASE("Strings que são palíndromo - Com espaço em branco") 
{
    CHECK( ehPalindromo("a man a plan a canal panama") == true);
    CHECK( ehPalindromo("a nut for a jar of tuna") == true);
    CHECK( ehPalindromo("no lemon no melon") == true);
    CHECK( ehPalindromo("madam im adam") == true);
    CHECK( ehPalindromo("step on no pets") == true);
}

TEST_CASE("Strings que NÃO são palíndromo - Sem espaço em branco") 
{
    CHECK( ehPalindromo("hello") == false );
    CHECK( ehPalindromo("world") == false );
    CHECK( ehPalindromo("araran") == false ); 
    CHECK( ehPalindromo("computer") == false );
    CHECK( ehPalindromo("banana") == false );
}

TEST_CASE("Strings que NÃO são palíndromo - Com espaço em branco") 
{
    CHECK( ehPalindromo("hello world") == false );
    CHECK( ehPalindromo("just a test") == false );
    CHECK( ehPalindromo("a man a plan a canal banana") == false );
    CHECK( ehPalindromo("no step on my pets") == false ); 
    CHECK( ehPalindromo("madam in adma") == false ); 
}

