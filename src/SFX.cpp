#include "SFX.hpp"
#include "Log.hpp"

std::vector<SFX*> SFX::all;

SFX::SFX(std::string filepath):
	sfx(nullptr),
	filepath(filepath),
	channel(0)
{
	SFX::all.push_back(this);

	this->sfx = Mix_LoadWAV(this->filepath.c_str());
	if (!this->sfx)
	{
		Log::error("Mix_LoadWAV: Couldn't load SFX on '" +
		           this->filepath +
		           "':" +
		           Mix_GetError());
	}
	else
		Log::debug("SFX::load '" + this->filepath + "'");
}
SFX::~SFX()
{
	if (this->sfx)
		Mix_FreeChunk(this->sfx);
}
bool SFX::play(int times)
{
	if (!this->sfx)
		return false;

	if (this->isPlaying())
		return false;

	// If we send 0 to `Mix_PlayChannel` it plays once.
	// If we send 1 it plays twice and so on...
	if (times > 0)
		times--;

	int chan = Mix_PlayChannel(-1, this->sfx, times);
	if (chan == -1)
	{
		Log::error("Mix_PlayChannel: Couldn't play SFX on '" +
		           this->filepath +
		           "':" +
		           Mix_GetError());
		return false;
	}
	this->channel = chan;

//  how can I make it call a member function when done? apparently it
//  doesnt work this way
//  Mix_HookSFXFinished(this->finishedPlaying);

	return true;
}
void SFX::pause()
{
	// We don't want to pause other SFXs that
	// might be playing on this channel.

	if (Mix_GetChunk(this->channel) == this->sfx)
		Mix_Pause(this->channel);
}
void SFX::unpause()
{
	if (Mix_GetChunk(this->channel) == this->sfx)
		Mix_Resume(this->channel);
}
void SFX::stop()
{
	if (Mix_GetChunk(this->channel) == this->sfx)
		Mix_HaltChannel(this->channel);
}
bool SFX::isPlaying()
{
	return Mix_Playing(this->channel) && !isPaused();
}
bool SFX::isPaused()
{
	return Mix_Paused(this->channel);
}
int SFX::getVolume()
{
	return Mix_VolumeChunk(this->sfx, -1);
}
int SFX::setVolume(int volume)
{
	return Mix_VolumeChunk(this->sfx, volume);
}
int SFX::setVolumeAll(int volume)
{
	int previous = 0;

	for (std::vector<SFX*>::iterator it = SFX::all.begin();
	     it != SFX::all.end();
	     ++it)
	{
		previous = Mix_VolumeChunk((*it)->sfx, volume);
	}
	return previous;
}
int SFX::getMaxVolume()
{
	return MIX_MAX_VOLUME;
}
void SFX::stopAll()
{
	Mix_HaltChannel(-1);
}
void SFX::pauseAll()
{
	Mix_Pause(-1);
}
void SFX::unpauseAll()
{
	Mix_Resume(-1);
}

