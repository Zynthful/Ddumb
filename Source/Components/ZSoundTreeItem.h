/*
  ==============================================================================

    ZSoundTreeItem.h
    Created: 29 Dec 2024 6:40:15pm
    Author:  Jamie Carnell

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ZSoundTreeItem  : public juce::TreeViewItem
{
public:
    ZSoundTreeItem();
    ~ZSoundTreeItem() override;

    virtual Array<PropertyComponent*> CreatePropertyComponents() { return {}; }

    virtual bool CanPlay();
    virtual void Play();
    virtual void Stop();

    // Begin juce::TreeViewItem
    virtual bool mightContainSubItems() override;
    virtual juce::String getUniqueName() const override { return "SoundTreeItem"; }
    //virtual int getItemWidth() const override { return 50; }
    //virtual int getItemHeight() const override { return 50; }
    virtual void paintItem(Graphics& g, int width, int height) override;
    virtual void itemOpennessChanged(bool isNowOpen) override;
    //virtual std::unique_ptr<juce::Component> createItemComponent() override;
    virtual void itemSelectionChanged (bool isNowSelected) override;
    // End juce::TreeViewItem
    
    std::function<void()> onSelectionChanged;


private:
    juce::String DisplayName = "New Sound Tree Item";

    friend class ZSoundTreeComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ZSoundTreeItem)
};
