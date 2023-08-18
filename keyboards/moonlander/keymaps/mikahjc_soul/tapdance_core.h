#pragma once

#include QMK_KEYBOARD_H

#define _MOD_CTRL  0x8
#define _MOD_ALT   0x4
#define _MOD_SHIFT 0x2
#define _MOD_GUI   0x1

#define TD_KEY_DEFINE(MODIFIER_FLAGS, KEYCODE) \
 { .modifiers = MODIFIER_FLAGS, .keycode = KEYCODE }
#define TD_KEY(KEYCODE)                     TD_KEY_DEFINE(0x0, KEYCODE)
#define TD_KEY_GUI(KEYCODE)                 TD_KEY_DEFINE(_MOD_GUI, KEYCODE)
#define TD_KEY_SHIFT(KEYCODE)               TD_KEY_DEFINE(_MOD_SHIFT, KEYCODE)
#define TD_KEY_SHIFT_GUI(KEYCODE)           TD_KEY_DEFINE(_MOD_SHIFT | _MOD_GUI, KEYCODE)
#define TD_KEY_ALT(KEYCODE)                 TD_KEY_DEFINE(_MOD_ALT, KEYCODE)
#define TD_KEY_ALT_GUI(KEYCODE)             TD_KEY_DEFINE(_MOD_ALT | _MOD_GUI, KEYCODE)
#define TD_KEY_ALT_SHIFT(KEYCODE)           TD_KEY_DEFINE(_MOD_ALT | _MOD_SHIFT, KEYCODE)
#define TD_KEY_ALT_SHIFT_GUI(KEYCODE)       TD_KEY_DEFINE(_MOD_ALT | _MOD_SHIFT | _MOD_GUI, KEYCODE)
#define TD_KEY_CTRL(KEYCODE)                TD_KEY_DEFINE(_MOD_CTRL, KEYCODE)
#define TD_KEY_CTRL_GUI(KEYCODE)            TD_KEY_DEFINE(_MOD_CTRL | _MOD_GUI, KEYCODE)
#define TD_KEY_CTRL_SHIFT(KEYCODE)          TD_KEY_DEFINE(_MOD_CTRL | _MOD_SHIFT, KEYCODE)
#define TD_KEY_CTRL_SHIFT_GUI(KEYCODE)      TD_KEY_DEFINE(_MOD_CTRL | _MOD_SHIFT | _MOD_GUI, KEYCODE)
#define TD_KEY_CTRL_ALT(KEYCODE)            TD_KEY_DEFINE(_MOD_CTRL | _MOD_ALT, KEYCODE)
#define TD_KEY_CTRL_ALT_GUI(KEYCODE)        TD_KEY_DEFINE(_MOD_CTRL | _MOD_ALT | _MOD_GUI, KEYCODE)
#define TD_KEY_CTRL_ALT_SHIFT(KEYCODE)      TD_KEY_DEFINE(_MOD_CTRL | _MOD_ALT | _MOD_SHIFT, KEYCODE)
#define TD_KEY_CTRL_ALT_SHIFT_GUI(KEYCODE)  TD_KEY_DEFINE(_MOD_CTRL | _MOD_ALT | _MOD_SHIFT | _MOD_GUI, KEYCODE)
#define TD_KEY_NOOP TD_KEY(KC_NO)

#define ACTION_TAP_DANCE_FN_ADVANCED_USER_DATA(user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset, user_data_ptr) \
    { .fn = {user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset}, .user_data = user_data_ptr, }
#define ACTION_TAP_DANCE_FN_MAPS(user_data_ptr) ACTION_TAP_DANCE_FN_ADVANCED_USER_DATA(NULL, finished_basic, reset_basic, user_data_ptr)

// Types for tap dance code
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    uint8_t modifiers;
    uint16_t keycode;
} td_key_t;

// If not using an action, make sure to assign it noop
void TD_NOOP(void) {}
typedef struct {
    void (*single_tap_action)(void);
    void (*single_tap_release)(void);
    void (*single_hold_action)(void);
    void (*single_hold_release)(void);
    void (*double_tap_action)(void);
    void (*double_tap_release)(void);
    void (*double_hold_action)(void);
    void (*double_hold_release)(void);
    void (*double_single_tap_action)(void);
    void (*double_single_tap_release)(void);
} td_actions_t;

