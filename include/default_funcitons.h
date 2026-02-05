#include <string.h>
/* -------------------------------------------------------------------------- */
/*                              default fnucitons                             */
/* -------------------------------------------------------------------------- */
/* ----------------------------------- int ---------------------------------- */
int intHashFn(int key) { return key; };
bool intEqualFn(int key1, int key2) { return key1 == key2; };
/* ---------------------------------- char* --------------------------------- */
int strHashFn(char *key)
{
    int hash = 1;
    for (size_t i = 0; i < strlen(key); i++)
    {
        hash *= key[i];
    }
    return hash;
}
bool strEqualFn(char *key1, char *key2)
{
    return strcmp(key1, key2) == 0;
}
