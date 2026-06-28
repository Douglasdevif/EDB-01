auto indice = hash(chave);
    
    No* atual = this->array[indice];
    No* anterior = nullptr;

    while (atual != nullptr) {
        if (atual->chave == chave) {

            if (anterior == nullptr) {
                this->array[indice] = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }

            delete atual;
            this->quantidade--;
            return true;
        }
        
        anterior = atual;
        atual = atual->proximo;
    }

    return false;