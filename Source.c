#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

typedef struct __node {
	int value;
	struct __node *next;
} node_t;

void add_entry(node_t **head, int new_value)
{
	node_t **indirect = head;
	node_t *new_node = malloc(sizeof(node_t));

	new_node->value = new_value;
	new_node->next = NULL;

	assert(new_node);
	while (*indirect)
		indirect = &(*indirect)->next;
	*indirect = new_node;
}

node_t *find_entry(node_t *head, int value)
{
	node_t *current = head;
	for (; current && current->value != value; current = current->next)
		/* interate */;
	return current;
}

void remove_entry(node_t **head, node_t *entry)
{
	node_t **indirect = head;

	while ((*indirect) != entry)
		indirect = &(*indirect)->next;

	*indirect = entry->next;
	free(entry);
}

void print_list(node_t *head)
{
	for (node_t *current = head; current; current = current->next)
		printf("%d ", current->value);
	printf("\n");
}

void swap_pair(node_t **head)
{
	for (; *head && (*head)->next; head = &(*head)->next->next) {
		node_t *tmp = *head;
		*head = (*head)->next;
		tmp->next = (*head)->next;
		(*head)->next = tmp;
	}
}

node_t *reverse(node_t *head)
{
	node_t *cursor = NULL;
	while (head) {
		node_t *next = head->next;
		head->next = cursor; 
		cursor = head;
		head = next;
	}
	return cursor;
}

void reverse_v2(node_t **head)
{
	node_t *cursor = NULL;
	while (*head) {
		node_t *next = (*head)->next;
		(*head)->next = cursor;
		cursor = *head;
		*head = next;
	}
	*head = cursor;
}

void rev_recursive(node_t *cursor, node_t *now, node_t **head){
	if (!now) {
		*head = cursor;
		return;
	}
	node_t *next = now->next;
	now->next = cursor;
	rev_recursive(now, next, head);
}

void reverse_v3(node_t **head)
{
	rev_recursive(NULL, *head, head);
}

void FYshuffle(node_t **head) {
	srand((unsigned)time(NULL));
	int randnum;
	int lens = 0; // number of items
	node_t *p = *head;
	node_t *nhead = NULL;
	node_t *prev;

	// count number of items 
	while (p) {
		lens++;
		p = p->next;
	}

	// do shuffle
	while (lens - 1) {
		randnum = rand() % lens; // select number from 0 to (lens - 1)
		p = *head;
		prev = NULL;
		while (randnum) {
			prev = p;
			p = p->next;
			randnum--;
		}
		if (prev)
			prev->next = p->next;
		else
			*head = (*head)->next;
		p->next = nhead;
		nhead = p;
		lens--;
	}
	(*head)->next = nhead;
}

int main(int argc, char const *argv[])
{
	node_t *head = NULL;

	print_list(head);
	add_entry(&head, 72);
	add_entry(&head, 101);
	add_entry(&head, 108);
	add_entry(&head, 109);
	add_entry(&head, 110);
	add_entry(&head, 111);

	print_list(head);
	FYshuffle(&head);
	print_list(head);
	node_t *entry = find_entry(head, 101);
	remove_entry(&head, entry);

	entry = find_entry(head, 111);
	remove_entry(&head, entry);

	print_list(head);

	/* swap pair.
	 * See https://leetcode.com/problems/swap-nodes-in-pairs/
	 */
	swap_pair(&head);
	print_list(head);

	reverse_v3(&head);
	print_list(head);

	return 0;
}