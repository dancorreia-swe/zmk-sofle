# nice-view-gem (vendored)

Vendored from [M165437/nice-view-gem](https://github.com/M165437/nice-view-gem) at `v0.3.0`
(commit `7794ebf`, LVGL v8 / ZMK v0.3.0 compatible). MIT licensed, see `LICENSE`.

Local changes:

- `CONFIG_NICE_VIEW_GEM_ANIMATION_ON_KEYPRESS` (default `y`): the peripheral crystal advances
  one frame per key press on that half instead of looping continuously.
  Set it to `n` to get the upstream behavior back (`CONFIG_NICE_VIEW_GEM_ANIMATION` / `_MS`).
