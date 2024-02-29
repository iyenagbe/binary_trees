#include "binary_trees.h"

void binary_tree_levelorder(const binary_tree_t *tree, void (*func)(int));
tree_levelorder_queue_ft *create_node(binary_tree_t *node);
void pint_push(binary_tree_t *node, tree_levelorder_queue_ft *head,
		tree_levelorder_queue_ft **tail, void (*func)(int));
void free_queue(tree_levelorder_queue_ft *head);
void pop(tree_levelorder_queue_ft **head);

/**
 * binary_tree_levelorder - Goes through a bin-tree by level-order traversal.
 *
 * @tree: A pointer to the root node of the tree to traverse.
 * @func: A pointer to a function to call for each node.
 */
void binary_tree_levelorder(const binary_tree_t *tree, void (*func)(int))
{
	tree_levelorder_queue_ft *head, *tail;

	if (tree == NULL || func == NULL)
		return;

	head = tail = create_node((binary_tree_t *)tree);
	if (head == NULL)
		return;

	while (head != NULL)
	{
		pint_push(head->node, head, &tail, func);
		pop(&head);
	}
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
 * pint_push - Runs a function on a given binary tree node and
 *             pushes its children into a tree_levelorder_queue_ft queue.
 *
 * @node: The binary tree node to print and push.
 * @head: A double pointer to the head of the queue.
 * @tail: A double pointer to the tail of the queue.
 * @func: A pointer to the function to call on @node.
 *
 * Description: Upon malloc failure, exits with a status code of 1.
 */
void pint_push(binary_tree_t *node, tree_levelorder_queue_ft *head,
		tree_levelorder_queue_ft **tail, void (*func)(int))
{
	tree_levelorder_queue_ft *new;

	func(node->n);
	if (node->left != NULL)
	{
		new = create_node(node->left);
		if (new == NULL)
		{
			free_queue(head);
			exit(1);
		}
		(*tail)->next = new;
		*tail = new;
	}
	if (node->right != NULL)
	{
		new = create_node(node->right);
		if (new == NULL)
		{
			free_queue(head);
			exit(1);
		}
		(*tail)->next = new;
		*tail = new;
	}
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
