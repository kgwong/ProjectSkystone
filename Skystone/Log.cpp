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
	sstream_ << "\n" << "\t";
	sstream_ << "[" << function_ << "]"
				<< " [" << file_ << "] "
				<< " (Line: " << line_ << ")";
	sstream_ << "\n\n";
	outstream_ << sstream_.rdbuf();
	outstream_.flush();
}