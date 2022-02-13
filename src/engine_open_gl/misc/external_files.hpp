#pragma once

#include <string>

/*This is a collection of functions to get the locations for external files in 
* relation to the exe
*/


class external_paths
{
public:
	external_paths() { debug_loc = true; }

	std::string get_audio_loc(std::string item) { return combine(debug, audio, item); }
	std::string get_fonts_loc(std::string item) { return combine(debug, fonts, item); }
	std::string get_objs_loc(std::string item)  { return combine(debug, objects, item); }
	std::string get_textures_loc(std::string item) { return combine(debug, textures, item); }

	std::string get_audio_loc() { return combine(debug, audio); }
	std::string get_fonts_loc() { return combine(debug, fonts); }
	std::string get_objs_loc() { return combine(debug, objects); }
	std::string get_textures_loc() { return combine(debug, textures); }

private:

	std::string combine(std::string sr1, std::string sr2) {
		std::string out = sr1; 
		out.append(sr2); 
		return out;
	}

	std::string combine(std::string sr1, std::string sr2, std::string sr3 ) {
		std::string out = sr1; 
		out.append(sr2);
		out.append(sr3);
		return out;
	}

	bool debug_loc = false;

	std::string debug = "../../../resources/Assets_libs/";
	std::string release = "resources/Assets_libs/";

	std::string audio = "audio/";
	std::string fonts = "fonts/";
	std::string objects = "objects/";
	std::string textures = "textures/";

};