typedef struct {
    td_key_t single_tap;
    td_key_t single_hold;
    td_key_t double_tap;
    td_key_t double_hold;
    td_key_t double_single_tap;
} td_tap_keys_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
    td_actions_t actions;
    td_tap_keys_t keys;
} td_tap_t;

void activate_modifier_key(td_key_t modifier_key) {
    if (modifier_key.modifiers & _MOD_CTRL)
        register_code(KC_LCTL);
    if (modifier_key.modifiers & _MOD_ALT)
        register_code(KC_LALT);
    if (modifier_key.modifiers & _MOD_SHIFT)
        register_code(KC_LSFT);
    if (modifier_key.modifiers & _MOD_GUI)
        register_code(KC_LGUI);
    register_code(modifier_key.keycode);
}

void release_modifier_key(td_key_t modifier_key) {
    unregister_code(modifier_key.keycode);
    if (modifier_key.modifiers & _MOD_CTRL)
        unregister_code(KC_LCTL);
    if (modifier_key.modifiers & _MOD_ALT)
        unregister_code(KC_LALT);
    if (modifier_key.modifiers & _MOD_SHIFT)
        unregister_code(KC_LSFT);
    if (modifier_key.modifiers & _MOD_GUI)
        unregister_code(KC_LGUI);
}

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

void finished_basic(tap_dance_state_t *state, void *user_data) {
    td_tap_t* dance_data = (td_tap_t*)user_data;
    dance_data->state = cur_dance(state);
    switch (dance_data->state) {
        case TD_SINGLE_TAP: activate_modifier_key(dance_data->keys.single_tap); break;
        case TD_SINGLE_HOLD: activate_modifier_key(dance_data->keys.single_hold); break;
        case TD_DOUBLE_TAP: activate_modifier_key(dance_data->keys.double_tap); break;
        case TD_DOUBLE_HOLD: activate_modifier_key(dance_data->keys.double_hold); break; // Unconfigured
        case TD_DOUBLE_SINGLE_TAP: activate_modifier_key(dance_data->keys.double_single_tap); break; // Unconfigured
        default: break;
    }
}

void reset_basic(tap_dance_state_t *state, void *user_data) {
    td_tap_t* dance_data = (td_tap_t*)user_data;
    switch (dance_data->state) {
        case TD_SINGLE_TAP: release_modifier_key(dance_data->keys.single_tap); break;
        case TD_SINGLE_HOLD: release_modifier_key(dance_data->keys.single_hold); break;
        case TD_DOUBLE_TAP: release_modifier_key(dance_data->keys.double_tap); break;
        case TD_DOUBLE_HOLD: release_modifier_key(dance_data->keys.double_hold); break; // Unconfigured
        case TD_DOUBLE_SINGLE_TAP: release_modifier_key(dance_data->keys.double_single_tap); break; // Unconfigured
        default: break;
    }
    dance_data->state = TD_NONE;
}

void finished(tap_dance_state_t *state, void *user_data) {
    td_tap_t* dance_data = (td_tap_t*)user_data;
    dance_data->state = cur_dance(state);
    switch (dance_data->state) {
        case TD_SINGLE_TAP: dance_data->actions.single_tap_action(); break;
        case TD_SINGLE_HOLD: dance_data->actions.single_hold_action(); break;
        case TD_DOUBLE_TAP: dance_data->actions.double_tap_action(); break;
        case TD_DOUBLE_HOLD: dance_data->actions.double_hold_action(); break; // Unconfigured
        case TD_DOUBLE_SINGLE_TAP: dance_data->actions.double_single_tap_action(); break; // Unconfigured
        default: break;
    }
}

void reset(tap_dance_state_t *state, void *user_data) {
    switch (((td_tap_t*)user_data)->state) {
        case TD_SINGLE_TAP: ((td_tap_t*)user_data)->actions.single_tap_release(); break;
        case TD_SINGLE_HOLD: ((td_tap_t*)user_data)->actions.single_hold_release(); break;
        case TD_DOUBLE_TAP: ((td_tap_t*)user_data)->actions.double_tap_release(); break; // Unconfigured
        case TD_DOUBLE_HOLD: ((td_tap_t*)user_data)->actions.double_hold_release(); break;
        case TD_DOUBLE_SINGLE_TAP: ((td_tap_t*)user_data)->actions.double_single_tap_release(); break; // Unconfigured
        default: break;
    }
    ((td_tap_t*)user_data)->state = TD_NONE;
}
