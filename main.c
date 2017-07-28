#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include "termbox.h"
#include "uthash.h"
#include "mlbuf.h"
#include "mle.h"
#include <ncurses.h>
//#include <git2.h>
#include "common.h"

//implement tomorrow and add in dependecies
void print_loc(int x, int y){
       //might delete
        #ifdef DEBUG
	int oldx, oldy;
	getyx(stdscr, oldy, oldx);
	mvprintw(0, COLS - 20, "x: %d y: %d o: %d", x, y, y_offset);
	move(oldy, oldx);
	#endif


}



#ifdef _MSC_VER
#define snprintf sprintf_s
#define strcasecmp strcmpi
#endif

struct opts {
	char *path;
	char *commitspec;
	int C;
	int M;
	int start_line;
	int end_line;
	int F;
};
static void parse_opts(struct opts *o, int argc, char *argv[]);


editor_t _editor;

int main(int argc, char** argv) {
   
WINDOW * mainwin;
 if ( (mainwin = initscr()) == NULL ) {
	fprintf(stderr, "Error initialising ncurses.\n");
	exit(EXIT_FAILURE);
}
   mvaddstr(13, 33, "Welcome!");
    refresh();
    sleep(3);


    /*  Clean up after ourselves  */

    delwin(mainwin);
    endwin();
    refresh();

    //return EXIT_SUCCESS;









update_status("Press F4 to quit");

    memset(&_editor, 0, sizeof(editor_t));
    setlocale(LC_ALL, "");
    if (editor_init(&_editor, argc, argv) == MLE_OK) {
        if (!_editor.headless_mode) {
            tb_init();
            tb_select_input_mode(TB_INPUT_ALT);
        }
        editor_run(&_editor);
        if (_editor.headless_mode && _editor.active_edit) {
            buffer_write_to_fd(_editor.active_edit->buffer, STDOUT_FILENO, NULL);
        }
        editor_deinit(&_editor);
        if (!_editor.headless_mode) {
            tb_shutdown();
        }
    } else {
        editor_deinit(&_editor);
    }
    return _editor.exit_code;
}
//needs to be implemented tomorrow
void update_status(char *info) {
     int oldy, oldx; getyx(stdscr, oldy, oldx);
	
	attron(A_REVERSE);
	move(LINES - 1, 0);
	clrtoeol();
	printw(info);
	attroff(A_REVERSE);
	
	move(oldy, oldx);





}




