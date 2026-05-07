#ifndef AGENTEPF_H          // Guarda de inclusão
#define AGENTEPF_H

#include <iostream>
#include <string>
using namespace std;

class AgentePF {
private:
    string nome;
    string matricula;
    string cargo;
    int anosExperiencia;
    bool armado;
    static int quantidadeAgentes;

public:
    // Construtor padrão (apenas DECLARAÇÃO)
    AgentePF();
    
    // Construtor parametrizado (apenas DECLARAÇÃO)
    AgentePF(string nome, string matricula, string cargo, 
             int anosExperiencia, bool armado);
    
    // Destrutor (apenas DECLARAÇÃO)
    ~AgentePF();
    
    // Getters
    string getNome() const;
    string getMatricula() const;
    string getCargo() const;
    int getAnosExperiencia() const;
    bool isArmado() const;
    
    // Setters
    void setNome(string nomeAgente);
    void setMatricula(string matriculaAgente);
    void setCargo(string cargoAgente);
    void setAnosExperiencia(int anosExperienciaAgente);
    void setArmado(bool status);
    
    // Outros métodos
    void exibirIdentificacao() const;
    
    // Método estático
    static int getQuantidadeAgentes();
};

#endif  // Fim da guarda de inclusão