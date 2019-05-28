#include <iostream>
#include "filemanager.h"
#include "cliente.h"

using namespace std;

void show_menu(){

  int cont = 1;
  char op;

  while(cont){

    op = 'e';

    while(op != '1' &&
     op != '2' &&
     op != '3' &&
     op != '0'){
      cout << "" << endl;
      cout << "Selecione uma opção de menu: " << endl;
      cout << "0 - Sair" << endl;
      cout << "1 - Venda" << endl;
      cout << "2 - Clientes" << endl;
      cout << "3 - Produto" << endl;
      cin >> op;
    }

    if(op == '1'){ // opcao venda

    }else if(op == '2'){ // opcao dos clientes

      op = 'e';
      print_menu_cliente(&op);

      if(op == '1'){ // Adicionar cliente
        add_cliente();
      }else if (op == '2'){ // Alterar cliente
        update_cliente();
      }else if (op == '3'){ // Remover cliente

      }else if (op == '4'){ // Visualizar cliente
        list_cliente();
      }

    }else if(op == '3'){ // Opcao do acervo

    }else if(op == '0'){ // encerrar programa
      cont = 0;
    }

  }

}

int main()
{

  cout << "------------------- Super Market CPP ------------------- " << endl;

  if ( load_files() ) {
    show_menu();
    close_files();
  }else{
    cout << "Banco de dados indisponível!" << endl;
    return 1;
  }

  return 0;

}
