#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<stdbool.h>

#define BUFFER_SIZE 10

int pid = 0;

typedef struct {
    char type; // 0=chicken, 1=soup
    int amount;
    char unit; // 0=gram, 1=bowl
}item;	

item buffer [BUFFER_SIZE];
int first = 0;
int last = 0;

int pthread_create(
    pthread_t *thread,
    const pthread_attr_t *attr,
    void *(*start_routine) (void *),
    void *arg
);

void produce(item *i) {
    while ((first + 1) % BUFFER_SIZE == last){
      printf("No free buffer item\n");
    }
    memcpy(&buffer[first], i, sizeof(item));
    i->amount += 1;
    first = (first + 1) % BUFFER_SIZE;
      printf("first = %d\t last = %d\n", first, last);
}

item *consume() {
    item *i = malloc(sizeof(item));
    while (first == last){
      printf("Nothing to consume");
    }
    memcpy(i, &buffer[last], sizeof(item));
    i->amount += 1;
    last = (last +1) % BUFFER_SIZE;
    printf("first = %d\t last = %d\n", first, last);
    return i;
}

item* createItem(char type, int amount, char unit){
    item* i = malloc(sizeof(item));
    i->type = type;
    i->amount = amount;
    i->unit = unit;
    return i;
}
void *producerThread(void* param){
    item *chicken, gram;
    chicken = &gram;
    printf("3 Grams of beef please !!!\n");
    initBeef(chicken);
    produce(chicken);
    produce(chicken);
    produce(chicken);
    pthread_exit(NULL);
}
void *consumerThread(void* param) {
    printf("Selling 2 grams of chicken\nConsuming chickens...\n");
    consume();
    consume();
    consume();
    pthread_exit(NULL);
}

int main() {
    pthread_t tid;
    printf("Welcome to chicken shop\n");
    printf("Thank you for coming\n");
    pthread_create(&tid, NULL, producerThread, NULL);
    printf("2 customers are coming to buy chickens\n");
    pthread_create(&tid, NULL, consumerThread, NULL);
    pthread_join(tid, NULL);
    pthread_join(tid, NULL);
    pthread_exit(NULL);
}
