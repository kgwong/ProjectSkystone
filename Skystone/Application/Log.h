#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <sstream>
#include <string>

#define LOG											\
	Log(std::cout)

#define LOG_COUT									\
	LogDetail(std::cout, __FUNCTION__, __FILE__, __LINE__)   

#define LOG_STREAM(os)								\
	LogDetail(os, __FUNCTION__, __FILE__, __LINE__)   

class Log
{
public:
	Log(std::ostream& os);
	virtual ~Log();

	template <class T>
	Log& operator<<(const T& t);

protected:
	std::stringstream sstream_;
	std::ostream& outstream_;
};


template <class T>
inline Log& Log::operator<<(const T& t)
{
	sstream_ << t;
	return *this;
}

class LogDetail : public Log
{
public:
	LogDetail(std::ostream& os,
		const std::string& function,
		const std::string& file,
		int line);
	virtual ~LogDetail();

protected:
	const std::string& function_;
	const std::string& file_;
	int line_;

};


#endif //LOG_H