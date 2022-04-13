
#include <iostream>

#include "Base64Util.h"

void test1() 
{
	std::string raw = "abc";

	std::string base64 = Base64Util::encode(raw);
	std::string decode = Base64Util::decode(base64);

	printf("raw: %s\n", raw.data());
	printf("--------------------------------\n");
	printf("encode base64: %s\n",base64.data());
	printf("--------------------------------\n");
	printf("decode base64: %s\n", decode.data());
}

void test2()
{
	FILE* fp = nullptr;
	char buffer[1024] = { 0 };
	std::string raw;

	fp = fopen("./gaoyuanyuan.png", "rb");
	int length = fread(buffer, 1, sizeof(buffer), fp);
	while (length)
	{
		raw.append(std::string(buffer, length));
		memset(buffer, 0, sizeof(buffer));
		length = fread(buffer, 1, sizeof(buffer), fp);
	}
	fclose(fp);

	std::string base64 = Base64Util::encode(raw);
	std::string decode = Base64Util::decode(base64);

	printf("encode base64: \n");
	printf("%s\n", base64.data());
	printf("--------------------------------\n");
	printf("decode base64:(hexadecimal print) \n");
	for (int i = 0;i < decode.length();i++)
	{
		printf("%x ",(unsigned char)decode.at(i));
		if ((i + 1) % 16 == 0) 
		{
			printf("\n");
		}
	}
}

int main(int argc, char** argv)
{
	/* string test */
	//test1();

	/* binary file test */
	//test2();

	return 0;
}
