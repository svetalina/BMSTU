def dijkstra(graph, start):
    rows = len(graph)                                          #1
    columns = len(graph[0])                                    #2

    dists = [inf] * rows                                       #3
    dists[start] = 0                                           #4 

    queue = [i for i in range(rows)]                           #5

    while queue:                                               #6
        minVal = inf                                           #7
        minInd = -1                                            #8

        for i, dist in enumerate(dists):                       #9
            if dist < minVal and i in queue:                   #10
                minVal = dist                                  #11
                minInd = i                                     #12

        queue.remove(minInd)                                   #13

        for i in range(columns):                               #14
            if graph[minInd][i] and i in queue:                #15
                newDist = dists[minInd] + graph[minInd][i]     #16
                if newDist < dists[i]:                         #17
                    dists[i] = newDist                         #18

    return dists