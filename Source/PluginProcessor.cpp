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
const String ChaosChimpAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int ChaosChimpAudioProcessor::getNumParameters()
{
    return 0;
}

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

const String ChaosChimpAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String ChaosChimpAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool ChaosChimpAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool ChaosChimpAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool ChaosChimpAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ChaosChimpAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ChaosChimpAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double ChaosChimpAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ChaosChimpAudioProcessor::getNumPrograms()
{
    return 0;
}

int ChaosChimpAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ChaosChimpAudioProcessor::setCurrentProgram (int index)
{
}

const String ChaosChimpAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void ChaosChimpAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void ChaosChimpAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void ChaosChimpAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void ChaosChimpAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < getNumInputChannels(); ++channel)
    {
        float* channelData = buffer.getSampleData (channel);

        // ..do something to the data...
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
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ChaosChimpAudioProcessor::createEditor()
{
    return new ChaosChimpAudioProcessorEditor (this);
}

//==============================================================================
void ChaosChimpAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ChaosChimpAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ChaosChimpAudioProcessor();
}
