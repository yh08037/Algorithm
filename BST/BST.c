#include "BST.h"

BST_TREE* BST_Create(int (*compare) (void* argu1, void* argu2)) {
    BST_TREE* tree;

    tree = (BST_TREE*) malloc(sizeof(BST_TREE));
    if (tree) {
        tree->root = NULL;
        tree->count = 0;
        tree->compare = compare;
    }

    return tree;
}

BST_TREE* BST_Destroy(BST_TREE* tree) {
    //??

    free(tree);
}


bool BST_Insert(BST_TREE* tree, void* dataPtr) {
    NODE* newPtr;

    newPtr = (NODE*) malloc(sizeof(NODE));
    if (!newPtr)
        return false;

    newPtr->right = NULL;
    newPtr->left = NULL;
    newPtr->dataPtr = dataPtr;

    if (tree->count == 0)
        tree->root = newPtr;
    else
        _insert(tree, tree->root, newPtr);

    (tree->count)++;
    return true;
}


static NODE* _insert(BST_TREE* tree, NODE* root, NODE* newPtr) {
    if (!root)
        return newPtr;

    if (tree->compare(newPtr->dataPtr, root->dataPtr) < 0) {
        tree->left = _insert(tree, root->left, newPtr));
        return root;
    }
    else {
        root->right = _insert(tree, root->right, newPtr);
        return root;
    }

    return root;
}
