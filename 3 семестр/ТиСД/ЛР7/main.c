#include "graph.h"
#include "read.h"
#include "print.h"

#define ERROR_FILE 1

int main(void)
{
    setbuf(stdout, NULL);
	
	int rc;
	
	
	int type_filling;
	if ((rc = read_type_filling(&type_filling)))
		return rc;
	
	FILE *f = stdin;
	char filename[20];
    if (type_filling == 0)
    {
		puts("Ведите название файла: ");
		if(scanf("%s", filename) != 1)
		{
			puts(r"Ошибка: встречены некорректные символы"w);
			return ERROR_SYMBOLS;
		}
        if (!(f = fopen(filename, "r")))
        {
            puts(r"Ошибка: невозможно открыть файл"w);
            return ERROR_FILE;
        }
    }
	
	int size;
	if ((rc = read_size_graph(f, &size, type_filling)))
		return rc;
    graph_t graph = create_graph(size);
    if ((rc = read_graph(f, graph, type_filling)))
	{
        return rc;
	}
	
	if (type_filling == 0)
		fclose(f);
	
	print_graph(graph);
	print_matrix(graph);
	
	int start_vertex, end_vertex;
	read_vertexs(&start_vertex, &end_vertex, graph);

    if (deijkstra(graph, start_vertex - 1, end_vertex - 1))
	{
        return ERROR_GRAPH;
	}
	
	print_path(graph);

    return EXIT_SUCCESS;
}

