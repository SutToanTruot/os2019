#include<studio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include <stdbool.h>

#define BUFFER_SIZE 10

typedef struct {
	char type; // 0=fish, 1=chips
	int amount;
	char unit; 
}item;	

item buffer [BUFFER_SIZE];
int first = 0;
int last = 0;

void produce(item *i){
	while ((first + 1) % BUFFER_SIZE == last){
		printf("No free buffer item\n");
	}
	memcpy(&buffer[first], i, sizeof(item));
	first = (first + 1) % BUFFER_SIZE;
		printf("first = %d\t last = %d\n", first, last);

}

item *consume() {
	item *i = malloc(sizeof(item));
	while (first == last){
		printf("Nothing to consume");
	}
	memcpy(i, &buffer[last], sizeof(item));
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

int main(){
	item* order1 = createItem('1', '4', '1');
	item* order1 = createItem('3', '1', '4');
	printf("Position: \nfirst = %d\tlast = %d\n\n", first, last);
	produce(order1);
	produce(order2);
	consume();
	return 0;
}
