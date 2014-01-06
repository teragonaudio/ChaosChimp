ChaosChimp
==========

ChaosChimp is an audio effect plugin designed to cause problems for your
sequencer. Seriously! It's inspired by [Netflix's ChaosMonkey][1], which was
built under the philosophy that instead of hoping bad things never happen,
they should be forced to happen often so that one is better prepared for them.

![ChaosChimp User Interface](http://static.teragonaudio.com/ta_chaoschimp.png)


Why On Earth??
--------------

Why would someone want to run this plugin? To be fair, ChaosChimp should
probably *not* be used on stage. But it should be used during practice and
preparation sessions.

I've seen many headlining DJ's let down by their gear onstage. I won't name
any names, but let's just say that it can happen to the best of us. In some
cases, they just slammed their laptop in disgust and walked off the stage.
Other times, the sound technician had to frantically mute the house speakers
to prevent feedback or satan saws (a cruel term for when a soundcard's AD/DA
unit stops receiving new data and keeps outputting the last buffer received,
causing a horrendouse sawtooth-type noise). Sometimes the music just stopped
and everyone on the dancefloor stopped and looked around. Does any of this
sound familiar?

Most of the time, when this happens, the disgraced DJ's exits the stage,
proceeding to lament on Twitter/Facebook and complain about how buggy software
X or hardware Y ruined a perfect evening. *Screw that*. Always have a plan B
ready, and train yourself how to react when disaster strikes. ChaosChimp is
designed to cause such disasters at random intervals, allowing you to prepare
for them in the safety of your own studio.

Also, ChaosChimp can be useful for sequencer developers to simulate naughty or
misbehaving plugins.


Parameters
----------

At the top of the plugin are buttons to disable or enable the following types
of chaos:

* Audio dropouts
* Hogging a ton of CPU
* Try to crash the host (disabled by default)
* Simulate feedback (disabled by default). In actuality, this scenario will
  play a burst of white noise, as real feedback is quite harsh on
  loudspeakers (and ears).
* Leak lots of memory

ChaosChimp will run the scenarios at random intervals according to the values
set by the three knobs:

* Probability: Determines the likelihood that one of the selected chaos
  scenarios will be run.
* Duration: How long the chaos scenario will last (in seconds).
* Cooldown: How long to wait before running a new scenario after one has just
  occurred. Note that since the scenarios are run at random intervals, this
  value only guarantees the minimum amount of chaos-free time after a scenario
  has been run.

On the left side of the interface, there is a light which will illuminate when
a scenario is running. Below this light is a panic button, which will stop the
current scenario if you find it to be too overwhelming for your system.

For best results, place it on your master output channel and tweak the
settings before playing anything.


Licensing
---------

ChaosChimp is licensed under the GPL2. Further details can be found in the
LICENSE.txt file distributed with the software.


Disclaimer
----------

Teragon Audio is not responsible for any damage (either hardware or software)
caused by using this plugin. Use at your own risk, and always keep backups!


[1]: http://techblog.netflix.com/2010/12/5-lessons-weve-learned-using-aws.html

