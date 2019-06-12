#include <stdio.h>
#include <string.h>
#include "keymanager.h"
#include "filemanager.h"

char CLIENTE_KEY_NAME[] = "CLIENTE";
char PRODUTO_KEY_NAME[] = "PRODUTO";
char VENDA_KEY_NAME[] = "VENDA";
char ITENS_VENDA_KEY_NAME[] = "ITENS_VENDA";

extern FILE* FILE_KEY_MANAGER;

int is_equal(char a[], char b[])
{

  int len = strlen(a);

  if(len <= 0)
    return 0;
  if(len != strlen(b))
    return 0;

  for(int i = 0; i < len; i++){
    if(a[i] != b[i])
      return 0;
  }

  return 1;

}//strcmp

int generate_key(char name[])
{

  KeyType *kts = new KeyType;
  int found = 0, key = 0;

  fseek(FILE_KEY_MANAGER, 0, SEEK_SET);

  while(fread(kts, sizeof(KeyType), 1, FILE_KEY_MANAGER) != 0){

    if(is_equal(kts->name, name)){
      found = 1;
      break;
    }

  }

  if(found == 0){

    kts->key = 1;

    for(int i = 0; i < strlen(name); i++){
      kts->name[i] = name[i];
    }//strcpy

    fseek(FILE_KEY_MANAGER, 0, SEEK_END);
    fwrite(kts, sizeof(KeyType), 1, FILE_KEY_MANAGER);

    key = 1;

  }else{

    kts->key += 1;
    key = kts->key;

    fseek(FILE_KEY_MANAGER, sizeof(KeyType) * -1, SEEK_CUR);
    fwrite(kts, sizeof(KeyType), 1, FILE_KEY_MANAGER);

  }

  return key;

}
