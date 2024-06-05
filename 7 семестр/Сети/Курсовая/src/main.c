#include "main.h"
#include "error.h"

#define PORT 8080
#define THREAD_POOL_SIZE 4

SocketQueue socketQueue;

void init_server_socket(SOCKET *server_socket) 
{
    if ((*server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) 
		exit(ERROR_SOCKET);
	
	struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    if (bind(*server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR)
        exit(ERROR_BIND); 

    if (listen(*server_socket, 10) == SOCKET_ERROR)
        exit(ERROR_LISTEN);
}


int main() 
{	
	setbuf(stdout, NULL);

    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        exit(ERROR_WINSOCK);
	
    SOCKET server_socket;
	init_server_socket(&server_socket);
    printf("The server is running on the port %d\n", PORT);

    SocketQueue_init(&socketQueue);
    pthread_t threadPool[THREAD_POOL_SIZE];
    for (int i = 0; i < THREAD_POOL_SIZE; i++)
        pthread_create(&(threadPool[i]), NULL, worker_thread, NULL);
	
	SOCKET client_socket;
    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);
    fd_set readfds;
    while (1) 
	{
        FD_ZERO(&readfds);
        FD_SET(server_socket, &readfds);
        
        int activity = select(server_socket + 1, &readfds, NULL, NULL, NULL); 

        if (activity < 0)
            exit(ERROR_SELECT);

        if (FD_ISSET(server_socket, &readfds)) 
		{
            client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
            if (client_socket == INVALID_SOCKET) 
				 exit(ERROR_ACCEPT);
			 
            SocketQueue_push(&socketQueue, client_socket);
        }
    }

    for (int i = 0; i < THREAD_POOL_SIZE; i++)
        pthread_join(threadPool[i], NULL);
	
    closesocket(server_socket);
    WSACleanup();

    return 0;
}
