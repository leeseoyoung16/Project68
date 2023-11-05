#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50
#define MAX_QUEUE_SIZE 10
typedef struct GraphType {
    int n;
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int visited[MAX_VERTICES];


typedef struct {
    int data[MAX_VERTICES];
    int top;
} Stack;

void init(GraphType* g) { 
    int r, c;
    g->n = 0;
    for (r = 0; r < MAX_VERTICES; r++) {
        for (c = 0; c < MAX_VERTICES; c++) {
            g->adj_mat[r][c] = 0;
        }
    }
}
void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void stack_init(Stack* stack) { //스택 초기화
    stack->top = -1;
}

int is_stack_empty(Stack* stack) {
    return (stack->top == -1);
}

void push(Stack* stack, int item) {
    if (stack->top < MAX_VERTICES - 1) {
        stack->data[++stack->top] = item;
    }
}

int pop(Stack* stack) {
    if (!is_stack_empty(stack)) {
        return stack->data[stack->top--];
    }
    return -1; // 스택이 비어있음
}

void insert_vertex(GraphType* g, int v) {
    if ((g->n) + 1 > MAX_VERTICES) {
        fprintf(stderr, "그래프: 정점의 갯수 초과\n");
        return;
    }
    g->n++;
}

void insert_edge(GraphType* g, int start, int end) {
    if (start >= g->n || end >= g->n) {
        fprintf(stderr, "그래프: 정점 번호 오류\n");
        return;
    }
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1;
}

//stack으로 dfs 구현
int dfs_mat(GraphType* g, int start, int end) { 
    Stack stack;
    stack_init(&stack);

    for (int i = 0; i < MAX_VERTICES; i++) { //방문 초기화
        visited[i] = FALSE;
    }

    push(&stack, start);
    visited[start] = TRUE;
    int count = 0; //방문노드 카운트

    while (!is_stack_empty(&stack)) {
        int v = pop(&stack);
        count += 1;
        printf("%d ", v);
        

        if (v == end) {
            return count;
        }

        for (int w = 0; w < g->n; w++) {
            if (g->adj_mat[v][w] && !visited[w]) { //간선이 있고, 방문한 정점이 아니면
                push(&stack, w);
                visited[w] = TRUE;
                
                
            }
        }
    }

    return 0;
}

typedef int element;

typedef struct {
    element queue[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

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


//큐로 bfs 구현

int bfs_mat(GraphType* g, int start, int end) {
    QueueType queue;
    queue_init(&queue);
    int count = 0;

    for (int i = 0; i < MAX_VERTICES; i++) { //방문 초기화
        visited[i] = FALSE;
    }

    enqueue(&queue, start);
    visited[start] = TRUE;
    printf("%d ", start);

    while (!is_empty(&queue)) {
        int v = dequeue(&queue);

        if (v == end) {
            return count;
        }

        for (int w = 0; w < g->n; w++) {
            if (g->adj_mat[v][w] && !visited[w]) { //간선이 있고, 방문한 정점이 아니면
                printf("%d ", w);
                count += 1;
                enqueue(&queue, w);
                visited[w] = TRUE;
            }
        }
    }

    
    return 0;
}

int main(void) {
    GraphType g;
    init(&g);

    for (int i = 0; i < 11; i++) {
        insert_vertex(&g, i);
    }

    insert_edge(&g, 0, 2);
    insert_edge(&g, 0, 4);
    insert_edge(&g, 0, 5);
    insert_edge(&g, 0, 6);
    insert_edge(&g, 0, 9);
    insert_edge(&g, 1, 4);
    insert_edge(&g, 1, 5);
    insert_edge(&g, 1, 7);
    insert_edge(&g, 1, 10);
    insert_edge(&g, 2, 3);
    insert_edge(&g, 2, 4);
    insert_edge(&g, 3, 4);
    insert_edge(&g, 3, 5);
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
                printf("\n방문한 노드의 수: %d\n", count);
            else
                printf("탐색 실패\n");
        }
        if (n == 2) {
            int start, end;
            printf("시작 번호와 탐색할 값 입력: ");
            scanf_s("%d %d", &start, &end);
            count = bfs_mat(&g, start, end);
            if (count > 0)
                printf("\n방문한 노드의 수: %d\n", count);
            else
                printf("탐색 실패\n");
        }
        if (n == 3) {
            printf("종료\n");
            break;  
        }
        printf("\n");
    }

    return 0;
}
