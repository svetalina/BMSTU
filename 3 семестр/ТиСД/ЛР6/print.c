#include "print.h"

void print_menu(void)
{
	puts("Введите, если хотите:");
	puts("1. Считать числа из файла в дерево и таблицу");
	puts("2. Сбалансировать дерево");
	puts("3. Удалить элемент по значению");
	puts("4. Просмотреть занимаемую память");
	puts("0. Выход");
}

static void btree_apply_pre(struct tree_node_t *tree, ptr_action_first_t f, void *arg)
{
    if (!tree)
        return;

    f(tree, arg);
    btree_apply_pre(tree->left, f, arg);
    btree_apply_pre(tree->right, f, arg);
}

void node_to_dot(struct tree_node_t *tree, void *param)
{
    FILE *f = param;

    if (tree->left)
        fprintf(f, "%d -> %d;\n", tree->value, tree->left->value);

    if (tree->right)
        fprintf(f, "%d -> %d;\n", tree->value, tree->right->value);
}

static void btree_export_to_dot(FILE *f, const char *tree_name, struct tree_node_t *tree)
{
    fprintf(f, "digraph %s {\n", tree_name);

    btree_apply_pre(tree, node_to_dot, f);

    fprintf(f, "}\n");
}

static void graphiz(struct tree_node_t *root, int flag)
{
    if (flag)
    {
        FILE *f = fopen("balanced_tree.gv", "w");

        btree_export_to_dot(f, "balanced_tree", root);

        fclose(f);

        system("dot -Tpng balanced_tree.gv -o balanced_tree.png");
        system("start balanced_tree.png");
    }
    else
    {
        FILE *f = fopen("tree.gv", "w");

        btree_export_to_dot(f, "tree", root);

        fclose(f);

        system("dot -Tpng tree.gv -o tree.png");
        system("start tree.png");
    }
}

// static void node_print(tree_node_t *node, void *format)
// {
    // printf((const char)format, node->value);
// }

void print_tree(struct tree_node_t *root, int size, int flag)
{
    if (!size)
        puts(g"Дерево пустое"w);
    else
    {
        // btree_apply_pre(root, node_print, "%d ");

        // if (size > 1)
		if (flag)
			graphiz(root, 1);
		else
			graphiz(root, 0);
    }
}

void print_table(struct hash_t *hash_table, hash_func_t hash_func)
{
    puts("*--------------*--------------*--------------*");
    puts("|    номер     |     ключ     | хэш-значение |");
    puts("*--------------*--------------*--------------*");

    for (int i = 0; i < hash_table->size; i++)
        if (hash_table->array[i].status == BUSY)
        {
            printf("| %12d | %12d | %12d |\n", i, hash_table->array[i].key, hash_func(hash_table->array[i].key, hash_table->size));
            puts("*--------------*--------------*--------------*");
        }
        else
        {
            printf("| %12d |              |              |\n", i);
            puts("*--------------*--------------*--------------*");
        }
}