#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <locale.h>
#include <pthread.h>

typedef struct SocketQueue {
    SOCKET sockets[1024];
    int head;
    int tail;
    pthread_mutex_t mutex;
    pthread_cond_t condition;
} SocketQueue;

extern SocketQueue socketQueue;

void SocketQueue_init(SocketQueue *queue);
void SocketQueue_push(SocketQueue *queue, SOCKET s);
void *worker_thread(void *arg);

void handle_request(SOCKET client_socket);