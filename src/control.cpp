#include <assert.h>

#include "control.hpp"
#include "io.hpp"
#include "utils.hpp"

User_Input_Type get_user_input(char *c) {
    assert(c);
    while (1) {
        *c = get_char();
        if (ESCSEQ(*c)) {
            int next0 = get_char();
            if (CSI(next0)) {
                int next1 = get_char();
                if (next1 >= '0' && next1 <= '9') { // Modifier key detected
                    int semicolon = get_char();
                    if (semicolon == ';') {
                        int modifier = get_char();
                        int arrow_key = get_char();
                        if (modifier == '2') { // Shift modifier
                            switch (arrow_key) {
                                case 'A': *c = UP_ARROW;    return USER_INPUT_TYPE_SHIFT_ARROW;
                                case 'B': *c = DOWN_ARROW;  return USER_INPUT_TYPE_SHIFT_ARROW;
                                case 'C': *c = RIGHT_ARROW; return USER_INPUT_TYPE_SHIFT_ARROW;
                                case 'D': *c = LEFT_ARROW;  return USER_INPUT_TYPE_SHIFT_ARROW;
                                default: return USER_INPUT_TYPE_UNKNOWN;
                            }
                        }
                    }
                    return USER_INPUT_TYPE_UNKNOWN;
                } else { // Regular arrow key
                    switch (next1) {
                        case DOWN_ARROW:
                        case RIGHT_ARROW:
                        case LEFT_ARROW:
                        case UP_ARROW:
                            *c = next1;
                            return USER_INPUT_TYPE_ARROW;
                        default:
                            return USER_INPUT_TYPE_UNKNOWN;
                    }
                }
            } else { // [ALT] key
                *c = next0;
                return USER_INPUT_TYPE_ALT;
            }
        }
        else if (*c == CTRL_N || *c == CTRL_P || *c == CTRL_G ||
                 *c == CTRL_D || *c == CTRL_U || *c == CTRL_V ||
                 *c == CTRL_W || *c == CTRL_O || *c == CTRL_L ||
                 *c == CTRL_F || *c == CTRL_B || *c == CTRL_A ||
                 *c == CTRL_E || *c == CTRL_S || *c == CTRL_Q) {
            return USER_INPUT_TYPE_CTRL;
        }
        else return USER_INPUT_TYPE_NORMAL;
    }
    return USER_INPUT_TYPE_UNKNOWN;
}

