/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#ifndef __PLUGINPROCESSOR_H_270A7CC2__
#define __PLUGINPROCESSOR_H_270A7CC2__

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginParameters.h"
#include "ChaosProvider.h"

using namespace teragon;

static const char* kParamAudioDropoutsEnabled = "Audio Dropouts Enabled";
static const char* kParamCpuHogEnabled = "CPU Hog Enabled";
static const char* kParamCrasherEnabled = "Crasher Enabled";
static const char* kParamFeedbackEnabled = "Feedback Enabled";
static const char* kParamMemoryLeakerEnabled = "Memory Leaker Enabled";
// Must be updated if another chaos provider is added
static const int kNumChaosProviders = 5;

static const char* kParamProbability = "Probability";
static const char* kParamDuration = "Chaos Duration";
static const char* kParamCooldown = "Cooldown Period";

// Prevent causing chaos during silence
static const float kSilenceThreshhold = 0.1f;

//==============================================================================
class ChaosChimpAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    ChaosChimpAudioProcessor();
    ~ChaosChimpAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();

    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);

    //==============================================================================
    AudioProcessorEditor* createEditor();
    bool hasEditor() const;

    //==============================================================================
    const String getName() const { return JucePlugin_Name; }

    int getNumParameters() { return parameters.size(); }

    float getParameter (int index) { return parameters[index]->getScaledValue(); }
    void setParameter (int index, float newValue) {
        parameters[index]->setScaledValue(newValue);
        rebuildEnabledChaosProviders();
    }

    const String getParameterName (int index) { return parameters[index]->getName().c_str(); }
    const String getParameterText (int index) { return parameters[index]->getDisplayText().c_str(); }

    const String getInputChannelName (int channelIndex) const { return String(channelIndex + 1); }
    const String getOutputChannelName (int channelIndex) const { return String(channelIndex + 1); }
    bool isInputChannelStereoPair (int index) const { return true; }
    bool isOutputChannelStereoPair (int index) const { return true; }

    bool acceptsMidi() const { return false; }
    bool producesMidi() const { return false; }
    bool silenceInProducesSilenceOut() const { return true; }
    double getTailLengthSeconds() const { return 0; }

    //==============================================================================
    int getNumPrograms() { return 0; }
    int getCurrentProgram() { return 0; }
    void setCurrentProgram (int index) {}
    const String getProgramName (int index) { return String::empty; }
    void changeProgramName (int index, const String& newName) {}

    //==============================================================================
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);

private:
    void rebuildEnabledChaosProviders();

private:
    // Parameter dataset and associated caches
    PluginParameterSet parameters;
    unsigned long durationInSamples;
    unsigned long cooldownInSamples;

    OwnedArray<ChaosProvider> chaosProviders;
    Array<ChaosProvider*> enabledChaosProviders;
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
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChaosChimpAudioProcessor)
};

#endif  // __PLUGINPROCESSOR_H_270A7CC2__
