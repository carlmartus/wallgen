#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static const struct color {
	unsigned char r, g, b;
} cols[] = {
	{	0xff,	0x88,	0x88	},
	{	0x88,	0xff,	0x88	},
	{	0x88,	0x88,	0xff	},
	{	0xff,	0x88,	0xff	},
	{	0x88,	0xff,	0xff	},
	{	0xff,	0xff,	0x88	},
};
#define COLS_LEN (sizeof(cols) / sizeof(struct color))

static struct color
get_color(int x, int y)
{
	float angl = atan2f((float) x, (float) y);
	int rad = (int) (sqrtf(x*x + y*y) * 0.04f);
	float t = 1000 + angl*2.86f + 0.5 + 10.0f * (float) (rad & 1);
	float u = t - (int) t;
	struct color col0 = cols[(int) floorf(t) % COLS_LEN];
	struct color col1 = cols[(int) ceilf(t) % COLS_LEN];

	return (struct color) {
		col0.r + (int) ((float) (col1.r - col0.r) * u),
		col0.g + (int) ((float) (col1.g - col0.g) * u),
		col0.b + (int) ((float) (col1.b - col0.b) * u),
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
	printf("P6 %d %d %d\n", sw, sh, 255);

	int x, y;
	for (y=0; y<sh; y++) {
		for (x=0; x<sw; x++) {
			struct color c = get_color(x-(sw>>1), y-(sh>>1));
			putchar(c.r);
			putchar(c.g);
			putchar(c.b);
		}
	}

	return 0;
}

