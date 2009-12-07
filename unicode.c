/* unicode (c) 2006 
 * Joachim Breitner <mail@joachim-breitner.de>
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation.  No representations are made about the suitability of this
 * software for any purpose.  It is provided "as is" without express or 
 * implied warranty.
 *
 */

#include <X11/Xft/Xft.h>

#include "unicode-names.h"
#include "screenhack.h"

#define NUM_FONTS 2


struct unicode_state {
	Bool blank;

        XftFont*	fonts[NUM_FONTS];
	XftFont*	tfont;
	FcChar32	font_count[NUM_FONTS];
	XftDraw*	draw;
	XftColor	font_color;
};

static void *
unicode_init (Display *dpy, Window window)
{
	struct unicode_state *state = malloc(sizeof(struct unicode_state));
	state->blank = True;

	Colormap cmap;
	XWindowAttributes xgwa;
	XGetWindowAttributes (dpy, window, &xgwa);
	int i;

	cmap = xgwa.colormap;

	state->fonts[0] = XftFontOpen(dpy, 0, 
		XFT_FAMILY,  XftTypeString, "DejaVu Sans",
		XFT_PIXEL_SIZE, XftTypeInteger, xgwa.height-100,
		NULL
		);
	state->fonts[1] = XftFontOpen(dpy, 0, 
		XFT_FAMILY,  XftTypeString, "FreeSans",
		XFT_PIXEL_SIZE, XftTypeInteger, xgwa.height-100,
		NULL
		);
	state->tfont = XftFontOpen(dpy, 0, 
		XFT_FAMILY,  XftTypeString, "FreeSans",
		XFT_PIXEL_SIZE, XftTypeInteger, 40,
		NULL
		);
	for (i = 0; i < NUM_FONTS; i++) {
		state->font_count[i] = FcCharSetCount(state->fonts[i]->charset);
		printf("Font count: %d\n",state->font_count[i]);
	}

	state->draw = XftDrawCreate(dpy, window, xgwa.visual, cmap); 
	XftColorAllocName(dpy, xgwa.visual ,cmap,"black",&state->font_color);

	return state;
}

/* does a binary search on unicode_names */
/* (From gucharmap code) */
static inline const char *
get_unicode_data_name (FcChar32 uc)
{
	unsigned long min = 0;
	unsigned long mid;
	unsigned long max = (sizeof(unicode_names)/sizeof(unicode_names[0])) - 1;

	if (uc < unicode_names[0].index || uc > unicode_names[max].index)
		return "Out of range";

	while (max >= min)
	{
		mid = (min + max) / 2;
		if (uc > unicode_names[mid].index)
			min = mid + 1;
		else if (uc < unicode_names[mid].index)
			max = mid - 1;
		else
			return unicode_name_get_name(&unicode_names[mid]);
	}

	return "somethings wrong";
}


static unsigned long
unicode_draw (Display *dpy, Window win, struct unicode_state *state) {
	XGlyphInfo	extents;
	FcChar32	ucs4;
	FcChar32	map[FC_CHARSET_MAP_SIZE];
	FcChar32	next;
	FcChar32	pickn;
	FcChar32	pickc;
	FcChar32	pick;	
	char		name[100];
	int		font;

	if (state->blank) {
		XWindowAttributes xgwa;
		XGetWindowAttributes (dpy, win, &xgwa);

		font = random() % NUM_FONTS;

		pickn = random() % state->font_count[font];	

		pickc = 0;
		for (ucs4 = FcCharSetFirstPage (state->fonts[font]->charset, map, &next);
		     ucs4 != FC_CHARSET_DONE;
		     ucs4 = FcCharSetNextPage (state->fonts[font]->charset, map, &next))
		{
		    int	    i, j;
		    for (i = 0; i < FC_CHARSET_MAP_SIZE; i++)
			if (map[i])
			    for (j = 0; j < 32; j++)
				if (map[i] & (1 << j))
				    if (pickc++ == pickn) 
					pick = ucs4 + i * 32 + j;
		}
		

		sprintf(name,"U+%04X: ",pick);
		strcat(name, get_unicode_data_name(pick));

		XftTextExtents32(dpy,state->fonts[font],&pick,1,&extents); 
		XftDrawString32(state->draw,&state->font_color,state->fonts[font],
			xgwa.width/2  - extents.width/2  + extents.x,
			xgwa.height/2 - extents.height/2 + extents.y,
			&pick,1); 

		XftDrawStringUtf8(state->draw,&state->font_color,state->tfont,
			5,
			xgwa.height - 5,
			name,strlen(name)); 
		XSync (dpy, False);

		state->blank = False;
		return (7*1000*1000);
	} else {
		XClearWindow (dpy, win);
		XSync (dpy, False);
		state->blank = True;
		return (1000*1000);
	}

}

static void
unicode_reshape (Display *dpy, Window window, void *state,
	         unsigned int width, unsigned int height) {
}		

static Bool
unicode_event (Display *dpy, Window window, void *state,
	         XEvent *event) {
		 return False;
}		

static void
unicode_free (Display *dpy, Window window, void *state) {
}		



char *progclass = "Unicode";

static char *unicode_defaults [] = {
  ".background: white",
  "*delay:	7",
  0
};

static XrmOptionDescRec unicode_options [] = {
  { "-delay",           ".delay",               XrmoptionSepArg, 0 },
  { 0, 0, 0, 0 }
};

XSCREENSAVER_MODULE("Unicode",unicode)
