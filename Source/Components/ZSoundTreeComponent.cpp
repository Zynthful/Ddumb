/*
  ==============================================================================

	ZSoundTreeComponent.cpp
	Created: 29 Dec 2024 6:32:25pm
	Author:  Jamie Carnell

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ZSoundTreeComponent.h"
#include "ZSoundTreeItem_Sound.h"

//==============================================================================
ZSoundTreeComponent::ZSoundTreeComponent()
{
	// In your constructor, you should add any child components, and
	// initialise any special settings that your component needs.

	setName("Sound Tree");

	RootItem = std::make_unique<ZSoundTreeItem>();
	setRootItem(RootItem.get());
	setRootItemVisible(false);
	setMultiSelectEnabled(true);

	// Build context menu
	constexpr int SoundId = 1;
	juce::PopupMenu AddChildMenu;
	AddChildMenu.addItem(SoundId, "Sound");

	ContextMenu = std::make_unique<juce::PopupMenu>();
	ContextMenu->addSubMenu("Add...", AddChildMenu);
}

ZSoundTreeComponent::~ZSoundTreeComponent()
{
	RootItem.release();
	ContextMenu.release();
	deleteRootItem();
}

void ZSoundTreeComponent::paint (juce::Graphics& g)
{
	TreeView::paint(g);

	g.setColour(juce::Colours::grey);
	
	// Draw an outline around the component
	g.drawRect(getLocalBounds(), 1);
	
	//g.drawText ("ZSoundTreeComponent", getLocalBounds(),
	//            juce::Justification::centred, true);   // draw some placeholder text
}

void ZSoundTreeComponent::resized()
{
	TreeView::resized();

}

void ZSoundTreeComponent::mouseDown(const juce::MouseEvent& event)
{
	TreeView::mouseDown(event);
}

void ZSoundTreeComponent::mouseUp(const juce::MouseEvent& event)
{
	TreeView::mouseUp(event);

	const bool bClicked = event.mouseWasClicked();
	if (bClicked && !event.mods.isCtrlDown())
	{
		const int NumberOfSelectedItems = getNumSelectedItems();
		bool bHitAnySelectedItem = false;
		for (int Index = 0; Index < NumberOfSelectedItems; ++Index)
		{
			if (getItemComponent(getSelectedItem(Index))->contains(event.getPosition()))
			{
				bHitAnySelectedItem = true;
				break;
			}
		}
		if (!bHitAnySelectedItem)
		{
			clearSelectedItems();
		}
	}

	const bool bRightClicked = bClicked && event.mods.isRightButtonDown();
	if (bRightClicked)
	{
		ContextMenu->showMenuAsync(juce::PopupMenu::Options(),
			[this](int result)
		{
			if (result == 0)
			{
				// user dismissed the menu without picking anything
			}

			else if (result == 1)
			{
				// Add Sound TreeItem
				ZSoundTreeItem_Sound* Sound = new ZSoundTreeItem_Sound();
				getRootItem()->addSubItem(Sound);
				RegisterItem(Sound);
			}
		});
	}
}

void ZSoundTreeComponent::ItemSelected(ZSoundTreeItem* SoundTreeItem)
{
	OnItemSelected(SoundTreeItem);
}

void ZSoundTreeComponent::RegisterItem(ZSoundTreeItem* SoundTreeItem)
{
	SoundTreeItem->onSelectionChanged = [this, SoundTreeItem] { ItemSelected(SoundTreeItem); };
}
