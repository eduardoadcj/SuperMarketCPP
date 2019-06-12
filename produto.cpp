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

void add_produto()
{

  Produto prod;

  cout << "Cadastro de Produto" << endl;

  cout << "Nome: ";
  cin >> prod.nome;

  cout << "Preço: ";
  cin >> prod.preco;

  cout << "Quantidade: ";
  cin >> prod.quantidade;

  prod.id = generate_key(PRODUTO_KEY_NAME);
  prod.status = 1;

  if(prod.id != 0){

    fseek(FILE_PRODUTO, 0, SEEK_END);
    fwrite(&prod, sizeof(Produto), 1, FILE_PRODUTO);
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
    if(p.status)
      cout << p.id << " - " << p.nome << " - " << p.preco << "R$ - " << p.quantidade << endl;
  }

}

Produto* find_produto(int id)
{

  int found = 0;
  Produto *p = new Produto;

  fseek(FILE_PRODUTO, 0, SEEK_SET);

  while(fread(p, sizeof(Produto), 1, FILE_PRODUTO) != 0){
    if(p->id == id){
      found = 1;
      break;
    }
  }

  if(!found){
    delete p;
    return NULL;
  }

  return p;

}

void update_produto()
{

  Produto *produto;
  int id = 0;
  char op = 'e';

  cout << "Informe o código do produto: ";
  cin >> id;

  produto = find_produto(id);

  if(produto == NULL){
    cout << "Produto não encontrado!" << endl;
  }else{

    cout << produto->id << " - "
      << produto->nome << " - "
      << produto->preco << "R$ - "
      << produto->quantidade << " - "
      << (produto->status ? "Ativo" : "Inativo")
      << endl;

    while(op != '0'){
      cout << " -> Menu de alterações" << endl;
      cout << "Selecione uma das opções abaixo:" << endl;
      cout << "1 - Alterar nome" << endl;
      cout << "2 - Alterar preço" << endl;
      cout << "3 - Alterar quantidade" << endl;
      cout << "0 - Finalizar alteração" << endl;
      cin >> op;

      if(op == '1'){

        cout << "Novo nome: ";
        cin >> produto->nome;

      }else if(op == '2'){

        cout << "Novo preço: ";
        cin >> produto->preco;

      }else if(op == '3'){

        cout << "Nova quantidade: ";
        cin >> produto->quantidade;

      }else if(op == '0'){

        fseek(FILE_PRODUTO, sizeof(Produto) * -1, SEEK_CUR);
        fwrite(produto, sizeof(Produto), 1, FILE_PRODUTO);

        cout << "Alteração concluída!" << endl;
        cout << produto->id << " - "
          << produto->nome << " - "
          << produto->preco << "R$ - "
          << produto->quantidade << " - "
          << (produto->status ? "Ativo" : "Inativo")
          << endl;
      }

    }

  }

}

void remove_produto()
{

  Produto *produto;
  int id;

  cout << "Informe o código do produto: ";
  cin >> id;

  produto = find_produto(id);

  if(produto != NULL){

    produto->status = 0;

    fseek(FILE_PRODUTO, sizeof(Produto) * -1, SEEK_CUR);
    fwrite(produto, sizeof(Produto), 1, FILE_PRODUTO);

    cout << "Produto removido!" << endl;

  }else{
    cout << "Produto não encontrado!" << endl;
  }

}
