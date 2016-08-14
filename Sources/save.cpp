#include "save.hpp"
#include "settings.hpp"
#include "defines.hpp"

#include <cereal/archives/binary.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/utility.hpp>

void saveAndQuit () {
	std::ofstream os("Data/highscores");
	cereal::BinaryOutputArchive archive(os);
	archive(highscores);
	os.close();

	settings.save();
	exit (0);
	}
