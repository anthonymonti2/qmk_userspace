/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* Select hand configuration */
#define MASTER_LEFT
// Set up the master based on which side has USB input
#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 10000
#define SPLIT_USB_TIMEOUT_POLL 10
#define SPLIT_WATCHDOG_ENABLE
#define SPLIT_WATCHDOG_TIMEOUT 15000

// Enable NRKO
#define NKRO_DEFAULT_ON true

// Send WPM to the other side
#define SPLIT_WPM_ENABLE

// Sync caps lock state between sides
#define SPLIT_LED_STATE_ENABLE

// Sync on off state of OLED
#define SPLIT_OLED_ENABLE

// Sync activity between halves for luna animation
#define SPLIT_ACTIVITY_ENABLE

// Set to path to glcdfont.c for OLED font
#undef OLED_FONT_H
#define OLED_FONT_H "keyboards/lily58/rev1/keymaps/monti-lily58/glcdfont.c"

#define OLED_TIMEOUT 60000 // in ms
// Reduce to smooth out animations, I'm going for speed over animation quality
#define OLED_UPDATE_INTERVAL 100 //in ms

#define LAYER_LOCK_IDLE_TIMEOUT 60000  // Turn off layer lock after 60 seconds.

// Caps word settings
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

// Change debounce time for eager
#undef DEBOUNCE
#define DEBOUNCE 10

// // Change the default USB speed to USB2.0
// #define USB_POLLING_INTERVAL_MS 1

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U // Timeout window in ms in which the double tap can occur.

// default but used in macros
#undef TAPPING_TERM
#define TAPPING_TERM 200

// If a second key is pressed when holding a dual action key it will
// send the hold action key immediatly
#define PERMISSIVE_HOLD_PER_KEY

// Recommended for heavy chording.
#define QMK_KEYS_PER_SCAN 6

#define XXX KC_NO
#define U_NP KC_NO // key is not present
#define U_NA KC_NO // present but not available for use
#define U_NU KC_NO // available but not used
#define U_REDO C(KC_Y)
#define U_PSTE C(KC_V)
#define U_COPY C(KC_C)
#define U_CUT C(KC_X)
#define U_UNDO C(KC_Z) 
#define U_WINLK LGUI(KC_L) // Windows key & l for locking PC