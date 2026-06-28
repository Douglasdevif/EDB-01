int posRemovido = -1;
    int h = hash(chave);

    for(int delta = 0; delta < this->capacidade; delta++){
        int indice = (h + delta) % capacidade;
        Elemento& elemento = this->array[indice];

        if(elemento.estado == Estado::LIVRE){
            int posInsercao;

            if(posRemovido != -1){
                posInsercao = posRemovido;
            } else{
                posInsercao = indice;
            }

            this->array[posInsercao].chave = chave;
            this->array[posInsercao].valor = valor;
            this->array[posInsercao].estado = Estado::OCUPADO;
            this->quantidade++;
            return true;
        }
        else if(elemento.estado == Estado::OCUPADO && elemento.chave == chave){

            elemento.valor = valor;
            return true;
        }
        else if(elemento.estado == Estado::REMOVIDO && posRemovido == -1){ 
            posRemovido = indice;
        }
    }
    if(posRemovido != -1){
        this->array[posRemovido].chave = chave;
        this->array[posRemovido].valor = valor;
        this->array[posRemovido].estado = Estado::OCUPADO;
        this->quantidade++;
        return true;
    } else{
        throw std::overflow_error ("Tabela cheia.");
    }