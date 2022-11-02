#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node_tag {
	struct node_tag * prev;		// A pointer to this type of struct
	int    v;			// data
	struct node_tag * next;		// A pointer to this type of struct
} node;

node * create_node(int v) 
{
    node * p = malloc(sizeof(node)); // Allocate memory
    assert(p != NULL);          // you can be nicer
    
    // Set the value in the node.
    p->prev = NULL;
    p->v = v;           
    p->next = NULL;  
    return p;                   // return
}

void add_last(node **head, node **tail, node *newnode)
{
        if((*head) == NULL)
                (*head) = (*tail) = newnode;
        else
        {
                (*tail)->next = newnode;
		newnode->prev = (*tail);
                (*tail) = newnode;
        }
}

node * remove_first(node **head, node **tail) 
{
        node *p = (*head);
        if((*head)!=NULL)
	{
		if((*head)->next!=NULL)
			(*head)->next->prev = NULL;
		else (*tail) = NULL;
		(*head) = (*head)->next;
	}
        return p;
}

void print_list(node *head)
{
        node *p = head;

        while(p!=NULL)
        {
                printf("%d ", p->v);
                p = p->next;
        }
        printf("\n");
}

int get_count(node *head){
  int len = 1;
  while(head->next!=NULL){
    len++;
    head = head->next;
  }
  return len;
}

void *build_list(node *head, node *arr[], int len) {
  for(int i=len-1;i>=0;i--){
      arr[i] = head;
      head = head->next;
      //printf("arr[%i]: %p\n",i,arr[i]);
    }
  return arr;
}

//TODO
void reverse_list(node **head, node **tail)
{
	node *temp_head = *head;
    node *temp_tail = *tail;
    int len = get_count(temp_head);
    if(len>1){
      node *arr[len];
      node *curr_node;
      build_list(temp_head, arr, len);
      for(int i=0;i<len-1;i++){
            curr_node = arr[i];
            curr_node->next = arr[i+1];
            if(i!=0){
                curr_node->prev = arr[i-1];
            }
      }
      arr[len-1]->next = NULL;
      arr[len-1]->prev = arr[len-2];
      arr[0]->prev = NULL;
      temp_head = arr[0];
      temp_tail = arr[len-1];
    }
    head = &temp_head;
    tail = &temp_tail;
    
    //exit(1);
}
//TODO
void free_all(node **head, node **tail)
{
	node *current_head = *head;
    while(current_head!=NULL){
        node *previous_head = current_head;
        free(previous_head); 
        current_head = current_head->next;
    }
}

//Do not change the main function
int main(int argc, char * argv[])
{
	assert(argc == 2);
	int n = atoi(argv[1]);
	
	node *p, *head=NULL, *tail=NULL;

	for(int i=0; i<n; i++)
	{
		p = create_node(i);
		add_last(&head, &tail, p);	
	}		
	print_list(head);
	reverse_list(&head, &tail);
    printf("Head: %p, head->next: %p", head, head->next);
        print_list(head);
	free_all(&head, &tail);
	return 0;	
}