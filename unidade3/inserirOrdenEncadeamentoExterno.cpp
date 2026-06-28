auto indice = hash(chave);
    No* no = this->array[indice];
    No* anterior = nullptr;

    while (no != nullptr && no->chave < chave) {
        anterior = no;
        no = no->proximo;
    }
    if (no != nullptr && no->chave == chave) {
        no->valor = valor;
        return true;
    }
    No* novo = new No(chave, valor);

    if (anterior == nullptr) {
        novo->proximo = this->array[indice];
        this->array[indice] = novo;
    } else {
        novo->proximo = no;
        anterior->proximo = novo;
    }
    this->quantidade++;
    return true;