#ifndef VENDA_H
#define VENDA_H

struct Venda
{
  int id;
  int id_cliente;
  double total;
};

struct ItensVenda
{
  int id;
  int id_venda;
  int id_produto;
  double quantidade;
  double total;
};

#endif
