#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include <assert.h>
#include <stdbool.h>

typedef struct _Node // Declaring a struct Node
{ 
    struct _Node *left;
    struct _Node *right;
    int value;
}Node;

// Function to create parent node
Node * parentNode(Node * root, int value) 
{
  Node* next;
  if (value > root-> value)
    next = root->left;
  else
    next = root->right;

  if (next == NULL || next-> value == value) // if next is null or value is the same as value
    return root;                            // return the root
  else
    return parentNode(next, value);
}

// Create node function 
Node * createNode(int value) 
{
  Node * node = (Node *) malloc(sizeof(Node)); // Allocating memory for newly created node
  if (node != NULL) // if memory allocation is successful
    node->value = value;
    node->left = node->right = NULL;
  return node;
}


Node * addNode(Node * root, int value) 
{
  if (root == NULL) // if tree is empty
    return createNode(value);

  if (value == root->value) // if value is the same as root value
    return NULL;

  Node * parent = parentNode(root, value); 
  Node * child = value > parent->value ? parent->left : parent->right; 
  // if value is greater than parent value
  // go left, else go right

  if (child == NULL) // if child not found
  {   
    child = createNode(value); // child will be new node
    if (value > parent->value) // if value is bigger than parents value
        parent->left = child;  // move to left
    else
        parent->right = child; // move to right
    return child;
  } 
  else 
    return NULL; // value found, then return null
}

//Function to delete a node
Node* removeNode(Node *root, int value)
{
	if (root == NULL) // if root is empty
		return NULL;

	Node *parent, *node;
    // finding node with matching value parameter and its parent node
	if (root->value == value) // if root value is equal to value
    {
		parent = NULL;
		node = root;
    }
	else 
    {
		parent = parentNode(root, value); // find parent node
		node = value > parent->value ? parent->left : parent->right; // recursive transverse
    }

	//if value was not found
	if (node == NULL)
		return root;

	Node *new_node; 
	if (node->left == NULL) // if node has no left child, then make the right child the new node
    {
		new_node = node->right;
	}
	else if (node->right == NULL) // if node has no right child, then make the left child the new node
    {
        new_node = node->left;
    }
    else // if node has both left and right child
	{
		// otherwise make right child the rightmost leaf of the subtree rooted in the left child
		// and make the left child the new node
		Node *rightmost = new_node = node->left; 
		while (rightmost->right != NULL) 
			rightmost = rightmost->right; 
		rightmost->right = node->right; 
	}

	free(node);

	Node *new_root;
	if (parent == NULL)
	{ 
		// if node is the root, then make the new node the new root
		new_root = new_node;
	}
	else
	{
		// otherwise make the new node the child of the parent node
		new_root = root;
		if (value > parent->value)
			parent->left = new_node;
		else
			parent->right = new_node;
	}
	return new_root;
}

//Function to print Subtree

void displaySubtree(Node *N)
{
    if (N == NULL) // Return nothing when there is no subtree
        return;
    displaySubtree(N->right); 
    printf("%d\n", N->value);
    displaySubtree(N->left);
}

//Function to count leaves

int numberLeaves(Node *N)
{
    if (N == NULL) // Return 0 when there no nodes
    {
        return 0;
    }
    if (N->left == NULL && N->right == NULL) // Return 1 when there are no children of a node (it is a leaf)
    {
        return 1;
    }
    else // Return sum of leaves on left and right side of tree 
    {
        return numberLeaves(N->left) + numberLeaves(N->right);
    }
}

//Function to delete subtree
Node* removeSubtree(Node *root, int value)
{
    if (root == NULL) // If there are no nodes, return root
    {
        return root;
    }
    if (value > root->value) // If the value we want to delete is bigger, transverse the left subtree until the value is found 
    {
        root->left = removeSubtree(root->left, value);
    }
    else if (value < root->value) // else if, transverse the right subtree until the value is found 
    {
        root->right = removeSubtree(root->right, value);
    }
    else // if the value is equal to the root's value, delete the subtree
    {
        if (root->left == NULL) // if there is no left child, free the right child
        {
            free(root->right);
        }
        else if (root->right == NULL) // if there is no right child, free the left child
        {
            free(root->left);
        }
        else if (root->left != NULL && root->right != NULL) // if there are two childre, free both children
        {
            free(root->right);
            free(root->left);
        }
    }
    return root;
}

//Find the depth between the root and the node with the given value
int nodeDepth(Node *root, Node *N)
{
    
    if (root == NULL) // if root does not exist, return -1
    {
        return -1;
    } 
    else if (root->value == N->value) // if root value is equal to N value, return 0
    {
        return 0;
    } 
    else if(root->value > N->value) // else if root value is greater than N value, return 1 + nodeDepth of right subtree
    {
        return 1 + nodeDepth(root->right, N);
    }
    else // else return 1 + nodeDepth of left subtree
    {
        return 1 + nodeDepth(root->left,N);
    }
    
}