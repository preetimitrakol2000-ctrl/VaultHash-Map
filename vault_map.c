#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vault_map.h"

VaultTable* create_vault(int capacity) {
    VaultTable* vt = (VaultTable*)malloc(sizeof(VaultTable));
    vt->capacity = capacity;
    vt->buckets = (SecretItem**)calloc(capacity, sizeof(SecretItem*));
    return vt;
}

unsigned int generate_index(const char* key, int capacity) {
    unsigned long int hash_value = 5381;
    int i = 0;
    while (key[i] != '\0') {
        hash_value = ((hash_value << 5) + hash_value) + key[i];
        i++;
    }
    return hash_value % capacity;
}

void insert_secret(VaultTable* vt, const char* key, const char* token_val) {
    unsigned int idx = generate_index(key, vt->capacity);
    SecretItem* new_item = (SecretItem*)malloc(sizeof(SecretItem));
    new_item->key = strdup(key);
    new_item->token_val = strdup(token_val);
    new_item->next = vt->buckets[idx];
    vt->buckets[idx] = new_item;
}

char* query_secret(VaultTable* vt, const char* key) {
    unsigned int idx = generate_index(key, vt->capacity);
    SecretItem* current = vt->buckets[idx];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) return current->token_val;
        current = current->next;
    }
    return NULL;
}

void clear_vault(VaultTable* vt) {
    for (int i = 0; i < vt->capacity; i++) {
        SecretItem* item = vt->buckets[i];
        while (item != NULL) {
            SecretItem* temp = item;
            item = item->next;
            free(temp->key);
            free(temp->token_val);
            free(temp);
        }
    }
    free(vt->buckets);
    free(vt);
}
