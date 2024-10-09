
#ifndef TERMGUI_H
#define TERMGUI_H


/*** defines ***/

 /* font */
#define FONT_BOLD "\x1b[1m"

 /* color */
#define COLOR_RED "\x1b[1;38;5;167m"
#define COLOR_GREEN "\x1b[1;38;5;36m"
#define COLOR_VIOLET "\x1b[1;38;5;141m"
#define COLOR_GREY "\x1b[1;38;5;103m"
#define COLOR_WHITE "\x1b[37m"
#define COLOR_RESET "\x1b[0m"

 /* cursor */
#define CURSOR_RESET "\x1b[H"
#define CURSOR_HIDE "\x1b[?25l"
#define CURSOR_SHOW "\x1b[?25h"
#define CURSOR_RIGHT "\x1b[C"
#define CURSOR_LEFT "\x1b[D"

 /* screen*/
#define CLEAR_SCREEN "\x1b[2J"
#define CLEAR_RIGHT "\x1b[K"
#define CLEAR_LEFT "\x1b[1K"
#define CLEAR_TO_END "\x1b[0J"
#define CLEAR_FROM_START "\x1b[1J"


/*** macros ***/

extern void set_screen(void);
extern void reset_screen(void);


#endif

