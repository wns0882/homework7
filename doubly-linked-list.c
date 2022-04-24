#include<stdio.h>
#include<stdlib.h>
/* �ʿ��� ������� �߰� if necessary */


typedef struct Node { //Node ����ü ����
	int key;
	struct Node* llink; //����ü ������ llink ����
	struct Node* rlink; //����ü ������ rling ����
} listNode; //����ü�� ��Ī�� listNode�� ���� 



typedef struct Head { //Head ����ü ����
	struct Node* first; //����ü ������ first ����
}headNode; //����ü�� ��Ī�� headNode�� ����

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ����
         lab3�� initialize�� �������� ���� �Ұ� */
int initialize(headNode** h);

/* note: freeList�� �̱������͸� �Ű������� ����
        - initialize�� �� �ٸ��� ���� �Ұ�
         - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode=NULL; //����ü �������� ���� �ʱ�ȭ

	do{
		printf("[----- [���ؿ�] [2019038010] -----]");
        printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = "); 
		scanf(" %c", &command);//Ŀ�ǵ带 �Է¹޾Ƽ� �Է¹��� ���� ���� �Լ� ����

		switch(command) {//�Է¹��� Ŀ�ǵ忡���� �Լ� ����
		case 'z': case 'Z'://z�� �Է¹��� ���
			initialize(&headnode);//initalize �Լ� ���� �� ���ϰ� ����
			break;
		case 'p': case 'P'://p�� �Է¹��� ���
			printList(headnode);// printList �Լ� ����
			break;
		case 'i': case 'I'://i�� �Է¹��� ���
			printf("Your Key = ");
			scanf("%d", &key);//key���� �Է� ����
			insertNode(headnode, key);// insertnode �Լ� ���� -> key���� �Ѱ��ش�
			break;
		case 'd': case 'D'://d�� �Է¹��� ���
			printf("Your Key = ");
			scanf("%d", &key);//key���� �Է� ����
			deleteNode(headnode, key);//deleteNode �Լ� ���� -> key���� �Ѱ��ش� 
			break;
		case 'n': case 'N'://n�� �Է¹��� ���
			printf("Your Key = ");
			scanf("%d", &key);//key���� �Է� ����
			insertLast(headnode, key);//insertLast �Լ� ���� -> key���� �Ѱ��ش�
			break;
		case 'e': case 'E'://e�� �Է¹��� ���
			deleteLast(headnode);//deleteLast �Լ� ���� 
			break;
		case 'f': case 'F'://f�� �Է¹��� ���
			printf("Your Key = ");
			scanf("%d", &key);//key���� �Է� ����
			insertFirst(headnode, key);//insertFirst �Լ� ���� -> key���� �Ѱ��ش�
			break;
		case 't': case 'T'://t�� �Է¹��� ���
			deleteFirst(headnode);//deleteFirst �Լ� ����
			break;
		case 'r': case 'R'://r�� �Է¹��� ���
			invertList(headnode);//invertList �Լ� ����
			break;
		case 'q': case 'Q'://q�� �Է¹��� ���
			freeList(headnode);//freeList �Լ� ����
			break;
		default://�ٸ� Ŀ�ǵ带 �Է¹��� ��� �����̶�� ��� �޼��� ���
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //q�� �Է¹ޱ� ������ �ݺ��� ����

	return 1;
}


int initialize(headNode** h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL) //������� ���� �����ϸ� ����� �����ϴ� �� �޸� ����
		freeList(*h); //�޸����� �Լ�

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (headNode*)malloc(sizeof(headNode)); //����� ������ ���� ���� �޸� �Ҵ�
	(*h)->first = NULL; //���ο� ���� ����Ʈ ����
	return 1;
}

int freeList(headNode* h){ // �޸� ���� �Լ�
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
	 */
	listNode* p = h->first; //����Ʈ ����� �����Ͱ� ��带 ����Ű�� ����

	listNode* prev = NULL; //����Ʈ ��� ������ ���� ���� 
	while(p != NULL) { // ����Ʈ ����� ������ Null�� �� ������ �ݺ�
		prev = p; //prev�� p�� ����Ű�� �Ѵ�
		p = p->rlink; //p����� ������ ��带 ����Ű�� �Ѵ�
		free(prev); // prev �޸� ����
	}
	free(h); //����� ������h �޸� ����
	return 0;
}


