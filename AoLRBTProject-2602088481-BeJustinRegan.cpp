#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int n = 10;

struct Node {
	int key;
	int color;
	Node *parent;
	Node *left;
	Node *right;
} *root;

Node *newNode(int key){
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->key = key;
	newNode->parent = newNode->left = newNode->right = NULL;
	newNode->color = 1;
	return newNode;
}

Node *insert(Node *curr, Node *newNode){
	if(!curr) return newNode;
	else{
		if(newNode->key < curr->key){
			curr->left = insert(curr->left, newNode);
			curr->left->parent = curr;
		}
		else if(newNode->key > curr->key){
			curr->right = insert(curr->right, newNode);
			curr->right->parent = curr;
		}
		return curr;
	}
}

void leftRotate(Node *temp){
	Node *tempRight = temp->right;
	temp->right = tempRight->left;
	if(temp->right){
		temp->right->parent = temp;
	}
	tempRight->parent = temp->parent;
	
	if(!temp->parent){
		root = tempRight;
	}
	else if(temp == temp->parent->left){
		temp->parent->left = tempRight;
	}
	else{
		temp->parent->right = tempRight;
	}
	tempRight->left = temp;
	temp->parent = tempRight;
}

void rightRotate(Node *temp){
	Node *tempLeft = temp->left;
	temp->left = tempLeft->right;
	if(temp->left){
		temp->left->parent = temp;
	}
	tempLeft->parent = temp->parent;
	if(!temp->parent){
		root = tempLeft;
	}
	else if(temp == temp->parent->left){
		temp->parent->left = tempLeft;
	}
	else{
		temp->parent->right = tempLeft;
	}
	tempLeft->right = temp;
	temp->parent = tempLeft;
}

void fixing(Node *curr){
	while((curr != root) && ((!curr->color) && (curr->parent->color))){
		Node *currParent = curr->parent;
		Node *currGparent = currParent->parent;
		if(currParent == currGparent->left){
			Node *currUncle = currGparent->right;
			if(!currUncle && currUncle->color){
				currGparent->color = 1;
				(currParent->color)--;
				(currUncle->color)--;
				curr = currGparent;
			}
			else if(curr == currParent->right){
				leftRotate(currParent);
				curr = currParent;
				currParent = curr->parent;
			}
			else{
				rightRotate(currGparent);
				int temp = currParent->color;
				currParent->color = currGparent->color;
				currGparent->color = temp;
				curr = currParent;
			}
		}
		else{
			Node *currUncle = currGparent->left;
			if(!currUncle && currUncle->color){
				(currGparent->color)++;
				(currParent->color)--;
				(currUncle->color)--;
				curr = currGparent;
			}
			else if(curr == currParent->left){
				rightRotate(currParent);
				curr = currParent;
				currParent = curr->parent;
			}
			else{
				leftRotate(currGparent);
				int temp = currParent->color;
				currParent->color = currGparent->color;
				currGparent->color = temp;
				curr = currParent;
			}
		}
	}
}

int count;

void inorder(Node *curr){
	if(!curr) return;
	else{
		inorder(curr->left);
		count++;
		if(count < n) printf("%d ", curr->key);
		else printf("%d\n", curr->key);
		inorder(curr->right);
	}
}

int main(){
	int key[n] = {41, 22, 5, 51, 48, 29, 18, 21, 45, 3};
	for(int i = 0; i<n; i++){
		Node *temp = newNode(key[i]);
		root = insert (root, temp);
		fixing(temp);
		root->color = 0;
	}
	count = 0;
	puts("Inorder Traversal of Created Tree");
	inorder(root);
	return 0;
}
