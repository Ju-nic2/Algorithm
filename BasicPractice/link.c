#include <stdio.h>
#include <stdlib.h>
typedef struct node 
{
    int data;
    struct node *next;
}node;

//head 노드
node *head = NULL;

void insertF(int n)
{
    // 새로운 노드 생성. 
    node *tmp = (node*)malloc(sizeof(node)*1);
    tmp -> data = n;

    node* cur = head;
    // data가 하나도 없을때 
    if(cur == NULL)
    {
        head = tmp;
        tmp -> next = NULL;
        return;
    }
    //data가 하나 이상일때, 제일 마지막 까지이동.
    while(cur->next != NULL)
    {
        cur = cur -> next;
    }
    //새로운 data 넣고 
    cur -> next = tmp;

    //항상 끝은 NULL 넣어두기, 
    tmp -> next = NULL;
}
//N 오른쪽에 삽입
void insertN(int n,int target)
{
    //새로운 노드 생성.
    node *tmp = (node*)malloc(sizeof(node)*1);
    tmp -> data = n;
    node *cur = head;
    //마지막 까지 이동
    while(cur != NULL)
    {
        //target 찾았다면
        if(cur -> data == target)
        {
            // 새로운 노드 삽입
            tmp -> next = cur -> next;
            cur -> next = tmp;
            return;
        }
        cur = cur -> next;
    }
    printf("No data %d \n",target);
    

}
void deleteF()
{
   node* cur = head;

   node *tmp = NULL;
    if(cur == NULL)
    {
        printf("no data\n");
        return;
    }
    //끝까지 이동. 
    //cur == 현재 노드, tmp == 이전노드
    while(cur->next != NULL)
    {
        tmp = cur;
        cur = cur -> next;
    }
    //data가 2개 이상일때 tmp -> cur -> NULL 
    // tmp -> NULL, free(cur) 로 진행
    if(tmp != NULL) tmp -> next = NULL;
    //data가 1개일때 tmp(head) -> NULL 
    else head = NULL;
    free(cur);
}
void deleteN(int n)
{
    node *tmp = head;
    node *cur = tmp;
    //삭제하려는 data가 제일 앞에 있고, data가 2개 이상일때
    if(cur -> data == n && cur -> next != NULL)
    {
        //cur(head) -> data1 -> ... / (head) -> data1
        head = cur -> next;
        //cur 삭제
        free(cur);
        return;
    }
    //삭제 하려는 data가 젤 앞에있고 data가 1개 일때
    else if(cur -> data == n && cur -> next == NULL)
    {
        //cur 삭제
        free(cur);
        //(head) - > NULL
        head = NULL;
        return;
    }
    //그외
    tmp = tmp -> next;
    // 끝까지 찾아가면서
    while(tmp != NULL)
    {
        //삭제할 data 찾음 
        if(tmp -> data == n)
        {
            //cur -> tmp -> data // cur -> data
            cur->next = tmp->next;
            free(tmp);
            return;
        }
        else 
        {
            //cur -> tmp -> data1 // data-> cur-> tmp -> .. 
            cur = cur -> next;
            tmp = tmp -> next;
        }
    }
  
    printf("no data\n");
}

void printAll()
{
    node *tmp = head;
    while(tmp != NULL)
    {
        printf("%d -> ",tmp->data);
        tmp = tmp->next;
    }

    printf("NULL \n");
}

int main()
{
    int n;
    int k;
    int t;
    while(1)
    {
        scanf("%d",&n);
        switch(n)
        {
            case 1:
                 scanf("%d",&k); insertF(k);break;
            case 4:
                deleteF();break;
            case 3:
                printAll();break;
            case 5:
                scanf("%d",&k); deleteN(k);break;
            case 2:
                scanf("%d %d",&k,&t); insertN(k,t);break;

            case 0:
                return 1;
        }        
    }
}