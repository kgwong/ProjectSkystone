#include "Log.h"

#include <algorithm>


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


LogDetail::LogDetail(std::ostream& os,
	const std::string& function,
	const std::string& file,
	int line)
	:Log(os),
	function_(function),
	file_(file),
	line_(line)
{
}

LogDetail::~LogDetail()
{
	int tempPos = file_.rfind('\\');
	//Release mode seems to handle source files differently
	int pos = tempPos >= 0 ? tempPos : 0;

	sstream_ << " [" << function_ << " | "
		<< file_.substr(pos) << " | "
		<< line_ << "]";
	sstream_ << std::endl;
	outstream_ << sstream_.rdbuf();
	outstream_.flush();
}
