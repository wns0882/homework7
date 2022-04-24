#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node { //Node 구조체 정의
	int key;
	struct Node* llink; //구조체 포인터 llink 선언
	struct Node* rlink; //구조체 포인터 rling 선언
} listNode; //구조체의 별칭을 listNode로 설정 



typedef struct Head { //Head 구조체 정의
	struct Node* first; //구조체 포인터 first 선언
}headNode; //구조체의 별칭을 headNode로 설정

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         lab3의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
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
	headNode* headnode=NULL; //구조체 포인터의 값을 초기화

	do{
		printf("[----- [박준용] [2019038010] -----]");
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
		scanf(" %c", &command);//커맨드를 입력받아서 입력받은 값에 따라 함수 실행

		switch(command) {//입력받은 커맨드에따라 함수 실행
		case 'z': case 'Z'://z를 입력받은 경우
			initialize(&headnode);//initalize 함수 실행 후 리턴값 대입
			break;
		case 'p': case 'P'://p를 입력받은 경우
			printList(headnode);// printList 함수 실행
			break;
		case 'i': case 'I'://i를 입력받은 경우
			printf("Your Key = ");
			scanf("%d", &key);//key값을 입력 받음
			insertNode(headnode, key);// insertnode 함수 실행 -> key값을 넘겨준다
			break;
		case 'd': case 'D'://d를 입력받은 경우
			printf("Your Key = ");
			scanf("%d", &key);//key값을 입력 받음
			deleteNode(headnode, key);//deleteNode 함수 실행 -> key값을 넘겨준다 
			break;
		case 'n': case 'N'://n을 입력받은 경우
			printf("Your Key = ");
			scanf("%d", &key);//key값을 입력 받음
			insertLast(headnode, key);//insertLast 함수 실행 -> key값을 넘겨준다
			break;
		case 'e': case 'E'://e를 입력받은 경우
			deleteLast(headnode);//deleteLast 함수 실행 
			break;
		case 'f': case 'F'://f를 입력받은 경우
			printf("Your Key = ");
			scanf("%d", &key);//key값을 입력 받음
			insertFirst(headnode, key);//insertFirst 함수 실행 -> key값을 넘겨준다
			break;
		case 't': case 'T'://t를 입력받은 경우
			deleteFirst(headnode);//deleteFirst 함수 실행
			break;
		case 'r': case 'R'://r을 입력받은 경우
			invertList(headnode);//invertList 함수 실행
			break;
		case 'q': case 'Q'://q를 입력받은 경우
			freeList(headnode);//freeList 함수 실행
			break;
		default://다른 커맨드를 입력받은 경우 집중이라는 경고 메세지 출력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //q를 입력받기 전까지 반복문 실행

	return 1;
}


int initialize(headNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL) //헤드노드의 값이 존재하면 노드의 존재하는 값 메모리 해제
		freeList(*h); //메모리해제 함수

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (headNode*)malloc(sizeof(headNode)); //헤드노드 포인터 변수 동적 메모리 할당
	(*h)->first = NULL; //새로운 공백 리스트 생성
	return 1;
}

int freeList(headNode* h){ // 메모리 해제 함수
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first; //리스트 노드의 포인터가 헤드를 가리키게 선언

	listNode* prev = NULL; //리스트 노드 포인터 변수 선언 
	while(p != NULL) { // 리스트 노드의 값들이 Null이 될 때까지 반복
		prev = p; //prev가 p를 가리키게 한다
		p = p->rlink; //p노드의 오른쪽 노드를 가리키게 한다
		free(prev); // prev 메모리 해제
	}
	free(h); //헤드노드 포인터h 메모리 해제
	return 0;
}


