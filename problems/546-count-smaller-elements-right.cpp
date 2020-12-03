#include <stdio.h>
#include <stdlib.h>

// An AVL tree node
struct node
{
    int key;
    struct node *left;
    struct node *right;
    int height;
    int size; // size of the tree rooted with this node
};

// A utility function to get maximum of two integers
int max(int a, int b);

// A utility function to get height of the tree rooted with N
int height(struct node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

// A utility function to size of the tree of rooted with N
int size(struct node *N)
{
    if (N == NULL)
        return 0;
    return N->size;
}

// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b) ? a : b;
}

/* Helper function that allocates a new node with the given key and
	NULL left and right pointers. */
struct node *newNode(int key)
{
    struct node *node = (struct node *)
        malloc(sizeof(struct node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // new node is initially added at leaf
    node->size = 1;
    return (node);
}

// A utility function to right rotate subtree rooted with y
struct node *rightRotate(struct node *y)
{
    struct node *x = y->left;
    struct node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Update sizes
    y->size = size(y->left) + size(y->right) + 1;
    x->size = size(x->left) + size(x->right) + 1;

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
struct node *leftRotate(struct node *x)
{
    struct node *y = x->right;
    struct node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Update sizes
    x->size = size(x->left) + size(x->right) + 1;
    y->size = size(y->left) + size(y->right) + 1;

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(struct node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Inserts a new key to the tree rotted with node. Also, updates *count
// to contain count of smaller elements for the new key
struct node *insert(struct node *node, int key, int *count)
{
    /* 1. Perform the normal BST rotation */
    if (node == NULL)
        return (newNode(key));

    if (key < node->key)
        node->left = insert(node->left, key, count);
    else
    {
        node->right = insert(node->right, key, count);

        // UPDATE COUNT OF SMALLER ELEMENTS FOR KEY
        *count = *count + size(node->left) + 1;
    }

    /* 2. Update height and size of this ancestor node */
    node->height = max(height(node->left), height(node->right)) + 1;
    node->size = size(node->left) + size(node->right) + 1;

    /* 3. Get the balance factor of this ancestor node to check whether
	this node became unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

// The following function updates the countSmaller array to contain count of
// smaller elements on right side.
void constructLowerArray(int arr[], int countSmaller[], int n)
{
    int i, j;
    struct node *root = NULL;

    // initialize all the counts in countSmaller array as 0
    for (i = 0; i < n; i++)
        countSmaller[i] = 0;

    // Starting from rightmost element, insert all elements one by one in
    // an AVL tree and get the count of smaller elements
    for (i = n - 1; i >= 0; i--)
    {
        root = insert(root, arr[i], &countSmaller[i]);
    }
}

/* Utility function that prints out an array on a line */
void printArray(int arr[], int size)
{
    int i;
    printf("\n");
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
}

// Driver program to test above functions
int main()
{
    int arr1[] = {10, 6, 15, 20, 30, 5, 7};

    int arr2[] = {1, 3, 2, 4, 6, 9, 8, 7, 6, 5, 4};

    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

    int *low1 = (int *)malloc(sizeof(int) * n1);
    int *low2 = (int *)malloc(sizeof(int) * n2);

    constructLowerArray(arr1, low1, n1);
    constructLowerArray(arr2, low2, n2);

    printf("Following are the constructed smaller count arrays");
    printArray(low1, n1);
    printArray(low2, n2);
    return 0;
}