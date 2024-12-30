/*
  ==============================================================================

	ZAudioEngine.cpp
	Created: 30 Dec 2024 1:53:40pm
	Author:  Zynthful

  ==============================================================================
*/

#include "ZAudioEngine.h"

//==============================================================================
ZAudioEngine::ZAudioEngine()
{
}

ZAudioEngine::~ZAudioEngine()
{
}

void ZAudioEngine::Initialize()
{
	Instance = new ZAudioEngine();
	Instance->Implementation = new ZAudioEngineImpl();
}

void ZAudioEngine::Update()
{
	Instance->Implementation->Update();
}

void ZAudioEngine::Deinitialize()
{
	delete Instance->Implementation;
	delete Instance;
}

void ZAudioEngine::LoadSound(const String& SoundName, bool bLooping, bool bStream)
{
	FMOD::Sound* Sound = nullptr;
	FMOD_MODE Mode = FMOD_DEFAULT;
	Mode |= FMOD_2D;
	const FMOD_RESULT Result = Instance->Implementation->System->createSound(SoundName.toUTF8(), Mode, nullptr, &Sound);
	if (Result != FMOD_OK || Sound == nullptr)
	{
		return;
	}

	Instance->Implementation->SoundMap.emplace(SoundName, Sound);
}

void ZAudioEngine::UnloadSound(const String& SoundName)
{
	auto SoundIt = Instance->Implementation->SoundMap.find(SoundName);
	if (SoundIt == Instance->Implementation->SoundMap.end())
	{
		// Couldn't find loaded sound in our cache
		return;
	}

	FMOD::Sound* Sound = SoundIt->second;
	Sound->release();
	Instance->Implementation->SoundMap.erase(SoundIt);
}

int ZAudioEngine::PlaySound(const String& SoundName)
{
	int ChannelId = Instance->Implementation->NextChannelId++;
	auto SoundIt = Instance->Implementation->SoundMap.find(SoundName);
	if (SoundIt == Instance->Implementation->SoundMap.end())
	{
		// Not loaded yet. So load it.
		LoadSound(SoundName, false, false);
		SoundIt = Instance->Implementation->SoundMap.find(SoundName);
		if (SoundIt == Instance->Implementation->SoundMap.end())
		{
			// Couldn't load
			return ChannelId;
		}
	}

	FMOD::Channel* Channel = nullptr;

	FMOD::Sound* Sound = SoundIt->second;
	Instance->Implementation->System->playSound(Sound, nullptr, false, &Channel);

	if (Channel != nullptr)
	{
		Instance->Implementation->Channels[ChannelId] = Channel;
	}

	return ChannelId;
}

ZAudioEngineImpl::ZAudioEngineImpl()
{
	FMOD_RESULT Result;

	Result = FMOD::System_Create(&System);
	if (Result != FMOD_OK)
	{
		jassertfalse;
		return;
	}

	Result = System->init(512, FMOD_INIT_NORMAL, nullptr);
	if (Result != FMOD_OK)
	{
		jassertfalse;
		return;
	}
}

ZAudioEngineImpl::~ZAudioEngineImpl()
{
}

void ZAudioEngineImpl::Update()
{
}
