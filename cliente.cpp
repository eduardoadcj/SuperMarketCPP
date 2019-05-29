#include <iostream>
#include "cliente.h"
#include "keymanager.h"

using namespace std;

extern FILE* FILE_CLIENTE;
extern char CLIENTE_KEY_NAME[];
extern char PRODUTO_KEY_NAME[];

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

  Cliente cli;

  cout << "Cadastro de Cliente" << endl;

  cout << "Nome: ";
  cin >> cli.nome;

  cli.id = generate_key(CLIENTE_KEY_NAME);
  cli.status = 1;

  if(cli.id != 0){

    fseek(FILE_CLIENTE, 0, SEEK_END);
    fwrite(&cli, sizeof(Cliente), 1, FILE_CLIENTE);

  }else{
    cout << "Erro ao inserir o cliente!" << endl;
  }

}

void list_cliente()
{

  Cliente c;

  fseek(FILE_CLIENTE, 0, SEEK_SET);

  cout << "------------------- Clientes Registrados -------------------" << endl;

  while(fread(&c, sizeof(Cliente), 1, FILE_CLIENTE) != 0){
    if(c.status)
      cout << c.id << " - " << c.nome << endl;
  }

}

Cliente* find_cliente(int id)
{

  int found = 0;
  Cliente *c = new Cliente;

  fseek(FILE_CLIENTE, 0, SEEK_SET);

  while(fread(c, sizeof(Cliente), 1, FILE_CLIENTE) != 0){
    if(c->id == id){
      found = 1;
      break;
    }
  }

  if(!found)
    return NULL;

  return c;

}

void update_cliente()
{

  Cliente *cliente;
  int id;

  cout << "Informe o código do cliente: ";
  cin >> id;

  cliente = find_cliente(id);

  if(cliente != NULL){
    cout << cliente->id << " - " << cliente->nome << endl;

    cout << "Novo nome: ";
    cin >> cliente->nome;

    fseek(FILE_CLIENTE, sizeof(Cliente) * -1, SEEK_CUR);

    fwrite(cliente, sizeof(Cliente), 1, FILE_CLIENTE);

  }else{
    cout << "Cliente não encontrado!" << endl;
  }

}

void remove_cliente()
{

  Cliente *cliente;
  int id;

  cout << "Informe o código do cliente: ";
  cin >> id;

  cliente = find_cliente(id);

  if(cliente != NULL){

    cliente->status = 0;

    fseek(FILE_CLIENTE, sizeof(Cliente) * -1, SEEK_CUR);
    fwrite(cliente, sizeof(Cliente), 1, FILE_CLIENTE);

    cout << "Cliente removido!" << endl;

  }else{
    cout << "Cliente não encontrado!" << endl;
  }

}
