/*
  ==============================================================================

    ZSoundTreeComponent.h
    Created: 29 Dec 2024 6:32:25pm
    Author:  Jamie Carnell

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ZSoundTreeItem;

//==============================================================================
/*
*/
class ZSoundTreeComponent  : public juce::TreeView
{
public:
    ZSoundTreeComponent();
    ~ZSoundTreeComponent() override;

    virtual void paint (juce::Graphics&) override;
    virtual void resized() override;

    virtual void mouseDown(const juce::MouseEvent& event) override;
    virtual void mouseUp(const juce::MouseEvent& event) override;

    virtual void ItemSelected(ZSoundTreeItem* SoundTreeItem);

    std::function<void(ZSoundTreeItem*)> OnItemSelected;

private:
    void RegisterItem(ZSoundTreeItem* SoundTreeItem);

    std::unique_ptr<ZSoundTreeItem> RootItem;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ZSoundTreeComponent)
};
