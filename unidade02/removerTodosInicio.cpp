 int removidos = 0;

    while( inicio != nullptr && inicio->valor == val){
        auto noparaDeletar = inicio;
        inicio = inicio->proximo;
        delete noparaDeletar;
        removidos++;
    }
    if(inicio == nullptr) return removidos;

    auto atual = inicio;

    while(atual->proximo != nullptr){
        if(atual->proximo->valor == val){
            auto noparaDeletar = atual->proximo;

            atual->proximo = atual->proximo->proximo;
            delete noparaDeletar;
            removidos++;
        } else {
            atual = atual->proximo;
        }
    }

    return removidos;
}




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
            } else {
                anterior->proximo = atual;
            }

            delete noParaDeletar;
            removidos++;
        } 
        else {
            anterior = atual;      
            atual = atual->proximo; 
        }
    }
    return removidos;