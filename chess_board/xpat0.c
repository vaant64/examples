#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/keysymdef.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "xpat.h"

#define COLOR_BACK 0x00FFFF
#define COLOR_CATCH 0xFFFF00

#define CLOCK_LIMIT 3500

#define A 4
#define STEP1 0.1
#define STEP2 0.0125	// ((STEP1)/8)

static Display* dpy;
static GC gc[3];
static Window root;
static Window** box;

static int X0 = 0;
static int Y0 = 0;
static unsigned NX = 8;
static unsigned NY = 8;
static unsigned CN = 14;
static char* mark = "B";
static XRectangle cell;

static BPoint* pos;
static TPoint take = { .catch = 0 };
static double t1 = 0;
static double t2 = 0;

int relink(void* p, void** b) {
	pos = (BPoint*)p;
	box = (Window**)b;
	return(0);
}

int window() {
	static unsigned XSP = 4;
	static unsigned YSP = 4;
	static unsigned BW = 32;
	static unsigned BH = 32;

	int x, y;
	unsigned w, h;
	int dx, dy;
	int i, j;

	int src;
	int depth;
	XSetWindowAttributes attr;
	unsigned long amask;
	XSizeHints hint;
	XFontStruct* fn;
	char* fontname = "9x15";

	src = DefaultScreen(dpy);
	depth = DefaultDepth(dpy, src);
	gc[0] = DefaultGC(dpy, src);

	if (!(fn = XLoadQueryFont(dpy, fontname)))
		return(puts("Incorrect FontStruct id"));
	XSetFont(dpy, gc[0], fn->fid);

	cell.width = fn->max_bounds.width;
	cell.height = fn->max_bounds.ascent + fn->max_bounds.descent;
	cell.x = (BW - fn->max_bounds.width) / 2;
	cell.y = BH/2 + (fn->max_bounds.ascent - fn->max_bounds.descent)/2;

	amask = (CWOverrideRedirect | CWBackPixel | CWEventMask);
	attr.override_redirect = False;
	attr.background_pixel = WhitePixel(dpy, src);
	attr.event_mask = (ButtonPressMask | ButtonReleaseMask | KeyPressMask);
	w = NX*BW + (NX + 1)*XSP + 2*NX + 2;
	h = NY*BH + (NY + 1)*YSP + 4*NY;
	x = X0; y = Y0;
	root = XCreateWindow(dpy, DefaultRootWindow(dpy), x, y, w, h, 1, depth,
							InputOutput, CopyFromParent, amask, &attr);

	hint.flags = (PMinSize | PMaxSize | PPosition);
	hint.min_width = hint.max_width = w;
	hint.min_height = hint.max_height = h;
	hint.x = x; hint.y = y;
	XSetNormalHints(dpy, root, &hint);

	amask = (CWOverrideRedirect | CWBackPixel | CWEventMask);
	attr.override_redirect = True;
	attr.background_pixel = COLOR_BACK;
	attr.event_mask = (ExposureMask);
	w = BW; h = BH;
	dx = w + XSP + 2;
	dy = h + YSP + 4;
	for (i = 0, y = YSP; i < NY; i++, y += dy) {
		for (j = 0, x = XSP ; j < NX; j++, x += dx) {
			box[i][j] = XCreateWindow(dpy, root, x, y, w, h, 1,  depth,
										InputOutput, CopyFromParent, amask, &attr);
		}
	}

	XMapWindow(dpy, root);
	XMapSubwindows(dpy, root);
	for (i = 0; i < NY; i++) {
		for (j = 0; j < NX; j++) { XMapSubwindows(dpy, box[i][j]); }
	}
	XStoreName(dpy, root, "xpat");

	gc[1] = XCreateGC(dpy, root, 0, 0);
	XCopyGC(dpy, gc[0], GCFont, gc[1]);
	XSetForeground(dpy, gc[1], COLOR_BACK);

	gc[2] = XCreateGC(dpy, root, 0, 0);
	XCopyGC(dpy, gc[0], GCFont, gc[2]);
	XSetForeground(dpy, gc[2], COLOR_CATCH);

	return(0);
}

int dispatch() {
	XEvent event;
	long emask = (ButtonPressMask | ButtonReleaseMask | KeyPressMask | ExposureMask);

	int flag = 0;
	clock_t ck = clock();

	while(!flag) {
		if ((clock() - ck) > CLOCK_LIMIT) {
			XCheckMaskEvent(dpy, emask, &event);

			switch(event.type) {
			case Expose:
				// putchar('E'); fflush(stdout);
				sketch_event(&event);
				break;

			case ButtonPress:
				// putchar('P'); fflush(stdout);
				export(&event);
				break;

			case ButtonRelease:
				// putchar('R'); fflush(stdout);
				if (take.catch) { import(&event); /* warning_old(); */ }
				break;

			case KeyPress:
				// putchar('K'); fflush(stdout);
				if (!take.catch) { flag = keydrive(&event); /* warning_old(); */ }
				break;

			default:
				break;
			}

			warning();
			ck = clock();
		}
	}
	return(0);
}

