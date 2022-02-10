#include "perifericos.h"

Test::Test(int numero){

    this->numero = numero;

    return;

}

int Test::getNumero(void){

    return this->numero;

}

void Test::setNumero(int valor){

    this->numero = valor;

    return;

}