void printList(headNode* h) { //���Ḯ��Ʈ�� ������ ����ϴ� �Լ�
	int i = 0;
	listNode* p; //listNode ������ ���� p ���� 

	printf("\n---PRINT\n"); 

	if(h == NULL) {   //������� ���� �������� ������ ���Ḯ��Ʈ�� ���� ���������ʴ´ٴ� �޼��� ���
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; //����Ʈ ��� ������ ���� p�� ����带 ����Ű�� ����

	while(p != NULL) { //������ ���� p�� Null�� �� ������ �ݺ�
		printf("[ [%d]=%d ] ", i, p->key); //���Ḯ��Ʈ�� ������ ���
		p = p->rlink; //p�� ���� ��带 ����Ű�� ����
		i++; //����� �� ��½� �ε��� ��ȣ�� �˸��� ���� ���
	}

	printf("  items = %d\n", i); //���Ḯ��Ʈ�� �����ϴ� ��� ���� ���
}




/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) { //���Ḯ��Ʈ ������ ��忡 �߰��ϴ� �Լ� 

	listNode* node = (listNode*)malloc(sizeof(listNode));//node �����Ҵ�
	node->key = key; //����� key���� �Է¹��� key���� ����
	node->rlink = NULL; //����� ���� link�� ����Ǵ� ��ũ�� ������ ����
	node->llink = NULL;//����� ���� link�� ����Ǵ� ��ũ�� ������ ����

	if (h->first == NULL)//����� ���� �������� �ʴ°�� �Է¹��� key���� ����忡 ������ ����
	{
		h->first = node; //�Է¹��� ��尡 ����尡 �ǰ��Ѵ�
		return 0;
	}

	listNode* n = h->first; //����ü ������ ���� n������ ����带 ����Ű���Ѵ�
	while(n->rlink != NULL) { //���Ḯ��Ʈ���� �� ���� ���� �̵��ϴ� �ݺ���
		n = n->rlink; // ����� ���� ��尡 Null���� ������ �ݺ��ؼ� �� ���� ���� �̵��Ѵ�
	}
	n->rlink = node; //�� ���� ���ο� ��带 �����ؼ� ���� ���� ����
	node->llink = n; //�� ���� �ִ� ��带 ���� ���� ����
	return 0;
}



/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) { //list�� ������ ��带 �����ϴ� �Լ�

	if (h->first == NULL) //����尡 ���������ʴ� ��� ������ ���� ���ٴ� �޼��� ���
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first; //n��尡 ����带 ����Ű�� �Ѵ�
	listNode* trail = NULL;//trail ���� ��� ����

	/* ��尡 �ϳ��� �ִ� ���, �� first node == last node��  ��� ó�� */
	if(n->rlink == NULL) {  //��尡 �ϳ��� �ִ� ���
		h->first = NULL; //����带 Null�� �ʱ�ȭ���ش�
		free(n);//��带 �޸� ����
		return 0;
	}

	/* ������ ������ �̵� */
	while(n->rlink != NULL) { //���� ���� ���� �̵��Ѵ�
		trail = n; //trail�� n����� ������带 ����Ŵ
		n = n->rlink;//n��忡 ���� ��带 ����Ű�� �Ѵ�
	}

	/* n�� �����ǹǷ�, ���� ����� ��ũ NULL ó�� */
	trail->rlink = NULL; //trail�� ���� ��尡 ����Ű�� ��带 ���ش�
	free(n); // ���� ������ �ִ� ��带 ����

	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) { //list�� ù��° ��忡 ���� �����ϴ� �Լ�

	listNode* node = (listNode*)malloc(sizeof(listNode)); // node �����Ҵ�
	node->key = key; //�Է¹��� key���� ���� ��带 ����
	node->rlink = node->llink = NULL; //����� �¿��� ��ũ�� Null�� �ʱ�ȭ 

	if(h->first == NULL) //����尡 ���������ʴ°��
	{
		h->first = node; //node�� ������ ����
		return 1;
	}

	node->rlink = h->first; //������ ����带 ���ο� ����� ���� ��ũ�� ����
	node->llink = NULL; //����� ���� ��ũ�� Null�� �ʱ�ȭ
	
    listNode *p = h->first; //p��尡 h->first�� ����Ű�� �Ѵ�
	p->llink = node; //p�� ���� link�� ������ ����
	h->first = node; //�Է¹��� ��尡 ����尡 �ǰ��Ѵ�

	return 0;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) { //ù�� ° ��带 �����ϴ� �Լ�

	if (h->first == NULL) //��尡 �������� �ʴ� ��� �޼��� ���
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first; // n ��尡 ������ ���� 
	h->first = n->rlink; // 2��° ��带 ������ ����

	free(n);//ù�� ° ��带 ������Ų��

	return 0;
}



