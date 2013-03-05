/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
ChaosChimpAudioProcessor::ChaosChimpAudioProcessor()
{
}

ChaosChimpAudioProcessor::~ChaosChimpAudioProcessor()
{
}

//==============================================================================

float ChaosChimpAudioProcessor::getParameter (int index)
{
    return 0.0f;
}

void ChaosChimpAudioProcessor::setParameter (int index, float newValue)
{
}

const String ChaosChimpAudioProcessor::getParameterName (int index)
{
    return String::empty;
}

const String ChaosChimpAudioProcessor::getParameterText (int index)
{
    return String::empty;
}

//==============================================================================
void ChaosChimpAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
}

void ChaosChimpAudioProcessor::releaseResources()
{
}

void ChaosChimpAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    for (int channel = 0; channel < getNumInputChannels(); ++channel)
    {
        float* channelData = buffer.getSampleData (channel);
    }

    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
    {
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
}

void ChaosChimpAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ChaosChimpAudioProcessor();
}
