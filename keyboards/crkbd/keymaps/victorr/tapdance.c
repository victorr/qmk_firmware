

#pragma once
// . ; ..
void td_dotsemicolon_each(qk_tap_dance_state_t *state, void *user_data) {
    // if(state->weak_mods & MOD_MASK_CTRL) {
    //     // send CMD-. immediately
    //     tap_code(KC_DOT);
    //     state->finished = true;
    // }
    // else {
        switch(state->count) {
        case 1:
            tap_code(KC_DOT);
            break;
        case 2:
            tap_code(KC_BSPC);
            tap_code(KC_SCLN);
            break;
        case 3:
            tap_code(KC_BSPC);
            tap_code(KC_DOT);
            tap_code(KC_DOT);
            break;
        default:
            tap_code(KC_DOT);
        }
    // }
}

// , - --
void td_commadash_each(qk_tap_dance_state_t *state, void *user_data) {
    if(state->weak_mods & MOD_MASK_GUI) {
        // send CMD-, immediately
        tap_code(KC_COMM);
        state->finished = true;
    }
    else {
        switch(state->count) {
        case 1:
            tap_code(KC_COMM);
            break;
        case 2:
            tap_code(KC_BSPC);
            tap_code(KC_MINS);
            // SEND_STRING("\ncase 2\n");
            break;
        default:
            tap_code(KC_MINS);
            //SEND_STRING("\ndefault\n");
        }
    }
}

void td_commadash_finished(qk_tap_dance_state_t *state, void *user_data) {
    // if(state->count > 2) {
    //     tap_code(KC_MINS);
    //     SEND_STRING("\nfinished\n");
    // }
}

void td_commadash_reset(qk_tap_dance_state_t *state, void *user_data) {
}

// T_SLSH
//   * C-/
//   1 / 2 \ 3 //
void td_slash_each(qk_tap_dance_state_t *state, void *user_data) {
    if(state->weak_mods & MOD_MASK_CTRL) {
        tap_code(KC_SLSH);
        state->finished = true;
    }
    else {
        switch(state->count) {
        case 1:
            tap_code(KC_SLSH);
            break;
        case 2:
            tap_code(KC_BSPC);
            tap_code(KC_BSLS);
            break;
        case 3:
            tap_code(KC_BSPC);
            tap_code(KC_SLSH);
            tap_code(KC_SLSH);
            break;
        default:
            tap_code(KC_SLSH);
        }
    }
}

void td_slash_finished(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        // Probably typing a // comment
        tap_code16(KC_SPC);
    }
}

void td_slash_reset(qk_tap_dance_state_t *state, void *user_data) {
    // SEND_STRING("reset\n");
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void td_debug_each(qk_tap_dance_state_t *state, void *user_data) {
    SEND_STRING("each");

    /* if(state->oneshot_mods & MOD_MASK_SHIFT) { */
    /*     SEND_STRING(" *one shot control* \n"); */
    /* } */
    if(state->interrupted)
        SEND_STRING(" interrupted\n");
    if(state->pressed)
        SEND_STRING(" pressed\n");
    if(state->interrupted)
        SEND_STRING(" finished\n");
    SEND_STRING("\n");
}

void td_debug_finished(qk_tap_dance_state_t *state, void *user_data) {
    SEND_STRING("finished\n");
    // for(int i = 0; i<state->count; i++)
    //     SEND_STRING("o");
    // SEND_STRING("\n");
}

void td_debug_reset(qk_tap_dance_state_t *state, void *user_data) {
    SEND_STRING("reset\n");
}