void printList(headNode* h) { //연결리스트의 값들을 출력하는 함수
	int i = 0;
	listNode* p; //listNode 포인터 변수 p 선언 

	printf("\n---PRINT\n"); 

	if(h == NULL) {   //헤드노드의 값이 존재하지 않으면 연결리스트의 값이 존재하지않는다는 메세지 출력
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; //리스트 노드 포인터 변수 p가 헤드노드를 가리키게 선언

	while(p != NULL) { //포인터 변수 p가 Null이 될 때까지 반복
		printf("[ [%d]=%d ] ", i, p->key); //연결리스트의 값들을 출력
		p = p->rlink; //p가 다음 노드를 가리키게 변경
		i++; //노드의 값 출력시 인덱스 번호를 알리기 위해 사용
	}

	printf("  items = %d\n", i); //연결리스트의 존재하는 노드 갯수 출력
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) { //연결리스트 마지막 노드에 추가하는 함수 

	listNode* node = (listNode*)malloc(sizeof(listNode));//node 동적할당
	node->key = key; //노드의 key값을 입력받은 key으로 지정
	node->rlink = NULL; //노드의 우측 link에 연결되는 링크가 없도록 선언
	node->llink = NULL;//노드의 좌측 link에 연결되는 링크가 없도록 선언

	if (h->first == NULL)//노드의 값이 존재하지 않는경우 입력받은 key값이 헤드노드에 들어가도록 선언
	{
		h->first = node; //입력받은 노드가 헤드노드가 되게한다
		return 0;
	}

	listNode* n = h->first; //구조체 포인터 변수 n선언후 헤드노드를 가리키게한다
	while(n->rlink != NULL) { //연결리스트에서 맨 우측 노드로 이동하는 반복문
		n = n->rlink; // 노드의 우측 노드가 Null값일 때까지 반복해서 맨 우측 노드로 이동한다
	}
	n->rlink = node; //맨 끝에 새로운 노드를 생성해서 이전 노드랑 연결
	node->llink = n; //맨 끝에 있는 노드를 좌측 노드와 연결
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) { //list의 마지막 노드를 삭제하는 함수

	if (h->first == NULL) //헤드노드가 존재하지않는 경우 삭제할 것이 없다는 메세지 출력
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first; //n노드가 헤드노드를 가리키게 한다
	listNode* trail = NULL;//trail 공백 노드 생성

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->rlink == NULL) {  //노드가 하나만 있는 경우
		h->first = NULL; //헤드노드를 Null로 초기화해준다
		free(n);//노드를 메모리 해제
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->rlink != NULL) { //가장 우측 노드로 이동한다
		trail = n; //trail은 n노드의 이전노드를 가리킴
		n = n->rlink;//n노드에 우측 노드를 가리키게 한다
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->rlink = NULL; //trail의 우측 노드가 가리키는 노드를 없앤다
	free(n); // 가장 우측에 있는 노드를 삭제

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) { //list에 첫번째 노드에 값을 대입하는 함수

	listNode* node = (listNode*)malloc(sizeof(listNode)); // node 동적할당
	node->key = key; //입력받은 key값에 대한 노드를 생성
	node->rlink = node->llink = NULL; //노드의 좌우측 링크를 Null로 초기화 

	if(h->first == NULL) //헤드노드가 존재하지않는경우
	{
		h->first = node; //node를 헤드노드로 지정
		return 1;
	}

	node->rlink = h->first; //원래의 헤드노드를 새로운 노드의 우측 링크와 연결
	node->llink = NULL; //노드의 좌측 링크는 Null로 초기화
	
    listNode *p = h->first; //p노드가 h->first를 가리키게 한다
	p->llink = node; //p의 좌측 link를 헤드노드와 연결
	h->first = node; //입력받은 노드가 헤드노드가 되게한다

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) { //첫번 째 노드를 삭제하는 함수

	if (h->first == NULL) //노드가 존재하지 않는 경우 메세지 출력
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first; // n 노드가 헤드노드로 선언 
	h->first = n->rlink; // 2번째 노드를 헤드노드로 선언

	free(n);//첫번 째 노드를 삭제시킨다

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) { //리스트의 노드를 역순으로 바꾸는 함수


	if(h->first == NULL) { //노드가 존재하지 않는 경우 메세지 출력
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first; //n을 헤드노드로 지정
	listNode *trail = NULL;// 공백 노드 생성
	listNode *middle = NULL;//공백 노드 생성

	while(n != NULL){ //n이 Null값일 때까지 반복
		trail = middle; 
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	} //새로운 노드를 2개 만들어서 trail -> middle -> n 이런식으로 이동하면서 노드의 값들을 한개씩 바꿔준다

	h->first = middle;

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //node 동적할당
	node->key = key; //노드의 key값을 입력받은 key값으로 생성
	node->llink = node->rlink = NULL; //생성한 노드의 좌우측 링크를 초기화

	if (h->first == NULL) //노드가 존재하지 않을 경우
	{
		h->first = node; //입력받은 노드를 헤드노드로 지정
		return 0;
	}

	listNode* n = h->first; // 새로운 노드를 만든 후 연결리스트 첫번째 주소를 대입

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {//n이 Null값일 때까지 반복
		if(n->key >= key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) { // n이 헤드 노드일 경우 -> 첫번째 노드인 경우
				insertFirst(h, key); //첫번째 노드로 삽입
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n;//노드의 우측 링크를 n과 연결
				node->llink = n->llink;//node의 좌측 링크를 n의 좌측 링크와 연결 
				n->llink->rlink = node; //node를 중간에 삽입해서 양쪽 노드와 연결
			}
			return 0;
		}

		n = n->rlink; //한칸씩 이동
	} 

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);//리스트 마지막에 노드 삽입
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) { //노드를 삭제하는 함수

	if (h->first == NULL) //노드안에 key값이 존재하지 않는 경우 메세지 출력
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first; // 새로운 노드를 만든 후 연결리스트 첫번째 주소를 대입

	while(n != NULL) {
		if(n->key == key) {
			if(n == h->first) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h); //노드를 삭제
			} else if (n->rlink == NULL){ /* 마지막 노드인 경우 */
				deleteLast(h);//마지막 노드 삭제
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n); //노드 n의 좌우측 노드들을 연결한 후 노드 n을 삭제시킨다
			}
			return 1;
		}

		n = n->rlink;//노드를 한칸씩 이동
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);//입력한 키값을 가진 노드가 없다는 메세지 출력 
	return 1;
}


