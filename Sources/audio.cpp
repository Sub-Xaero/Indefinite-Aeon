#include "audio.hpp"
#include "settings.hpp"

sf::Music music;
unsigned currentSong;
vector <string> Songs;
map <string, pair<sf::SoundBuffer, sf::Sound>> soundManager;
int soundCount = 0;

bool loadSound (const string &name, const string &filename) {
	auto &sound = soundManager[name] = pair<sf::SoundBuffer, sf::Sound> (sf::SoundBuffer(), sf::Sound() );
	//	SFML Internally has a limit of 256 sounds
	if (!sound.first.loadFromFile (filename) || soundCount >= 255) {
		soundManager.erase (name);
		return false;
		}
	else sound.second.setBuffer (sound.first);
	soundCount++;
	sound.second.setVolume (settings.soundVolume);
	return true;
	}

bool nextSong () {
	if (!settings.musicEnabled)
		return false;

	currentSong++;

	if (Songs.size() <= 0)
		return false;

	if (currentSong >= Songs.size() )
		currentSong = 0;

	if (!music.openFromFile (string (MUSIC_DIRECTORY) + Songs[currentSong]) )
		return false;
	else music.play();

	return true;
	}
