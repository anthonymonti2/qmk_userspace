#include QMK_KEYBOARD_H
//#include "caps_word.h"
#include "layer_lock.h"
// Smart shift implementation - https://github.com/qmk/qmk_firmware/blob/master/keyboards/crkbd/keymaps/rpbaptist/keymap.c
// Luna - https://github.com/HellSingCoder/qmk_firmware/tree/master/keyboards/sofle/keymaps/helltm
// Layer indicator - https://github.com/JReneHS/crkb_conf/tree/main/nahum_qwerty
// LOCKING LAYER https://getreuer.info/posts/keyboards/layer-lock/index.html

enum layer_number {
  _COLEMAK = 0,
  _QWERTY,
  _CGAME,
  _QGAME,
  NAV,
  NUM,
  MEDIA,
  SYM,
  FUN,
  LAYER_NUMBER_MAX 
};

// For AVR you need to make each string a const in program memory
const char PROGMEM LAYER_NAME_COLE[] = "COLE";
const char PROGMEM LAYER_NAME_QWRTY[] = "QWRTY";
const char PROGMEM LAYER_NAME_CGAME[] = "CGAME";
const char PROGMEM LAYER_NAME_QGAME[] = "QGAME";
const char PROGMEM LAYER_NAME_NAV[] = "NAV";
const char PROGMEM LAYER_NAME_NUM[] = "NUM";
const char PROGMEM LAYER_NAME_MEDIA[] = "MEDIA";
const char PROGMEM LAYER_NAME_SYMBOL[] = "SYMB";
const char PROGMEM LAYER_NAME_FUNCTION[] = "FUNC";
const char PROGMEM LAYER_NAME_UNDEF[] = "UNDEF";

//"CGAME", "QGAME", "NAV", "NUM", "MEDIA", "SYMB", "FUNC"
const char* LAYER_NAME[] = {
    LAYER_NAME_COLE, LAYER_NAME_QWRTY, 
    LAYER_NAME_CGAME, LAYER_NAME_QGAME, 
    LAYER_NAME_NAV, LAYER_NAME_NUM,
    LAYER_NAME_MEDIA, LAYER_NAME_SYMBOL,
    LAYER_NAME_FUNCTION, LAYER_NAME_UNDEF
};

// Todo: Make compile time assert to check number of layer names to layers
//sizeof(arr)/sizeof(LAYER_NAME[0]);
// Checking to see if the number of layers matches the layer name list
//__Static_assert((sizeof(arr)/sizeof(LAYER_NAME[0])) != LAYER_NUMBER_MAX)

enum custom_keycodes {
  LLOCK = SAFE_RANGE,
  // Other custom keys...
};

/* Display functions*/
uint8_t get_current_layer(void) {
    return get_highest_layer(layer_state | default_layer_state);
}

