#ifndef XPAT_H
#define XPAT_H

#include <X11/Xlib.h>

typedef struct {
	_Bool danger;
	short row;
	short col;
} BPoint;

typedef struct {
	_Bool catch;
	int i;
	short row;
	short col;
} TPoint;

// xpat0.o
int relink(void*, void**);
int window();
int dispatch();
int sketch_event(XEvent*);
int export(XEvent*);
int import(XEvent*);
int peel();
int undo();
int keydrive(XEvent*);
int cleanup();
int sketch();
int warning();

// xpat1.o
int alloc(unsigned, unsigned, unsigned);
int dealloc(void*, void**);
int redraw_source();
int new_state(int);
int check_state();

#endif // XPAT_H
