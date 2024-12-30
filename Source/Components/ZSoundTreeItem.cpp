/*
  ==============================================================================

    ZSoundTreeItem.cpp
    Created: 29 Dec 2024 6:40:15pm
    Author:  Jamie Carnell

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ZSoundTreeItem.h"

//==============================================================================
ZSoundTreeItem::ZSoundTreeItem()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

ZSoundTreeItem::~ZSoundTreeItem()
{
}

bool ZSoundTreeItem::CanPlay()
{
    return false;
}

void ZSoundTreeItem::Play()
{
}

void ZSoundTreeItem::Stop()
{
}

bool ZSoundTreeItem::mightContainSubItems()
{
    return getNumSubItems() > 0;
}

void ZSoundTreeItem::paintItem(Graphics& g, int width, int height)
{
    TreeViewItem::paintItem(g, width, height);

    // if this item is selected, fill it with a background colour..
    if (isSelected())
    {
        g.fillAll(juce::Colours::blue.withAlpha(0.3f));
    }

    g.setColour(juce::Colours::black);
    g.drawText(DisplayName, 4, 0, width - 4, height, juce::Justification::left, true);
}

void ZSoundTreeItem::itemOpennessChanged(bool isNowOpen)
{
    TreeViewItem::itemOpennessChanged(isNowOpen);

    if (isNowOpen)
    {
        // if we've not already done so, we'll now add the tree's sub-items. You could
        // also choose to delete the existing ones and refresh them if that's more suitable
        // in your app.
        if (getNumSubItems() == 0)
        {
            // create and add sub-items to this node of the tree, corresponding to
            // each sub-element in the XML..

            //forEachXmlChildElement(xml, child)
            //{
            //    jassert(child != 0);
            //    addSubItem(new TreeViewDemoItem(*child));
            //}
        }
    }
    else
    {
        // in this case, we'll leave any sub-items in the tree when the node gets closed,
        // though you could choose to delete them if that's more appropriate for
        // your application.
    }
    //clearSubItems();

    //if (isNowOpen)
    //{
    //    for (int Index = 0; Index < getNumSubItems(); ++Index)
    //    {
    //        addSubItem(getSubItem(Index));
    //    }
    //}
}

void ZSoundTreeItem::itemSelectionChanged(bool isNowSelected)
{
    TreeViewItem::itemSelectionChanged(isNowSelected);
    if (onSelectionChanged != nullptr)
    {
        onSelectionChanged();
    }
}

//std::unique_ptr<juce::Component> ZSoundTreeItem::createItemComponent()
//{
//    std::unique_ptr<juce::DrawableText> Text(new juce::DrawableText());
//    Text->setText(DisplayName);
//    return Text;
//}
