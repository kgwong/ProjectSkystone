#ifndef PATH_H
#define PATH_H

#include <string>

class Path
{
public:
	static void initBasePath();
	static std::string getBasePath();
	static std::string getFullPath(std::string relativePath);

private:
	static std::string basePath;

	Path() = delete;
};

#endif //PATH_H
