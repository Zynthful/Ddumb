/*
  ==============================================================================

    ZSoundTreeItem_Sound.h
    Created: 29 Dec 2024 6:43:12pm
    Author:  Jamie Carnell

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "ZSoundTreeItem.h"

//==============================================================================
/*
*/
class ZSoundTreeItem_Sound  : public ZSoundTreeItem
{
public:
    ZSoundTreeItem_Sound();
    ~ZSoundTreeItem_Sound() override;

    virtual Array<PropertyComponent*> CreatePropertyComponents() override;

    virtual bool CanPlay() { return true; }
    virtual void Play() override;
    virtual void Stop() override;

private:
    // Relative to the "Originals" directory of the project
    String RelativeFilePath;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ZSoundTreeItem_Sound)
};
