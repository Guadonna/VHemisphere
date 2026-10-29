---
layout: default
nav_order: 4
---
# UI Gestures

Operating **Hemispheres** makes use of button combinations to perform various actions. See below for a complete list.

Certain applet (or parameter editing) contexts may override the default behaviours of the buttons and/or encoders. Typically, in split-screen contexts, the left side uses the UP button and LEFT encoder; right side uses DOWN button and RIGHT encoder. In full-screen contexts, the LEFT encoder jumps between pages while the RIGHT encoder moves the cursor and activates selections.


## Global

_Attention!_ As of v2.0, the global UI gestures have changed!

| Action    | Gesture    |   Notes   |
| --------- |:----------:|:---------:|
| **Return to main menu** | Hold UP and press RIGHT Encoder | Execution continues in the background. |
| **Open IO Settings** | Hold UP and press LEFT Encoder | Used to configure settings for current App.<br>Press UP again to invoke screensaver. |
| **[Save Global Settings to EEPROM](Saving-State)** | Long-press RIGHT encoder while on main menu | This includes the currently selected App, user scales, saved sequence patterns, etc. Use [Presets](Hemisphere-Presets) instead to store Applet settings inside Hemispheres |

## Hemispheres

| Action    | Gesture    |   Notes   |
| --------- |:----------:|:---------:|
| **Change left applet**             | Press UP button - a solid border will appear around the applet. Rotate LEFT encoder to scroll through each applet one by one. Press either UP or LEFT encoder to exit selection mode. | Alternatively, double-press UP button to enter help/config screen. Select applet name with RIGHT encoder cursor and press to enter applet selection menu. Scroll menu with RIGHT encoder and press to select. Press UP or DOWN to escape without changing applet. |
| **Change right applet**            | Press DOWN button - a solid border will appear around the applet. Rotate RIGHT encoder to scroll through each applet one by one. Press either DOWN or RIGHT encoder to exit selection mode. | Alternatively, double-press DOWN button to enter help/config screen. Select applet name with RIGHT encoder cursor and press to enter applet selection menu. Scroll menu with RIGHT encoder and press to select. Press UP or DOWN to escape without changing applet. |
| **Open full-screen applet help/config** | Double press UP button for left hemisphere, double press DOWN button for right hemisphere. Press UP or DOWN again to exit. | RIGHT encoder is always used to move cursor and edit params; LEFT encoder swaps between applet config and full-screen view.     |
| **View applet UI in full-screen**   | Open help screen (see above), and rotate LEFT encoder. Then, use RIGHT encoder to interact with the Applet UI. | Applets that make use of full-screen view currently include Scope, EuclidX, and Ebb&LFO. More to come.    |
| **Open [Clock / Trigger Setup](Clock-Setup)**      | Press both UP + DOWN buttons together.  | Adjust internal BPM, swing, external sync, and per-trigger clock mult/div; remap trigger inputs (also available within the [Config menus](Hemisphere-Config) or in applet help/config view); and manually perform triggers.  |
| **Cycle Internal Clock state**     | Long-press LEFT encoder  | Stop -> Arm _(i.e. play on next input trigger)_ -> Start |
| **Open [Hemisphere Config menu](Hemisphere-Config)** | Long-press DOWN button. Scroll pages with LEFT encoder, move cursor with RIGHT encoder | Load/save presets; adjust trigger length; select screensaver and cursor mode; toggle auto-MIDI out; trigger and CV input mapping; quantizer settings; applet filtering |
| **AuxButton**  | _**After pushing encoder to highlight a parameter for editing**_, press the corresponding select button (UP or DOWN) | This gesture is only enabled in certain applets for secondary functions, typically indicated with a dotted cursor line. Use it to mute/unmute steps in DivSeq, SequenceX, Seq32, etc.; re-randomize sequences in Shredder; Toggle additional CV mapping in DuoTET; and directly edit the current [Quantizer engine](Hemisphere-Quantizer-Setup) |
