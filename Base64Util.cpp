
#include "Base64Util.h"

#include <algorithm>

std::string Base64Util::index = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

std::string Base64Util::encode(const std::string& raw)
{
	std::string base64;

	unsigned char* p = (unsigned char*)raw.data();
	int count = raw.length() / 3 + 1;
	int cursor = 0;
	for (int i = 0; i < count; i++)
	{
		unsigned char first = 0x00;
		unsigned char second = 0x00;
		unsigned char third = 0x00;
		unsigned char fourth = 0x00;

		unsigned char tmp = 0x00;

		/* first charactor */
		first = *(p) >> 2;
		base64.push_back(index[first]);

		/* second charactor */
		tmp = *(p) << 6;
		tmp = tmp >> 2;
		second = second | tmp;
		tmp = 0x00;
		cursor++;
		if (cursor < raw.length())
		{
			p++;
			second = second | (*(p) >> 4);
			base64.push_back(index[second]);

			/* third charactor */
			tmp = *(p) << 4;
			tmp = tmp >> 2;
			third = third | tmp;
			tmp = 0x00;
			cursor++;
			if (cursor < raw.length())
			{
				p++;
				third = third | (*(p) >> 6);
				base64.push_back(index[third]);

				/* fourth charactor */
				tmp = *(p) << 2;
				tmp = tmp >> 2;
				fourth = fourth | tmp;
				tmp = 0x00;
				base64.push_back(index[fourth]);

				cursor++;
				if (cursor < raw.length())
				{
					p++;
				}
				else
				{
					break;
				}
			}
			else
			{
				fourth = index.length() - 1;

				base64.push_back(index[third]);
				base64.push_back(index[fourth]);
			}
		}
		else
		{
			third = index.length() - 1;
			fourth = third;

			base64.push_back(index[second]);
			base64.push_back(index[third]);
			base64.push_back(index[fourth]);
		}
	}

	return base64;
}

std::string Base64Util::decode(const std::string& base64)
{
	std::string raw;

	if (base64.length() % 4 == 0)
	{
		int count = base64.length() / 4;

		/* equal sign count */
		int equalCount = std::count(base64.begin(), base64.end(), '=');

		for (int i = 0; i < count; i++)
		{
			unsigned char first = 0x00;
			unsigned char second = 0x00;
			unsigned char third = 0x00;

			unsigned char tmp = 0x00;

			/* first charactor */
			tmp = index.find(base64.at(i * 4));
			tmp = tmp << 2;
			first = first | tmp;
			tmp = 0x00;
			tmp = index.find(base64.at(i * 4 + 1));
			tmp = tmp >> 4;
			first = first | tmp;
			tmp = 0x00;
			raw.push_back(first);

			/* second charactor */
			tmp = index.find(base64.at(i * 4 + 1));
			tmp = tmp << 4;
			second = second | tmp;
			tmp = 0x00;
			tmp = index.find(base64.at(i * 4 + 2));
			tmp = tmp >> 2;
			second = second | tmp;
			tmp = 0x00;
			raw.push_back(second);

			/* third charactor */
			tmp = index.find(base64.at(i * 4 + 2));
			tmp = tmp << 6;
			third = third | tmp;
			tmp = 0x00;
			tmp = index.find(base64.at(i * 4 + 3));
			third = third | tmp;
			tmp = 0x00;
			raw.push_back(third);

			if (i + 1 >= count)
			{
				switch (equalCount)
				{
				case 1:
					raw.pop_back();
					break;
				case 2:
					raw.pop_back();
					raw.pop_back();
					break;
				default:
					break;
				}
			}
		}
	}

	return raw;
}
	