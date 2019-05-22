#include <stdio.h>
#include "keymanager.h"
#include "filemanager.h"

extern FILE* FILE_KEY_MANAGER;

int generate_key(char name[])
{

  KeyType *kts = 0x00;
  int n, p = 0, found = 0, key = 0;

  fseek(FILE_KEY_MANAGER, 0, SEEK_SET);

  while(!feof(FILE_KEY_MANAGER)){
    fread(kts, sizeof(KeyType), 1, FILE_KEY_MANAGER);
    if(kts->name == name){
      found = 1;
      break;
    }
  }

  if(feof(FILE_KEY_MANAGER) && found == 0){

    kts = new KeyType;
    kts->name = name;
    kts->key = 1;

    fseek(FILE_KEY_MANAGER, 0, SEEK_END);
    fwrite(kts, sizeof(KeyType), 1, FILE_KEY_MANAGER);

    key = 1;

  }else{

    kts->key += 1;
    key = kts->key;

    fseek(FILE_KEY_MANAGER, sizeof(KeyType), SEEK_CUR);
    fwrite(kts, sizeof(KeyType), 1, FILE_KEY_MANAGER);

  }

  return key;

}
