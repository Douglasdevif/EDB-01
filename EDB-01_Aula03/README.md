
# Informações do Projeto

- **Instituição:** IMD
- **Disciplina:** EDB1
- **Professor:** Prof. Eiji Adachi

# Lista Simplesmente Encadeada

As listas simplesmente encadeadas são estruturas de dados fundamentais para a implementação de diversos tipos abstratos de dados. Neste capítulo, vamos estudar uma variação muito utilizada: a **lista simplesmente encadeada com ponteiros tanto para o primeiro quanto para o último elemento**.

Para facilitar o entendimento, apresentaremos a lista encadeada em três partes:

1. Estrutura da classe `No`
2. Estrutura e operações da classe `Lista`
3. Observações gerais e tabela de complexidades

---

## A Classe `No`

A classe `No` representa cada elemento da lista. Sua função é encapsular o valor armazenado e o ponteiro para o próximo nó da sequência.

```cpp
class No
{
public:
    ~No();
    
    No( std::string valor );

    std::string valor;

    No* proximo;
};
```

**Explicação**  
- **Atributo `valor`**: é o conteúdo do nó, um valor do tipo string no nosso caso, mas que poderia ser qualquer outro tipo, até mesmo um tipo variável implementado usando o recurso de *templates* de C++.  
- **Atributo `proximo`**: aponta para o próximo nó da lista, ou é `nullptr` caso este seja o último nó.

A classe permite acessar e alterar o valor dos seus atributos, declarando-os na interface pública, além de um construtor que inicializa o `valor` e define `proximo` como `nullptr` por padrão.

---

## A Classe `Lista` e Suas Operações

A classe `Lista` é responsável por manter e gerenciar a sequência de nós. Ela utiliza dois ponteiros principais e expõe uma interface pública para as principais operações.

```cpp
class Lista 
{
private:
    No* primeiro;
    No* ultimo;
    unsigned long quantidade;
    
public:
    Lista();
    ~Lista();

    bool inserirInicio(const std::string& elemento);
    bool inserirFim(const std::string& elemento);
    bool inserirNaPosicao(int i, const std::string& elemento);

    bool removerInicio();
    bool removerFim();
    bool removerNaPosicao(int i);

    const std::string& primeiroElemento() const;
    const std::string& ultimoElemento() const;
    const std::string& elementoNaPosicao(int i) const;

    unsigned long tamanho() const;
    void imprimir() const;
};
```

**Atributos principais:**  
- `primeiro`: aponta para o primeiro nó da lista.  
- `ultimo`: aponta para o último nó da lista.  
- `quantidade`: armazena a quantidade atual de elementos na lista.

Numa lista simplesmente encadeada com apenas um ponteiro para o primeiro nó (`primeiro`), as operações no início da lista são realizadas em tempo constante, enquanto as operações no fim da lista são realizadas em tempo linear. A presença do ponteiro para o último nó (`ultimo`) permite que inserções no final sejam realizadas em tempo constante. No entanto, para remoções no final da lista ainda é necessário percorrer a lista inteira, pois para atualizar `ultimo` é preciso acessar o penúltimo elemento. Já as operações realizadas na i-ésima posição são realizadas, no pior caso, em tempo linear.

### Operações e Como Funcionam

#### ✅ `bool inserirInicio(const std::string& elemento);`  
- Cria um novo nó e o seu próximo aponta para o primeiro nó.
- Atualiza o primeiro nó da lista para o novo nó.
- Se a lista estava vazia, `ultimo` também aponta para o novo nó.  
- Incrementa o contador de elementos.

#### ✅ `bool inserirFim(const std::string& elemento);`  
- Cria um novo nó e o coloca após o último.  
- Atualiza `ultimo` para o novo nó.  
- Se a lista estava vazia, `primeiro` também aponta para o novo nó.  
- Incrementa o contador de elementos.

#### ✅ `bool inserirNaPosicao(int i, const std::string& elemento);`  
- `i` começa em 1 (primeira posição).  
- Percorre até o nó `i - 1` e insere após ele.  
- **Erros:** lança `out_of_range` se `i < 1` ou `i > quantidade + 1`.

