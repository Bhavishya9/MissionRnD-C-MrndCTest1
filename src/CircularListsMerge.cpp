/*
Given two SORTED Circular Linked Lists ,
Write a function to merge those two linked lists .
The First Linked List head should point to the final merged linked list .
The Final merged linked list should also be in SORTED order and a Circular Linked List.
You need to return the Length of Final SLL.

*********
The First linked list head should now point to the Final sorted(Ascending) Linked list First Node
*********
Ex : A: 0->3->5->10->20 (and 20 now pointing back to 0,instead of Null )
B: 1->2->6->11->21->50->70 (70 Pointing back to 1).

The Final Linked List is A:0->1->2->3->5->6->10->11->20->21->50->70 .

Note : Dont use Malloc or create any new nodes ,Only pointers need to be interchanged,
You can use temp pointers although.
Note : The Final Linked List should be  also be a circular Linked List where Last node is
pointing towards the first node.
Note : Return -1 for Invalid Inputs like NULL;

Input : head1 and head2 are Addresses of Two Circular Linked Lists heads .
Output :Return Length of New SLL .Modify the head1 value, such that it now points to 
Merged Sorted Circular SLL .

Difficulty : Medium
*/
#include <stdlib.h>
#include <stdio.h>

struct node{
	int data;
	struct node *next;
};

int count(struct node *head)
{
	struct node *current;
	current = head;
	int n = 0;
	while (current->next != NULL)
	{
		current = current->next;
		n++;
	}
	n++;
	return n;
}

struct node * mergeSort(struct node *list1, struct node *list2){
	struct node *list = NULL;
	if (list1 == NULL)
		return list2;
	else if (list2 == NULL)
		return list1;
	if (list1->data < list2->data)
	{
		list = list1;
		list->next = mergeSort(list1->next, list2);
	}
	else if (list1->data == list2->data)
	{
		list = list1;
		list->next = mergeSort(list1->next, list2->next);
	}
	else 
	{
		list = list2;
		list->next = mergeSort(list1, list2->next);
	}
	return list;
}

int merge_circularlists(struct node **head1, struct node **head2){
	//Returns Length of merged Sorted circular SLL and also points *head1 to final SLL .
	if (*head1 == NULL || *head2 == NULL)
		return -1;
	struct node* current1 = (*head1)->next;
	while (current1->next->data != (*head1)->data)
	{
		current1 = current1->next;
	}
	current1->next = NULL;
	struct node* current2 = (*head2)->next;
	while (current2->next->data != (*head2)->data)
	{
		current2 = current2->next;
	}
	current2->next = NULL;
	struct node *head = mergeSort(*head1, *head2);
	int n = count(head);
	struct node *current;
	current = head;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = head;
	head1 = &head;
	return n;
}