/*
 * Keep the Windows overlay layer on exactly while the Windows BLE profile is active.
 *
 * ZMK raises zmk_ble_active_profile_changed when a profile is selected and when the
 * active profile connects or disconnects, so the layer comes back by itself after
 * the keyboard wakes from deep sleep and reconnects.
 */

#include <zephyr/kernel.h>

#include <zmk/event_manager.h>
#include <zmk/events/ble_active_profile_changed.h>
#include <zmk/keymap.h>

static int win_profile_layer_listener(const zmk_event_t *eh) {
    const struct zmk_ble_active_profile_changed *ev = as_zmk_ble_active_profile_changed(eh);
    if (ev == NULL) {
        return ZMK_EV_EVENT_BUBBLE;
    }

    if (ev->index == CONFIG_MIX_WIN_PROFILE) {
        zmk_keymap_layer_activate(CONFIG_MIX_WIN_LAYER);
    } else {
        zmk_keymap_layer_deactivate(CONFIG_MIX_WIN_LAYER);
    }

    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(win_profile_layer, win_profile_layer_listener);
ZMK_SUBSCRIPTION(win_profile_layer, zmk_ble_active_profile_changed);
