
## Dedicated Hardware for Ableton Devices

### Contents

## **Purpose and Goals**

The primary purpose of this project is to design and develop dedicated Eurorack format MIDI controllers tailored specifically for controlling Ableton Live devices. These will be plug and play, and function as control surfaces, meaning they will auto-map parameters as well as detect and target the specified device no matter where it is in your effects chain. Each hardware device will target it’s paired device on the selected track, and re-detect, and remap each time a track is changed for ease of workflow.

The goal is to have seamless and hands-on experience for musicians and producers who use Ableton Live as their digital audio workstation (DAW) of choice.

The project is currently in the prototype stage, with an Ableton compressor as the target, and using a off the shelf microcontroller as the brain.

## **Features**

- Dedicated modules for selected Ableton FX devices
- Most useful controls mapped to panel
- Eurorack format
- Plug and play Midi by USB
- Recognised as Ableton Control surface
- Chainable so multiple devices use one USB
- Sexy faceplates and graphic design

## **Getting Started**

- At its current stage in the prototype phase, no elements of this project are open source.

## **Project Status**

- Currently, a Compressor device works as a control surface in Ableton, is plug and play and when changing tracks, the device auto-detects a compressor on your effects chain and automatically maps parameters to hardware encoders.

### Accomplished so far

- Created a plug-and-play midi controller with manual mapping of parameters
- Tuned encoders so that they have hardware debounce and value scaling
- Created proto faceplates to fit Eurorack format and experiment with control spacing and ergonomics
- Created a control surface script that maps to devices in the FX chain
- Updated control surface script so that the compressor is located, and controlled

### Challenges

- Control scripts for Ableton are not documented, the only custom scripts Ableton lets you create are for 16 macro controls on selected devices, this lacks the majority of functionality we want our end user to have.
- Currently, there are issues with the control script detecting any device with ‘Compressor’ in the namespace, this means that if there is a ‘Glue_compressor’ in the chain, this can be controlled instead of the compressor. Adding exceptions to the Python has not solved this.

## **Roadmap**

- Solve all control script issues
- Create v2 faceplates
- Create EQ8 hardware in SSL layout
- Redesign hardware so devices can be daisy-chained
- Redesign hardware so that only one microcontroler is used (perhaps have a single brain module that all modules attach to)
- Redesign Control scripts so daisy-chaining

## **Contributing**

- TBD  - Hoping from some TAKT brain power for the hardware redesign
