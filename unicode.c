/* unicode (c) 2006,2009
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

#define NUM_FONTS 3


struct unicode_state {
	Bool blank;

        XftFont*	fonts[NUM_FONTS];
	XftFont*	tfont;
	XftDraw*	draw;
	XftColor	font_color;
	XColor		bg_color;
	unsigned	delay;
};

static void *
unicode_init (Display *dpy, Window window)
{
	struct unicode_state *state = malloc(sizeof(struct unicode_state));
	Colormap cmap;
	XWindowAttributes xgwa;
	XColor color;
	XRenderColor font_color;
	char *extra;

	XGetWindowAttributes (dpy, window, &xgwa);
	state->blank = True;

	cmap = xgwa.colormap;

	state->fonts[0] = XftFontOpen(dpy, 0,
		XFT_FAMILY,  XftTypeString, "Open Symbol",
		XFT_PIXEL_SIZE, XftTypeInteger, xgwa.height-100,
		NULL
		);
	state->fonts[1] = XftFontOpen(dpy, 0,
		XFT_FAMILY,  XftTypeString, "FreeSans",
		XFT_PIXEL_SIZE, XftTypeInteger, xgwa.height-100,
		NULL
		);
	extra = get_string_resource(dpy, "font", "Font");
	state->fonts[2] = extra ?
		XftFontOpen(dpy, 0,
			    XFT_FAMILY,  XftTypeString, extra,
			    XFT_PIXEL_SIZE, XftTypeInteger, xgwa.height-100,
			    NULL
		) : NULL;

	state->tfont = XftFontOpen(dpy, 0,
		XFT_FAMILY,  XftTypeString, "FreeSans",
		XFT_PIXEL_SIZE, XftTypeInteger, 40,
		NULL
		);

	state->draw = XftDrawCreate(dpy, window, xgwa.visual, cmap); 
	state->bg_color.pixel = get_pixel_resource(dpy, cmap, "background", "Background");
	XQueryColor(dpy, cmap, &state->bg_color);

	color.pixel = get_pixel_resource(dpy, cmap, "foreground", "Foreground");
	XQueryColor(dpy, cmap, &color);

	state->delay = get_seconds_resource(dpy, "delay", "Delay")*1000*1000;
	font_color.red = color.red;
	font_color.green = color.green;
	font_color.blue = color.blue;
	font_color.alpha = 0xFFFF;

	XftColorAllocValue(dpy, xgwa.visual, cmap, &font_color, &state->font_color);
	XSetWindowBackground(dpy, window, state->bg_color.pixel);
	XClearWindow (dpy, window);

	return state;
}

static unsigned long
unicode_draw (Display *dpy, Window win, void *void_state) {
	XGlyphInfo	extents;
	FcChar32	pick;
	char		name[100];
	int		font;
	int             i;
	struct unicode_state *state = (struct unicode_state *)void_state;
	unsigned long unicode_names_length
		= (sizeof(unicode_names)/sizeof(unicode_names[0]));
	const UnicodeName* nameEntry;

	if (state->blank) {
		XWindowAttributes xgwa;
		XGetWindowAttributes (dpy, win, &xgwa);

		/* Find a unicode character that is contained in one of the fonts
		   We try 100 random points before sleeping, to avoid an endless cycle */
		for (i = 0; i < 100; i++) {
			nameEntry = &unicode_names[random() % unicode_names_length];
			pick = nameEntry->index;
			/* printf("Trying U+%04X\n", pick); */

			for (font = 0; font < NUM_FONTS; font++) {
				if (state->fonts[font] &&
				    XftCharExists (dpy, state->fonts[font], pick)) break;
			}
			if (font < NUM_FONTS) break;
		}
		if (i == 100) return (1000*1000);

		/* printf("Picked font %d, U+%04X\n", font, pick); */
		sprintf(name,"U+%04X: ", pick);
		strcat(name, unicode_name_get_name(nameEntry));

		XftTextExtents32(dpy,state->fonts[font],&pick,1,&extents); 
		XftDrawString32(state->draw,&state->font_color,state->fonts[font],
			xgwa.width/2  - extents.width/2  + extents.x,
			xgwa.height/2 - extents.height/2 + extents.y,
			&pick,1); 

		XftDrawStringUtf8(state->draw,&state->font_color,state->tfont,
			5,
			xgwa.height - 5,
			(unsigned char *)name,strlen(name)); 
		XSync (dpy, False);

		state->blank = False;
		return (state->delay);
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

static char const *unicode_defaults [] = {
  ".background: white",
  ".foreground: black",
  "*delay:	7",
  0
};

static XrmOptionDescRec unicode_options [] = {
  { "-delay",           ".delay",               XrmoptionSepArg, 0 },
  { "-font",		".font",		XrmoptionSepArg, 0 },
  { "-foreground",      ".foreground",          XrmoptionSepArg, 0 },
  { "-background",      ".background",          XrmoptionSepArg, 0 },
  { 0, 0, 0, 0 }
};

XSCREENSAVER_MODULE("Unicode",unicode)
