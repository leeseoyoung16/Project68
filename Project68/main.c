#include <stdio.h>
#include <stdlib.h>

// Ž��(�ݺ�)���� ����

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50
#define MAX_QUEUE_SIZE 10

typedef struct GraphType {
    int n;
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int visited[MAX_VERTICES];

void init(GraphType* g) {
    int r, c;
    g->n = 0;
    for (r = 0; r < MAX_VERTICES; r++) {
        for (c = 0; c < MAX_VERTICES; c++) {
            g->adj_mat[r][c] = 0;
        }
    }
}

typedef int element;

typedef struct {
    element queue[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

void error(char* message) {
    fprintf(stderr, "%s\n", message);  // ����: %s�� ����
    exit(1);
}

void queue_init(QueueType* q) {
    q->front = q->rear = 0;
}

int is_empty(QueueType* q) {
    return (q->front == q->rear);
}

int is_full(QueueType* q) {
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType* q, element item) {
    if (is_full(q))
        error("ť�� ��ȭ�����Դϴ�.");
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->queue[q->rear] = item;
}

element dequeue(QueueType* q) {
    if (is_empty(q))
        error("ť�� ��������Դϴ�.");
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->queue[q->front];
}

void insert_vertex(GraphType* g, int v) {
    if ((g->n) + 1 > MAX_VERTICES) {
        fprintf(stderr, "�׷���: ������ ���� �ʰ�\n");  // ����: %s�� %d�� �����ϰ� ���� ���� �߰�
        return;
    }
    g->n++;
}

void insert_edge(GraphType* g, int start, int end) {
    if (start >= g->n || end >= g->n) {
        fprintf(stderr, "�׷���: ���� ��ȣ ����\n");  // ����: %s�� %d�� �����ϰ� ���� ���� �߰�
        return;
    }
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1;
}

int dfs_mat(GraphType* g, int v, int end) {
    int w;
    visited[v] = TRUE;
    printf("%d ", v); // �湮�� ���� ���

    if (v == end) {
        printf("\n��ǥ ��带 ã�ҽ��ϴ�.\n");
        return 1;  // ��ǥ ��带 ã�����Ƿ� Ž�� ����
    }

    for (w = 0; w < g->n; w++) {
        if (g->adj_mat[v][w] && !visited[w]) {
            if (dfs_mat(g, w, end)) {
                return 1;  // ��ǥ ��带 ã�����Ƿ� Ž�� ����
            }
        }
    }

    return 0;  // ��ǥ ��带 ���� ã�� �ʾ���
}

int bfs_mat(GraphType* g, int v, int end) {
    QueueType queue;
    int w;
    int found = 0;  // ��ǥ ��带 ã�Ҵ��� ���θ� ��Ÿ���� ����

    queue_init(&queue);
    visited[v] = TRUE;
    enqueue(&queue, v);

    while (!is_empty(&queue)) {
        v = dequeue(&queue);
        printf("%d ", v); // �湮�� ���� ���

        if (v == end) {
            printf("\n��ǥ ��带 ã�ҽ��ϴ�.\n");
            found = 1;  // ��ǥ ��带 ã�����Ƿ� Ž�� ����
            break;
        }

        for (w = 0; w < g->n; w++) {
            if (g->adj_mat[v][w] && !visited[w]) {
                visited[w] = TRUE;
                enqueue(&queue, w);
            }
        }
    }

    if (found) {
        return found; 
    }
    else {
        return 0;  // ��ǥ ��带 ã�� ����
    }
}

int main(void) {
    GraphType g;
    init(&g);

    for (int i = 0; i < 11; i++) {
        insert_vertex(&g, i);
    }
    insert_edge(&g, 0, 5);
    insert_edge(&g, 0, 2);
    insert_edge(&g, 0, 4);
    insert_edge(&g, 0, 6);
    insert_edge(&g, 0, 9);
    insert_edge(&g, 1, 5);
    insert_edge(&g, 1, 4);
    insert_edge(&g, 1, 7);
    insert_edge(&g, 1, 10);
    insert_edge(&g, 2, 3);
    insert_edge(&g, 2, 4);
    insert_edge(&g, 3, 5);
    insert_edge(&g, 3, 4);
    insert_edge(&g, 4, 5);
    insert_edge(&g, 4, 6);
    insert_edge(&g, 4, 7);
    insert_edge(&g, 6, 8);
    insert_edge(&g, 7, 10);
    insert_edge(&g, 8, 10);

    printf("---------------------------\n");
    printf("  1        : ���� �켱 Ž��|\n");
    printf("  2        : �ʺ� �켱 Ž��|\n");
    printf("  3        :      ����     |\n");
    printf("---------------------------\n");

    int n;
    int count;

    while (1) {
        printf("�޴� �Է�: ");
        scanf_s("%d", &n);

        if (n == 1) {
            int start, end;
            printf("���� ��ȣ�� Ž���� �� �Է�: ");
            scanf_s("%d %d", &start, &end);  
            count = dfs_mat(&g, start, end);
            if (count > 0)
                printf("Ž�� ����: %d\n", count);
            else
                printf("Ž�� ����\n");
        }
        if (n == 2) {
            int start, end;
            printf("���� ��ȣ�� Ž���� �� �Է�: ");
            scanf_s("%d %d", &start, &end);
            count = bfs_mat(&g, start, end);
            if (count > 0)
                printf("Ž�� ����: %d\n", count);
            else
                printf("Ž�� ����\n");
        }
        if (n == 3) {
            printf("����\n");
            break;  
        }
    }

    return 0;
}
