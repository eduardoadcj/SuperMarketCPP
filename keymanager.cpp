#include <stdio.h>
#include <string.h>
#include "keymanager.h"
#include "filemanager.h"

char CLIENTE_KEY_NAME[] = "CLIENTE";
char PRODUTO_KEY_NAME[] = "PRODUTO";
char VENDA_KEY_NAME[] = "VENDA";
char ITENS_VENDA_KEY_NAME[] = "ITENS_VENDA";

extern FILE* FILE_KEY_MANAGER;

int generate_key(char name[])
{

  KeyType *kts = new KeyType;
  int found = 0, key = 0;

  fseek(FILE_KEY_MANAGER, 0, SEEK_SET);

  while(fread(kts, sizeof(KeyType), 1, FILE_KEY_MANAGER) != 0){

    if(strcmp(kts->name, name) == 0){ // este método verifica se as strings são iguais
      found = 1;
      break;
    }

  }

  if(found == 0){

    kts->key = 1;

    strcpy(kts->name, name); // este metodo copia o conteudo de nom para kts->nome

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
