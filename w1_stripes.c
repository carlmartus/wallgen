#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GRAD_ADD 0x20
#define ADD 0x20
#define SOLID_ADD 0x60
#define SOLID_NEG 0x20

static struct color {
	unsigned char r, g, b;
} root_color;

static struct color
get_color(int x, int y, int maxy)
{
	unsigned id = x + (y<<1);
	unsigned grad = (id>>4) & 1 ? GRAD_ADD : 0;

	float t = (float) y / (float) maxy;
	int solidadd = (unsigned) (t * (float) SOLID_ADD) - SOLID_NEG;

	struct color cl = {
		root_color.r + grad + ADD + solidadd,
		root_color.b + grad + ADD + solidadd,
		root_color.g + grad + ADD + solidadd,
	};
	return cl;
}

static struct color
random_color(int seed)
{
	srand(seed);
	unsigned grad = 1<<(rand() % 3);
	return (struct color) {
		((grad & 1) ? 0xff : 0) >> 2,
		((grad & 2) ? 0xff : 0) >> 2,
		((grad & 4) ? 0xff : 0) >> 2,
	};
}

int
main(int argc, char **argv)
{
	if (argc < 3) {
		fprintf(stderr, "Usage: %s [Width] [Height]\n", argv[0]);
		return 1;
	}
	int sw = atoi(argv[1]);
	int sh = atoi(argv[2]);
	int seed = argc > 3 ? atoi(argv[3]) : time(NULL);
	printf("P6 %d %d %d\n", sw, sh, 255);

	root_color = random_color(seed);

	int x, y;
	for (y=0; y<sh; y++) {
		for (x=0; x<sw; x++) {
			struct color c = get_color(x, y, sh);
			printf("%c%c%c", c.r, c.g, c.b);
		}
	}

	return 0;
}

