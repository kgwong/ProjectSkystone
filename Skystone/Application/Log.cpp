#include "Log.h"

#include <algorithm>

#include <fstream>

#include "Path.h"

std::set<std::string> Log::TAGS;

void Log::init()
{
	std::ifstream ifs(Path::getFullPath("log.config"));

	std::string token;
	while (ifs >> token)
	{
		TAGS.insert(token);
	}
}

Log::Log(std::ostream& os)
	:outstream_(os)
{
}

Log::~Log()
{
	sstream_ << std::endl;
	outstream_ << sstream_.rdbuf();
	outstream_.flush();
}


LogDetail::LogDetail(const std::string& tag,
	std::ostream& os,
	const std::string& function,
	const std::string& file,
	int line)
	:Log(os),
	tag_(tag),
	function_(function),
	file_(file),
	line_(line)
{
	int tempPos = file_.rfind('\\');
	//Release mode seems to handle source files differently
	int pos = tempPos >= 0 ? tempPos : 0;

	sstream_ << "[ " << file_.substr(pos+1) << " | " << line_ << " | " << tag_ << " ] ";
}

LogDetail::~LogDetail()
{
}
