#include "main.h"
#include "error.h"

void SocketQueue_init(SocketQueue *queue) 
{
    queue->head = 0;
    queue->tail = 0;
    pthread_mutex_init(&(queue->mutex), NULL);
    pthread_cond_init(&(queue->condition), NULL);
}

void SocketQueue_push(SocketQueue *queue, SOCKET s) 
{
    pthread_mutex_lock(&(queue->mutex));
    queue->sockets[queue->tail++] = s;
    pthread_cond_signal(&(queue->condition));
    pthread_mutex_unlock(&(queue->mutex));
}

SOCKET SocketQueue_pop(SocketQueue *queue) 
{
    pthread_mutex_lock(&(queue->mutex));
    while (queue->head == queue->tail) 
        pthread_cond_wait(&(queue->condition), &(queue->mutex));
    SOCKET s = queue->sockets[queue->head++];
    pthread_mutex_unlock(&(queue->mutex));
    return s;
}

void *worker_thread(void *arg) 
{
    while (1) 
	{
        SOCKET client_socket = SocketQueue_pop(&socketQueue);
        handle_request(client_socket);
        closesocket(client_socket);
    }
}