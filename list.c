//Steven Wojcio
//A3
//Brandon Whitehead

/**
 * CS 2110 - Fall 2011 - Homework #11
 * Edited by: Brandon Whitehead
 *
 * list.c: Complete the functions!
 **/

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

/* The node struct.  Has a prev pointer, next pointer, and data. */
/* DO NOT DEFINE ANYTHING OTHER THAN WHAT'S GIVEN OR YOU WILL GET A ZERO*/
/* Design consideration only this file should know about nodes */
/* Only this file should be manipulating nodes */
typedef struct lnode
{
  struct lnode* prev; /* Pointer to previous node */
  struct lnode* next; /* Pointer to next node */
  void* data; /* User data */
} node;


/* Do not create any global variables here. Your linked list library should obviously work for multiple linked lists */
// This function is declared as static since you should only be calling this inside this file.
static node* create_node(void* data);

/** create_list
  *
  * Creates a list by allocating memory for it on the heap.
  * Be sure to initialize size to zero and head to NULL.
  *
  * @return an empty linked list
  */
list* create_list(void)
{
    	list* newLinkedList=(list*)malloc(sizeof(list));
	newLinkedList->head=NULL;
	newLinkedList->size=0;
    	return newLinkedList;
}

/** create_node
  *
  * Helper function that creates a node by allocating memory for it on the heap.
  * Be sure to set its pointers to NULL.
  *
  * @param data a void pointer to data the user wants to store in the list
  * @return a node
  */
static node* create_node(void* data)
{
	node* newNode=(node*)malloc(sizeof(node));
  	newNode->prev=NULL;
	newNode->next=NULL;
	newNode->data=data;

    	return newNode;
}

/** push_front
  *
  * Adds the data to the front of the linked list
  *
  * @param llist a pointer to the list.
  * @param data pointer to data the user wants to store in the list.
  */
void push_front(list* llist, void* data)
{	
	node* temp=create_node(data);
	if(llist->size==0){
		temp->next=temp;
		temp->prev=temp;	
		llist->head=temp;
	}
	else {
		temp->next=llist->head;
		temp->prev=llist->head->prev;
		llist->head->prev->next=temp;
		llist->head->prev=temp;
		llist->head=temp;
	}
	llist->size++;
}

/** push_back
  *
  * Adds the data to the back/end of the linked list
  *
  * @param llist a pointer to the list.
  * @param data pointer to data the user wants to store in the list.
  */
void push_back(list* llist, void* data)
{
   	node* temp=create_node(data);
	if(llist->size==0){
		temp->next=temp;
		temp->prev=temp;	
		llist->head=temp;
	}
	else{
		temp->next=llist->head;
		temp->prev=llist->head->prev;
		llist->head->prev->next=temp;
		llist->head->prev=temp;
	}
	llist->size++;
}

/** remove_front
  *
  * Removes the node at the front of the linked list
  *
  * @warning Note the data the node is pointing to is also freed. If you have any pointers to this node's data it will be freed!
  *
  * @param llist a pointer to the list.
  * @param free_func pointer to a function that is responsible for freeing the node's data.
  * @return -1 if the remove failed (which is only there are no elements) 0 if the remove succeeded.
  */
int remove_front(list* llist, list_op free_func)
{
    /// @todo Implement
    /// @note remember to also free the node itself
    /// @note free_func is a function that is responsible for freeing the node's data only.	
	if(llist->size==0){	
		return -1;
	}
	else if(llist->size==1){

		free_func(llist->head->data);
		free(llist->head);
		llist->head=NULL;
		
		llist->size--;
		return 0;
	}
	else{	//2 or more
		free_func(llist->head->data);
		node* newHead=llist->head->next;
		node* lastItem=llist->head->prev;
		free(llist->head);
		llist->head=newHead;
		llist->head->prev=lastItem;
		llist->head->prev->next=newHead;
	
		llist->size--;
		return 0;
	}
    	
}

