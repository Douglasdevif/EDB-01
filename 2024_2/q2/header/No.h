#ifndef NO_H
#define NO_H

template <typename T>
class No
{
public:
    ~No();
    
    No( T valor );
    
    T getValor();
    
    void setValor(T val); 

    No* getProximo();

    void setProximo(No* proximo); 

    T valor;

    No* proximo;
};

template<typename T>
No<T>::No(T val):
valor(val), proximo(nullptr) {}

template<typename T>
No<T>::~No() {}

template<typename T>
T No<T>::getValor(void)
{
    return this->valor;
}

template<typename T>
void No<T>::setValor(T t)
{
    this->valor = t;
}

template<typename T>
No<T>* No<T>::getProximo(void)
{
    return this->proximo;
}

template<typename T>
void No<T>::setProximo(No<T>* n)
{
    this->proximo = n;
}
#endif
