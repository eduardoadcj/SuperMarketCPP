#ifndef KEY_MANAGER_H
#define KEY_MANAGER_H

struct KeyType
{
  char name[15];
  int key;
};

int generate_key(char name[]);

#endif
