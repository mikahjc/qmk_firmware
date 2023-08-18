#include QMK_KEYBOARD_H
#include "layout_tapdance.h"
#include "user_song_list.h"



uint8_t top_row_led_indices[] = {0, 5, 10, 15, 20, 25, 30};
float zelda_puzzle[][2] = SONG(ZELDA_PUZZLE);

enum custom_keycodes {
	SS_EQGT = SAFE_RANGE,
	SS_HYGT,
    MUS_ZELDA_PUZZLE
};

void send_on_press(keyrecord_t *record, const char* to_send) {
	if (record->event.pressed) {
		SEND_STRING(to_send);
	}
	return;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
	case SS_EQGT:
		send_on_press(record, "=>");
		break;
	case SS_HYGT:
		send_on_press(record, "->");
		break;
    case MUS_ZELDA_PUZZLE:
        if (record->event.pressed) {
            PLAY_SONG(zelda_puzzle);
        }
        break;
	}
	return true;
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    RGB_MATRIX_INDICATOR_SET_COLOR(top_row_led_indices[get_highest_layer(layer_state|default_layer_state)], 255, 255, 255);
    return false;
}
		

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_moonlander(
			KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_LEFT,		KC_RGHT, KC_6, KC_7, KC_8, KC_9, KC_0, TO(4),
			KC_TAB, KC_Q, KC_W, KC_L, KC_D, KC_P, KC_EQL, 		KC_MINS, KC_K, KC_M, KC_U, KC_Y, KC_SCLN, KC_BSLS,
			KC_ESC, KC_A, KC_S, KC_R, KC_T, KC_G, KC_LBRC, 		KC_RBRC, KC_F, KC_N, KC_E, KC_I, LT(2,KC_O), LGUI_T(KC_QUOT),
			SC_LSPO, KC_Z, KC_X, KC_C, KC_V, KC_J,				 KC_B, KC_H, KC_COMM, KC_DOT, KC_SLSH, SC_RSPC,
			KC_LCTL, KC_LGUI, KC_LALT, TO(2), KC_PSCR, TD(L_LAUNCH), 	TD(R_LAUNCH), KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_DEL,
					KC_SPC, TT(1), MO(3),				KC_ENT, KC_BSPC, KC_SPC
	),
	[1] = LAYOUT_moonlander(
			KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, RGB_SPD,		        RGB_SPI, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
			KC_TRNS, KC_EXLM, KC_AT, KC_LCBR, KC_RCBR, SS_EQGT, KC_TRNS, 	KC_TRNS, KC_UP, KC_7, KC_8, KC_9, KC_ASTR, KC_F12,
			KC_TRNS, KC_HASH, KC_DLR, KC_LPRN, KC_RPRN, SS_HYGT, KC_TRNS, 	KC_TRNS, KC_DOWN, KC_4, KC_5, KC_6, KC_PLUS, KC_TRNS,
			KC_TRNS, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, 			 KC_AMPR, KC_1, KC_2, KC_3, KC_BSLS, KC_TRNS,
			EE_CLR, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_MOD, 		RGB_TOG, KC_0, KC_0, KC_DOT, KC_EQL, KC_TRNS,
					RGB_VAD, KC_TRNS, RGB_VAI, 				TO(5), RGB_HUD, RGB_HUI
	),
	[2] = LAYOUT_moonlander(
			KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 		EE_CLR, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT,
			KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS, 		KC_TRNS, KC_WH_U, KC_TRNS, KC_BTN3, KC_TRNS, KC_TRNS, KC_TRNS,
			KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS, 		KC_TRNS, KC_WH_D, KC_BTN1, KC_BTN2, KC_TRNS, KC_TRNS, KC_MPLY,
			KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 				KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
			KC_TRNS, KC_TRNS, KC_TRNS, TO(0), KC_TRNS, KC_TRNS, 			KC_TRNS, KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
					KC_TRNS, KC_TRNS, KC_TRNS, 				KC_TRNS, KC_TRNS, KC_TRNS
	),
	[3] = LAYOUT_moonlander(
			KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
			KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 		KC_NO, KC_NO, KC_INS, KC_HOME, KC_PGUP, KC_NO, KC_NO,
			TO(0), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 		KC_NO, KC_NO, KC_DEL, KC_END, KC_PGDN, KC_NO, KC_NO,
			KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 			       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
			KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 			       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
					KC_NO, KC_NO, KC_TRNS, 						KC_NO, KC_NO, KC_NO
    ),
	[4] = LAYOUT_moonlander(
			KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TO(0),
			KC_TRNS, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_TRNS, 			KC_TRNS, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_TRNS,
			KC_TRNS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_TRNS, 			KC_TRNS, KC_H, KC_J, KC_K, KC_L, LT(2,KC_SCLN), KC_TRNS,
			KC_TRNS, KC_Z, KC_X, KC_C, KC_V, KC_B, 						KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_TRNS,
			KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 				KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
					KC_TRNS, TT(1), KC_TRNS, 					KC_TRNS, KC_TRNS, KC_TRNS
	),
    [5] = LAYOUT_moonlander(
            QK_AUDIO_ON, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
            KC_NO, MUS_ZELDA_PUZZLE, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
            TO(0), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                    KC_NO, KC_NO, KC_TRNS,                      KC_NO, KC_NO, KC_NO
    ),
};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)