#### ✅ `const std::string& primeiroElemento() const;`  
- Retorna o valor do primeiro elemento.  
- **Erros:** lança `out_of_range` se a lista estiver vazia.

#### ✅ `const std::string& ultimoElemento() const;`  
- Retorna o valor do último elemento.  
- **Erros:** lança `out_of_range` se a lista estiver vazia.

#### ✅ `const std::string& elementoNaPosicao(int i) const;`  
- Percorre a lista até o elemento `i` e retorna o valor armazenado neste nó.
- **Erros:** lança `out_of_range` se `i < 1` ou `i > quantidade`.

#### ✅ `bool removerInicio();`  
- Faz um ponteiro auxiliar apontar para o primeiro nó.
- Atualiza `primeiro` para o próximo nó.  
- Se a lista ficar vazia, `ultimo` vira `nullptr`.  
- Libera o nó auxiliar e decrementa o contador.  
- Retorna `false` se a lista estiver vazia.

#### ✅ `bool removerFim();`  
- Se há um único elemento, chama `removerInicio`.  
- Caso contrário, percorre até o penúltimo nó e atualiza `ultimo`.  
- Remove o último nó e ajusta os ponteiros.  
- Retorna `false` se a lista estiver vazia.

#### ✅ `bool removerNaPosicao(int i);`  
- Percorre até `i - 1` e mantém um ponteiro auxiliar apontando para o nó `i`.
- Ajusta o ponteiro próximo do nó `i - 1` para apontar para o nó `i + 1`.
- Libera o nó `i` e decrementa o contador.  
- Retorna `false` se a lista estiver vazia.
- **Erros:** lança `out_of_range` se `i < 1` ou `i > quantidade`.

---

## Observações Importantes

A lista simplesmente encadeada com ponteiros para o primeiro e o último elemento é uma estrutura versátil e eficiente, especialmente para inserções no início ou no final. No entanto, a remoção no final e acessos em posições arbitrárias continuam a exigir percorrer toda a lista. Atenção especial deve ser dada aos casos de listas vazias e de listas com apenas um elemento.

### Tabela de Complexidades

| Operação                   | Complexidade |
|-----------------------------|--------------|
| Inserção no início         | O(1)         |
| Inserção no fim            | O(1)         |
| Inserção em posição i      | O(n)         |
| Acesso ao primeiro         | O(1)         |
| Acesso ao último           | O(1)         |
| Acesso em posição i        | O(n)         |
| Remoção no início          | O(1)         |
| Remoção no fim             | O(n)         |
| Remoção em posição i       | O(n)         |

---

## 📂 **Estrutura de Diretórios**

```
.
├── bin/       # Executáveis gerados após a compilação
├── doc/       # Documentação do projeto
├── header/    # Arquivos de cabeçalho (.h) 
├── lib/       # Bibliotecas externas (ex: doctest.h)
├── src/       # Implementação das classes (.cpp)
├── test/      # Arquivos de teste (usando doctest)
├── .gitignore # Arquivos/diretórios ignorados pelo Git
├── makefile   # Automação da compilação e execução
└── README.md  # Este arquivo
```

---

## 🛠️ **Compilação e Execução Usando o Makefile**

#### 🔧 **Comandos Disponíveis:**

| Comando           | Descrição                                    |
|--------------------|----------------------------------------------|
| `make` ou `make all` | Compila o programa principal e os testes.   |
| `make run`        | Executa o programa principal (`bin/main`).   |
| `make test`       | Compila apenas os testes.                    |
| `make run-test`   | Executa os testes (`bin/test`).              |
| `make clean`      | Remove arquivos objeto e executáveis.        |

#### 📌 **Exemplos de Uso:**

```bash
# Compilar o projeto
make

# Executar o programa principal
make run

# Compilar e rodar os testes
make run-test

# Limpar os arquivos de build
make clean
```

---
