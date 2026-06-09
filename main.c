#include <stdio.h>
#include "vault_map.h"

int main() {
    printf("🔑 Starting VaultHash-Map Memory Isolation System...\n\n");

    VaultTable* auth_vault = create_vault(10);

    // Register cryptographic identifiers securely
    insert_secret(auth_vault, "Admin_Node", "Ax92_Klf781_M");
    insert_secret(auth_vault, "IoT_Gateway", "Zx44_Plm102_B");

    printf("🔍 Querying Vault Registry for Key ID [IoT_Gateway]...\n");
    char* credential = query_secret(auth_vault, "IoT_Gateway");
    
    if (credential != NULL) {
        printf("🔓 Identity Decoupled | Authorized Token Reference: %s\n", credential);
    } else {
        printf("🚨 Access Denied: Identifier not found.\n");
    }

    clear_vault(auth_vault);
    return 0;
}
