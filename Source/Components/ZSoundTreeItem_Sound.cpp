/*
  ==============================================================================

    ZSoundTreeItem_Sound.cpp
    Created: 29 Dec 2024 6:43:12pm
    Author:  Jamie Carnell

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ZSoundTreeItem_Sound.h"

//==============================================================================
ZSoundTreeItem_Sound::ZSoundTreeItem_Sound()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

ZSoundTreeItem_Sound::~ZSoundTreeItem_Sound()
{
}

Array<PropertyComponent*> ZSoundTreeItem_Sound::CreatePropertyComponents()
{
    Array<PropertyComponent*> Components;
    
    Value RelativeFilePathPropertyValue(RelativeFilePath);
    TextPropertyComponent* RelativeFilePathPropertyComponent = new TextPropertyComponent(RelativeFilePathPropertyValue, "RelativeFilePath", 32, false, true);
    Components.add(RelativeFilePathPropertyComponent);
    
    return Components;
}

void ZSoundTreeItem_Sound::Play()
{
}

void ZSoundTreeItem_Sound::Stop()
{
}
