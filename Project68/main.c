#include <stdio.h>
#include <stdlib.h>

// 탐색(반복)으로 구현

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
    fprintf(stderr, "%s\n", message);  // 수정: %s로 수정
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
        error("큐가 포화상태입니다.");
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->queue[q->rear] = item;
}

element dequeue(QueueType* q) {
    if (is_empty(q))
        error("큐가 공백상태입니다.");
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->queue[q->front];
}

void insert_vertex(GraphType* g, int v) {
    if ((g->n) + 1 > MAX_VERTICES) {
        fprintf(stderr, "그래프: 정점의 갯수 초과\n");  // 수정: %s를 %d로 수정하고 개행 문자 추가
        return;
    }
    g->n++;
}

void insert_edge(GraphType* g, int start, int end) {
    if (start >= g->n || end >= g->n) {
        fprintf(stderr, "그래프: 정점 번호 오류\n");  // 수정: %s를 %d로 수정하고 개행 문자 추가
        return;
    }
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1;
}

int dfs_mat(GraphType* g, int v, int end) {
    int w;
    visited[v] = TRUE;
    printf("%d ", v); // 방문한 정점 출력

    if (v == end) {
        printf("\n목표 노드를 찾았습니다.\n");
        return 1;  // 목표 노드를 찾았으므로 탐색 종료
    }

    for (w = 0; w < g->n; w++) {
        if (g->adj_mat[v][w] && !visited[w]) {
            if (dfs_mat(g, w, end)) {
                return 1;  // 목표 노드를 찾았으므로 탐색 종료
            }
        }
    }

    return 0;  // 목표 노드를 아직 찾지 않았음
}

int bfs_mat(GraphType* g, int v, int end) {
    QueueType queue;
    int w;
    int found = 0;  // 목표 노드를 찾았는지 여부를 나타내는 변수

    queue_init(&queue);
    visited[v] = TRUE;
    enqueue(&queue, v);

    while (!is_empty(&queue)) {
        v = dequeue(&queue);
        printf("%d ", v); // 방문한 정점 출력

        if (v == end) {
            printf("\n목표 노드를 찾았습니다.\n");
            found = 1;  // 목표 노드를 찾았으므로 탐색 종료
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
        return 0;  // 목표 노드를 찾지 못함
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
    printf("  1        : 깊이 우선 탐색|\n");
    printf("  2        : 너비 우선 탐색|\n");
    printf("  3        :      종료     |\n");
    printf("---------------------------\n");

    int n;
    int count;

    while (1) {
        printf("메뉴 입력: ");
        scanf_s("%d", &n);

        if (n == 1) {
            int start, end;
            printf("시작 번호와 탐색할 값 입력: ");
            scanf_s("%d %d", &start, &end);  
            count = dfs_mat(&g, start, end);
            if (count > 0)
                printf("탐색 성공: %d\n", count);
            else
                printf("탐색 실패\n");
        }
        if (n == 2) {
            int start, end;
            printf("시작 번호와 탐색할 값 입력: ");
            scanf_s("%d %d", &start, &end);
            count = bfs_mat(&g, start, end);
            if (count > 0)
                printf("탐색 성공: %d\n", count);
            else
                printf("탐색 실패\n");
        }
        if (n == 3) {
            printf("종료\n");
            break;  
        }
    }

    return 0;
}
