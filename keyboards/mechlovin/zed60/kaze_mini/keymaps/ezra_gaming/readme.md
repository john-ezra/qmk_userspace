# NRD Kaze Mini (Mechlovin Zed60 Hotswap) Ezra Gaming Keymap

The [standard keymap](../ezra/readme.md) plus a QWERTY base layer, for the Kaze Mini on the gaming PC.

## Layers

| Layer | Select with | Contents |
| --- | --- | --- |
| Colemak | `Fn` + `1` | Identical to the standard keymap |
| QWERTY | `Fn` + `2` | Standard QWERTY with Caps Lock and a plain Enter in place of the Super mod-taps; the three `Fn` keys stay where they are |

The selection is written to EEPROM, so the board comes back in whichever layer it was left in after unplugging. The rest of the `Fn` layer is the standard one; because `1` and `2` are taken by the layer switches, `F1` and `F2` are not available on this keymap.

## Flashing

Same board and same procedure as the standard keymap, including the dfu-util hazard explained in its [readme](../ezra/readme.md). Enter the bootloader by holding `Esc` while plugging in USB, or press the reset button on the back of the PCB.

```sh
qmk flash -kb mechlovin/zed60/kaze_mini -km ezra_gaming
```

**Unplug and replug the keyboard to start the new firmware.**
