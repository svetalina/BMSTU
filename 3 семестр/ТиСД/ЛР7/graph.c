#include "graph.h"
#include <string.h>

graph_t create_graph(int size)
{
    graph_t graph;
    graph.size = size;

    graph.matrix = malloc(size * sizeof(road_t *));
    for (int i = 0; i < size; i++)
	{
        *(graph.matrix + i) = calloc(size, sizeof(road_t));
	}
	
	graph.path = calloc(size, sizeof(char));
	
    return graph;
}

static void reverse(char *string)
{
    int len = strlen(string);
    for (int i = 0; i < len / 2; i++)
    {
        char temp = string[i];
        string[i] = string[len - i - 1];
        string[len - i - 1] = temp;
    }
}

static void save_path(graph_t graph, int start_vertex, int end_vertex, int *path)
{
	char buffer[10];
	sprintf(buffer, "%d ", end_vertex + 1);
	
	int i = end_vertex;
	do
	{
		strcat(graph.path, buffer);
		i = path[i];
		sprintf(buffer, ">- %d ", i + 1);
	} while(i != start_vertex);

	strcat(graph.path, buffer);
	reverse(graph.path);
}

static int min_distance(int *distance, int *visited, int size)
{
    int min = INT_MAX;
    int min_index;

    for (int i = 0; i < size; i++)
    {
        if (visited[i] == 0 && distance[i] <= min)
        {
            min = distance[i];
            min_index = i;
        }
    }

    return min_index;
}

int deijkstra(graph_t graph, int start_vertex, int end_vertex)
{
    int *distance = malloc(graph.size * sizeof(int));
    int *visited = malloc(graph.size * sizeof(int));
    int *path = malloc(graph.size * sizeof(int));

    for (int i = 0; i < graph.size; i++)
    {
        *(distance + i) = INT_MAX;
        *(visited + i) = 0;
        *(path + i) = 0;
    }

    *(distance + start_vertex) = 0;
    for (int i = 0; i < graph.size - 1; i++)
    {
        int index_to_min = min_distance(distance, visited, graph.size);
        *(visited + index_to_min) = 1;

        for (int j = 0; j < graph.size; j++)
        {
            if (!visited[j] && (graph.matrix[index_to_min][j].length + graph.matrix[index_to_min][j].price) && distance[index_to_min] != INT_MAX
                && distance[index_to_min] + (graph.matrix[index_to_min][j].length + graph.matrix[index_to_min][j].price) < distance[j])
            {
                distance[j] = distance[index_to_min] + (graph.matrix[index_to_min][j].length + graph.matrix[index_to_min][j].price);
                path[j] = index_to_min;
            }
        }
    }
	
	if (distance[end_vertex] == INT_MAX)
	{
		puts(r"Ошибка: граф не является связным"w);
		return ERROR_GRAPH;
	}
    save_path(graph, start_vertex, end_vertex, path);


    free(distance);
    free(visited);
    free(path);

    return EXIT_SUCCESS;
}