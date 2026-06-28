auto indice = this->hash(chave);
No* no = this->array[indice];

while(no != nullptr){
    if(chave == no->chave){
        return no->valor;
    }
    no = no->proximo;
}
return std::nullopt;