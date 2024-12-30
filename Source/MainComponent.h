#pragma once

#include <JuceHeader.h>

#include "Components/ZSoundTreeComponent.h"

enum class EZTransportState
{
    Stopped,
    Starting,
    Playing,
    Stopping
};

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

    virtual void mouseDown(const juce::MouseEvent& event) override;

private:
    //==============================================================================
    // Your private member variables go here...

    ZSoundTreeComponent SoundTree;
    PropertyPanel PropertyPanel;

    AudioFormatManager AudioFormatManager;
    juce::TextButton openButton;
    std::unique_ptr<FileChooser> ImportFileChooser;

    void openButtonClicked();

    void OnSoundTreeItemSelected(ZSoundTreeItem* SoundTreeItem);
    void ShowDetailsFor(ZSoundTreeItem* HasDetails);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
