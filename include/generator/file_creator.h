/**
* File Creator: This object's job is to
* create files given a path in a string. 
* It also provides a way to check for the 
* existence of a file.
*/

#include <string>
#include <boost/filesystem.hpp>

#ifndef __FILE_CREATOR_H__
#define __FILE_CREATOR_H__

class FileCreator
{
	private:
	std::string FILE_PATH;
        boost::filesystem::path convertStringToPath(std::string);

	public:
		FileCreator(std::string);
		~FileCreator();

        bool checkFileExists(std::string); //overloaded for string path
        bool checkFileExists(boost:filesystem::path); //overloaded for boost path
        void createFile(std::string);
        void createFile(boost::filesystem::path);
};

#endif
