/*
 * Copyright (c) 2013 - Teragon Audio LLC
 *
 * Permission is granted to use this software under the terms of either:
 * a) the GPL v2 (or any later version)
 * b) the Affero GPL v3
 *
 * Details of these licenses can be found at: www.gnu.org/licenses
 *
 * This software is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * ------------------------------------------------------------------------------
 *
 * This software uses the JUCE library.
 *
 * To release a closed-source product which uses JUCE, commercial licenses are
 * available: visit www.juce.com for more information.
 */

#include "ChaosFeedbackSimulator.h"

static const float kGain = 0.5f;

void ChaosFeedbackSimulator::doChaos(float *channelData, int numSamples) {
    // Note that the name of this class implies *SIMULATOR*. Feedback sucks, and
    // my ears fear for it. So instead we replace the output channel with static
    // hissing. The goal here is to train that all-important reflect to slam the
    // "mute" button, not to blow out a nice pair of studio monitors...

    // Algorithm borrowed from MusicDSP.org:
    // http://musicdsp.org/archive.php?classid=1#216
    for(int i = 0; i < numSamples; ++i) {
        x1 ^= x2;
        channelData[i] = x2 * kGain;
        x2 += x1;
    }
}
