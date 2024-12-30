/*
  ==============================================================================

	ZAudioEngine.h
	Created: 30 Dec 2024 1:53:40pm
	Author:  Zynthful

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "fmod/core/fmod.hpp"

//==============================================================================
/*
*/
class ZAudioEngine
{
public:
	static ZAudioEngine* Get() { return Instance; }

	static void Initialize();
	static void Update();
	static void Deinitialize();

	static void LoadSound(const String& SoundName, bool bLooping, bool bStream);
	static void UnloadSound(const String& SoundName);

	/**
	 * Returns ChannelId
	 */
	static int PlaySound(const String& SoundName);

private:
	ZAudioEngine();
	~ZAudioEngine();

	static inline ZAudioEngine* Instance = nullptr;

	struct ZAudioEngineImpl* Implementation;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ZAudioEngine)
};

struct ZAudioEngineImpl
{
private:
	ZAudioEngineImpl();
	~ZAudioEngineImpl();

	void Update();

	FMOD::System* System = nullptr;

	std::map<String, FMOD::Sound*> SoundMap;

	int NextChannelId = -1;

	std::map<int, FMOD::Channel*> Channels;

	friend class ZAudioEngine;
};