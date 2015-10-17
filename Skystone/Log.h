#ifndef LOG_H
#define LOG_H

#define LOG											\
	Log(std::cout, __FUNCTION__, __FILE__, __LINE__)   

#define LOG_STREAM(os)								\
	Log(os, __FUNCTION__, __FILE__, __LINE__)   

#include <iostream>
#include <sstream>
#include <string>


class Log
{
public:
	Log(std::ostream& os,
		const std::string& function,
		const std::string& file,
		int line);
	~Log();

	template <class T>
	Log& operator<<(const T& t);
 
private:
	std::stringstream sstream_;
	std::ostream& outstream_;
	const std::string& function_;
	const std::string& file_;
	int line_;

};

#endif //LOG_H

template<class T>
inline Log & Log::operator<<(const T & t)
{
	sstream_ << t;
	return *this;
}
