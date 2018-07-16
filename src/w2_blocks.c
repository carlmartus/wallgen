#include <stdio.h>
#include <stdlib.h>

#define GRID_BS 4
#define GRID_ON		0x40, 0x40, 0x80
#define GRID_OFF	0x20
#define GRID_OFF_ADD 0x80

static struct color {
	unsigned char r, g, b;
} *out;

static struct color
base_color(int x, int y, int maxy)
{
	int px = x+y, py=y-x;
	float t = (float) y / (float) maxy;
	unsigned add = (unsigned) (t * (float) GRID_OFF_ADD);

	return ((px>>GRID_BS)&1) ^ ((py>>GRID_BS)&1) ?
		(struct color) { GRID_ON } :
		(struct color) { GRID_OFF, GRID_OFF, GRID_OFF+add };
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
	out = malloc(sizeof(struct color)*sw*sh);

	printf("P6 %d %d %d\n", sw, sh, 255);

	struct color *itr;
	int x, y;
	for (y=0; y<sh; y++) {
		itr = out + sw*y;
		for (x=0; x<sw; x++) {
			*itr++ = base_color(x, y, sh);
		}
	}

	for (y=0; y<sh; y++) {
		itr = out + sw*y;
		for (x=0; x<sw; x++) {
			putchar(itr->r);
			putchar(itr->g);
			putchar(itr->b);
			itr++;
		}
	}

	free(out);
	return 0;
}

