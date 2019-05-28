#ifndef CLIENTE_H
#define CLIENTE_H

struct Cliente
{
  int id;
  char nome[100];
  int status;
};

void print_menu_cliente(char *op);
void add_cliente();
void list_cliente();
void update_cliente();

#endif
