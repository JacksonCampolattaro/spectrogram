# spectrogram

A live spectrogram visualizer for system audio.
Originally inspired by the spectrogram in [Foobar2000](https://www.foobar2000.org/)

A spectrogram is a type of plot for visualizing audio. 
In a spectrogram, 
the x-axis represents time, 
the y-axis represents frequency, 
and brightness/intensity represents audio volume. 
For example, a plot that shows a diagonal line would imply a rising tone. 

Modern operating systems provide mechanisms for accessing the audio that’s being played from any application context. 
Using the API, it’s possible to create software that analyzes the audio 
produced by any and all other programs on the system. 

We propose a program that uses this approach to generate a spectrogram of the system’s sound in real-time. 
It could also connect to other audio sources, like the computer’s microphone. 
Such a program has properties that other spectrogram generators don't provide:
- Not tethered to an audio source: 
  Similar programs need to load an audio file and play it themselves in order to show a spectrogram. 
  Ours would have no restrictions on the source of the audio, 
  it would even be possible to generate a spectrogram for a live audio source that isn’t recorded, like a Skype call!
- Real-time: 
  Other programs that can generate a plot from a live source (like a microphone), 
  tend to do it by recording short chunks of sound and processing them, 
  which results in a large delay visible in the plot. 
  Our program should be heavily optimized for latency, 
  and sound artifacts should appear on the plot with as little delay as possible.
