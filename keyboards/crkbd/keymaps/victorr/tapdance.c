

#pragma once
// , - --
void td_commadash_each(qk_tap_dance_state_t *state, void *user_data) {
    if(state->weak_mods & MOD_MASK_GUI) {
        // send CMD-, immediately
        tap_code(KC_COMM);
        state->finished = true;
    }
    else if(state->count > 2) {
        tap_code(KC_MINS);
    }
}

void td_commadash_finished(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 1)
        tap_code(KC_COMM);
    else
        tap_code(KC_MINS);
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
    else if(state->count > 2) {
        tap_code16(KC_SLSH);
    }
}

void td_slash_finished(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 2)
        tap_code16(KC_BSLS);
    else
        tap_code16(KC_SLSH);
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
