#include "PluginProcessor.h"
#include "PluginEditor.h"

AnimeTuneAudioProcessor::AnimeTuneAudioProcessor()
    : parameters(*this, nullptr, "PARAMETERS", createParameterLayout()) {}

AnimeTuneAudioProcessor::~AnimeTuneAudioProcessor() {}

juce::AudioProcessorValueTreeState::ParameterLayout AnimeTuneAudioProcessor::createParameterLayout() {
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterFloat>("retune", "Retune Speed", juce::NormalisableRange<float>(1.0f, 400.0f, 1.0f, 0.5f), 120.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("formant", "Formant Shift", juce::NormalisableRange<float>(0.8f, 2.0f, 0.01f), 1.35f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("strength", "Correction Strength", juce::NormalisableRange<float>(0.0f, 100.0f, 0.1f), 85.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("pitch", "Pitch Shift (Semi)", juce::NormalisableRange<float>(-12.0f, 12.0f, 1.0f), 0.0f));

    return { params.begin(), params.end() };
}

void AnimeTuneAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {}

void AnimeTuneAudioProcessor::releaseResources() {}

void AnimeTuneAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) {
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());
}

const juce::String AnimeTuneAudioProcessor::getProgramName(int index) {
    const char* names[10] = {
        "1. Natural Tune", "2. Anime Soft", "3. Anime Bright", "4. Chibi / Cute",
        "5. Cyber Idol", "6. Hard Tune (Robot)", "7. Whisper Anime",
        "8. Male->Female Nat", "9. Male->Female Airy", "10. Male->Female Idol"
    };
    if (index >= 0 && index < 10) return names[index];
    return "Default";
}

juce::AudioProcessorEditor* AnimeTuneAudioProcessor::createEditor() {
    return new AnimeTuneAudioProcessorEditor(*this);
}

void AnimeTuneAudioProcessor::getStateInformation(juce::MemoryBlock& destData) {
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void AnimeTuneAudioProcessor::setStateInformation(const void* data, int sizeInBytes) {
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState != nullptr && xmlState->hasTagName(parameters.state.getType()))
        parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new AnimeTuneAudioProcessor();
}
