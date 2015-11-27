#include "Log.h"

Log::Log(std::ostream& os,
	const std::string& function,
	const std::string& file,
	int line)
	:outstream_(os),
	function_(function),
	file_(file),
	line_(line)
{
}

Log::~Log()
{
	sstream_ << " [" << function_ << " | "
				<< file_.substr(file_.rfind('\\')) << " | "
				<< line_ << "]";
	sstream_ << std::endl;
	outstream_ << sstream_.rdbuf();
	outstream_.flush();
}