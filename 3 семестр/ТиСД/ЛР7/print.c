#include "print.h"

void print_graph(graph_t graph)
{
	FILE *f = fopen("graph.gv", "w");
	fprintf(f, "%s", "graph g{\n");
	
	char buffer[20];
	for (int i = 0; i < graph.size; i++)
		for (int j = i; j < graph.size; j++)
			if (graph.matrix[i][j].length + graph.matrix[i][j].price != 0)
			{
				sprintf(buffer, "\"[%d, %d]\"", graph.matrix[i][j].length, graph.matrix[i][j].price);
				fprintf(f, "\t%d -- %d [label=%s] \n", i + 1, j + 1, buffer);
			}
			
	fprintf(f, "%c", '}');
	fclose(f);
	
	system("dot -Tpng graph.gv -o graph.png");
    system("start graph.png");
}

void print_matrix(graph_t graph)
{
	puts(g"Матрица смежностей введенного графа [длина пути, стоимость проезда]:"w);
    for (int i = 0; i < graph.size; i++)
    {
        for (int j = 0; j < graph.size; j++)
            printf("[%d, %d] ", graph.matrix[i][j].length, graph.matrix[i][j].price);
        puts("");
    }
}

void print_path(graph_t graph)
{
	puts(g"Кратчайший путь между вершинами:"w);
    printf("%s", graph.path);
}