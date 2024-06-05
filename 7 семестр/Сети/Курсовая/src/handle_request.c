#include "main.h"
#include "error.h"

#define MAX_FILE_SIZE 100 * 1024 * 1024

#define SEND(client_socket, response) send(client_socket, response, strlen(response), 0)

char ROOT[] = "./www";

const char* get_content_type(const char *path) 
{
    const char *extension = strrchr(path, '.');
    if (extension != NULL) 
	{
        if (strcasecmp(extension, ".html") == 0)	return "text/html";
        if (strcasecmp(extension, ".css")  == 0) 	return "text/css";
        if (strcasecmp(extension, ".js")   == 0) 	return "application/javascript";
        if (strcasecmp(extension, ".png")  == 0) 	return "image/png";
        if (strcasecmp(extension, ".jpg")  == 0) 	return "image/jpeg";
		if (strcasecmp(extension, ".jpeg") == 0) 	return "image/jpeg";
		if (strcasecmp(extension, ".gif")  == 0) 	return "image/gif";
        if (strcasecmp(extension, ".mp4")  == 0) 	return "video/mp4";
    }
    return NULL;
}

void process_GET(SOCKET client_socket, const char *full_path) 
{
    char buffer[1024];
    ssize_t bytes_read;
    ssize_t total_bytes_read = 0;

    int file_fd = open(full_path, O_BINARY | O_RDONLY);
    while ((bytes_read = read(file_fd, buffer, sizeof(buffer))) > 0) 
	{
        ssize_t total_sent = 0;
        total_bytes_read += bytes_read;
        while (total_sent < bytes_read) 
		{
            ssize_t sent = send(client_socket, buffer + total_sent, bytes_read - total_sent, 0);
			if (sent == -1)
				exit(ERROR_SEND);
            total_sent += sent;
        }
    }
    close(file_fd);
    printf("Total: %ld\n", total_bytes_read);
}

void process_request(SOCKET client_socket, const char *request) 
{
    char method[255];
    char path[1024];
    sscanf(request, "%s %s", method, path);

    if (strcmp(path, "/") == 0)
        strncpy(path, "/index.html", sizeof(path) - 1);

    char full_path[1024];
    snprintf(full_path, sizeof(full_path), "%s%s", ROOT, path);

    struct stat file_stat;
    if (stat(full_path, &file_stat) == -1 || file_stat.st_size > MAX_FILE_SIZE)
        SEND(client_socket, "HTTP/1.1 404 Not Found\r\n\r\n");
    else if (get_content_type(full_path) == NULL) 
        SEND(client_socket, "HTTP/1.1 403 Forbidden\r\n\r\n");
    else 
	{
        int file_fd = open(full_path, O_RDONLY);
        if (file_fd == -1)
            SEND(client_socket, "HTTP/1.1 404 Not Found\r\n\r\n");
        else 
		{
            if (strcmp(method, "GET") == 0 || strcmp(method, "HEAD") == 0)
			{
				const char *content_type = get_content_type(full_path);
				char response_header[512];
				snprintf(response_header, sizeof(response_header), "HTTP/1.1 200 OK\r\nContent-Length: %ld\r\nContent-Type: %s\r\n\r\n", file_stat.st_size, content_type);
				SEND(client_socket, response_header);
				
                if (strcmp(method, "GET") == 0)
                    process_GET(client_socket, full_path);
			}
            else 
                SEND(client_socket, "HTTP/1.1 405 Method Not Allowed\r\n\r\n");
			
            close(file_fd);
        }
    }
}

void handle_request(SOCKET client_socket) 
{
    char request[1024];
    int bytes_received = recv(client_socket, request, sizeof(request), 0);
	if (bytes_received <= 0) 
		exit(ERROR_RECV);
    request[bytes_received] = '\0';
    printf("\nRequest: %s", request);

    process_request(client_socket, request);

    shutdown(client_socket, SD_SEND);
}