//TODO: Code needs to coverted to AVR from ARM
const char *layer_upper_name(uint8_t layer) {
    if (layer < LAYER_NUMBER_MAX) {
        return LAYER_NAME[layer];
    } else {
        return "UNDEFINED";
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* COLEMAK
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ALT  |  Q   |  W   |  F   |  P   |  B   |                    |  J   |  L   |  U   |  Y   |  ;   |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | LCRTL|  A   |  R   |  S   |  T   |  G   |                    |  M   |  N   |  E   |  I   |  O   |  '   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | LSFT |  Z   |  X   |  C   |  D   |  V   |                    |  K   |  H   |  ,   |  .   |  /   | RSFT |
 * `-----------------------------------------/-------.     .------\-----------------------------------------'
 *                          | ESC  | SPC  | / TAB   /       \ ENTR \  | BSPCE| DEL  |
 *                          |      |      |/       /         \      \ |      |      |
 *                          '---------------------'           '--------------------'
 */

[_COLEMAK] = LAYOUT_split_3x6_3( \
  KC_LALT,  KC_Q,   KC_W,    KC_F,    KC_P,    KC_B,                     KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN , KC_MINS, \
  KC_LCTL,  KC_A,   KC_R,    KC_S,    KC_T,    KC_G,                     KC_M,    KC_N,    KC_E,    KC_I,    KC_O    , KC_QUOT,\
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_D,    KC_V,                     KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH , KC_RSFT,\
                  LT(MEDIA, KC_ESC), LT(NAV, KC_SPC), KC_TAB, LT(SYM, KC_ENT), LT(NUM, KC_BSPC), LT(FUN, KC_DEL)               
),
/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ALT  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |                    |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |                    |   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/------.       .-----\-----------------------------------------'
 *                          | ESC  | SPC  | / TAB   /       \ ENTR \  | BSPCE| DEL  |
 *                          |      |      |/       /         \      \ |      |      |
 *                          '---------------------'           '--------------------'
 */

 [_QWERTY] = LAYOUT_split_3x6_3( \
  KC_LALT,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS, \
  KC_LCTL, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,                     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT, \
                           _______, _______, _______, _______,  _______, _______
),
/* COLEMAK GAME
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ALT  |  Q   |  W   |  F   |  P   |  B   |                    |  J   |  L   |  U   |  Y   |  ;   |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | LCRTL|  A   |  R   |  S   |  T   |  G   |                    |  M   |  N   |  E   |  I   |  O   |  '   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | LSFT |  Z   |  X   |  C   |  D   |  V   |                    |  K   |  H   |  ,   |  .   |  /   | RSFT |
 * `-----------------------------------------/-------.     .------\-----------------------------------------'
 *                          | ESC  | SPC  | / TAB   /       \ ENTR \  | BSPCE| DEL  |
 *                          |      |      |/       /         \      \ |      |      |
 *                          '---------------------'           '--------------------'
 */

[_CGAME] = LAYOUT_split_3x6_3( \
  KC_LALT,  KC_Q,   KC_W,    KC_F,    KC_P,    KC_B,                     KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN , KC_MINS, \
  KC_LCTL,  KC_A,   KC_R,    KC_S,    KC_T,    KC_G,                     KC_M,    KC_N,    KC_E,    KC_I,    KC_O    , KC_QUOT,\
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_D,    KC_V,                     KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH , KC_RSFT,\
                                    KC_ESC, KC_LALT, KC_SPC, KC_ENT,  KC_BSPC, _______               
),
/* QWERTY GAME
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |                    |   H  |   J  |   K  |   L  |  UP  |  '   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |                    |   N  |   M  |   ,  | LEFT | DOWN | RGHT |
 * `-----------------------------------------/------.       .-----\-----------------------------------------'
 *                          | ESC  | LALT | / SPCE  /       \ ENTR \  | BSPCE| DEL  |
 *                          |      |      |/       /         \      \ |      |      |
 *                          '---------------------'           '--------------------'
 */

 [_QGAME] = LAYOUT_split_3x6_3( \
  KC_TAB  ,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS, \
  KC_LCTL,    KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_UP,   KC_QUOT, \
  KC_LSFT,    KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,                     KC_N,    KC_M,    KC_COMM, KC_LEFT, KC_DOWN, KC_RIGHT, \
                                KC_ESC, KC_LALT, KC_SPC, KC_ENT,  KC_BSPC, _______
),
// Need the del key to be transparent so we can use the func layer

// NAV
/*
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    | REDO | PSTE |  UP  | CUT  | UNDO |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | LGUI | LALT | LCTRL| LSFT | LOCK |                    | CAPS | LEFT | DOWN | RGHT | COPY |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | RGUI | RALT | RCTRL| RSFT |      |                    |  INS | HOME | PBUP | PGDN | END  | RSFT |
 * `-----------------------------------------/-------.     .------\-----------------------------------------'
 *                          |      |      | /       /       \ ENTR \  | BSPCE| DEL  |
 *                          |      |      |/       /         \      \ |      |      |
 *                          '---------------------'           '--------------------'
 */
[NAV] = LAYOUT_split_3x6_3(\
    U_NU, U_NU,    U_NU,    U_NU,    U_NU,    U_NU,                U_REDO,  U_PSTE,  KC_UP,   U_CUT,   U_UNDO, U_NU, \
    U_NU, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, LLOCK,               KC_CAPS, KC_LEFT, KC_DOWN, KC_RGHT, U_COPY, U_NU, \
    U_NU, KC_RGUI, KC_RALT, KC_RCTL, KC_RSFT, U_NU,                KC_INS,  KC_HOME, KC_PGUP, KC_PGDN, KC_END,  U_NU, \
                                     U_NA,    U_NA, U_NA, KC_ENT,  KC_BSPC, KC_DEL
    ),

//NUMBER
/*
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | LL   |  [   |  7   |  8   |  9   |  ]   |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | LL   |  ;   |  4   |  5   |  6   |  =   |                    | LOCK | LSFT | LCTRL| LALT | LGUI |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | LL   |  +   |  1   |  2   |  3   |  /   |                    |      | RSFT | RCTRL| RALT | RGUI |      |
 * `-----------------------------------------/-------.     .------\-----------------------------------------'
 *                          |  .   |  0   | /   -   /       \      \  |      |      |
 *                          |      |      |/       /         \      \ |      |      |
 *                          '---------------------'           '--------------------'
 */
[NUM] = LAYOUT_split_3x6_3(
    KC_TRNS,KC_LBRC, KC_7,    KC_8,    KC_9,    KC_RBRC,         U_NU,    U_NU,    U_NU,    U_NU,    U_NU,    U_NU, \
    KC_TRNS,KC_SCLN, KC_4,    KC_5,    KC_6,    KC_EQL,          LLOCK,   KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, U_NU,\
    KC_TRNS,KC_PLUS, KC_1,    KC_2,    KC_3,    KC_BSLS,         U_NA,    KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, U_NU,\
                                KC_DOT,  KC_0,  KC_MINS,     U_NA,    U_NA,    U_NA
  ),

/* SYMBOLS
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   &  |   @  |   <  |   (  |   )  |   >  |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   \  |   !  |   _  |   +  |   =  |   *  |                    | LOCK |LShift| LCtrl| LAlt | LGUI |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   ~  |   ^  |   -  |  [|{ |  }|] |   |  |-------.    .-------|   `  | RSFT | RCTRL| RALT | RGUI |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |   %  |   $  | /   #   /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[SYM] = LAYOUT_split_3x6_3(
    KC_AMPR, KC_AT  , KC_LABK, KC_LPRN, KC_RPRN, KC_RABK,           U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NU, \
    KC_BSLS, KC_EXLM, KC_UNDS, KC_PLUS, KC_EQL,  KC_ASTR,           LLOCK,   KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, U_NU, \
    KC_TILD, KC_CIRC, KC_MINS, KC_LBRC, KC_RBRC ,KC_PIPE,           KC_GRV,  KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, U_NU,\
                               KC_PERC, KC_DLR , KC_HASH,           U_NA,    U_NA,    U_NA
    ),

//MEDIA
/*
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      | WINL |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | LGUI | LALT | LCTRL| LSFT | LOCK |                    |      | REWD | VOLD | VOLU | FORW |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | RGUI | RALT | RCTRL| RSFT |      |                    |      |      |      |      |      |      |
 * `-----------------------------------------/-------.     .------\-----------------------------------------'
 *                          |      |      | /       /       \ MPAUS\  | PLAY |  MUTE |
 *                          |      |      |/       /         \      \ |      |      |
 *                          '---------------------'           '--------------------'
 */
[MEDIA] = LAYOUT_split_3x6_3(
    U_NU ,U_NU,    U_NU,    U_NU,    U_NU,    U_NU,             U_NU,    U_WINLK, U_NU,    U_NU,    U_NU,    U_NU , \
    U_NU ,KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, LLOCK,            U_NU,    KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, U_NU , \
    U_NU, KC_RGUI, KC_RALT, KC_RCTL, KC_RSFT, U_NU,             U_NU,    U_NU,    U_NU,    U_NU,    U_NU,    U_NU , \
                            U_NA,    U_NA,    U_NA,         KC_MSTP, KC_MPLY, KC_MUTE
    ),

//FUNCTION
/*
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F12 |  F7  |  F8  |  F9  | PSCR |                    | CALC |QWERTY| QGME | CGME |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  F11 |  F4  |  F5  |  F6  | APP  |                    | LOCK | LSFT | LCTRL| LALT | LGUI |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  F10 |  F1  |  F2  |  F3  | PAUSE|                    | NKRO | RSFT | RCTRL| RALT | RGUI |      |
 * `-----------------------------------------/-------.     .------\-----------------------------------------'
 *                          |      |      | /       /       \      \  |      |      |
 *                          |      |      |/       /         \      \ |      |      |
 *                          '---------------------'           '--------------------'
 */
[FUN] = LAYOUT_split_3x6_3(
    U_NU, KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR,          KC_CALC, TG(_QWERTY),   TG(_QGAME), TG(_CGAME), U_NA, U_NA,\
    U_NU, KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_APP,           LLOCK,   KC_LSFT,       KC_LCTL,   KC_LALT, KC_LGUI, U_NU, \
    U_NU, KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_PAUS,          NK_TOGG, KC_RSFT,       KC_RCTL,   KC_RALT, KC_RGUI, U_NU, \
                            U_NU ,  U_NU,    U_NU,              U_NA,    U_NA,    U_NA
  )
};

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

/* KEYBOARD PET START */

/* settings */
#    define MIN_WALK_SPEED      10
#    define MIN_RUN_SPEED       40

/* advanced settings */
#    define ANIM_FRAME_DURATION 200  // how long each frame lasts in ms
#    define ANIM_SIZE           96   // number of bytes in array. If you change sprites, minimize for adequate firmware size. max is 1024

/* timers */
uint32_t anim_timer = 0;

/* current frame */
uint8_t current_frame = 0;

/* status variables */
int   current_wpm = 0;
bool caps_on = false;

bool isSneaking = false;
bool isJumping  = false;
bool showedJump = true;

/* logic */
static void render_luna(int LUNA_X, int LUNA_Y) {
    /* Sit */
    static const char PROGMEM sit[2][ANIM_SIZE] = {/* 'sit1', 32x22px */
                                                   {
                                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c, 0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x68, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28, 0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   },

                                                   /* 'sit2', 32x22px */
                                                   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c, 0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x90, 0x08, 0x18, 0x60, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0e, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28, 0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

    /* Walk */
    static const char PROGMEM walk[2][ANIM_SIZE] = {/* 'walk1', 32x22px */
                                                    {
                                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x90, 0x90, 0x90, 0xa0, 0xc0, 0x80, 0x80, 0x80, 0x70, 0x08, 0x14, 0x08, 0x90, 0x10, 0x10, 0x08, 0xa4, 0x78, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0xfc, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0xea, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x03, 0x06, 0x18, 0x20, 0x20, 0x3c, 0x0c, 0x12, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    },

                                                    /* 'walk2', 32x22px */
                                                    {
                                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x20, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x28, 0x10, 0x20, 0x20, 0x20, 0x10, 0x48, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x20, 0xf8, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x30, 0xd5, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x02, 0x1c, 0x14, 0x08, 0x10, 0x20, 0x2c, 0x32, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    }};

    /* Run */
    static const char PROGMEM run[2][ANIM_SIZE] = {/* 'run1', 32x22px */
                                                   {
                                                       0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x08, 0xc8, 0xb0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0xc4, 0xa4, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x58, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x09, 0x04, 0x04, 0x04, 0x04, 0x02, 0x03, 0x02, 0x01, 0x01, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   },

                                                   /* 'run2', 32x22px */
                                                   {
                                                       0x00, 0x00, 0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x78, 0x28, 0x08, 0x10, 0x20, 0x30, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0xb0, 0x50, 0x55, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x1e, 0x20, 0x20, 0x18, 0x0c, 0x14, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   }};

    /* Bark */
    static const char PROGMEM bark[2][ANIM_SIZE] = {/* 'bark1', 32x22px */
                                                    {
                                                        0x00, 0xc0, 0x20, 0x10, 0xd0, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    },

                                                    /* 'bark2', 32x22px */
                                                    {
                                                        0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 0x2c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x20, 0x4a, 0x09, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    }};

    /* Sneak */
    static const char PROGMEM sneak[2][ANIM_SIZE] = {/* 'sneak1', 32x22px */
                                                     {
                                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x40, 0x80, 0x00, 0x80, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x21, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x04, 0x04, 0x04, 0x03, 0x01, 0x00, 0x00, 0x09, 0x01, 0x80, 0x80, 0xab, 0x04, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x02, 0x06, 0x18, 0x20, 0x20, 0x38, 0x08, 0x10, 0x18, 0x04, 0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00,
                                                     },

                                                     /* 'sneak2', 32x22px */
                                                     {
                                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xa0, 0x20, 0x40, 0x80, 0xc0, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x41, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x04, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x40, 0x40, 0x55, 0x82, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x04, 0x18, 0x10, 0x08, 0x10, 0x20, 0x28, 0x34, 0x06, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                     }};

    /* animation */
    void animate_luna(void) {
        /* jump */
        if (isJumping || !showedJump) {
            /* clear */
            oled_set_cursor(LUNA_X, LUNA_Y + 2);
            oled_write("     ", false);

            oled_set_cursor(LUNA_X, LUNA_Y - 1);

            showedJump = true;
        } else {
            /* clear */
            oled_set_cursor(LUNA_X, LUNA_Y - 1);
            oled_write("     ", false);

            oled_set_cursor(LUNA_X, LUNA_Y);
        }

        /* switch frame */
        current_frame = (current_frame + 1) % 2;

        /* current status */
        if (caps_on) {
            oled_write_raw_P(bark[current_frame], ANIM_SIZE);

        } else if (isSneaking) {
            oled_write_raw_P(sneak[current_frame], ANIM_SIZE);

        } else if (current_wpm <= MIN_WALK_SPEED) {
            oled_write_raw_P(sit[current_frame], ANIM_SIZE);

        } else if (current_wpm <= MIN_RUN_SPEED) {
            oled_write_raw_P(walk[current_frame], ANIM_SIZE);

        } else {
            oled_write_raw_P(run[current_frame], ANIM_SIZE);
        }
    }

    /* animation timer */
    if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
        anim_timer = timer_read32();
        animate_luna();
    }
}

/* KEYBOARD PET END */

void render_mod_status_gui_alt(uint8_t modifiers) {
    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM gui_on_1[] = {0x8d, 0x8e, 0};
    static const char PROGMEM gui_on_2[] = {0xad, 0xae, 0};

    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM alt_on_1[] = {0x8f, 0x90, 0};
    static const char PROGMEM alt_on_2[] = {0xaf, 0xb0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_1, false);
    } else {
        oled_write_P(gui_off_1, false);
    }

    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_1, false);
    } else {
        oled_write_P(alt_off_1, false);
    }

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_2, false);
    } else {
        oled_write_P(gui_off_2, false);
    }

    if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_2, false);
    } else {
        oled_write_P(alt_off_2, false);
    }
}


