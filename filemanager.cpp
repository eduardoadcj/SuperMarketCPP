#include <stdio.h>
#include "filemanager.h"

const char ADDR_CLIENTE[] = "data/cliente.dat";
FILE* FILE_CLIENTE = 0x00;

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

  if(FILE_CLIENTE == NULL)
    return 0;

  return 1;

}
