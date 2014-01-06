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

#ifndef __PLUGINPROCESSOR_H_270A7CC2__
#define __PLUGINPROCESSOR_H_270A7CC2__

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginParameters.h"
#include "TeragonPluginBase.h"
#include "PluginEditor.h"
#include "ChaosProvider.h"
#include "Resources.h"

using namespace teragon;

static const char *kParamAudioDropoutsEnabled = "Audio Dropouts Enabled";
static const char *kParamCpuHogEnabled = "CPU Hog Enabled";
static const char *kParamCrasherEnabled = "Crasher Enabled";
static const char *kParamFeedbackEnabled = "Feedback Enabled";
static const char *kParamMemoryLeakerEnabled = "Memory Eater Enabled";
// Must be updated if another chaos provider is added
static const int kNumChaosProviders = 5;

static const char *kParamChaosActive = "Chaos Active";
static const char *kParamPanic = "Panic";
static const char *kParamProbability = "Probability";
static const char *kParamDuration = "Chaos Duration";
static const char *kParamCooldown = "Cooldown Period";

static const char *kParamVersion = "Version";

// Prevent causing chaos during silence
static const float kSilenceThreshhold = 0.1f;

class ChaosChimpAudioProcessor : public TeragonPluginBase, public ParameterObserver {
public:
    ChaosChimpAudioProcessor();
    ~ChaosChimpAudioProcessor() {}

    // Playback
    void prepareToPlay(double sampleRate, int samplesPerBlock);
    void releaseResources();
    void processBlock(AudioSampleBuffer &buffer, MidiBuffer &midiMessages);

    const String getName() const { return JucePlugin_Name; }
    AudioProcessorEditor *createEditor();

    // PluginParameterObserver methods
    bool isRealtimePriority() const { return true; }
    void onParameterUpdated(const Parameter *parameter);

private:
    ChaosProvider *getChaosProviderForName(const String &name);
    void rebuildEnabledChaosProviders();
    void stopCausingChaos(); // greatest method name, or greatest method name EVER?

private:
    Array<String> enabledChaosProviders;
    ChaosProvider *currentChaosProvider;

    typedef enum {
        kStateSilence,
        kStateAudioPlaying,
        kStateCausingChaos,
        kStateCooldown,
    } PluginState;
    PluginState pluginState;
    unsigned long currentStateSample;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChaosChimpAudioProcessor)
};

#endif  // __PLUGINPROCESSOR_H_270A7CC2__
