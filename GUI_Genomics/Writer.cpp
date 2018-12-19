#include "Writer.h"
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <iostream>


void Writer::create_file() {

	DIR* dir = opendir("result");

	if (dir) {

		process();

	} else if (ENOENT == errno) {

		mkdir("../result", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		process();

	} else {

    std::cerr << "That's bad" << std::endl;
	}

}

//------------------------------------------------------------------------------
