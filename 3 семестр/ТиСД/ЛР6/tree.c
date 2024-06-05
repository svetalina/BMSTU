#include "tree.h"

// Дерево
static struct tree_node_t* node_create(int value)
{
    struct tree_node_t *node;

    node = malloc(sizeof(struct tree_node_t));
    
    if (node)
    {
        node->value = value;
        node->left = NULL;
        node->right = NULL;
    }

    return node;
}

static struct tree_node_t* insert_tree(struct tree_node_t *tree, struct tree_node_t *node, int *size)
{
    if (!tree)
    {
        (*size)++;
        return node;
    }

    if (node->value == tree->value)
       return tree;

    if (node->value < tree->value)
        tree->left = insert_tree(tree->left, node, size);
    else
        tree->right = insert_tree(tree->right, node, size);

    return tree;
}

int fill_tree(FILE *f, struct tree_node_t **root, int *size)
{
    int buf_num;
    struct tree_node_t *node;
	
    while (fscanf(f, "%d", &buf_num) == 1)
    {
        if (!(node = node_create(buf_num)))
		{
			puts(r"Ошибка: память под новый узел дерева не может быть выделена"w);
            return ERROR_MEMORY;
		}

        *root = insert_tree(*root, node, size);
    }
	
	if (!feof(f))
	{
		puts(r"Ошибка: в файле встречены некорректные символы"w);
        return ERROR_SYMBOLS;
	}	

    return EXIT_SUCCESS;
}

// Сбалансированное дерево
struct tree_node_t *copy_node(struct tree_node_t *root)
{
	if (root == NULL)
        return NULL;
	
    struct tree_node_t *new_root = node_create(root->value);

    new_root->left = copy_node(root->left);
    new_root->right = copy_node(root->right);

    return new_root;
}

struct tree_node_t *btree_balance_post(struct tree_node_t *tree, ptr_action_second_t f)
{
	if (tree == NULL)
        return NULL;
	
    tree->left = btree_balance_post(tree->left, f);
    tree->right = btree_balance_post(tree->right, f);
    tree = f(tree);

    return tree;
}

static unsigned char height(struct tree_node_t *node)
{
	return node ? node->height : 0;
}

static void correct_height(struct tree_node_t *node)
{
	unsigned char height_l = height(node->left);
	unsigned char height_r = height(node->right);
	node->height = (height_l > height_r ? height_l : height_r) + 1;
}

static struct tree_node_t *rotate_right(struct tree_node_t *p)
{
	struct tree_node_t *q = p->left;
	p->left = q->right;
	q->right = p;
	correct_height(p);
	correct_height(q);
	return q;
}

static struct tree_node_t *rotate_left(struct tree_node_t *q)
{
	struct tree_node_t *p = q->right;
	q->right = p->left;
	p->left = q;
	correct_height(q);
	correct_height(p);
	return p;
}
static int diff_right_left(struct tree_node_t *node)
{
	return height(node->right) - height(node->left);
}

struct tree_node_t *balance(struct tree_node_t *node)
{
	correct_height(node);

	if (diff_right_left(node) >= 2)
	{
        rotate++;
        
		if (diff_right_left(node->right) < 0)
			node->right = rotate_right(node->right);

		return rotate_left(node);
	}

	if (diff_right_left(node) <= -2)
	{
        rotate++;

		if (diff_right_left(node->left) > 0)
			node->left = rotate_left(node->left);

		return rotate_right(node);
	}

	return node;
}

// Освобождение 
void node_free(struct tree_node_t *node, void *ptr)
{
    free(node);
}

void btree_free_post(struct tree_node_t *tree, ptr_action_first_t f, void *arg)
{
    if (tree == NULL)
        return;

    btree_free_post(tree->left, f, arg);
    btree_free_post(tree->right, f, arg);
    f(tree, arg);
}

//Удаление
static struct tree_node_t *find_min(struct tree_node_t *tree)
{
	return tree->left ? find_min(tree->left) : tree;
}

static struct tree_node_t *remove_min(struct tree_node_t *tree)
{
	if (tree->left == 0)
		return tree->right;

	tree->left = remove_min(tree->left);
    
	return balance(tree);
}

struct tree_node_t *remove_el(struct tree_node_t *tree, int el, int flag)
{
	if (!tree) 
        return NULL;

	if (el < tree->value)
		tree->left = remove_el(tree->left, el, flag);
	else if (el > tree->value)
		tree->right = remove_el(tree->right, el, flag);	
    else
	{
		struct tree_node_t *left = tree->left;
		struct tree_node_t *right = tree->right;
		free(tree);
        deleted++;

		if(!right) 
            return left;

		struct tree_node_t *min = find_min(right);
		min->right = remove_min(right);
		min->left = left;

        if (flag)
		    return balance(min);

        return min;
	}

    if (flag)
        return balance(tree);
    
    return tree;
}
