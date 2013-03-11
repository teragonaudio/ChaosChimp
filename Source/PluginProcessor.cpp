/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ChaosAudioDropouts.h"
#include "ChaosCpuHog.h"
#include "ChaosCrasher.h"
#include "ChaosFeedbackSimulator.h"
#include "ChaosMemoryLeaker.h"

//==============================================================================
ChaosChimpAudioProcessor::ChaosChimpAudioProcessor()
{
    // First add parameters corresponding to the chaos providers so that the indexes match
    parameters.add(new BooleanParameter(kParamAudioDropoutsEnabled, true));
    chaosProviders.add(new ChaosAudioDropouts());
    parameters.add(new BooleanParameter(kParamCpuHogEnabled, true));
    chaosProviders.add(new ChaosCpuHog());
    parameters.add(new BooleanParameter(kParamCrasherEnabled, false));
    chaosProviders.add(new ChaosCrasher());
    parameters.add(new BooleanParameter(kParamFeedbackEnabled, true));
    chaosProviders.add(new ChaosFeedbackSimulator());
    parameters.add(new BooleanParameter(kParamMemoryLeakerEnabled, true));
    chaosProviders.add(new ChaosMemoryLeaker());

    parameters.add(new FloatParameter(kParamProbability, 0.0, 10.0, 0.0));
    parameters.add(new FloatParameter(kParamDuration, 0.1, 20.0, 1.0));
    parameters.add(new FloatParameter(kParamCooldown, 0.1, 20.0, 1.0));
}

ChaosChimpAudioProcessor::~ChaosChimpAudioProcessor()
{
}

//==============================================================================

void ChaosChimpAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    currentChaosProvider = nullptr;
    durationInSamples = parameters[kParamDuration]->getValue() * sampleRate;
    cooldownInSamples = parameters[kParamCooldown]->getValue() * sampleRate;
    currentStateSample = 0;
    rebuildEnabledChaosProviders();
}

void ChaosChimpAudioProcessor::releaseResources()
{
    chaosProviders.clear(true);
}

void ChaosChimpAudioProcessor::rebuildEnabledChaosProviders()
{
    enabledChaosProviders.clear();
    for (int providerIndex = 0; providerIndex < kNumChaosProviders; ++providerIndex) {
        if (parameters[providerIndex]->getValue()) {
            enabledChaosProviders.add(chaosProviders[providerIndex]);
        }
    }
}

void ChaosChimpAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    bool inputIsSilent = true;
    float* channelData = buffer.getSampleData(0);
    for (int i = 0; i < buffer.getNumSamples(); ++i) {
        if (fabs(channelData[i]) >= kSilenceThreshhold) {
            inputIsSilent = false;
            break;
        }
    }

    switch (pluginState) {
        case kStateSilence:
            if (!inputIsSilent) {
                pluginState = kStateAudioPlaying;
            }
            break;
        case kStateAudioPlaying: {
            double randomPercent = (double)random() / (double)RAND_MAX;
            if (randomPercent < parameters[kParamProbability]->getValue()) {
                if (enabledChaosProviders.size() > 0) {
                    int randomIndex = random() % enabledChaosProviders.size();
                    currentChaosProvider = enabledChaosProviders[randomIndex];
                    currentStateSample = 0;
                    pluginState = kStateCausingChaos;
                    // Note that the chaos will actually start *next* block. Whatever.
                }
            }
            break;
        }
        case kStateCausingChaos:
            currentStateSample += buffer.getNumSamples();
            if (currentStateSample > durationInSamples) {
                currentChaosProvider = nullptr;
                currentStateSample = 0;
                pluginState = kStateCooldown;
            }
            break;
        case kStateCooldown:
            currentStateSample += buffer.getNumSamples();
            if (currentStateSample > cooldownInSamples) {
                currentStateSample = 0;
                pluginState = kStateSilence;
            }
            break;
        default:
            break;
    }

    if (pluginState == kStateCausingChaos && currentChaosProvider != nullptr) {
        for (int channel = 0; channel < getNumInputChannels(); ++channel) {
            channelData = buffer.getSampleData(channel);
            currentChaosProvider->doChaos(channelData, buffer.getNumSamples());
        }
    }

    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i) {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
}

//==============================================================================
bool ChaosChimpAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* ChaosChimpAudioProcessor::createEditor()
{
    return new ChaosChimpMainEditor(this);
}

//==============================================================================
void ChaosChimpAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    XmlElement xml(getName());
    for (int i = 0; i < getNumParameters(); i++) {
        PluginParameter *parameter = parameters[i];
        xml.setAttribute(parameter->getSafeName().c_str(), parameter->getValue());
    }
}

void ChaosChimpAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState != 0 && xmlState->hasTagName(getName())) {
        for (int i = 0; i < getNumParameters(); i++) {
            PluginParameter *parameter = parameters[i];
            if (xmlState->hasAttribute(parameter->getSafeName().c_str())) {
                parameter->setValue(xmlState->getDoubleAttribute(parameter->getSafeName().c_str()));
            }
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ChaosChimpAudioProcessor();
}
