#include "tapdance_core.h"

// Tap dance enums
enum {
    L_LAUNCH,
    R_LAUNCH
};

// Create an instance of 'td_tap_t' for the 'L_LAUNCH' tap dance.
static td_tap_t l_launch_tap_state = {
    .is_press_action = true,
    .state = TD_NONE,
    .keys = {
        .single_tap = TD_KEY_ALT(KC_SPC),
        .single_hold = TD_KEY_CTRL_SHIFT(KC_ESC),
        .double_tap = TD_KEY_NOOP,
        .double_hold = TD_KEY_GUI(KC_L),
        .double_single_tap = TD_KEY_NOOP
    }
};

// Create an instance of 'td_tap_t' for the 'R_LAUNCH' tap dance.
static td_tap_t r_launch_tap_state = {
    .is_press_action = true,
    .state = TD_NONE,
    .keys = {
        .single_tap = TD_KEY_CTRL_ALT_SHIFT(KC_B),
        .single_hold = TD_KEY_NOOP,
        .double_tap = TD_KEY_CTRL_SHIFT(KC_B),
        .double_hold = TD_KEY_NOOP,
        .double_single_tap = TD_KEY_NOOP
    }
};

// Wire up tap dance functions
tap_dance_action_t tap_dance_actions[] = {
    [L_LAUNCH] = ACTION_TAP_DANCE_FN_MAPS(&l_launch_tap_state),
    [R_LAUNCH] = ACTION_TAP_DANCE_FN_MAPS(&r_launch_tap_state)
};