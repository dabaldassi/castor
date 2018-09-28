#ifndef FONT_H
#define FONT_H

#define FONT_PATH /usr/share/fonts/truetype/freefont/
#define STR(X,Y) #X#Y
#define FONT_BUILD(X,Y) STR(X,Y) 

#define CS_REGULAR FONT_BUILD(FONT_PATH, cs_regular.ttf)
#define FREE_MONO_BOLD_OBLIQUE FONT_BUILD(FONT_PATH, FreeMonoBoldOblique.ttf)
#define FREE_MONO_BOLD FONT_BUILD(FONT_PATH, FreeMonoBold.ttf)
#define FREE_MONO FONT_BUILD(FONT_PATH, FreeMono.ttf)
#define FREE_SANS_BOLD_OBLIQUE FONT_BUILD(FONT_PATH, FreeSansBoldOblique.ttf)
#define FREE_SANS FONT_BUILD(FONT_PATH, FreeSans.ttf)
#define FREE_SANS_BOLD FONT_BUILD(FONT_PATH, FreeSansBold.ttf)
#define FREE_SANS_OBLIQUE FONT_BUILD(FONT_PATH, FreeSansOblique.ttf)
#define FREE_SERIF FONT_BUILD(FONT_PATH, FreeSerif.ttf)
#define FREE_SERIF_BOLD FONT_BUILD(FONT_PATH, FreeSerifBold.ttf)
#define FREE_SERIF_BOLD_ITALIC FONT_BUILD(FONT_PATH, FreeSerifBoldItalic.ttf)
#define FREE_SERIF_ITALIC FONT_BUILD(FONT_PATH, FreeSerifItalic.ttf)



#endif /* FONT_H */
