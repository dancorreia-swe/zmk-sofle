#include <stdlib.h>
#include <zephyr/kernel.h>
#include "animation.h"

#if IS_ENABLED(CONFIG_NICE_VIEW_GEM_ANIMATION_ON_KEYPRESS)
#include <zmk/display.h>
#include <zmk/event_manager.h>
#include <zmk/events/position_state_changed.h>
#endif

LV_IMG_DECLARE(crystal_01);
LV_IMG_DECLARE(crystal_02);
LV_IMG_DECLARE(crystal_03);
LV_IMG_DECLARE(crystal_04);
LV_IMG_DECLARE(crystal_05);
LV_IMG_DECLARE(crystal_06);
LV_IMG_DECLARE(crystal_07);
LV_IMG_DECLARE(crystal_08);
LV_IMG_DECLARE(crystal_09);
LV_IMG_DECLARE(crystal_10);
LV_IMG_DECLARE(crystal_11);
LV_IMG_DECLARE(crystal_12);
LV_IMG_DECLARE(crystal_13);
LV_IMG_DECLARE(crystal_14);
LV_IMG_DECLARE(crystal_15);
LV_IMG_DECLARE(crystal_16);

const lv_img_dsc_t *anim_imgs[] = {
    &crystal_01, &crystal_02, &crystal_03, &crystal_04, &crystal_05, &crystal_06,
    &crystal_07, &crystal_08, &crystal_09, &crystal_10, &crystal_11, &crystal_12,
    &crystal_13, &crystal_14, &crystal_15, &crystal_16,
};

#define ANIM_FRAMES (sizeof(anim_imgs) / sizeof(anim_imgs[0]))

#if IS_ENABLED(CONFIG_NICE_VIEW_GEM_ANIMATION_ON_KEYPRESS)
/**
 * Keypress animation: each key press on this half advances the crystal one frame
 **/

static lv_obj_t *keypress_art;
static uint32_t keypress_count;

struct keypress_anim_state {
    uint32_t count;
};

static struct keypress_anim_state keypress_anim_get_state(const zmk_event_t *eh) {
    // Count presses here rather than in the callback, so presses coalesced
    // into a single display refresh still advance the frame
    if (eh != NULL) {
        const struct zmk_position_state_changed *ev = as_zmk_position_state_changed(eh);
        if (ev != NULL && ev->state) {
            keypress_count++;
        }
    }

    return (struct keypress_anim_state){.count = keypress_count};
}

static void keypress_anim_update_cb(struct keypress_anim_state state) {
    if (keypress_art == NULL) {
        return;
    }

    lv_img_set_src(keypress_art, anim_imgs[state.count % ANIM_FRAMES]);
}

ZMK_DISPLAY_WIDGET_LISTENER(widget_keypress_anim, struct keypress_anim_state,
                            keypress_anim_update_cb, keypress_anim_get_state)
ZMK_SUBSCRIPTION(widget_keypress_anim, zmk_position_state_changed);
#endif

void draw_animation(lv_obj_t *canvas) {
#if IS_ENABLED(CONFIG_NICE_VIEW_GEM_ANIMATION_ON_KEYPRESS)
    lv_obj_t *art = lv_img_create(canvas);

    keypress_art = art;
    widget_keypress_anim_init();
#elif IS_ENABLED(CONFIG_NICE_VIEW_GEM_ANIMATION)
    lv_obj_t *art = lv_animimg_create(canvas);
    lv_obj_center(art);

    lv_animimg_set_src(art, (const void **)anim_imgs, ANIM_FRAMES);
    lv_animimg_set_duration(art, CONFIG_NICE_VIEW_GEM_ANIMATION_MS);
    lv_animimg_set_repeat_count(art, LV_ANIM_REPEAT_INFINITE);
    lv_animimg_start(art);
#else
    lv_obj_t *art = lv_img_create(canvas);

    int length = sizeof(anim_imgs) / sizeof(anim_imgs[0]);
    srand(k_uptime_get_32());
    int random_index = rand() % length;

    lv_img_set_src(art, anim_imgs[random_index]);
#endif

    lv_obj_align(art, LV_ALIGN_TOP_LEFT, 36, 0);
}
