 Elemento* arrayNovo = new Elemento[novaCapacidade];
        Elemento* arrayVelho = this->array;

        auto capacidadeVelha = this->capacidade;
        this->capacidade = novaCapacidade;
        this->array = arrayNovo;

        for(int i = 0; i < capacidadeVelha; i++){
            Elemento& elemento = arrayVelho[i];

            if(elemento.estado == Estado::OCUPADO){
                auto h = this->hash(elemento.chave);

                for(int delta = 0; delta < novaCapacidade; delta++){
                    auto indice = (h + delta)%novaCapacidade;

                    if(arrayNovo[indice].estado == Estado::LIVRE){
                        arrayNovo[indice].chave = elemento.chave;
                        arrayNovo[indice].valor = elemento.valor;
                        arrayNovo[indice].estado = Estado::OCUPADO;
                        break;
                    }
                }
            }
        }
        delete [] arrayVelho;