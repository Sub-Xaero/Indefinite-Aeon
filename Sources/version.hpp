#ifndef VERSION_HPP
#define VERSION_HPP

namespace AutoVersion{
	
	//Software Status
	static const char STATUS[] =  "Release Candidate";
	static const char STATUS_SHORT[] =  "rc";
	
	//Standard Version Type
	static const long MAJOR  = 0;
	static const long MINOR  = 5;
	static const long BUILD  = 390;
	static const long REVISION  = 2207;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 699;
	#define RC_FILEVERSION 0,5,390,2207
	#define RC_FILEVERSION_STRING "0, 5, 390, 2207\0"
	static const char FULLVERSION_STRING [] = "0.5.390.2207";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 41;
	

}
#endif //VERSION_HPP
