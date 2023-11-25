#include QMK_KEYBOARD_H
#define WIN_CTRL_SPACE LGUI(LCTL(KC_SPACE))
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_65_ansi(
        QK_GESC,        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,
        KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PAUS,
        CTL_T(KC_CAPS), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_VOLU,
        KC_LSFT,                 KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_VOLD,
        KC_LCTL,    KC_LALT    , KC_LGUI,                            KC_SPC,                    WIN_CTRL_SPACE, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT_65_ansi(
        QK_GESC,        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_HOME,
        _______,        RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, KC_PSCR, KC_SCRL, KC_PAUS, QK_BOOT,  KC_PGUP,
        CTL_T(KC_CAPS), RGB_SPI, RGB_SPD, _______, _______, _______, _______, _______, _______, _______, _______, _______,          RGB_TOG,  KC_PGDN,
        KC_LSFT,                 _______, _______, _______, _______, _______, NK_TOGG, _______, _______, _______, _______, _______, RGB_VAI, KC_MUTE,
        _______,        _______, _______,                            _______,                   _______, _______, _______, KC_MPRV, RGB_VAD, RGB_MOD
    ),
    [2] = LAYOUT_65_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                            _______,                   _______, _______, _______, _______, _______, _______
    ),
    [3] = LAYOUT_65_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                            _______,                   _______, _______, _______, _______, _______, _______
    )
};
static bool L_CMD_FLAG     = false;
static bool BACKSPACE_FLAG = false;
static bool SPACEBAR_FLAG = false;

const uint8_t SpaceBarKeys[3][7] = {{18, 19, 20, 21, 22, 23, 24}, {33, 34, 35, 36, 37, 38}, {47, 48, 49, 50, 51, 52}};
const uint8_t backSpaceRow[8]    = {7, 8, 9, 10, 11, 12, 13, 14};
const uint8_t GUIKEYS[5][5]      = {{1, 2, 3, 4, 5}, {16, 17, 18, 19}, {31, 32, 33}, {45, 46}, {60}};

void timeWaster(void) {
    for (int i = 0; i < 500; i++)
        ;
}
void handleLEDSTriangle(const uint8_t key[5][5]) {
    for (uint8_t row = 0; row < 5; row++) {
        for (uint8_t col = 0; col < 5; col++) {
            rgb_matrix_set_color(key[row][col], 50, 100, 50);
        }
    }
}

void handleLEDSSingleRow(const uint8_t key[], size_t size) {
    for (uint8_t i = 0; i < size; i++) {
        rgb_matrix_set_color(key[i], 50, 100, 50);
    }
}

void matrix_scan_user(void) {
    if (L_CMD_FLAG) {
        handleLEDSTriangle(GUIKEYS);
    }
    if (BACKSPACE_FLAG) {
        handleLEDSSingleRow(backSpaceRow, sizeof(backSpaceRow) / sizeof(backSpaceRow[0]));
    }
    if (SPACEBAR_FLAG) {
        handleLEDSSingleRow(SpaceBarKeys[0], 7);
        handleLEDSSingleRow(SpaceBarKeys[1], 6);
        handleLEDSSingleRow(SpaceBarKeys[2], 6);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // static uint16_t KeyPressTimer;
    switch (keycode) {
        case KC_LGUI:
            if (record->event.pressed) {
                L_CMD_FLAG = !L_CMD_FLAG;
            } else {
                L_CMD_FLAG = !L_CMD_FLAG;
            }
            break;
        case KC_BACKSPACE:
            if (record->event.pressed) {
                BACKSPACE_FLAG = !BACKSPACE_FLAG;
            } else {
                BACKSPACE_FLAG = !BACKSPACE_FLAG;
            }
            break;
        case KC_SPACE:
            if (record->event.pressed){
                SPACEBAR_FLAG = !SPACEBAR_FLAG;
            }else{
                SPACEBAR_FLAG = !SPACEBAR_FLAG;
            }
        break;
    }

    return true;
};
