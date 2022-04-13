
#ifndef __BASE64UTIL_H__
#define __BASE64UTIL_H__

#include <string>

class Base64Util
{
public:
	static std::string encode(const std::string& raw);
	static std::string decode(const std::string& base64);

private:
	static std::string index;
};

#endif



