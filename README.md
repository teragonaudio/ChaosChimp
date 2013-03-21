ChaosChimp
==========

ChaosChimp is an audio effect plugin designed to cause problems for your
sequencer. It's inspired by [Netflix's ChaosMonkey][1], which was built under
the philosophy that instead of hoping bad things never happen, they should be
caused to happen often so that one is better prepared for the worst.

I've seen many headlining DJ's let down by their gear onstage (I won't name
any names, but let's just say that it can happen to the best of us). In some
cases, they just slammed their laptop shut in disgust and walked off the
stage. Other times, the sound guys had to frantically mute the house speakers
to prevent feedback or satan saws (a nickname used for when a soundcard's
AD/DA stops receiving new data and just keeps playing the same buffer out the
speakers, causing a horrendouse sawtooth-wave-type noise). Sometimes the music
just stopped and everyone on the dancefloor stopped and looked around quite
confused. Does any of this sound familiar?

Most of the time, when this happens, the disgraced DJ's exits the stage and
proceeds to Twitter to flame about how buggy software X or hardware Y is.
*Screw that*. Have a backup plan in place, and train yourself how to react
when disaster strikes. ChaosChimp is designed to cause such disasters at
random intervals, allowing you to prepare for them in the safety of your own
studio.


Chaos Scenarios
---------------

ChaosChimp can currently simulate the following disasters:

* Audio dropouts
* Hogging a ton of CPU
* Try to crash the host
* Simulate feedback
* Leak lots of memory

The scenarios can be individually disabled, and the duration of the chaos and
frequency which it occurs can be tweaked within the plugin. ChaosChimp will
only run a disaster scenario when actual signal is being sent through it,
otherwise it could easily crash your host while you are simply configuring it.
For best results, place it on your master output channel and tweak the
settings before playing anything. Always save your work and keep backups. :)

Obviously, ChaosChimp is not intended to be used when performing. But more
bonus points to the ballsy DJ's who do.


[1]: http://techblog.netflix.com/2010/12/5-lessons-weve-learned-using-aws.html

