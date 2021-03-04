#include <stdio.h>
#include <stdlib.h>
#include "xpat.h"

#define LEFT_SOURCE	pos[i].danger = 0;	\
					pos[i].row = i;		\
					pos[i].col = 0;

#define RIGHT_SOURCE	pos[i].danger = 0;	\
						pos[i].row = i - CN/2;	\
						pos[i].col = NX - 1;

#define NEW_STATE	if ((abs(i_col - pos[j].col) == abs(i_row - pos[j].row)))	\
						MX[i][j] = MX[j][i] = 1;								\
					else														\
						MX[i][j] = MX[j][i] = 0;

static BPoint* pos;
static unsigned NX;
static unsigned NY;
static unsigned CN;
static _Bool** MX;

int alloc(unsigned _nx, unsigned _ny, unsigned _cn) {
	void* p;
	void** b;
	int i;

	NX = _nx; NY = _ny; CN = _cn;

	p = calloc(CN, sizeof(BPoint));
	b = calloc(NY, sizeof(void*));
	for (i = 0; i < NY; i++) { b[i] = calloc(NX, sizeof(unsigned long)); }
	relink(p, b);

	MX = calloc(CN, sizeof(_Bool*));
	for (i = 0; i < CN; i++) { MX[i] = calloc(CN, sizeof(_Bool)); }

	pos = (BPoint*)p;
	for (i = 0; i < CN/2; i++) { LEFT_SOURCE }
	for (; i < CN; i++) { RIGHT_SOURCE }

	return(0);
}

int dealloc(void* p, void** b) {
	int i;

	for (i = 0; i < NY; i++) {free(b[i]); }
	free(p);
	free(b);

	for (i = 0; i < CN; i++) { free(MX[i]); }
	free(MX);

	return(0);
}

int redraw_source() {
	int i, j;

	cleanup();
	for (i = 0; i < CN/2; i++) { LEFT_SOURCE }
	for (; i < CN; i++) { RIGHT_SOURCE }

	for (i = 0; i < CN; i++)
		for (j = 0; j < CN; j++) { MX[i][j] = 0; }
	sketch();

	return(0);
}

int new_state(int i) {
	short i_col = pos[i].col;
	short i_row = pos[i].row;
	int j;

	for (j = 0; j < i; j++) { NEW_STATE }
	for (++j; j < CN; j++) { NEW_STATE }
	check_state();

	return(0);
}

int check_state() {
	int i, j;

	for (i = 0; i < CN; i++) {
		pos[i].danger = 0;

		for (j = 0; j < CN; j++)
			if (MX[i][j]) { pos[i].danger = 1; break; }
	}

	return(0);
}