int sketch_event(XEvent* ev) {
	int i;
	for (i = 0; i < CN; i++) {
		if (ev->xexpose.window == box[pos[i].row][pos[i].col]) {
			XDrawString(dpy, box[pos[i].row][pos[i].col],
							gc[0], cell.x, cell.y, mark, 1);
		}
	}
	return(0);
}

int export(XEvent* ev) {
	int i;

	for (i = 0; i < CN; i++)
		if (ev->xbutton.subwindow == box[pos[i].row][pos[i].col]) { break; }
	if (i == CN) { return(CN); }

	take.catch = 1;
	take.i	= i;
	take.row = pos[i].row;
	take.col = pos[i].col;

	XSetWindowBackground(dpy, box[take.row][take.col], COLOR_CATCH);
	XClearWindow(dpy, box[take.row][take.col]);
	if (!pos[take.i].danger)
		XDrawString(dpy, box[take.row][take.col], gc[0], cell.x, cell.y, mark, 1);

	return(0);
}

int import(XEvent* ev) {
	int i, j, k;
	unsigned long ev_subw = ev->xbutton.subwindow;

	k = 0;	// flag
	for (i = 0; i < NY; i++) {
		for (j = 0; j < NX; j++) {
			if (ev_subw == box[i][j]) { k = 1; break; }
		}
		if (k) { break; }
	}
	if (i == NY) { undo(); return(NY); }

	for (k = 0; k < CN; k++) {
		if (box[i][j] == box[pos[k].row][pos[k].col]) { break; }
	}
	if (k != CN) { undo(); return(CN); }

	XDrawString(dpy, box[i][j], gc[0], cell.x, cell.y, mark, 1);
	peel();

	pos[take.i].row = i;
	pos[take.i].col = j;

	new_state(take.i);

	return(0);
}

int peel() {
	XSetWindowBackground(dpy, box[take.row][take.col], COLOR_BACK);
	XClearWindow(dpy, box[take.row][take.col]);
	take.catch = 0;
	return(0);
}

int undo() {
	peel();
	if (!pos[take.i].danger)
		XDrawString(dpy, box[take.row][take.col], gc[0], cell.x, cell.y, mark, 1);
	return(0);
}

int keydrive(XEvent* ev) {
	int flag = 0;
	KeySym sym;
	XLookupString((XKeyEvent*)ev, NULL, 0, &sym, NULL);

	switch(sym) {
	case XK_Escape:
		flag = 1;
		break;

	case XK_F10:
		redraw_source();
		break;

	default:
		break;
	}

	return(flag);
}

int cleanup() {
	int i;
	for (i = 0; i < CN; i++) {
		XSetWindowBackground(dpy, box[pos[i].row][pos[i].col], COLOR_BACK);
		XClearWindow(dpy, box[pos[i].row][pos[i].col]);
	}
	return(0);
}

int sketch() {
	int i;
	for (i = 0; i < CN; i++) {
		XDrawString(dpy, box[pos[i].row][pos[i].col],
				gc[0], cell.x, cell.y, mark, 1);
	}
	return(0);
}

int warning() {
	int i;
	int sh1;
	int sh2;

	sh1 = (int)(A*sin(t2)*sin(t1));
	t1 += STEP1;
	t2 += STEP2;
	sh2 = (int)(A*sin(t2)*sin(t1));

	for (i = 0; i < CN; i++) {
		if (pos[i].danger) {

			if ((take.catch) && (take.i == i)) {
				XDrawString(dpy, box[pos[i].row][pos[i].col],
							gc[2], cell.x, cell.y - sh1, mark, 1); }
			else {
				XDrawString(dpy, box[pos[i].row][pos[i].col],
							gc[1], cell.x, cell.y - sh1, mark, 1); }


			XDrawString(dpy, box[pos[i].row][pos[i].col],
						gc[0], cell.x, cell.y - sh2, mark, 1);
		}
	}

	return(0);
}

int main(int argc, char* argv[]) {
	if (argc < 2)
		fprintf(stderr, "Default: xpat %dx%d+%d+%d\n", NX, NY, X0, Y0);

	XParseGeometry(argv[1], &X0, &Y0, &NX, &NY);

	alloc(NX, NY, CN);
	dpy = XOpenDisplay(NULL);
	if (window() > 0)
		return(1);

	dispatch();

	XDestroySubwindows(dpy, root);
	XDestroyWindow(dpy, root);
	XCloseDisplay(dpy);
	dealloc(pos, (void**)box);

	return(0);
}