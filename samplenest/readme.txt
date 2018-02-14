SampleNest
Sample or load up to 12 sounds or loops, then chop them up, loop, reverse  filter.
Then sequence, resample to a new file, mutate, sequence, resample…..
Inspired by early digital samplers and tape music.

Pressing Keys 1-12 plays the sample and allows you to edit parameters for that value
Pressing keys 13-24 allows you to edit parameters without retriggering
Move the knob ~2% before it starts responding after switching sample slot

On pages 1,2,4, aux controls a sequencer
On page 3 aux records audio sequence to a new wav file. 

IMPORTANT:
All samples are stored in /Media/samples/
You must create this folder before running the patch.
I’ve also uploaded an archive with some to get you started (mainly field recordings and other organelle patches).
This patch will find files in that folder ending in .wav (case sensitive!).

Samples/Loops recorded in this patch are saved in the format sn_####.wav

P1 - sample
1 sample select 
2 pitch 
3 pan
4 volume
Aux seq  play/stop/record 

P2 - loop
1 sample start point
2 sample send point - (if less than start value playback  is reversed)
3 playback mode - gate/ oneshot / loop / pingpong 
4 Env - adds attack and decay, if 0 samples may click
Aux  seq play/stop/record 
Note - start/end can actually start/end slightly before the sample


P3 - mix/rec - (global effects, pre-recorder)
1 - Locut - lowpass filter
2 - Hicut - highpass filter
3 - input vol- volume of input to monitor in as well as to record
4 - Resample Vol - volume of output of samples to record (set to 0 to only record input)
Aux- press to arm, if the sequencer is playing the recording will automatically sync with the next iteration of the loop
If the sequencer is idle, press again to start recording, play the keys or input to line-in, then press to end (max 15 seconds)
All recordings are mono.

P4 - FX (recorder does not go through the FX)
1- Delay fdbk
2- delay time
3 Reverb size
4 reverb mix

TIPS/NOTES:
1: After loading a recorded sequence and loading it into a new slot, you can record a new sequence in sync with the first one.
Play the recorded sample while playing a new sequence.
You can then turn the volume off on the last recorded sequence and record the new sequence to a file
After you make a set of synchronized sequences , then load them into slots and make a song structure by triggering the loops for different parts/layers/sections.

2: Fiddling with pitch and sample loop end points in real-time for some interesting effects

3: Most parameters are saved when the patch is shutdown, but if samples are added/removed from the samples directory, each slot may have a different sample
