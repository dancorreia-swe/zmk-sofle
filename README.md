# ZMK Config - Eyelash Sofle

Personal ZMK firmware configuration for my Eyelash Sofle split keyboard.

![Build](https://github.com/dancorreia-swe/zmk-sofle/actions/workflows/build.yml/badge.svg)

## Hardware

- **Board**: Eyelash Sofle (nRF52840)
- **Left**: Rotary encoder + 5-way joystick (wired as keys in the middle column: arrows/Enter on Base, mouse move/click on Nav and Mouse)
- **Display**: nice!view on both halves, using [nice-view-gem](https://github.com/M165437/nice-view-gem)

## Keymap

<img src="keymap-drawer/eyelash_sofle.svg">

## Symbol Layer Design

The symbol layer is organized with mnemonic patterns for each hand:

```
┌────────────────────────────────────────────────────────────────────────────┐
│ LEFT HAND (Vim motions)             │ RIGHT HAND (Code constructs)         │
├─────┬─────┬─────┬─────┬─────┬───────┼─────┬─────┬─────┬─────┬─────┬────────┤
│  `  │  ?  │  #  │  %  │  \  │       │  ~  │  {  │ <=  │ >=  │  }  │        │
│     │ ↑   │ ↑   │     │     │       │     │     │     │     │     │ BLOCKS │
├─────┼─────┼─────┼─────┼─────┼───────┼─────┼─────┼─────┼─────┼─────┼────────┤
│  ^  │  ;  │  =  │  $  │  &  │       │  @  │  (  │  "  │  '  │  )  │        │
│ GUI │ ALT │CTRL │SHFT │     │ ←───→ │     │SHFT │CTRL │ ALT │ GUI │ CALLS  │
├─────┼─────┼─────┼─────┼─────┼───────┼─────┼─────┼─────┼─────┼─────┼────────┤
│  +  │  /  │  *  │  !  │  |  │       │ ::  │  [  │  :  │  .  │  ]  │        │
│     │ ↓   │ ↓   │     │     │       │     │     │     │     │     │ ACCESS │
└─────┴─────┴─────┴─────┴─────┴───────┴─────┴─────┴─────┴─────┴─────┴────────┘
```

### Left Hand: Vim Motions

Physical key position matches logical direction in Vim:

| Type | Keys | Position | Purpose |
|------|------|----------|---------|
| **Vertical** | `?` ↔ `/` | ring top/bottom | Search backward/forward |
| **Vertical** | `#` ↔ `*` | middle top/bottom | Word search backward/forward |
| **Horizontal** | `^` ↔ `$` | pinky ↔ index (home row) | Line start ↔ end |
| **Neutral** | `%` | index top | Match pairs (bidirectional) |

### Right Hand: Code Constructs (Row Categories)

| Row | Symbols | Use Case |
|-----|---------|----------|
| **Blocks** | `{ <= >= }` | Conditionals: `if x <= y { }` |
| **Calls** | `( " ' )` | Function calls: `func("str", 'c')` |
| **Access** | `[ : . ] ::` | Properties: `ns::arr[0].prop` |

### Operator Mod-Morphs

| Key | Tap | + Shift | Use Case |
|-----|-----|---------|----------|
| `<` | `<` | `<=` | Comparisons |
| `>` | `>` | `>=` | Comparisons |
| `\|` | `\|` | `\|>` | Elixir pipe |
| `-` | `-` | `->` | PHP/Elixir arrow |

## Building

Firmware builds automatically via GitHub Actions on push. Download the `firmware` artifact from the [Actions tab](../../actions):

| File | Flash to | When |
|------|----------|------|
| `eyelash_sofle_left.uf2` | Left half | Every keymap/config change (keymap, display and ZMK Studio live here) |
| `eyelash_sofle_right.uf2` | Right half | Only when ZMK version or board config changes |
| `settings_reset.uf2` | Either half | To wipe pairings/saved settings, then flash the normal firmware again |

> **ZMK Studio note:** changes saved in Studio are stored on the keyboard and take priority over `config/eyelash_sofle.keymap`.
> Use "Restore Stock Settings" in Studio (or `settings_reset`) to go back to the file's keymap.

## Resources

- [ZMK Documentation](https://zmk.dev/docs)
- [Keymap Editor](https://nickcoutsos.github.io/keymap-editor/)
