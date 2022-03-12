

#pragma once

// T_SLSH
//   * C-/
//   1 / 2 \ 3 //
void td_slash_each(qk_tap_dance_state_t *state, void *user_data) {
    /* if(state->pressed) */
    /*     return; */
    if(state->weak_mods & MOD_MASK_CTRL) {
        register_code(KC_SLSH);
        unregister_code(KC_SLSH);
        state->finished = true;
        // unregister_code(KC_LCTL);
        // SEND_STRING("undo\n");
        // there will be no call to finished
    }
    else if(state->count == 3) {
        register_code16(KC_SLSH); unregister_code16(KC_SLSH);
        register_code16(KC_SLSH); unregister_code16(KC_SLSH);
        state->finished = true;
        // SEND_STRING("3 taps\n");
        // there will be no call to finish
    }
    // SEND_STRING("each ignoring\n");
}

void td_slash_finished(qk_tap_dance_state_t *state, void *user_data) {
    switch(state->count) {
    case 1:
        register_code16(KC_SLSH); unregister_code16(KC_SLSH);
        // SEND_STRING("finish 1\n");
        break;
    case 2:
        register_code16(KC_BSLS); unregister_code16(KC_BSLS);
        // SEND_STRING("finish 2\n");
        break;
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
