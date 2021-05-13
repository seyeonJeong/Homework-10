/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL;

	printf("[----- [������] [2018038027] -----]");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout);
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224s
 */
void iterativeInorder(Node* node)
{
	//������ ������ �̿��ؼ� ��͸� ��������ʰ� �ݺ������� inorder����� ������ �� �ִ�.
	top = -1; // top�� -1�� �ʱ�ȭ
	for (;;) //�ݺ����� ����
	{
		for (; node;) //node�� NULL�� �ƴ϶��
		{
			push(node); //node�� stack�� push�ϰ�
			node = node->left; //node�� node�� left�� ����Ű�� ���� ����
		}
		node = pop(); //node�� stack���� pop
		if (node == NULL) //node�� NULL�̶�� �� stack��
		{
			break;
		}
		printf("[%d]", node->key); //node��key���� ���
		node = node->right; //node�� node�� right�� ����Ű�� ���� ����
	}

}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	front = rear = -1; // front�� rear�� -1�� �ʱ�ȭ ����
	Node* n1 = NULL; //��������� n1�� ���� �� �ʱ�ȭ
	if (ptr == NULL) //ptr(head->left)�� NULL�̶��
		return; //���� Ʈ��
	enQueue(ptr); // ptr�� ���� ť�� ����
	for (;;) //�ݺ���
	{

		n1 = deQueue(); //delete Queue�� �� ���� n1�� ����

		if (n1 != NULL) //n1�� NULL�� �ƴ϶��, �� Queue�� ���� �ϳ� �̻� �����ߴٸ�
		{
			printf("[%d]", n1->key); //n1�� key�� ���
			if(n1->left) //���� n1�� left�� NULL�� �ƴ϶��
				enQueue(n1->left); //Queue�� n1�� left�� ����
			if(n1->right) //���� n1�� right�� NULL�� �ƴ϶��
				enQueue(n1->right); //Queue�� n1�� right�� ����
		}
		else
			break;
	}
	for (int i = 0; i < MAX_QUEUE_SIZE; i++) //�ݺ����� ������ ť�� �ʱ�ȭ ���ش�
	{
		queue[i] = NULL;
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	Node* node = head->left;
	Node* parents = NULL; //������ ���� �θ��带 ����ų �����͸� �����ϰ� �ʱ�ȭ
	Node* cur = NULL; // �ڽĳ�� 2���� �� Ž���� ���� �����͸� �����ϰ� �ʱ�ȭ
	Node* precur = NULL; //cur�� ������带 ������ �����͸� �����ϰ� �ʱ�ȭ
	if (node == NULL) // ��� ���� root��尡 NULL�̶�� ��尡 �������� �ʴ´�.
	{
		printf("������ ��尡 �������� �ʽ��ϴ�.\n");
		return 0;
	}
	while (node != NULL) // node�� NULL���� �ƴ� ������ �ݺ�
	{
		if (node->key > key) //node�� key���� key������ ū���
		{
			parents = node; // node�� ����Ű�� ��带 �θ��尡 ����Ű�� ��
			node = node->left; //node�� ����Ű�� ��带 ���ʳ��� �̵�
		}
		else if (node->key < key) //node�� key���� key������ �������
		{
			parents = node; //node�� ����Ű�� ��带 �θ��尡 ����Ű����
			node = node->right; //node�� ����Ű�� ��带 �����ʳ��� �̵�
		}
		else if(node->key == key) //node�� key���� key���� �������(�ϴ� ������ ��带 ã�Ƴ´�)
		{
			if (node->right == NULL && node->left == NULL)//���� node�� right���� NULL �̰� node�� left���� NULL�̸� ���ǹ��� ����(���� ����� ����)
			{
				if (node == head->left) //���� node�� ������� left���? �ش� ���� root����̴�. root����� right=left=NULL�̶�� ���� root����� �������� ����
				{
					free(node); //node�� �ش��ϴ� ��带 ���������ְ� �ݺ����� ������(�����Ϸ�)
					break;
				}
				else if (parents->right == node) //�θ����� �������� node���
				{
					parents->right = NULL; // �θ����� right�� ����Ű�� ���� NULL�� ��ȯ(�����Ϸ��� ���� �̾��� ����Ʈ ������ ����)
					node->right = node->left = NULL;
					free(node);//node�� ���������ְ� �ݺ����� ������(�����Ϸ�)
					break;
				}
				else if (parents->left == node) //�θ����� left�� ����Ű�� ���� node���
				{
					parents->left = NULL; //�θ����� left�� ����Ű�� ���� NULL�� ��ȯ(�����Ϸ��� ���� �̾��� ������ ������ ����)
					node->right = node->left = NULL;
					free(node); //node�� ���������ְ� �ݺ����� ������(�����Ϸ�)
					break;
				}

			}
			else if (node->right == NULL || node->left == NULL) //���� �ϳ��� �ڽ��� ���� ���� �����
			{
				if (node == head->left) //���� node�� head->left���
				{
					if (node->right == NULL) //���� node��right�� NULL���� ���´ٸ�  (�ϳ��� �ڽ��� ���� ��� �̹Ƿ� �ΰ��� ���� �з�)
					{
						head->left = node->left; //head�� left�� node�� left�� ����
						node->left = NULL; //node�� left�� NULL
						free(node); //node�� ����
						break;
					}
					if (node->left == NULL) //���� node�� left�� NULL���� ���´ٸ�
					{

						head->left = node->right;
						node->right = NULL; //node->right�� NULL�� ���� �̹��� �ϳ��� �ٸ���
						free(node);
						break;
					}
					break;
				}
				if (node->right == NULL) // node�� right�� �������� ������
				{
					if (parents->left == node) // �θ����� left�� node���
					{
						parents->left = node->left; //�θ����� left�� node�� left���� ����(node�� right�� ���ٴ� ����)
						free(node); // node�� ����
						break;
					}
					if (parents->right == node) // �θ����� right�� node���
					{
						parents->right = node->left; //�θ����� right�� node�� left���� ����
						free(node); //node�� ����
						break;
					}
					break;
				}
				else if (node->left == NULL) //node�� left�� �������� ������
				{
					if (parents->right == node) //���� �θ����� right�� �����
					{
						parents->right = node->right; //�θ����� right�� node�� right���� ����
						free(node); //node�� ����
						break;
					}
					if (parents->left == node) //���� �θ����� left�� �����
					{
						parents->left = node->right; //�θ����� left�� node�� right���� ����
						free(node); //node�� ����
						break;
					}
					break;
				}
			}
			else if (node->left != NULL && node->right != NULL) // node�� �ΰ��� �ڽ��� ������ ��
			{
				if (node == head->left) // ���� node�� head->left��� (ù��° �����)
				{
					if (node->right->left == NULL) // ���� ����� right�� left ���� NULL�̶�� (�����ʿ��� ���� ������ ���� ��ü���� ã�⶧���� �̷��� ������ ���ԵǾ����ϴ�.)
					{
						head->left = node->right; // �������� left�� node�� right������ ����
						node->right->left = node->left; //node�� right�� left�� node�� left�� ��
						node->left = node->right = NULL; //node�� left�� right���� NULL�� �ʱ�ȭ ��Ų�� ����
						free(node);
						break;
					}
					cur = node->right; //��ü��带 Ž���ϱ� ���� ������ ���� cur�� node�� right�� ����(�����ʿ��� ���� ������ ���� ã�� ����)
					while (cur->left != NULL) //cur�� left�� NULL���� ���� ������ �ݺ��Ѵ�
					{
						precur = cur; //cur�� ���� ��带 ����
						cur = cur->left; //cur�� cur�� left ��带 ����
					}
					precur->left = NULL; //���� cur�� left�� NULL (cur�� ��ü����̹Ƿ� cur�� ������忡�� left�� �����)
					head->left = cur; //head->left�� cur�� ��(������ ����� �ڸ��� �̵�)
					//cur�� ���ʰ� �������� ���� �ִ� ����� ���ʰ� ���������� �ٲ�
					cur->left = node->left;
					cur->right = node->right;
					//������ ����� ���ʰ� �������� NULL�� �ʱ�ȭ ������ �� ��带 ������
					node->right = node->left = NULL;
					free(node);
					break;

				}
				if (parents->left == node) //���� �θ����� ������ �����
				{
					if (node->right->left == NULL) // ���� ����� right�� left ���� NULL�̶�� (�����ʿ��� ���� ������ ���� ��ü���� ã�⶧���� �̷��� ������ ���ԵǾ����ϴ�.)
					{
						//������ ��带 �����ϰ� ��ü�� ��带 ������ ����� �ڸ��� �������ִ� �۾�.(ù��° ������ �Լ��� ����� �۾��̹Ƿ� �ּ� ����ۼ��Ͽ����ϴ�.)
						parents->left = node->right; //���� ���ǰ� �ٸ����� parents�� �̿��Ѵٴ� ���̴�.
						node->right->left = node->left;
						node->left = node->right = NULL;
						free(node);
						break;
					}
					//cur������ ������ �̿��Ͽ� �����ʿ��� ���� ������ ��带 ã�Ƴ���,
					cur = node->right;
					while (cur->left != NULL)
					{
						precur = cur;
						cur = cur->left;
					}
					//������ ��带 ��ü�� ��带 ã�ұ� ������ ������ ����� �ڸ��� ��ü�� ��带 �����ϰ� ��ü�� ��忡 ����Ǿ��� ���� ����� left���� NULL�� �������ش�.
					precur->left = NULL;
					parents->left = cur;
					cur->left = node->left;
					cur->right = node->right;
					//������ ����� ���ʰ� �������� NULL������ �ʱ�ȭ ���� �� ������
					node->left = node->right = NULL;
					free(node);
					break;
				}
				if (parents->right == node) //���� �θ����� �������� �����
				{
					if (node->right->left == NULL) // ���� ����� right�� left ���� NULL�̶�� (�����ʿ��� ���� ������ ���� ��ü���� ã�⶧���� �̷��� ������ ���ԵǾ����ϴ�.)
					{
						//�θ����� ������ ����϶��� �۾��� ����ϴ�. ������ ��带 �����ϰ� ��ü�� ��带 ������ ����� �ڸ��� ��ü���ִ� �۾�
						parents->right = node->right; //�ٸ����� parents�� right�� node�� right�� �ȴٴ� ���̴�.
						node->right->left = node->left;
						//node�� ���ʰ� �������� NULL������ �ʱ�ȭ �� ����
						node->left = node->right = NULL;
						free(node);
						break;
					}
					//cur�� �̿��Ͽ� �����ʿ��� ���� ������ ��带 ã�Ƴ��� �۾�
					cur = node->right;
					while (cur->left != NULL)
					{
						precur = cur;
						cur = cur->left;
					}
					//�����ʿ��� ���� ������ ��带 ã�Ƴ´ٸ� ������ ����� �ڸ��� ��ü�� ��带 �������ְ� ��ü�� ��尡 �ִ��ڸ��� �����͸� ����(precur�� left�� NULL�� �ʱ�ȭ)
					precur->left = NULL;
					parents->right = cur;
					cur->left = node->left;
					cur->right = node->right;
					//node�� �����ʰ� ������ ���� NULL�� �ʱ�ȭ �� �� ������
					node->left = node->right = NULL;
					free(node);
					break;
				}


			}




		}


	}
	if (node == NULL) // node�� NULL�� �Ǿ����� ���ǿ� �����ϴ� ��尡 �������� �ʴ� ���(������ ��尡 �������� �ʴ� ���)
	{
		printf("������ ��尡 �������� �ʽ��ϴ�.\n"); //�ȳ������� ���
		return 0;
	}


	return 0;

}


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{
	return stack[top--]; //stack[top]�� �������ص� top�� -1����
}

void push(Node* aNode)
{
	stack[++top] = aNode; //top�� +1 �� �� stack[top]�� ���� aNode�� ���� ����
}



Node* deQueue()
{
	if (front == rear&&rear == -1) //���� front�� rear�� ���� ���̰� rear�� -1�� �̶�� ��, �� queue�̶�� ������� ���
	{
		printf("Queue is Empty");
		return NULL;
	}
	else
	{
		front = front + 1; //fornt�� 1���� ��
		return queue[front]; //queue[front]�� ����
	}


}

void enQueue(Node* aNode)
{
	if (rear == MAX_QUEUE_SIZE) //rear�� ���س��� ť�� ũ����, �� ť�� ���� á�ٸ� ������� ���
	{
		printf("Queue is Full");
	}

	else
	{
		rear = rear + 1; //rear�� 1���� ��
		queue[rear] = aNode; //queue[rear]�� aNode�� ����
	}

}
