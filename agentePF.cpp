#include <iostream>
using namespace std;

class AgentePF{
    private:
    string nome;
    string matricula;
    string cargo;
    int anosExperiencia;
    bool armado;
    static int quantidadeAgentes;
    
    
    public:
    //construtor sem parâmetros
    AgentePF()
    : nome("Não informado"),
    matricula("Não informado"),
    cargo("Não informado"),
    anosExperiencia(0),
    armado(false)
    {
        quantidadeAgentes++;
        cout << "Agente criado (padrão)"<< endl;
    }
    
    
    
    //Construtor parametrizado
    AgentePF(string nome, string matricula, string cargo, int anosExperiencia, bool armado)
    : nome(nome),
    matricula(matricula),
    cargo(cargo),
    anosExperiencia(anosExperiencia),
    armado(armado)
    {
        quantidadeAgentes++;
        cout << "Mais 1 agente foi inserido!" << endl;
    }
    
    //Destrutor
    
    ~AgentePF(){
        quantidadeAgentes--;
        cout << "Agente " << nome << " removido do sistema" << endl;
    }
    
    
    
    string getNome() const {return nome;}
    string getMatricula() const {return matricula;}
    string getCargo() const {return cargo;}
    int getAnosExperiencia() const {return anosExperiencia;}
    bool isArmado() const {return armado;}
    
    
    void setNome(string nomeAgente){ nome = nomeAgente;}
    void setMatricula(string matriculaAgente){ matricula = matriculaAgente;}
    void setCargo(string cargoAgente){ cargo = cargoAgente; cout << "Cargos disponíveis: Delegado, Agente, Perito, Escrivão." << endl;}
    void setAnosExperiencia(int anosExperienciaAgente){ if(anosExperienciaAgente>=0){anosExperiencia = anosExperienciaAgente;}}
    void setArmado(bool status){armado = status;
    cout << "Agente" << nome << (armado ? "armado!" : "desarmado") << endl;}
    
    
    
    
};

int AgentePF::quantidadeAgentes = 0;