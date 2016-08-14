#include "includes.hpp"
#include "defines.hpp"
#include "resources.hpp"
#include "textureManager.hpp"
#include "progressModule.hpp"
#include "settings.hpp"
#include "audio.hpp"
#include "unispaceFont.hpp"

#include <thread>
#include <chrono>
#include <dirent.h>
#include <map>
#include <cereal/archives/binary.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/utility.hpp>

void resourceInit() {
	auto load = [&] (int &progress) {
		mtx.lock();
		progress = 0;
		mtx.unlock();

		bool status = true;
		int stages = 6, step = 100 / stages;

		auto updateProgress = [&] {
			mtx.lock();
			progress += step;
			mtx.unlock();
			};

		//TODO (Dylan #1 2016-01-11 ): FIX ERROR THROWING

		//NOTE Fonts Loaded Here
		if (!Font.loadFromMemory (unispaceFont, unispaceFont_size) )
			exit ( (int) RESOURCE_ERROR_CODE::FontError); // You're screwed if this fails
		if (!CleanFont.loadFromFile ("Fonts/Digitaldream.ttf") )
			throw (int) RESOURCE_ERROR_CODE::FontError;

		updateProgress();

			{
			std::ifstream is("Data/highscores");
			if (is) {
				cereal::BinaryInputArchive archive(is);
				archive(highscores);
				}
			is.close();
			if (highscores.size() < 14)
				highscores = {
					{"Lindy Marlon"      ,	1000},
					{"Ioachim Ares"      ,	5000},
					{"Verdandi Kamryn"   ,	10000},
					{"Norton Shirley"    ,	15000},
					{"Nikephoros Nina"   ,	20000},
					{"Saxon Korbin"      ,	25000},
					{"Brooks Christopher",	30000},
					{"Ammon Thane"       ,	35000},
					{"Lorne Vaughn"      ,	40000},
					{"Sosruko Medea"     ,	45000},
					{"Tim Parnel"        ,	50000},
					{"Cori Theobald"     ,	75000},
					{"Archibald Yasmine",	100000},
					{"Flanagan Dewayne",	25000},
				};
			sort(highscores.begin(), highscores.end(), [](pair<string, int> a, pair<string, int> b) {
				return b.second < a.second;
				});
			}

		//NOTE Data Loaded Here

		//		if (!loadNames() )
		//			throw ( (int) RESOURCE_ERROR_CODE::DataError);
		updateProgress();

		//NOTE Sounds Loaded Here
		if (!loadSound ("button", "Audio/Button.wav") ||
		        !loadSound ("explosion", "Audio/explosion.wav") ||
		        !loadSound ("hitmarker", "Audio/hitmarker.wav") ||
		        !loadSound ("shot", "Audio/shot.wav")
		   )
			throw RESOURCE_ERROR_CODE::AudioError;
		updateProgress();

		DIR *directory;
		dirent *entry;

		if ( (directory = opendir (MUSIC_DIRECTORY) ) != NULL) {
			while ( (entry = readdir (directory) ) != NULL) {
				string name (entry->d_name);
				if (name == "." || name == "..")
					continue;

				vector <string> extensions =
					{	"ogg", "wav", "flac", "aiff", "au", "raw", "paf", "svx", "nist", "voc", "ircam", "w64",
					"mat4", "mat5 pvf", "htk", "sds", "avr", "sd2", "caf", "wve", "mp	c2k", "rf64"
					};
				for (auto i : extensions) {
					if (name.find("." + i) != string::npos) {
						Songs.push_back (name);
						break;
						}
					}
				}
			closedir (directory);
			}
		else throw (int) RESOURCE_ERROR_CODE::AudioError;
		updateProgress();

		currentSong = 0;
		srand (time (0) + rand());
		if (Songs.size() > 0) {
			random_shuffle (Songs.begin(), Songs.end() );

			if (!music.openFromFile (string (MUSIC_DIRECTORY) + Songs[currentSong]) )
				throw  (int) RESOURCE_ERROR_CODE::AudioError;
			}
		updateProgress();

		//NOTE Textures Loaded Here
		if (!textureManager.loadTexture ("Background", "Graphics/Background.jpg") ||
		        !textureManager.loadTexture ("Tropical Ship", "Graphics/Tropical Ship.png") ||
		        !textureManager.loadTexture ("Blue Ship", "Graphics/Blue Ship.png") ||
		        !textureManager.loadTexture ("Green Ship", "Graphics/Green Ship.png") ||
		        !textureManager.loadTexture ("Pointy Ship", "Graphics/Pointy Ship.png") ||
		        !textureManager.loadTexture ("Red Ship", "Graphics/Red Ship.png") ||
		        !textureManager.loadTexture ("Fire Eye", "Graphics/Fire Eye.png") ||
		        !textureManager.loadTexture ("Pink Blob", "Graphics/Pink Blob.png") ||
		        !textureManager.loadTexture ("Green Blob", "Graphics/Green Blob.png") ||
		        !textureManager.loadTexture ("Planet1", "Graphics/Planet1.png") ||
		        !textureManager.loadTexture ("Planet2", "Graphics/Planet2.png") ||
		        !textureManager.loadTexture ("Explosion", "Graphics/Explosion.png") ||
		        !Icon.loadFromFile("Graphics/Icon.png"))
			throw  (int) RESOURCE_ERROR_CODE::GraphicsError;

		Background.setTexture(textureManager["Background"]);

		updateProgress();

		return status;
		};
	saveLoadScreen ("Loading", load);
	thread musicManager ([&] () {
		while (true) {
			if (settings.musicEnabled && music.getStatus() == sf::Music::Stopped)
				if (!nextSong() )
					return 0;
			this_thread::sleep_for (chrono::seconds (3) );
			}
		return 0;
		});
	musicManager.detach();
	}

void setGlobalVolume() {
	for (auto &i : soundManager)
		i.second.second.setVolume (settings.soundVolume);
	music.setVolume (settings.musicVolume);
	}

void instanciateWindow () {
	if (settings.graphics.fullscreenEnabled)
		App.create (settings.graphics.VideoMode, GAMENAME, sf::Style::Fullscreen);
	else App.create (settings.graphics.VideoMode, GAMENAME, sf::Style::Close);
	View.setSize (APP_WIDTH, APP_HEIGHT);
	View.setCenter (APP_WIDTH / 2, APP_HEIGHT / 2);
	App.setView (View);
	App.setFramerateLimit (30);
	App.setIcon(Icon.getSize().x, Icon.getSize().y , Icon.getPixelsPtr());
	App.setActive (true);
	}

sf::Vector2f mapPixelToCoords (sf::Event::MouseButtonEvent &pos) {
	return App.mapPixelToCoords (sf::Vector2i (pos.x, pos.y) );
	}

sf::Vector2f mapPixelToCoords (sf::Event::MouseMoveEvent &pos) {
	return App.mapPixelToCoords (sf::Vector2i (pos.x, pos.y) );
	}
