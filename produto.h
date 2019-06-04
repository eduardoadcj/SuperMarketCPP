#ifndef PRODUTO_H
#define PRODUTO_H

struct Produto{

  int id;
  char nome [100];
  double preco;
  double quantidade;
  int status;

};

void print_menu_produto(char *op);
void add_produto();
void list_produto();
void remove_produto();

#endif
