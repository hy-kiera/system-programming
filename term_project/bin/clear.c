/* clear : bring the command line on top of the terminal */
#include <unistd.h> // STDOUT_FIENO

#include "../headers/cmds.h"

void clear(void){
    /* ANSI Escape Sequences
       (http://ascii-table.com/ansi-escape-sequences.php)
       - Cursor Position
            Esc[Line;ColumnH
            : Moves the cursor to the specified position(coordinates)
       - Erase Display
            Esc[2J
            : Clears the screen and moves the cursor to the home position (line 0, column 0)
    */
    const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J"; // move the cursor to line 1, column 1 and clear the screen
    write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12); // write CLEAR_SCREEN_ANSI on the current terminal
}
