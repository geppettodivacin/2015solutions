#include <stdio.h>
#include <stdlib.h>


struct house {
	long x;
	long y;
	struct house *next;
};

char AddHouse(long, long, struct house *);
void RemoveHouses(struct house *haus);

int main(void)
{
	struct house *current;
	current = (struct house *) malloc(sizeof(struct house));
	*current = (struct house) {0,0,NULL};
	char c;
	long x[2], y[2];
	x[0] = y[0] = x[1] = y[1] = 0;
	unsigned char roboOrReal = 0;
	unsigned long houses = 1; // The initial house.
	while ((c = fgetc(stdin)) != EOF) {
		switch (c) {
		case '^':
			y[roboOrReal]++;
			break;
		case 'v':
			y[roboOrReal]--;
			break;
		case '>':
			x[roboOrReal]++;
			break;
		case '<':
			x[roboOrReal]--;
			break;
		default:
			printf("Unknown character input: %c.\n", c);
			break;
		}
		houses += AddHouse(x[roboOrReal],y[roboOrReal],current);
		roboOrReal = !roboOrReal;
	}
	printf("Houses visited: %lu\n", houses);
	RemoveHouses(current);
	return 0;
}

char AddHouse(long x, long y, struct house *haus)
{
	while (haus->x != x || haus->y != y) {
		if (haus->next) {
			haus = haus->next;
		} else {
			haus->next = (struct house *)
				malloc(sizeof(struct house));
			*(haus->next) = (struct house) {x,y,NULL};
			return 1;
		}
	}
	return 0;
}

void RemoveHouses(struct house *haus)
{
	struct house *cur, *old;
	cur = old = haus;
	while(cur->next) {
		old = cur;
		cur = cur->next;
		free(old);
	}
	return;
}
