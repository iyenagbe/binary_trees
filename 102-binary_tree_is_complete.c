#include "binary_trees.h"

int binary_tree_is_complete(const binary_tree_t *tree);
tree_levelorder_queue_ft *create_node(binary_tree_t *node);
void free_queue(tree_levelorder_queue_ft *head);
void push(binary_tree_t *node, tree_levelorder_queue_ft *head,
		tree_levelorder_queue_ft **tail);
void pop(tree_levelorder_queue_ft **head);

/**
 * binary_tree_is_complete - Checks if a binary tree is complete.
 *
 * @tree: A pointer to the root node of the tree to check.
 *
 * Return: 0 if tree is NULL.
 */
int binary_tree_is_complete(const binary_tree_t *tree)
{

	tree_levelorder_queue_ft *head, *tail;
	unsigned char flag = 0;

	if (tree == NULL)
		return (0);

	head = tail = create_node((binary_tree_t *)tree);
	if (head == NULL)
		exit(1);

	while (head != NULL)
	{
		if (head->node->left != NULL)
		{
			if (flag == 1)
			{
				free_queue(head);
				return (0);
			}
			push(head->node->left, head, &tail);
		}
		else
			flag = 1;
		if (head->node->right != NULL)
		{
			if (flag == 1)
			{
				free_queue(head);
				return (0);
			}
			push(head->node->right, head, &tail);
		}
		else
			flag = 1;
		pop(&head);
	}
	return (1);
}

/**
 * create_node - Creates a new tree_levelorder_queue_ft node.
 *
 * @node: The binary tree node for the new node to contain.
 *
 * Return: If an error occurs, NULL.
 *         Otherwise, a pointer to the new node.
 */
tree_levelorder_queue_ft *create_node(binary_tree_t *node)
{
	tree_levelorder_queue_ft *new;

	new = malloc(sizeof(tree_levelorder_queue_ft));
	if (new == NULL)
		return (NULL);

	new->node = node;
	new->next = NULL;

	return (new);
}

/**
 * free_queue - Frees a tree_levelorder_queue_ft queue.
 *
 * @head: A pointer to the head of the queue.
 */
void free_queue(tree_levelorder_queue_ft *head)
{
	tree_levelorder_queue_ft *tmp;

	while (head != NULL)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
}

/**
 * push - Pushes a node to the back of a tree_levelorder_queue_ft queue.
 *
 * @node: The binary tree node to print and push.
 * @head: A double pointer to the head of the queue.
 * @tail: A double pointer to the tail of the queue.
 *
 * Description: Upon malloc failure, exits with a status code of 1.
 */
void push(binary_tree_t *node, tree_levelorder_queue_ft *head,
		tree_levelorder_queue_ft **tail)
{
	tree_levelorder_queue_ft *new;

	new = create_node(node);
	if (new == NULL)
	{
		free_queue(head);
		exit(1);
	}
	(*tail)->next = new;
	*tail = new;
}

/**
 * pop - Pops the head of a tree_levelorder_queue_ft queue.
 *
 * @head: A double pointer to the head of the queue.
 */
void pop(tree_levelorder_queue_ft **head)
{
	tree_levelorder_queue_ft *tmp;

	tmp = (*head)->next;
	free(*head);
	*head = tmp;
}