/** remove_index
  *
  * Removes the indexth node of the linked list
  *
  * @warning Note the data the node is pointing to is also freed. If you have any pointers to this node's data it will be freed!
  *
  * @param llist a pointer to the list.
  * @param index index of the node to remove.
  * @param free_func pointer to a function that is responsible for freeing the node's data.
  * @return -1 if the remove failed 0 if the remove succeeded.
  */
int remove_index(list* llist, int index, list_op free_func)
{
	int i;
	if(llist->size<index){	
		return -1;
	}
	else if(index==0){
		return remove_front(llist,free_func);
	}
	else{
		if(index==llist->size)remove_back(llist,free_func);
		else{
			node* remNode=llist->head;
			for(i=0;i<index;i++){
				remNode=remNode->next;
			}
			free_func(remNode->data);
			remNode->prev->next=remNode->next;
			remNode->next->prev=remNode->prev;
			free(remNode);
			llist->size--;
		}
	}
	return 0;
    /// @todo Implement
    /// @note Remember to also free the node itself
    /// @note free_func is a function that is responsible for freeing the node's data only.
}

/** remove_back
  *
  * Removes the node at the back of the linked list
  *
  * @warning Note the data the node is pointing to is also freed. If you have any pointers to this node's data it will be freed!
  *
  * @param llist a pointer to the list.
  * @param free_func pointer to a function that is responsible for freeing the node's data.
  * @return -1 if the remove failed 0 if the remove succeeded.
  */
int remove_back(list* llist, list_op free_func)
{
    /// @todo Implement
    /// @note Remember to also free the node itself
    /// @note free_func is a function that is responsible for freeing the node's data only.
	if(llist->size==0){
		return -1;
	}
	else if(llist->size==1){
		return remove_front(llist,free_func);
	}
	else{
		node* indexNode=llist->head->prev;
		free_func(indexNode->data);
		indexNode->prev->next=llist->head;
		llist->head->prev=indexNode->prev;
		free(indexNode);
		llist->size--;
		return 0;
	}
	
}

/** remove_data
  *
  * Removes ALL nodes whose data is EQUAL to the data you passed in or rather when the comparison function returns true (!0)
  * @warning Note the data the node is pointing to is also freed. If you have any pointers to this node's data it will be freed!
  *
  * @param llist a pointer to the list
  * @param data data to compare to.
  * @param compare_func a pointer to a function that when it returns true it will remove the element from the list and do nothing otherwise @see equal_op.
  * @param free_func a pointer to a function that is responsible for freeing the node's data
  * @return the number of nodes that were removed.
  */
int remove_data(list* llist, const void* data, equal_op compare_func, list_op free_func)
{
    /// @todo Implement changing the return value!
    /// @note remember to also free all nodes you remove.
    /// @note free_func is a function that is responsible for freeing the node's data only.
	int count=0;
	int i;
	node* currentNode;
	node* temp;
	currentNode=llist->head;
	for(i=0;i<llist->size;i++){
		temp=currentNode->next;
		if(compare_func(data,currentNode->data)){
			count++;
			remove_index(llist,i,free_func);
		}	
		currentNode=temp;
	}
    return count;
}

/** remove_if
  *
  * Removes all nodes whose data when passed into the predicate function returns true
  *
  * @param llist a pointer to the list
  * @param pred_func a pointer to a function that when it returns true it will remove the element from the list and do nothing otherwise @see list_pred.
  * @param free_func a pointer to a function that is responsible for freeing the node's data
  * @return the number of nodes that were removed.
  */
int remove_if(list* llist, list_pred pred_func, list_op free_func)
{
    /// @todo Implement changing the return value!
    /// @note remember to also free all nodes you remove.
    /// @note be sure to call pred_func on the NODES DATA to check if the node needs to be removed.
    /// @note free_func is a function that is responsible for freeing the node's data only.
	int count=0;
	int i;
	node* temp;
	node* currentNode;
	currentNode=llist->head;
	for(i=0;i<llist->size;i++){
		temp=currentNode->next;
		if(pred_func(currentNode->data)){
			count++;
			remove_index(llist,i,free_func);
		}	
		currentNode=temp;
	}
	
    return count;
}

