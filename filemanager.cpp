#include <stdio.h>
#include "filemanager.h"

const char ADDR_CLIENTE[] = "data/cliente.dat";
const char ADDR_PRODUTO[] = "data/produto.dat";
const char ADDR_KEY_MANAGER[] = "data/key_manager.dat";

FILE* FILE_CLIENTE = 0x00;
FILE* FILE_PRODUTO = 0x00;
FILE* FILE_KEY_MANAGER = 0x00;

FILE* open_file(const char *name)
{

  FILE *fp;

  fp = fopen(name, "rb+");

  if(fp == NULL){

    fp = fopen(name, "wb");

    if(fp == NULL){
      return NULL;
    }

    fclose(fp);
    fp = fopen(name, "rb+");

  }

  return fp;

}

int load_files()
{

  FILE_CLIENTE = open_file(ADDR_CLIENTE);
  FILE_PRODUTO = open_file(ADDR_PRODUTO);
  FILE_KEY_MANAGER = open_file(ADDR_KEY_MANAGER);

  if(FILE_CLIENTE == NULL ||
        FILE_KEY_MANAGER == NULL ||
        FILE_PRODUTO == NULL)
    return 0;

  return 1;

}

void close_files()
{
  fclose(FILE_CLIENTE);
  fclose(FILE_PRODUTO);
  fclose(FILE_KEY_MANAGER);
}
