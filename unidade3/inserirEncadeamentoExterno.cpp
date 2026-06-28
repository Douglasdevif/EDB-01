auto indice = hash(chave);
No* no = this->array[indice];

while(no != nullptr){
    if(chave == no->chave){
        no->valor = valor;
        return true;
    }
    no = no->proximo;
}

No* novo = new No(chave, valor);
novo->proximo = this->array[indice];
this->array[indice] = novo;
this->quantidade++;
return true;