/** front
  *
  * Gets the data at the front of the linked list
  * If the list is empty return NULL.
  *
  * @param llist a pointer to the list
  * @return The data at the first node in the linked list or NULL.
  */
void* front(list* llist)
{
    /// @todo Implement changing the return value!
    /// @note you are returning the HEAD's DATA not the head node. Remember the user should never deal with the linked list nodes.
	
	return llist->head->data;
	
}

/** get_index
  *
  * Gets the data at the indexth node of the linked list
  * If the list is empty or if the index is invalid return NULL.
  *
  * @param llist a pointer to the list
  * @return The data at the indexth node in the linked list or NULL.
  */
void* get_index(list* llist, int index)
{
    /// @todo Implement changing the return value!
    	if(llist->size==0){
   		return NULL;
	}
	else{
		node* getNode;
		getNode=llist->head;
		int i;
		for(i=0;i<index;i++){
			getNode=getNode->next;
		}
		return getNode->data;
	}
}

/** back
  *
  * Gets the data at the "end" of the linked list
  * If the list is empty return NULL.
  *
  * @param llist a pointer to the list
  * @return The data at the last node in the linked list or NULL.
  */
void* back(list* llist)
{
    /// @todo Implement changing the return value!
    return get_index(llist,(llist->size-1));
}

/** is_empty
  *
  * Checks to see if the list is empty.
  *
  * @param llist a pointer to the list
  * @return 1 if the list is indeed empty 0 otherwise.
  */
int is_empty(list* llist)
{
    ///@note an empty list by the way we want you to implement it has a size of zero and head points to NULL.
	if(llist->head==NULL && llist->size==0){
    		return 1;
	}
	else return 0;
}

/** size
  *
  * Gets the size of the linked list
  *
  * @param llist a pointer to the list
  * @return The size of the linked list
  */
int size(list* llist)
{
    ///@note simply return the size of the linked list.  Its that easy!
    return llist->size;
}

/** find_occurence
  *
  * Tests if the search data passed in is in the linked list.
  *
  * @param llist a pointer to a linked list.
  * @param search data to search for the occurence.
  * @param compare_func a pointer to a function that returns true if two data items are equal @see equal_op.
  * @return 1 if the data is indeed in the linked list 0 otherwise.
  */
int find_occurrence(list* llist, const void* search, equal_op compare_func)
{
    /// @todo Implement changing the return value!
	node* searchNode;
	for(searchNode=llist->head;searchNode!=llist->head->prev;searchNode=searchNode->next){
		if(compare_func(search,searchNode->data))return 1;
	}
    return 0;
}

/** empty_list
  *
  * Empties the list after this is called the list should be empty.
  *
  * @param llist a pointer to a linked list.
  * @param free_func function used to free the node's data.
  *
  */
void empty_list(list* llist, list_op free_func)
{
    /// @todo Implement
    /// @note Free all of the nodes not the linked list itself.
    /// @note do not free llist.
	//traverse(llist,free_func);
	if(llist->size==0&&llist->head==NULL){
		return;
	}
	node* tNode= llist->head->next;
	node* temp;

	while(tNode!=llist->head){
		temp=tNode->next;
		free_func(tNode->data);
		free(tNode);
		tNode=temp;
	}
	if(llist->head!=NULL){
		free_func(llist->head->data);
		free(llist->head);
	}
	llist->head=NULL;
	llist->size=0;
}

/** traverse
  *
  * Traverses the linked list calling a function on each node's data.
  *
  * @param llist a pointer to a linked list.
  * @param do_func a function that does something to each node's data.
  */
void traverse(list* llist, list_op do_func)
{
    /// @todo Implement
	node* tNode= llist->head;
	if(tNode!=NULL){
		do_func(tNode->data);
		tNode=tNode->next;
	}
	while(tNode!=llist->head){
		do_func(tNode->data);
		tNode=tNode->next;
	}
}
