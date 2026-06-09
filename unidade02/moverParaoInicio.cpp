auto atual = this->cabeca->proximo;

    while (atual != this->cauda && atual->valor != str) {
        atual = atual->proximo;
    }

    if (atual == this->cauda) {
        return false;
    }
    
    if (atual == this->cabeca->proximo) { 
        return true;
    }

    auto vizinhoEsquerdaAntigo = atual->anterior;
    auto vizinhoDireitaAntigo = atual->proximo;

    vizinhoEsquerdaAntigo->proximo = vizinhoDireitaAntigo;
    vizinhoDireitaAntigo->anterior = vizinhoEsquerdaAntigo;

    auto primeiroAntigo = this->cabeca->proximo;

    atual->proximo = primeiroAntigo;
    atual->anterior = this->cabeca;

    this->cabeca->proximo = atual;
    primeiroAntigo->anterior = atual;

    return true;