void render_mod_status_ctrl_shift(uint8_t modifiers) {
    static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
    static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
    static const char PROGMEM ctrl_on_1[] = {0x91, 0x92, 0};
    static const char PROGMEM ctrl_on_2[] = {0xb1, 0xb2, 0};

    static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
    static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
    static const char PROGMEM shift_on_1[] = {0xcd, 0xce, 0};
    static const char PROGMEM shift_on_2[] = {0xcf, 0xd0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_1, false);
    } else {
        oled_write_P(ctrl_off_1, false);
    }

    if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_1, false);
    } else {
        oled_write_P(shift_off_1, false);
    }

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_2, false);
    } else {
        oled_write_P(ctrl_off_2, false);
    }

    if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_2, false);
    } else {
        oled_write_P(shift_off_2, false);
    }
}

const void render_on_off_status(char *name, bool status) {
    static const char PROGMEM on_symbol[] = {0x82,0x83,0x0};
    static const char PROGMEM off_symbol[] = {0x80,0x81,0x0};

    oled_write((name),false);
    if (status) {
        oled_write_P(on_symbol, false);
    } else {
        oled_write_P(off_symbol, false);
    }
}

void render_status_main(void) {
    led_t led_usb_state = host_keyboard_led_state();
    bool  caps          = led_usb_state.caps_lock || is_caps_word_on();    
    /* Display the letter layout */
    oled_clear();
    oled_set_cursor(0, 5);

    if(layer_state_is(_COLEMAK)) {
        oled_write_ln_P(LAYER_NAME_COLE,false);
    } else if(layer_state_is(_QWERTY)) {
        oled_write_ln_P(LAYER_NAME_QWRTY,false);
    } else if(layer_state_is(_QGAME)) {
        oled_write_ln_P(LAYER_NAME_QGAME,false);
    } else if(layer_state_is(_CGAME)) {
        oled_write_ln_P(LAYER_NAME_CGAME,false);
    } else {
        oled_write_ln_P(LAYER_NAME_COLE,false);  
    }

    //TODO: Code needs to coverted to AVR from ARM
    //oled_write_ln(layer_upper_name(get_current_layer()), false);

    oled_set_cursor(0, 7);


    // Display the status of the keyboard
    // NOTE: each one is exactly 1 line long so no need to new line
    render_on_off_status("CPS", caps);
    render_on_off_status("LCK", is_any_layer_locked());
    render_on_off_status("NRO", keymap_config.nkro);

    oled_set_cursor(0,11);

    render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
    render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
}

