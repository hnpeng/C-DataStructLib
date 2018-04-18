#include "Hash.h"

#include <stdlib.h>
#include "BSTree/BSTree.h"

typedef struct
{
    BSTreeNode header;
    HashValue* value;
}HashNode;

Hash* Hash_Create()
{
    return BSTree_Create();
}

static void recursive_clear(BSTreeNode* root)
{
    if (root != NULL) {
        recursive_clear(root->left);
        recursive_clear(root->right);

        free(root);
    }
}

void Hash_Clear(Hash* hash)
{
    recursive_clear(BSTree_Root(hash));
}

void Hash_Destroy(Hash* hash)
{
    Hash_Clear(hash);
    BSTree_Destroy(hash);
}

int Hash_Add(Hash* hash, HashKey* key, HashValue* value, Hash_Compare* compare)
{
    HashNode* node = (HashNode*)malloc(sizeof(HashNode));
    int ret = node != NULL;

    if (ret) {
        node->header.key = key;
        node->value = value;

        ret = BSTree_Insert(hash, (BSTreeNode*)node, compare);

        if (!ret) {
            free(node);
        }
    }

    return ret;
}

HashValue* Hash_Delete(Hash* hash, HashKey* key, Hash_Compare* compare)
{
    HashValue* ret = NULL;
    HashNode* node = (HashNode*)BSTree_Delete(hash, key, compare);

    if (node != NULL) {
        ret = node->value;
        free(node);
    }

    return ret;
}

HashValue* Hash_Get(Hash* hash, HashKey* key, Hash_Compare* compare)
{
    HashValue* ret = NULL;
    HashNode* node = (HashNode*)BSTree_Get(hash, key, compare);

    if (node != NULL)
        ret = node->value;

    return ret;
}

int Hash_Count(Hash* hash)
{
    return BSTree_Count(hash);
}
