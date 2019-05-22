#include <iostream>
#include "cliente.h"
#include "keymanager.h"

using namespace std;

extern FILE* FILE_CLIENTE;
extern char CLIENTE_KEY_NAME[];

void print_menu_cliente(char *op)
{
  while(*op != '0' &&
    *op != '1' &&
    *op != '2' &&
    *op != '3' &&
    *op != '4'){
    cout << "" << endl;
    cout << " -> Menu clientes" << endl;
    cout << "0 - Voltar" << endl;
    cout << "1 - Adicionar cliente" << endl;
    cout << "2 - Alterar cliente" << endl;
    cout << "3 - Remover cliente" << endl;
    cout << "4 - Visualizar clientes" << endl;
    cin >> *op;
  }
}

void add_cliente(){

  int k = generate_key(CLIENTE_KEY_NAME);

  cout << "Chave gerada: " << k;

  // Cliente cliente;
  //
  //
  //
  // fseek(FILE_CLIENTE, 0, SEEK_END);
  // fwrite(&cliente, sizeof(Cliente), 1, FILE_CLIENTE);

}
