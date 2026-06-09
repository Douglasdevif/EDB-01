int removidos = 0;

    while(primeiro != nullptr && primeiro->valor == valor){
        No* noparaDeletar = primeiro;
        primeiro = primeiro->proximo;

        delete noparaDeletar;
        this->quantidade--;
        removidos++;
    }
    if(primeiro == nullptr){
        this->ultimo = nullptr;
        return removidos;
    }

    No* atual = primeiro;

    while(atual->proximo != nullptr){
        if(atual->proximo->valor == valor){
            No* noparaDeletar = atual->proximo;

            atual->proximo = atual->proximo->proximo;

            if(atual->proximo == nullptr){
                this->ultimo = atual;
            }

            delete noparaDeletar;
            this->quantidade--;
            removidos++;
            
        } else{
            atual = atual->proximo;
        }
    }
    return removidos;





    //Outra forma de fazer


    int removidos = 0;

    No* atual = this->inicio; 
    No* anterior = nullptr;

    while (atual != nullptr) {
        if (atual->valor == val) {
            No* noParaDeletar = atual;
            
            atual = atual->proximo; 

            if (anterior == nullptr) {
                this->inicio = atual; 
            } 
            else {
                anterior->proximo = atual;
            }
            delete noParaDeletar;
            this->quantidade--;
            removidos++;
        }else {
            anterior = atual;   
            atual = atual->proximo; 
        }
    }

    if (this->inicio == nullptr) {
        this->fim = nullptr;
    } else {
        this->fim = anterior;
    }

    return removidos;
