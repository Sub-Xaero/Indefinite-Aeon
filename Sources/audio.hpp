#ifndef AUDIO_HPP
#define AUDIO_HPP

#include "includes.hpp"

#define MUSIC_DIRECTORY "Audio/Songs/"

extern sf::Music music;
extern unsigned currentSong;
extern vector <string> Songs;
extern map <string, pair<sf::SoundBuffer, sf::Sound>> soundManager;
extern int soundCount;

bool loadSound (const string &name, const string &filename);
bool nextSong ();

#endif // AUDIO_HPP

