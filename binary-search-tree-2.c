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

	printf("[----- [정세연] [2018038027] -----]");

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
	//스택의 성질을 이용해서 재귀를 사용하지않고 반복적으로 inorder방식을 구현할 수 있다.
	top = -1; // top을 -1로 초기화
	for (;;) //반복문의 역할
	{
		for (; node;) //node가 NULL이 아니라면
		{
			push(node); //node를 stack에 push하고
			node = node->left; //node를 node의 left가 가리키는 노드로 변경
		}
		node = pop(); //node를 stack에서 pop
		if (node == NULL) //node가 NULL이라면 빈 stack임
		{
			break;
		}
		printf("[%d]", node->key); //node의key값을 출력
		node = node->right; //node를 node의 right가 가리키는 노드로 변경
	}

}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	front = rear = -1; // front와 rear을 -1로 초기화 해줌
	Node* n1 = NULL; //노드포인터 n1을 선언 후 초기화
	if (ptr == NULL) //ptr(head->left)가 NULL이라면
		return; //공백 트리
	enQueue(ptr); // ptr의 값을 큐에 삽입
	for (;;) //반복문
	{

		n1 = deQueue(); //delete Queue를 한 값을 n1에 대입

		if (n1 != NULL) //n1이 NULL이 아니라면, 즉 Queue에 값이 하나 이상 존재했다면
		{
			printf("[%d]", n1->key); //n1의 key값 출력
			if(n1->left) //만약 n1의 left가 NULL이 아니라면
				enQueue(n1->left); //Queue에 n1의 left를 삽입
			if(n1->right) //만약 n1의 right가 NULL이 아니라면
				enQueue(n1->right); //Queue에 n1의 right를 삽입
		}
		else
			break;
	}
	for (int i = 0; i < MAX_QUEUE_SIZE; i++) //반복문이 끝나고 큐를 초기화 해준다
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
	Node* parents = NULL; //삭제시 사용될 부모노드를 가리킬 포인터를 정의하고 초기화
	Node* cur = NULL; // 자식노드 2개일 때 탐색에 사용될 포인터를 정의하고 초기화
	Node* precur = NULL; //cur의 이전노드를 저장할 포인터를 정의하고 초기화
	if (node == NULL) // 헤드 왼쪽 root노드가 NULL이라면 노드가 존재하지 않는다.
	{
		printf("삭제할 노드가 존재하지 않습니다.\n");
		return 0;
	}
	while (node != NULL) // node가 NULL값이 아닐 때까지 반복
	{
		if (node->key > key) //node의 key값이 key값보다 큰경우
		{
			parents = node; // node가 가리키는 노드를 부모노드가 가리키게 함
			node = node->left; //node가 가리키는 노드를 왼쪽노드로 이동
		}
		else if (node->key < key) //node의 key값이 key값보다 작은경우
		{
			parents = node; //node가 가리키는 노드를 부모노드가 가리키게함
			node = node->right; //node가 가리키는 노드를 오른쪽노드로 이동
		}
		else if(node->key == key) //node의 key값이 key값과 같은경우(일단 삭제할 노드를 찾아냈다)
		{
			if (node->right == NULL && node->left == NULL)//만약 node의 right값이 NULL 이고 node의 left값이 NULL이면 조건문이 실행(말단 노드의 조건)
			{
				if (node == head->left) //만약 node가 헤드노드의 left라면? 해당 노드는 root노드이다. root노드의 right=left=NULL이라면 노드는 root빼고는 존재하지 않음
				{
					free(node); //node에 해당하는 노드를 해제시켜주고 반복문을 나간다(삭제완료)
					break;
				}
				else if (parents->right == node) //부모노드의 오른쪽이 node라면
				{
					parents->right = NULL; // 부모노드의 right가 가리키는 값을 NULL로 변환(삭제하려는 노드와 이어진 포인트 연결을 해제)
					node->right = node->left = NULL;
					free(node);//node를 해제시켜주고 반복문을 나간다(삭제완료)
					break;
				}
				else if (parents->left == node) //부모노드의 left가 가리키는 값이 node라면
				{
					parents->left = NULL; //부모노드의 left가 가리키는 값을 NULL로 변환(삭제하려는 노드와 이어진 포인터 연결을 해제)
					node->right = node->left = NULL;
					free(node); //node를 해제시켜주고 반복문을 나간다(삭제완료)
					break;
				}

			}
			else if (node->right == NULL || node->left == NULL) //만약 하나의 자식을 가진 비리프 노드라면
			{
				if (node == head->left) //만약 node가 head->left라면
				{
					if (node->right == NULL) //만약 node의right가 NULL값을 갖는다면  (하나의 자식을 가진 경우 이므로 두가지 경우로 분류)
					{
						head->left = node->left; //head의 left에 node의 left를 대입
						node->left = NULL; //node의 left는 NULL
						free(node); //node를 해제
						break;
					}
					if (node->left == NULL) //만약 node의 left가 NULL값을 갖는다면
					{

						head->left = node->right;
						node->right = NULL; //node->right가 NULL일 경우와 이문장 하나만 다르다
						free(node);
						break;
					}
					break;
				}
				if (node->right == NULL) // node의 right가 존재하지 않을때
				{
					if (parents->left == node) // 부모노드의 left가 node라면
					{
						parents->left = node->left; //부모노드의 left를 node의 left노드로 설정(node의 right는 없다는 가정)
						free(node); // node를 해제
						break;
					}
					if (parents->right == node) // 부모노드의 right가 node라면
					{
						parents->right = node->left; //부모노드의 right를 node의 left노드로 설정
						free(node); //node를 해제
						break;
					}
					break;
				}
				else if (node->left == NULL) //node의 left가 존재하지 않을때
				{
					if (parents->right == node) //만약 부모노드의 right가 노드라면
					{
						parents->right = node->right; //부모노드의 right는 node의 right노드로 설정
						free(node); //node를 해제
						break;
					}
					if (parents->left == node) //만약 부모노드의 left가 노드라면
					{
						parents->left = node->right; //부모노드의 left는 node의 right노드로 설정
						free(node); //node를 해제
						break;
					}
					break;
				}
			}
			else if (node->left != NULL && node->right != NULL) // node가 두개의 자식을 가졌을 때
			{
				if (node == head->left) // 만약 node가 head->left라면 (첫번째 노드라면)
				{
					if (node->right->left == NULL) // 만약 노드의 right의 left 값이 NULL이라면 (오른쪽에서 가장 왼쪽의 값을 대체노드로 찾기때문에 이러한 조건이 포함되었습니다.)
					{
						head->left = node->right; // 헤더노드의 left는 node의 right값으로 설정
						node->right->left = node->left; //node의 right의 left는 node의 left가 됨
						node->left = node->right = NULL; //node의 left와 right값을 NULL로 초기화 시킨후 해제
						free(node);
						break;
					}
					cur = node->right; //대체노드를 탐색하기 위한 포인터 변수 cur을 node의 right로 설정(오른쪽에서 가장 왼쪽의 값을 찾기 위해)
					while (cur->left != NULL) //cur의 left가 NULL값을 가질 때까지 반복한다
					{
						precur = cur; //cur의 이전 노드를 저장
						cur = cur->left; //cur에 cur의 left 노드를 대입
					}
					precur->left = NULL; //이전 cur의 left는 NULL (cur은 대체노드이므로 cur의 이전노드에서 left는 사라짐)
					head->left = cur; //head->left는 cur이 됨(삭제할 노드의 자리로 이동)
					//cur의 왼쪽과 오른쪽을 원래 있던 노드의 왼쪽과 오른쪽으로 바꿈
					cur->left = node->left;
					cur->right = node->right;
					//삭제할 노드의 왼쪽과 오른쪽을 NULL로 초기화 시켜준 후 노드를 해제함
					node->right = node->left = NULL;
					free(node);
					break;

				}
				if (parents->left == node) //만약 부모노드의 왼쪽이 노드라면
				{
					if (node->right->left == NULL) // 만약 노드의 right의 left 값이 NULL이라면 (오른쪽에서 가장 왼쪽의 값을 대체노드로 찾기때문에 이러한 조건이 포함되었습니다.)
					{
						//삭제할 노드를 삭제하고 대체할 노드를 삭제할 노드의 자리에 삽입해주는 작업.(첫번째 조건의 함수와 비슷한 작업이므로 주석 약식작성하였습니다.)
						parents->left = node->right; //위의 조건과 다른점은 parents를 이용한다는 점이다.
						node->right->left = node->left;
						node->left = node->right = NULL;
						free(node);
						break;
					}
					//cur포인터 변수를 이용하여 오른쪽에서 가장 왼쪽의 노드를 찾아낸다,
					cur = node->right;
					while (cur->left != NULL)
					{
						precur = cur;
						cur = cur->left;
					}
					//삭제할 노드를 대체할 노드를 찾았기 때문에 삭제할 노드의 자리에 대체할 노드를 연결하고 대체할 노드에 연결되었던 이전 노드의 left값을 NULL로 변경해준다.
					precur->left = NULL;
					parents->left = cur;
					cur->left = node->left;
					cur->right = node->right;
					//삭제할 노드의 왼쪽과 오른쪽을 NULL값으로 초기화 해준 후 해제함
					node->left = node->right = NULL;
					free(node);
					break;
				}
				if (parents->right == node) //만약 부모노드의 오른쪽이 노드라면
				{
					if (node->right->left == NULL) // 만약 노드의 right의 left 값이 NULL이라면 (오른쪽에서 가장 왼쪽의 값을 대체노드로 찾기때문에 이러한 조건이 포함되었습니다.)
					{
						//부모노드의 왼쪽이 노드일때의 작업과 비슷하다. 삭제할 노드를 삭제하고 대체할 노드를 삭제할 노드의 자리에 대체해주는 작업
						parents->right = node->right; //다른점은 parents의 right가 node의 right가 된다는 점이다.
						node->right->left = node->left;
						//node의 왼쪽과 오른쪽을 NULL값으로 초기화 후 해제
						node->left = node->right = NULL;
						free(node);
						break;
					}
					//cur을 이용하여 오른쪽에서 가장 왼쪽의 노드를 찾아내는 작업
					cur = node->right;
					while (cur->left != NULL)
					{
						precur = cur;
						cur = cur->left;
					}
					//오른쪽에서 가장 왼쪽의 노드를 찾아냈다면 삭제할 노드의 자리에 대체할 노드를 삽입해주고 대체할 노드가 있던자리의 포인터를 해제(precur의 left를 NULL로 초기화)
					precur->left = NULL;
					parents->right = cur;
					cur->left = node->left;
					cur->right = node->right;
					//node의 오른쪽과 왼쪽의 값을 NULL로 초기화 한 후 해제함
					node->left = node->right = NULL;
					free(node);
					break;
				}


			}




		}


	}
	if (node == NULL) // node가 NULL이 되었지만 조건에 부합하는 노드가 존재하지 않는 경우(삭제할 노드가 존재하지 않는 경우)
	{
		printf("삭제할 노드가 존재하지 않습니다.\n"); //안내문구를 출력
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
	return stack[top--]; //stack[top]을 리턴해준뒤 top을 -1해줌
}

void push(Node* aNode)
{
	stack[++top] = aNode; //top을 +1 한 후 stack[top]의 값에 aNode의 값을 대입
}



Node* deQueue()
{
	if (front == rear&&rear == -1) //만약 front와 rear이 같은 값이고 rear이 -1일 이라면 즉, 빈 queue이라면 경고문구를 출력
	{
		printf("Queue is Empty");
		return NULL;
	}
	else
	{
		front = front + 1; //fornt를 1증가 후
		return queue[front]; //queue[front]를 리턴
	}


}

void enQueue(Node* aNode)
{
	if (rear == MAX_QUEUE_SIZE) //rear이 정해놓은 큐의 크기라면, 즉 큐가 가득 찼다면 경고문구를 출력
	{
		printf("Queue is Full");
	}

	else
	{
		rear = rear + 1; //rear을 1증가 후
		queue[rear] = aNode; //queue[rear]에 aNode를 삽입
	}

}
