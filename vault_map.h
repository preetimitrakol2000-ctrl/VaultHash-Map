#ifndef VAULT_MAP_H
#define VAULT_MAP_H

typedef struct SecretItem {
    char* key;
    char* token_val;
    struct SecretItem* next;
} SecretItem;

typedef struct {
    int capacity;
    SecretItem** buckets;
} VaultTable;

VaultTable* create_vault(int capacity);
unsigned int generate_index(const char* key, int capacity);
void insert_secret(VaultTable* vt, const char* key, const char* token_val);
char* query_secret(VaultTable* vt, const char* key);
void clear_vault(VaultTable* vt);

#endif