/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) { //����Ʈ�� ��带 �������� �ٲٴ� �Լ�


	if(h->first == NULL) { //��尡 �������� �ʴ� ��� �޼��� ���
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first; //n�� ������ ����
	listNode *trail = NULL;// ���� ��� ����
	listNode *middle = NULL;//���� ��� ����

	while(n != NULL){ //n�� Null���� ������ �ݺ�
		trail = middle; 
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	} //���ο� ��带 2�� ���� trail -> middle -> n �̷������� �̵��ϸ鼭 ����� ������ �Ѱ��� �ٲ��ش�

	h->first = middle;

	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //node �����Ҵ�
	node->key = key; //����� key���� �Է¹��� key������ ����
	node->llink = node->rlink = NULL; //������ ����� �¿��� ��ũ�� �ʱ�ȭ

	if (h->first == NULL) //��尡 �������� ���� ���
	{
		h->first = node; //�Է¹��� ��带 ������ ����
		return 0;
	}

	listNode* n = h->first; // ���ο� ��带 ���� �� ���Ḯ��Ʈ ù��° �ּҸ� ����

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL) {//n�� Null���� ������ �ݺ�
		if(n->key >= key) {
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->first) { // n�� ��� ����� ��� -> ù��° ����� ���
				insertFirst(h, key); //ù��° ���� ����
			} else { /* �߰��̰ų� �������� ��� */
				node->rlink = n;//����� ���� ��ũ�� n�� ����
				node->llink = n->llink;//node�� ���� ��ũ�� n�� ���� ��ũ�� ���� 
				n->llink->rlink = node; //node�� �߰��� �����ؼ� ���� ���� ����
			}
			return 0;
		}

		n = n->rlink; //��ĭ�� �̵�
	} 

	/* ������ ������ ã�� ���� ���, �������� ���� */
	insertLast(h, key);//����Ʈ �������� ��� ����
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) { //��带 �����ϴ� �Լ�

	if (h->first == NULL) //���ȿ� key���� �������� �ʴ� ��� �޼��� ���
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first; // ���ο� ��带 ���� �� ���Ḯ��Ʈ ù��° �ּҸ� ����

	while(n != NULL) {
		if(n->key == key) {
			if(n == h->first) { /* ù ���° ��� �ΰ�� */
				deleteFirst(h); //��带 ����
			} else if (n->rlink == NULL){ /* ������ ����� ��� */
				deleteLast(h);//������ ��� ����
			} else { /* �߰��� ��� */
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n); //��� n�� �¿��� ������ ������ �� ��� n�� ������Ų��
			}
			return 1;
		}

		n = n->rlink;//��带 ��ĭ�� �̵�
	}

	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key);//�Է��� Ű���� ���� ��尡 ���ٴ� �޼��� ��� 
	return 1;
}


