#include <iostream>
#include <list>
#include "keymanager.h"
#include "cliente.h"
#include "produto.h"
#include "venda.h"

using namespace std;

extern FILE* FILE_VENDA;
extern FILE* FILE_ITENS_VENDA;
extern FILE* FILE_PRODUTO;
extern char VENDA_KEY_NAME;
extern char ITENS_VENDA_KEY_NAME;

void make_sale()
{

  int id_cliente = 0;
  int id_produto = 0;
  char op = 'e';
  Cliente *cliente;
  Produto *produto;
  Venda venda;
  ItensVenda iv;
  list<ItensVenda> itens_venda;
  list<ItensVenda>::iterator it_itens_venda;

  cout << "Informe o id do cliente: "
  cin >> id_cliente;

  cliente = find_cliente(id_cliente); //trocar esse metodo por um que busque os com status diferente de 0

  if(cliente != NULL){

    cout << cliente->id << " - " << cliente->nome << endl;

    venda.id_cliente = cliente->id;

    do{

      cout << "Informe o id de um produto: ";
      cin >> id_produto;

      produto = find_produto(id_produto); //trocar esse metodo por um que busque os com status e quantidade diferente de 0

      if(produto != NULL){

        cout << produto->id << " - "
          << produto->nome << " - "
          << produto->preco << "R$ - "
          << produto->quantidade << " - "
          << endl;

        iv.id_produto = produto->id;

        do{

          cout << "Informe a quantidade: ";
          cin >> iv.quantidade;

          if(iv.quantidade > produto->quantidade)
            cout << "Quantidade indisponível!" << endl;

        }while(iv.quantidade <= produto->quantidade);

        itens_venda.push_back(iv);

        cout << "Deseja informar mais um produto? (s/n) ";
        cin >> op;

      }else{

        cout << "Produto não encontrado!" << endl;

        if(itens_venda.size() > 0){
          cout << "Deseja informar outro? (s/n) ";
          cin >> op;
        }else{
          op = 'n';
        }

      }

    }while(op != 'n');

    if(itens_venda.size() == 0){
      cout << "Nenhum item adicionado!" << endl;
      return;
    }

    //Iniciando processo de salvamento das informações

    venda.total = 0;

    for(it_itens_venda = itens_venda.begin();
      it_itens_venda != itens_venda.end();
      it_itens_venda++)
      venda.total += it->total

    venda.id = generate_key(VENDA_KEY_NAME);

    fseek(FILE_VENDA, sizeof(Venda), 1, SEEK_END);
    fwrite(&venda, sizeof(Venda), 1, FILE_VENDA);

    for(it_itens_venda = itens_venda.begin();
      it_itens_venda != itens_venda.end();
      it_itens_venda++){

      produto = find_produto(it_itens_venda->id_produto);
      fseek(FILE_PRODUTO, sizeof(Produto) * -1, 1, SEEK_CUR);
      fwrite(produto, sizeof(Produto), 1, FILE_PRODUTO);

      fseek(FILE_ITENS_VENDA, sizeof(ItensVenda), 1, SEEK_END);
      fwrite(it_itens_venda, sizeof(ItensVenda), 1, FILE_ITENS_VENDA);

    }

  }else{
    cout << "Cliente não encontrado!" << endl;
  }

}
