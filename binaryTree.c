#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;

    struct Node *left;
    struct Node *right; 
}Node;

typedef struct BinaryTree {
    Node *root;

    int size;
}BinaryTree;

void insertOnLeft(Node *node, BinaryTree *Btree, int data);// só pra corrigir o erro de chamada de função antes da declaração dela

void insertOnRight(Node  *node, BinaryTree *Btree, int data) {
    if (node->right == NULL){

        Node *newNode = (Node*)malloc(sizeof(Node));

        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;

        node->right = newNode;
        Btree->size++;
    }else{
        if (data > node->right->data){
            insertOnRight(node->right, Btree, data);
        }
        if (data < node->right->data){
            insertOnLeft(node->right, Btree, data);
        }
    }
}

void insertOnLeft(Node *node, BinaryTree *Btree, int data){
    if (node->left == NULL){
        Node *newNode = (Node*)malloc(sizeof(Node));

        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;

        node->left = newNode;
        Btree->size++;
    }else{
        if (data < node->left->data){
            insertOnLeft(node->left, Btree, data);
        }
        if (data > node->left->data){
            insertOnRight(node->left, Btree, data);
        }
    }
}

void insert(BinaryTree *Btree, int data){
    if (Btree->root == NULL){
        Node *newNode = (Node*)malloc(sizeof(Node));

        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;

        Btree->root = newNode;
        Btree->size++;
    }else{
        if (data <  Btree->root->data){
            insertOnLeft(Btree->root, Btree, data);
        }
        if (data >  Btree->root->data){
            insertOnRight(Btree->root, Btree, data);
        }
    }
}

void printTree(Node *root){
    if (root != NULL){
        printTree(root->left);
        printf("%d ", root->data);
        printTree(root->right);
    }
}

void printTreeSize(BinaryTree *treeSize) {
    if (treeSize->size == 0){
        printf("The tree is empty\n");
    }else{
        printf("\n---------------------\n");
        printf("Tree Size: %d ", treeSize->size);
        printf("\n---------------------\n");
    }
}

int search(Node *root, int key){
    if (root == NULL){
        printf("\nempty tree or value not found.\n");
        return 0;
    }else{
        if (root->data == key){
            return printf("\nthe element was found: %d\n", root->data);
        }else{
            if (key < root->data){
                return search(root->left, key);
            }else{
                return search(root->right, key);
            }
        } 
    }
}

Node* removeNode(Node *root, int key){
    if (root == NULL){
        printf("\nElement not found.\n");
        return NULL;
    }else{
        if (root->data == key){
           if (root->left ==  NULL && root->right == NULL){
                free(root);
                return NULL;
           }
        }else{
            if (key < root->data){
                root->left = removeNode(root->left, key);
            }else{
                root->right = removeNode(root->right, key);
            }
            return root;
        }
    }
}

int main(){

    int option;
    int data;
    int key;

    BinaryTree tree;
    tree.root = NULL;
    tree.size = 0;

    do{
        printf("\n---------------------\n");
        printf("Exit - 0\nInsert - 1\nPrint Tree - 2\nPrint tree size - 3\nSearch in the tree - 4\nRemove - 5");
        printf("\n---------------------\n");
        scanf("%d", &option );

        switch (option){
            case 0:
                printf("Exiting...\n");
                break;
            case 1:
                printf("Enter the value to be inserted: ");
                scanf("%d",&data);
                insert(&tree, data);
                break;
            case 2:
                printf("\nPrinting the binary tree:");
                printf("\n---------------------\n");
                printTree(tree.root);
                printf("\n---------------------\n");
                break;
            case 3:
                printTreeSize(&tree);
                break;
            case 4:
                printf("Enter the value you want to search for: ");
                scanf("%d", &key);
                search(tree.root, key);
                break;
            case 5:
                printf("Enter the value you want to remove: ");
                scanf("%d", &key);
                removeNode(tree.root, key);
                break;
            default:
                printf("Invalid Option!\n");
                break;
            }
    } while (option != 0);
    
    return 0;
}