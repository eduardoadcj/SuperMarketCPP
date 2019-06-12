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
extern FILE* FILE_CLIENTE;
extern char VENDA_KEY_NAME[];
extern char ITENS_VENDA_KEY_NAME[];

void print_menu_venda(char *op)
{
  while(*op != '0' &&
    *op != '1' &&
    *op != '2' &&
    *op != '3' &&
    *op != '4'){
    cout << "" << endl;
    cout << " -> Menu venda" << endl;
    cout << "0 - Voltar" << endl;
    cout << "1 - Efetuar venda" << endl;
    cout << "2 - Listar vendas" << endl;
    cout << "3 - Listar total comprado por cliente" << endl;
    cin >> *op;
  }
}

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

  cout << "Informe o id do cliente: ";
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
          << produto->quantidade
          << endl;

        iv.id_produto = produto->id;

        do{

          cout << "Informe a quantidade: ";
          cin >> iv.quantidade;

          if(iv.quantidade > produto->quantidade)
            cout << "Quantidade indisponível!" << endl;

        }while(iv.quantidade > produto->quantidade);

        iv.total = iv.quantidade * produto->preco;

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
      venda.total += it_itens_venda->total;


    cout << "Total da venda: " << venda.total << "R$" << endl;

    venda.id = generate_key(VENDA_KEY_NAME);

    fseek(FILE_VENDA, 0, SEEK_END);
    fwrite(&venda, sizeof(Venda), 1, FILE_VENDA);

    for(it_itens_venda = itens_venda.begin();
      it_itens_venda != itens_venda.end();
      it_itens_venda++){

      produto = find_produto(it_itens_venda->id_produto);
      produto->quantidade -= it_itens_venda->quantidade;
      fseek(FILE_PRODUTO, sizeof(Produto) * -1, SEEK_CUR);
      fwrite(produto, sizeof(Produto), 1, FILE_PRODUTO);

      iv = *it_itens_venda;
      iv.id = generate_key(ITENS_VENDA_KEY_NAME);
      iv.id_venda = venda.id;

      fseek(FILE_ITENS_VENDA, 0, SEEK_END);
      fwrite(&iv, sizeof(ItensVenda), 1, FILE_ITENS_VENDA);

    }

  }else{
    cout << "Cliente não encontrado!" << endl;
  }

}

void list_venda()
{

  Cliente *cliente = new Cliente;
  Produto *produto = new Produto;
  ItensVenda *itens_venda = new ItensVenda;
  Venda *venda = new Venda;

  cout << "--------------------- Relatório de Vendas ---------------------" << endl;

  fseek(FILE_VENDA, 0, SEEK_SET);
  while(fread(venda, sizeof(Venda), 1, FILE_VENDA)){
    if(venda != NULL){

      cout << venda->id << " -----------------------" << endl;

      cliente = find_cliente(venda->id_cliente);
      if(cliente != NULL)
        cout << "Cliente: " << cliente->nome << endl;

      //Buscando itens da venda
      fseek(FILE_ITENS_VENDA, 0, SEEK_SET);

      cout << "     Itens ------------" << endl;

      while(fread(itens_venda, sizeof(ItensVenda), 1, FILE_ITENS_VENDA)){
        if(itens_venda != NULL && itens_venda->id_venda == venda->id){
          produto = find_produto(itens_venda->id_produto);
          if(produto != NULL)
            cout << "      " << produto->id << " - "
            << produto->nome << " - "
            << produto->preco << " - "
            << itens_venda->quantidade << " - "
            << itens_venda->total
            << endl;
        }
      }

      cout << "Total: " << venda->total << endl;

    }
  }

}

void list_total_cliente()
{

  Cliente *cliente = new Cliente;
  Venda *venda = new Venda;
  double total = 0;

  cout << "------------------ Total comprado por cliente ------------------" << endl;

  fseek(FILE_CLIENTE, 0, SEEK_SET);
  while(fread(cliente, sizeof(Cliente), 1, FILE_CLIENTE)){
    if(cliente != NULL){

      fseek(FILE_VENDA, 0, SEEK_SET);
      while(fread(venda, sizeof(Venda), 1, FILE_VENDA)){
        if(venda != NULL && venda->id_cliente == cliente->id){
          total += venda->total;
        }
      }

      cout << cliente->nome << " - " << total << endl;

    }
  }

}
