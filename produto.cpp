#include <iostream>
#include "produto.h"
#include "keymanager.h"

using namespace std;

extern FILE* FILE_PRODUTO;
extern char PRODUTO_KEY_NAME[];

void print_menu_produto(char *op)
{

  while(*op != '0' &&
    *op != '1' &&
    *op != '2' &&
    *op != '3' &&
    *op != '4'){

    cout << "" << endl;
    cout << " -> Menu Produtos" << endl;
    cout << "0 - Voltar" << endl;
    cout << "1 - Adicionar produto" << endl;
    cout << "2 - Alterar produto" << endl;
    cout << "3 - Remover produto" << endl;
    cout << "4 - Visualizar produtos" << endl;
    cin >> *op;

  }

}

void add_produto(){

  Produto prod;

  cout << "Cadastro de Produto" << endl;

  cout << "Nome: ";
  cin >> prod.nome;

  prod.id = generate_key(PRODUTO_KEY_NAME);
  prod.status = 1;

  if(prod.id != 0){

    fseek(FILE_PRODUTO, 0, SEEK_END);
    fwrite(&cli, sizeof(Produto), 1, FILE_PRODUTO);
    fflush(FILE_PRODUTO);

  }else{
    cout << "Erro ao inserir o produto!" << endl;
  }

}

void list_produto()
{

  Produto p;

  fseek(FILE_PRODUTO, 0, SEEK_SET);

  cout << "------------------- Produtos Registrados -------------------" << endl;

  while(fread(&p, sizeof(Produto), 1, FILE_PRODUTO) !=0){

      cout << p.id << " - " << p.nome << endl;

  }

}

Produto* find_produto(int id)
{

}
