#ifndef CLIENTE_H
#define CLIENTE_H

struct Cliente
{
  int id;
  char[100] nome;
  int status;
};

void salvar_cliente();
void visualizar_cliente();
void alterar_cliente();
void excluir_cliente();

#endif
