#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void main()
{
    int nodes[10][10];
    int root, nodeCount, nodesAdded[10], nodesAddedCount = 0;

    printf("Enter node count:");
    scanf("%d", &nodeCount);

    for (int i = 0; i < nodeCount; ++i)
        nodesAdded[i] = 0;

    printf("Enter cost matrix:\n");
    for (int i = 0; i < nodeCount; ++i)
        for (int j = 0; j < nodeCount; ++j)
            scanf("%d", &nodes[i][j]);

    printf("Enter source node: ");
    scanf("%d", &root);

    nodesAdded[root] = 1;
    nodesAddedCount++;

    while (nodesAddedCount < nodeCount)
    {
        int indexNode;
        int min = INT_MAX;

        for (int i = 0; i < nodeCount; ++i)
        {
            if (nodes[root][i] != -1 && root != i && nodesAdded[i] != 1 && nodes[root][i] < min)
            {
                indexNode = i;
                min = nodes[root][i];
            }
        }

        nodesAdded[indexNode] = 1;
        nodesAddedCount++;

        for (int i = 0; i < nodeCount; ++i)
        {
            if (nodesAdded[i] == 1)
                continue;

            int distAC = nodes[root][i] == -1 ? INT_MAX : nodes[root][i];
            int distBC = nodes[indexNode][i] == -1 ? INT_MAX : nodes[indexNode][i];

            if (distBC != INT_MAX && distBC + min < distAC)
                nodes[root][i] = distBC + min;
        }
    }

    printf("After Link State Routing:\nShortest distance from node %d\nNode\tShortest path cost\n", root);
    for (int i = 0; i < nodeCount; ++i)
        printf("%d\t%d\n", i, nodes[root][i]);
}