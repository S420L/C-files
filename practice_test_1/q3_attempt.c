#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define MAX 10000

typedef struct node_tag
{
   int    v;                    // data
   struct node_tag * next;  // A pointer to this type of struct
} node;                        // Define a type. Easier to use.


node * create_node(int v)
{
    node    * p = malloc(sizeof(node)); // Allocate memory
    assert(p != NULL);      // you can be nicer

    // Set the value in the node.
    p->v = v;
    p->next = NULL;
    return p;           // return
}

//Print the list
void print_list(node *head)
{   
    while(head!=NULL)
    {   
        printf("%d ", head->v);
        head = head->next;
    }
    printf("\n");
}

//Add newnode at the head of the list
void add_first(node **head, node *newnode)
{
    if(*head == NULL)
    {
        *head = newnode;
        newnode->next = NULL;
    }
    else
    {
        newnode->next = *head;
        *head = newnode;
    }
}

//Remove the first node from the list
node * remove_first(node **head) 
{
	node *p;

	p = (*head);
	if((*head)!=NULL) (*head) = (*head)->next;
	return p;
}

node *find_previous(node *head, node *p) {
  while (head != NULL) {
    if (head->next == p)
      return head;
    head = head->next;
  }
  return head;
}

node *find_node(node *head, int v) {
  while (head != NULL) {
    if (head->v == v)
      return head;
    head = head->next;
  }
  return head;
}

node *delete_list(node *head) {
  while (head != NULL) {
    node *p = head->next;
    free(head);
    head = p;
  }
  return head;
}

node *delete_node(node *head, int v) {
  node *p;
  p = find_node(head,v);
  if(!p){
    printf("Not goooood ;(");
    return head;
    }
  node *plast;
  node *pnext;
  plast = find_previous(head,p);
  pnext = p->next;
  if((plast!=NULL) & (p!=NULL) & (pnext!=NULL)){
    plast->next = p->next;
    free(p);
  }
  else if((pnext==NULL) & (plast==NULL)){
    delete_list(head);
    return NULL;
  }
  else if(pnext==NULL){
    plast->next = NULL;
    free(p);
  }
  else if(p==head){
    head = pnext;
    free(p);
  }
  else{printf("should not be here ;(");}
  return head;
}

//Remove all the nodes whose value is a multiple of k but not k itself from the list, and free
//their allocated memory
void remove_multiple(node **head, int k)
{
    node *temp_head = *head;
    while(temp_head!=NULL)
    {   
        //printf("head=%p  K=%i  *head=%p  *head->next: %p, *head-v: %i\n", head, k, temp_head, temp_head->next, temp_head->v);
        node *current = temp_head;
        print_list(*head);
        printf("CURRENT:   %i\n", current->v);
        if(current->v%k==0 && current->v!=k){
            delete_node(*head, current->v);
            printf("Here deleting node: %i\n", current->v);
        }
        temp_head = temp_head->next;        
    }
    //exit(1);
}

//Remove all the nodes from the list and free the corresponding memory
void free_all(node **head)
{
    node *current_head = *head;
    while(current_head!=NULL){
        printf("before");
        node *previous_head = current_head;
        printf("\nPrevious head:    %p\n\n Current headL       %p",previous_head,current_head);
        free(previous_head); 
        current_head = current_head->next;
    }
}

//Return the number of items in the list
int list_length(node *head)
{
  int len = 1;
  while(head->next!=NULL){
    len++;
    head = head->next; 
  }
  return len;
}
//Do not change the main function
int main(int argc, char *argv[])
{
    if(argc!=2)
    {
        printf("Usage: %s n\n", argv[0]);
        return -1;
    }
    int n = atoi(argv[1]);
    assert(n >= 1 && n <= MAX);
    node *head, *p;
    head = NULL;

    int i;

    for(i=n; i>=2; i--)
    {
        p = create_node(i);
        add_first(&head, p);
    }

    for(i = 2; i<n; i++)
    {
        printf("i equals: ___   %i    _____   \n", i);
        remove_multiple(&head, i);
    }

    printf("%d primes between 1 and %d:\n", list_length(head), n);
    print_list(head);
    free_all(&head);
    printf("%d items left in the list after free_all().\n", list_length(head));
    printf("\nAFTER SWIGGA 420\n");
    return 0;
}
