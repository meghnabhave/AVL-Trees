#include<stdio.h>
#include<stdlib.h>

//typedef enum{LB,EB,RB} BalanceFactor;

typedef struct node_tag{
	int data;
	int b;
	struct node_tag *left;
	struct node_tag *right;
}node;

node* makeNode(int data){
	node *nptr = (node*)malloc(sizeof(node));
	nptr->data = data;
	nptr->left = NULL;
	nptr->right = NULL;
	nptr->b = 0;
	return(nptr);
}	

int heightTree(node *tree){
	int retval=1;
	if(tree != NULL){
		int heightleft,heightright;
		heightleft = heightTree(tree->left);
		heightright = heightTree(tree->right);
		if(heightleft>heightright)
		retval = heightleft+1;
 		else
		retval = heightright+1;
	}
	return retval;
}

int heightTreeBST(node *tree){
	int height = heightTree(tree);
	return height-2;
}


void computeBalanceFactors(node *tree){	
	if(tree !=NULL)
	{
		int hleft,hright;
		hleft = heightTreeBST(tree->left);
		hright = heightTreeBST(tree->right);
		tree->b = hright-hleft;
		computeBalanceFactors(tree->left);
		computeBalanceFactors(tree->right);
	}
}
void insert(node *root,node *nptr){
	
	node *prev,*ptr;
	ptr = root;
	while(ptr != NULL){
		if(nptr->data > ptr->data){
			prev = ptr;
			ptr=ptr->right;		
		}
		else{
			prev = ptr;
			ptr = ptr->left;
		}
	}
	if(nptr->data >prev->data)
	{
		prev->right = nptr;
	}
	else
		prev->left = nptr;
}

node* CreateBST(int n){
	
	int i,d;
	
	node *tree;
	node *nptr;
	if(n>0){
	scanf("%d",&d);
	tree = makeNode(d);
	nptr = tree;
	}
	else
	tree = NULL;

	for(i=1;i<n;i++){
		scanf("%d",&d);	
		nptr=makeNode(d);
		insert(tree,nptr);
	}
	computeBalanceFactors(tree);
	return tree;
}

void printTreeinOrder(node *tree){
	if(tree !=NULL)
	{
		printTreeinOrder(tree->left);
		printf("%d:%d ",tree->data,tree->b);
		printTreeinOrder(tree->right);
	}
}



node* checkBal(node *tree,node **prev){
	node* retval = NULL;
	if(tree !=NULL){
		*prev = tree;
		checkBal(tree->left,prev);
		if(tree->b<-1 || tree->b >1)
		retval = tree;
		else
		checkBal(tree->right,prev);
	}
	return retval;
}	

node* rotateLeft(node *nptr){

	node *q = NULL;
	if(nptr != NULL && nptr->right != NULL){
		node *p;
		p = nptr;
		q = nptr->right;
		p->right = q->left;
		q->left = p;
		
	}
	return q;
	
}

node* rotateRight(node *nptr){

	node *q = NULL;
	if(nptr != NULL && nptr->left != NULL){
		node *p;
		p = nptr;
		q = nptr->left;
		p->left = q->right;
		q->right = p;
		
	}
	return q;
	
}

void insertAVL(node *tree, node *ptr){
	insert(tree,ptr);
	computeBalanceFactors(tree);
	node *nptr = NULL;
	node *prev = NULL;
	do{
		
		nptr = checkBal(tree,&prev);
		if(nptr!=NULL){
			if(nptr->b < -1){  /*rotate right*/
				if(nptr->left->b <0){
					if(prev->left == nptr)
					prev->left = rotateRight(nptr); /*single rotate right*/
					else
					prev->right = rotateRight(nptr); /*single rotate right*/
					
				}
				else{
					nptr = rotateLeft(nptr->left);
					if(prev->left == nptr)
					prev->left = rotateRight(nptr);  /*rotate left (nptr->left) then right(nptr)*/
					else
					prev->right = rotateRight(nptr);  /*rotate left (nptr->left) then right(nptr)*/
				}
								
			}
			else{
				if(nptr->left->b >0){
					if(prev->left == nptr)
					prev->left = rotateLeft(nptr); /*single rotate right*/
					else
					prev->right = rotateLeft(nptr); /*single rotate right*/
				}
				else{
					nptr = rotateRight(nptr->right);
					if(prev->left == nptr)
					prev->left = rotateLeft(nptr);  /*rotate left (nptr->left) then right(nptr)*/
					else
					prev->right = rotateLeft(nptr);
					/*rotate left (nptr->right) then right(nptr)*/
				}
			}
			
		}

	}while(nptr!=NULL);
	
	
}

node* CreateAVL(int n){
	
	int i,d;
	
	node *tree;
	node *nptr;
	if(n>0){
	scanf("%d",&d);
	tree = makeNode(d);
	nptr = tree;
	}
	else
	tree = NULL;

	for(i=1;i<n;i++){
		scanf("%d",&d);	
		nptr=makeNode(d);
		insertAVL(tree,nptr);
	}
	computeBalanceFactors(tree);
	return tree;
}

void main(){

	node *tree;
	int n;
	printf("Enter no. of nodes: ");
	scanf("%d",&n);
	tree = CreateAVL(n);
	printTreeinOrder(tree);
	printf("\n");
	int height = heightTreeBST(tree);
	printf("%d\n",height);

}
