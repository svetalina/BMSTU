#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <mutex>
#include <thread>

#include "conveyor.h"

static request_t generate_request(FILE *f, int n, int a, int d)
{
	request_t request;
	request.n = n;
	request.a = a;
	request.d = d;
	request.f = f;
	return request;
}

static void init_request_state_array(std::vector<request_state_t> &request_state_array, int num_of_requests)
{
    request_state_array.resize(num_of_requests);
    for (int i = 0; i < num_of_requests; i++)
    {
        request_state_t request_state;
        request_state.stage_1 = false;
        request_state.stage_2 = false;
        request_state.stage_3 = false;
        request_state_array[i] = request_state;
    }
}

void log_data(const request_t *const request)
{
	fprintf(request->f, "Matrix:\n");
	for (int i = 0; i < request->n; i++)
	{
		for (int j = 0; j < request->n; j++)
			fprintf(request->f, "%5d", request->m[i][j]);
		fprintf(request->f, "\n");
	}
	fprintf(request->f, "\n");
		
	fprintf(request->f, "Distances:\n");
	for (int i = 0; i < request->n; i++)
		fprintf(request->f, "%5d", request->w[i]);
	fprintf(request->f, "\n");
	
	bool flag;
	for (int i = 0; i < request->n; i++)
	{	
		flag = true;
		for (int j = i - 1; j >= 0; j--)
			if (request->w[i] == request->w[j])
				flag = false;
		
		if (flag)
		{
			fprintf(request->f, "Distance %d to vertices: %d ", request->w[i], i);
			for (int j = i + 1; j < request->n; j++)
				if (request->w[i] == request->w[j])
						fprintf(request->f, "%d ", j);
			fprintf(request->f, "\n");
		}
	}
	
	fprintf(request->f, "\n\n");
}

static void stage_1(std::queue<request_t> &q1, std::queue<request_t> &q2)
{
    std::mutex m;
    m.lock();
    request_t request = q1.front();
    m.unlock();
	init_data(request.m, request.n, request.a, request.d);
    m.lock();
    q2.push(request);
    m.unlock();
    m.lock();
    q1.pop();
    m.unlock();
}

static void stage_2(std::queue<request_t> &q2, std::queue<request_t> &q3)
{
    std::mutex m;
    m.lock();
    request_t request = q2.front();
    m.unlock();
    dijkstra(request.m, request.w, request.v, request.n);
    m.lock();
    q3.push(request);
    m.unlock();
    m.lock();
    q2.pop();
    m.unlock();
}

static void stage_3(std::queue<request_t> &q3, int task_num)
{
    std::mutex m;
    m.lock();
    request_t request = q3.front();
    m.unlock();
	log_data(&request);
    m.lock();
    q3.pop();
    m.unlock();
}

void linear_processing(int num_of_requests, int n, int a, int d)
{
	size_t time_start = 0, time_end = 0;
	FILE *f = fopen("linear.log", "w");
    std::queue<request_t> q1, q2, q3;
    std::mutex m;
    for (int i = 0; i < num_of_requests; i++)
    {
        request_t request = generate_request(f, n, a, d);
        q1.push(request);
    }
    get_time(time_start);
    for (int i = 0; i < num_of_requests; i++)
    {
        stage_1(std::ref(q1), std::ref(q2));
        stage_2(std::ref(q2), std::ref(q3));
        stage_3(std::ref(q3), i + 1);
    }
	get_time(time_end);
	printf("Time: %zu ticks.\n", time_end - time_start);
	fclose(f);
}

static void parallel_stage_1(std::queue<request_t> &q1, std::queue<request_t> &q2,
                      std::vector<request_state_t> &request_state_array, 
                      bool &q1_is_empty)
{
    int task_num = 1;
    while(!q1.empty())
    {   
        stage_1(std::ref(q1), std::ref(q2));
        request_state_array[task_num - 1].stage_1 = true;
        task_num++;
    }
    q1_is_empty = true;
}

static void parallel_stage_2(std::queue<request_t> &q2, std::queue<request_t> &q3,
                      std::vector<request_state_t> &request_state_array, 
                      bool &q1_is_empty, bool &q2_is_empty)
{
    int task_num = 1;
    while(true)
    {      
        if (!q2.empty())
        {   
            if (request_state_array[task_num - 1].stage_1 == true)
            {
                stage_2(std::ref(q2), std::ref(q3));
                request_state_array[task_num - 1].stage_2 = true;
                task_num++;
            }
        }
        else if (q1_is_empty)
            break;
    }
    q2_is_empty = true;
}

static void parallel_stage_3(std::queue<request_t> &q3, 
                      std::vector<request_state_t> &request_state_array, 
                      bool &q2_is_empty)
{
    int task_num = 1;
    while(true)
    {      
        if (!q3.empty())
        {   
            if (request_state_array[task_num - 1].stage_2 == true)
            {
                stage_3(std::ref(q3), task_num);
                request_state_array[task_num - 1].stage_3 = true;
                task_num++;
            }
        }
        else if(q2_is_empty)
            break;
    }
}

void conveyor_processing(int num_of_requests, int n, int a, int d)
{
	size_t time_start = 0, time_end = 0;
	FILE *f = fopen("conveyor.log", "w");
    std::queue<request_t> q1, q2, q3;
    std::mutex m;
    for (int i = 0; i < num_of_requests; i++)
    {
        request_t request = generate_request(f, n, a, d);
        q1.push(request);
    }
    bool q1_is_empty = false, q2_is_empty = false;
    std::vector<request_state_t> request_state_array;
    init_request_state_array(request_state_array, num_of_requests);
    std::thread threads[THREADS_COUNT];
	get_time(time_start);
    threads[0] = std::thread(parallel_stage_1, std::ref(q1), std::ref(q2), std::ref(request_state_array), std::ref(q1_is_empty));
    threads[1] = std::thread(parallel_stage_2, std::ref(q2), std::ref(q3), std::ref(request_state_array), std::ref(q1_is_empty), std::ref(q2_is_empty));
    threads[2] = std::thread(parallel_stage_3, std::ref(q3), std::ref(request_state_array), std::ref(q2_is_empty));
    get_time(time_end);
	for (int i = 0; i < THREADS_COUNT; i++)
        threads[i].join();
	printf("Time: %zu ticks.\n", time_end - time_start);
	fclose(f);
}
