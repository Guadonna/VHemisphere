---
title: App & Applet Index
nav_order: 7
---

# App and Applet Index

Hemisphere runs two CV applets. This build also includes Setup/About, Scale
Editor, Waveform Editor, and Backup/Restore as utilities. Applet descriptions
below refer to internal signal values; see the project README for output scaling.

## CV Applets
Hemisphere splits the screen into two halves: each side available to load any one of a long list of applets. On o_C hardware with inputs and outputs arranged in 3 rows of 4 columns (i.e. most 8hp units), the I/O corresponding to an applet should be in line with that half of the display (i.e. paired into 1+2/A+B and 3+4/C+D).

If you're coming from any of the other Hemisphere forks, note that many of the applets have been upgraded for additional flexibility and functionality, and several are brand new.


* [ADSR](ADSR-EG) - Dual attack / decay / sustain / release envelope
* [AD EG](AD-EG) - Attack / decay envelope
* [ASR](ASR) - Analog Shift Register
* [AttenOff](AttenOff) - Attenu-vert, Offset, and Mix inputs (now with +/-200% range, mix control)
* [Binary Counter](Binary-Counter) - 1 bit per input, output as voltage
* [BitBeat](BitBeat) - ByteBeats algorithms from Viznutcracker, in an applet
* [BootsNCat](BootsNCat) - Noisy percussion
* [Brancher](Brancher) - Bernoulli gate
* [BugCrack](BugCrack) - Sick drums, don't bug out
* [Burst](Burst) - Rapid trigger / ratchet generator
* [Button2](Button2) - 2 simple triggers or latching gates. Press the button!
* [Calculate](Calculate) - Dual Min, Max, Sum, Diff, Mean, Random, S&H
* [Calibr8](Calibr8) - 2-channel, mini Calibr8or for v/Oct correction
* [Carpeggio](Carpeggio) - X-Y table of pitches from a scale/chord
* [Chordinate](Chordinate) - Quantizer with scale mask, outputs root + scale degree (from qiemem)
* [ClockDivider](ClockDivider) - Dual complex clock pulse multiplier / divider.
* [Clk2Gate](Clk2Gate) - Variable-length gate generator
* [ClockSkip](Clock-Skipper) - Randomly skip pulses
* [Combin8](Combin8) - Two 3:1 mixer channels
* [Compare](Compare) - Basic comparator
* [Cumulus](Cumulus) - Bit accumulator, inspired by Schlappi Nibbler
* [CVRec](CV-Recorder) - Record / smooth / playback CV up to 384 steps on 2 tracks
* [DivSeq](DivSeq) - Two sequences of clock dividers
* [DrumMap](DrumMap) - Clone of Mutable Instruments Grids
* [DualQuant](Dual-Quantizer) - Basic 2-channel quantizer with sample and hold
* [DuoTET](DuoTET) - microtonal N-TET duophonic quantizer
* [Ebb & LFO](Ebb-&-LFO) - clone of Mutable Instruments Tides; oscillator / LFO with CV-controllable waveshape, slope, V/Oct, folding
* [Enigma Jr.](Enigma-Jr) - compact player of curated shift registers
* [EnvFollow](Envelope-Follower) - follows or ducks based on incoming audio
  - added Speed control
* [EnvSeq](EnvSeq) - envelope sequencer
* [EuclidX](EuclidX) - Euclidean pattern generator (replacement for [AnnularFusion](https://github.com/Chysn/O_C-HemisphereSuite/wiki/Annular-Fusion-Euclidean-Drummer))
* [GameOfLife](GameOfLife) - experimental cellular automaton modulation source
* [GateDelay](Gate-Delay) - simple gate delay
* [GatedVCA](Gated-VCA) - simple VCA
* [Dr. LoFi](Dr.-LoFi) - super crunchy PCM delay line with bitcrushing and rate reduction
  - based on [LoFi Tape](https://github.com/Chysn/O_C-HemisphereSuite/wiki/LoFi-Tape) and Dr. Crusher
* [Logic](Logic) - AND / OR / XOR / NAND / NOR / XNOR
* [LowerRenz](LowerRenz) - orbiting particles, chaotic modulation source
* [Metronome](Metronome) - internal clock tempo control + multiplier output
* [MIDI In](MIDI-Input) - from USB to CV
* [MIDI Out](MIDI-Out) - from CV to USB
* [MarkoV](MarkoV) - first-order Markov chain melodic generator with Tendency Profiles and Chaos control
* [MarkovPerc](MarkovPerc) - first-order Markov chain rhythmic generator
* [MultiScale](MultiScale) - like ScaleDuet, but with 4 scale masks
* [Palimpsest](Palimpsest) - accent sequencer
* [Panner](Panner) - routes one CV signal between two outputs, with gate-controllable hard pan
* [Pigeons](Pigeons) - dual Fibonacci-style melody generator
* [PolyDiv](PolyDiv) - four concurrent clock dividers with assignable outputs
* [ProbDiv](ProbDiv) - stochastic trigger generator
* [ProbMeloD](ProbMeloD) - stochastic melody generator
* [Relabi](Relabi) - triple LFO with cross-FM, chaotic gate generator
* [ResetClk](Reset-Clock) - rapidly advance a sequencer to the desired step (from [pkyme](https://github.com/pkyme/O_C-HemisphereSuite/tree/reset-additions))
* [RndWalk](Random-Walk) - clocked random walk CV generator (from [adegani](https://github.com/adegani/O_C-HemisphereSuite))
* [RunglBook](RunglBook) - chaotic shift-register modulation
* [ScaleDuet](ScaleDuet) - 2 quantizers with independent scale masks
* [Schmitt](Schmitt-Trigger) - Dual comparator with low and high threshold
* [Scope](Scope) - tiny CV scope / voltmeter / BPM counter
  - expanded with X-Y view
* [Seq32](Seq32) - compact 32-step sequencer using Sequins pattern storage — record, play, and CV switch between 8 sequences!
* [SeqPlay7](SeqPlay7) - Make a playlist of Seq32 sequences, with quantizer override
* [SequenceX](SequenceX) - up to 8 steps of CV, quantized to semitones
* [ShiftGate](ShiftGate) - dual shift register-based gate/trigger sequencer
* [Shredder](Shredder) - clone of Mimetic Digitalis
* [Shuffle](Shuffle) - it don't mean a thing if it ain't got that swing
  - triplets added on 2nd output
* [Slew](Slew) - Dual channel slew: one linear, the other exponential
* [Squanch](Squanch) - advanced quantizer with transpose
* [Stairs](Stairs) - stepped CV
* [Strum](Strum) - the ultimate arpeggiator (pairs well with Rings)
* [Switch](Switch) - CV switch & toggle
* [SwitchSeq](Switch-Seq) - multiple Seq32 patterns running in parallel
* [TB-3PO](TB-3PO) - a brilliant 303-style sequencer
* [TL Neuron](Threshold-Logic-Neuron) - clever logic gate
* [Trending](Trending) - rising / falling / moving / steady / state change / value change
* [TrigSeq](TrigSeq) - two 8-step trigger sequences
* [TrigSeq16](TrigSeq16) - one 16-step trigger sequence
* [Tuner](Tuner) - oscillator frequency detector
* [TwoRings](TwoRings) - Highly configurable pair of Turing-Machine-style shift registers (formerly DualTM, replacement for ShiftReg/TM)
* [VectorEG](VectorEG) - Dual envelopes from a library of bipolar and unipolar shapes (customizable with the [Waveform Editor](Waveform-Editor))
* [VectorLFO](VectorLFO) - Dual LFOs from a library of bipolar and unipolar shapes
* [VectorMod](VectorMod) - Dual One-shots from a library of bipolar and unipolar shapes
* [VectorMorph](VectorMorph) - Dual (or linked) phase scrubbing along a library of bipolar and unipolar shapes
* [Voltage](Voltage) - static output CV
* [WTVCO](WTVCO) - WaveTable Voltage Controlled Oscillator
* [Xfader](Xfader) - basic CV mixer, with gate-controllable fader (formerly Mixer:Bal)
