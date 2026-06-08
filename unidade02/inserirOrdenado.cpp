

auto atual = this->cabeca->proximo;

while(atual != cauda && atual->valor > s){
    atual = atual->proximo;
}

if ((atual != this->cauda && atual->valor == s) || 
    (atual->anterior != this->cabeca && atual->anterior->valor == s)) {
    return false;
}

auto novoElement = new no<std::string>(s);
auto anterior = atual->anterior;

anterior->proximo = novoElement;
atual->anterior = novoElement;

this->quantidade++;
return true;