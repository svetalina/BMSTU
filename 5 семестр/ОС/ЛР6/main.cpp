#include <windows.h>
#include <cstdio>
#include <ctime>

#define READERS_CNT 4
#define WRITERS_CNT 3

#define ITER_CNT 20

HANDLE canRead;
HANDLE canWrite;
HANDLE mutex;

LONG waitingWritersCount = 0;
LONG waitingReadersCount = 0;
LONG activeReadersCount = 0;

HANDLE readerThreads[READERS_CNT];
HANDLE writerThreads[WRITERS_CNT];

int count = 0;

void StartRead()
{
	InterlockedIncrement(&waitingReadersCount);

	if (WaitForSingleObject(canWrite, 0) == WAIT_OBJECT_0)
		WaitForSingleObject(canRead, INFINITE);

	WaitForSingleObject(mutex, INFINITE);
	InterlockedDecrement(&waitingReadersCount);
	InterlockedIncrement(&activeReadersCount);
	SetEvent(canRead);
	ReleaseMutex(mutex);
}

void StopRead()
{
	InterlockedDecrement(&activeReadersCount);

	if (!activeReadersCount)
		SetEvent(canWrite);
}

void StartWrite()
{
	InterlockedIncrement(&waitingWritersCount);

	if (activeReadersCount > 0)
		WaitForSingleObject(canWrite, INFINITE);

	InterlockedDecrement(&waitingWritersCount);
}

void StopWrite()
{
	ResetEvent(canWrite);

	if (waitingReadersCount)
		SetEvent(canRead);
	else
		SetEvent(canWrite);
}

DWORD WINAPI ReaderRun(CONST LPVOID param)
{	
    int id = *(int *)param;
	srand(time(NULL) + id);
	
    for (int i = 0; i < ITER_CNT; i++)
    {
		int stime = rand() % 100 + 100;
        Sleep(stime);

        StartRead();
        printf("Читатель %d прочитал: %d (время сна: %d)\n", id, count, stime);
        StopRead();
    }
}

DWORD WINAPI WriterRun(CONST LPVOID param)
{
    int id = *(int *)param;
	srand(time(NULL) + id);

    for (int i = 0; i < ITER_CNT; i++)
    {
        int stime = rand() % 100 + 100;
        Sleep(stime);

        StartWrite();
        printf("Писатель %d написал:  %d (время сна: %d)\n", id, ++count, stime);
        StopWrite();
    }
}

int main()
{
	setbuf(stdout, NULL);

    if ((mutex = CreateMutex(NULL, FALSE, NULL)) == NULL)
    {
        perror("Ошибка: CreateMutex");
        exit(1);
    }

    if ((canRead = CreateEvent(NULL, FALSE, FALSE, NULL)) == NULL)
    {
        perror("Ошибка: CreateEvent (canRead)");
        exit(1);
    }

    if ((canWrite = CreateEvent(NULL, TRUE, FALSE, NULL)) == NULL)
    {
        perror("Ошибка: CreateEvent (canWrite)");
        exit(1);
    }

    int readersID[READERS_CNT];
    DWORD id = 0;
    for (int i = 0; i < READERS_CNT; i++)
    {
        readersID[i] = i;
        if ((readerThreads[i] = CreateThread(NULL, 0, ReaderRun, readersID + i, 0, &id)) == NULL)
        {
            perror("Ошибка: CreateThread (reader)");
            exit(1);
        }
    }

    int writersID[WRITERS_CNT];
    for (int i = 0; i < WRITERS_CNT; i++)
    {
        writersID[i] = i;

        if ((writerThreads[i] = CreateThread(NULL, 0, WriterRun, writersID + i, 0, &id)) == NULL)
        {
            perror("Ошибка: CreateThread (writer)");
            exit(1);
        }
    }

	WaitForMultipleObjects(READERS_CNT, readerThreads, TRUE, INFINITE);
	WaitForMultipleObjects(WRITERS_CNT, writerThreads, TRUE, INFINITE);

    for (int i = 0; i < READERS_CNT; i++)
        CloseHandle(readerThreads[i]);

    for (int i = 0; i < WRITERS_CNT; i++)
        CloseHandle(writerThreads[i]);

    CloseHandle(canRead);
    CloseHandle(canWrite);
    CloseHandle(mutex);

	return 0;
}