void render_status_secondary(void) {
  /* KEYBOARD PET RENDER START */

  render_luna(0,12);

  /* KEYBOARD PET RENDER END */
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_270;
}

bool oled_task_user(void) {
    #if OLED_TIMEOUT > 0
    /* let the main half decide when to turn off the animation
        using last activite. The animation prevents the normal
        timeout from occuring */
    if (is_keyboard_master() == true && 
        last_input_activity_elapsed() > OLED_TIMEOUT && 
        last_led_activity_elapsed() > OLED_TIMEOUT) {
        oled_off();
    } else {
        led_t led_usb_state = host_keyboard_led_state();

        // Get global state of certain keyboard stats for the oled rendering
        caps_on = led_usb_state.caps_lock || is_caps_word_on(); 
        current_wpm = get_current_wpm();

        if (is_keyboard_master()) {
            // Renders the current keyboard state (layer, lock, caps, scroll, etc)
            render_status_main();  
        } else {
            render_status_secondary();
        }
    }
    #endif

    return true;
}
#endif // OLED_ENABLE

uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    mod_state = get_mods();
    switch (keycode) {
        #ifdef OLED_ENABLE
        /* KEYBOARD PET STATUS START */
        case KC_LCTL:
        case KC_RCTL:
            if (record->event.pressed) {
                isSneaking = true;
            } else {
                isSneaking = false;
            }
            break;
        // Disable jumping as it looks weird
        // case KC_SPC:
        //     if (record->event.pressed) {
        //         isJumping = true;
        //         showedJump = false;
        //     } else {
        //         isJumping = false;
        //     }
        //     break;
        #endif
        /* KEYBOARD PET STATUS END */
    }

    // Check if we need to handle the layer lock (llock) key
    if (!process_layer_lock(keycode, record, LLOCK)) { return false; }
    
    // // Checks if we need to do caps word
    // if(!process_caps_word(keycode, record)) 
    // {
    //     return false;
    // }

    return true;
}

// For layer lock. Need to add timeout every scan cycle
// Run time based events at then end of each update cycle
void housekeeping_task_user(void) {
    layer_lock_task();
}

// Tasks to do when the keyboard is told the system is idle
void suspend_power_down_user(void) {
    #ifdef OLED_ENABLE
    oled_off();
    #endif

    // Reset layer back to default
    layer_clear();

}

//Template
/*
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */