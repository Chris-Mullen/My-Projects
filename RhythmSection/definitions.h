#ifndef DEFINITIONS_H
#define DEFINITIONS_H

const char * const STICK_CLICK = "./16bitWAV/stick_click_1_16.wav";
const char * const FINGER_CLICK = "./16bitWAV/snap_1_16.wav";
const char * const HAND_CLAP = "./16bitWAV/clap_1_16.wav";
const char * const COW_BELL = "./16bitWAV/cow_bell_1_16.wav";
const char * const HIGH_HAT_OPEN = "./16bitWAV/high_hat_open_1_16.wav";
const char * const HIGH_HAT_CLOSED = "./16bitWAV/high_hat_L_closed_1_16.wav";
const char * const KICK_DRUM = "./16bitWAV/kick_1_16.wav";
const char * const SNARE_DRUM_1 = "./16bitWAV/snare_L_1_16.wav";
const char * const SNARE_DRUM_2 = "./16bitWAV/snare_L_2_16.wav";
const char * const SNARE_BRUSH_1 = "./16bitWAV/snare_brush_1_16.wav";
const char * const SNARE_BRUSH_2 = "./16bitWAV/snare_brush_2_16.wav";
const char * const FLOOR_TOM_1 = "./16bitWAV/tom_1_L_16.wav";
const char * const FLOOR_TOM_2 = "./16bitWAV/tom_2_L_16.wav";
const char * const CRASH_CYMBAL = "./16bitWAV/cymbal_crash_1_16.wav";
const char * const RIDE_CYMBAL = "./16bitWAV/cymbal_ride_1_16.wav";

const char * const DIVIDER = "~~~~~~~~";
const char * const DIVIDER2 = "~~~~~~~~~~~~~~~~";
const char * const DIVIDER3 = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
const char * const DIVIDER4 = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";

const int SDL_SAMPLE_FREQUENCY = 48000;

const int SDL_BUFFER_SIZE = 512;  /*
                                  Smaller Buffer Sizes Reduce Latency 512
                                  */

const int SDL_RESERVED_CHANNELS = 32;

#endif
