//
//  ListaDuplamenteEncadeada.cpp
//
//  Criado por Eiji Adachi Medeiros Barbosa
//

#include "../header/ListaDuplamenteEncadeada.h"
#include "../header/No.h"
#include <string>
#include <sstream>

void ListaDuplamenteEncadeada::init()
{
	this->cabeca = new No<std::string>("CABECA_NAO_DEVE_SER_ACESSADA");
    this->cauda = new No<std::string>("CAUDA_NAO_DEVE_SER_ACESSADA");
    
    this->cabeca->setProximo(this->cauda);
    this->cabeca->setAnterior(nullptr);

    this->cauda->setProximo(nullptr);
    this->cauda->setAnterior(this->cabeca);

    this->quantidade = 0;
}

ListaDuplamenteEncadeada::ListaDuplamenteEncadeada()
{
	this->init();
}

ListaDuplamenteEncadeada::ListaDuplamenteEncadeada(std::string s)
{
	this->init();																																																			auto n = new No<std::string>( s );n->setAnterior(this->cabeca);n->setProximo(this->cabeca->getProximo());n->getAnterior()->setProximo( n );n->getProximo()->setAnterior( n );this->quantidade++; 
}

ListaDuplamenteEncadeada::~ListaDuplamenteEncadeada()
{
    auto aux = this->cabeca;

	while(aux != nullptr)
	{
		auto outro = aux;
		aux = aux->getProximo();
		delete outro;
	}
}

bool ListaDuplamenteEncadeada::inserirAntes(std::string novoElemento, std::string referencia)
{	
	 auto atual = this->cabeca->getProximo();

	 for(int j = 1; j< this->quantidade+1; j++){
		if(atual->getValor() == referencia){
			auto novoElement = new No<std::string>(novoElemento);

			novoElement->setProximo(atual);
			novoElement->setAnterior(atual->getAnterior());

			atual->getAnterior()->setProximo(novoElement);
			atual->setAnterior(novoElement);

			this->quantidade++;
			return true;
		}
		atual = atual->getProximo();
	 }
	 return false;

}

No<std::string>* ListaDuplamenteEncadeada::getCabeca(void)
{
    return this->cabeca;
}

No<std::string>* ListaDuplamenteEncadeada::getCauda(void)
{
    return this->cauda;
}

int ListaDuplamenteEncadeada::tamanho(void)
{
    return this->quantidade;
}

bool ListaDuplamenteEncadeada::vazia(void)
{
    return this->tamanho() == 0;
}

std::string ListaDuplamenteEncadeada::imprimir(void)
{
	std::stringstream resultado; 
	
	No<std::string>* n = this->cabeca->getProximo();

	if(n == this->cauda){
		return "{}";
	}
	else {
		resultado << n->getValor();
		n = n->getProximo();
	}
	
	for(; n != this->cauda; n = n->getProximo())
	{
		resultado  << "<->" << n->getValor();
	}

	return resultado.str();
}

StatusDaLista ListaDuplamenteEncadeada::checarConsistencia()
{
	if( this->cabeca == nullptr )
	{
		return CABECA_NULA;
	}
	else if( this->cabeca->getProximo() == nullptr )
	{
		return CABECA_PROXIMO_NULO;
	}
	else if( this->cabeca->getProximo()->getAnterior() != this->cabeca )
	{
		return ENCADEAMENTO_INCORRETO;
	}
	else if( this->cabeca->getAnterior() != nullptr )
	{
		return CABECA_ANTERIOR;
	}
	
	if( this->cauda == nullptr )
	{
		return CAUDA_NULA;
	}
	else if( this->cauda->getAnterior() == nullptr )
	{
		return CAUDA_ANTERIOR_NULO;
	}
	else if( this->cauda->getAnterior()->getProximo() != this->cauda )
	{
		return ENCADEAMENTO_INCORRETO;
	}
	else if( this->cauda->getProximo() != nullptr )
	{
		return CAUDA_PROXIMO;
	}
	
	if(this->vazia())
	{
		if( this->cabeca->getProximo() != this->cauda )
		{
			return CABECA_CAUDA;
		}
		
		if( this->cabeca != this->cauda->getAnterior() )
		{
			return CABECA_CAUDA;
		}
	}
	else
	{
		// Verifica encadeamento dos elementos
		for(No<std::string>* i = this->cabeca->getProximo(); i != this->cauda; i=i->getProximo())
		{
			if( i->getProximo()->getAnterior() != i )
			{
				return ENCADEAMENTO_INCORRETO;
			}
			if( i->getAnterior()->getProximo() != i )
			{
				return ENCADEAMENTO_INCORRETO;
			}
		}
	}
	
	return OK;
}
