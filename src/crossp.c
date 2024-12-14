#include "crossp.h"
#include <ctype.h>

int strincmp(const char *a, const char *b, uint64_t maxLen)
{
	int ca, cb, i = 0;
	do
	{
		ca = (unsigned char)*a++;
		cb = (unsigned char)*b++;
		ca = tolower(toupper(ca));
		cb = tolower(toupper(cb));
	} while (ca == cb && ca != '\0' && i++ < maxLen - 1);
	return ca - cb;
}

size_t strcspnc(const char *str1, const char *str2)
{
	const char *sc1, *sc2;
	for (sc1 = str1; *sc1 != '\0'; ++sc1)
	{
		for (sc2 = str2; *sc2 != '\0'; ++sc2)
		{
			if (*sc1 == *sc2)
				return (sc1 - str1);
		}
	}
	return (sc1 - str1); // terminating nulls match.
}

size_t strspnc(const char *s1, const char *s2)
{
	const char *sc1, *sc2;
	for (sc1 = s1; *sc1 != '\0'; ++sc1)
	{
		for (sc2 = s2;; ++sc2)
		{
			if (*sc2 == '\0')
			{
				return (sc1 - s1);
			}
			else if (*sc1 == *sc2)
			{
				break;
			}
		}
	}
	return (sc1 - s1);
}

char *strtok_r(char *str, const char *delim, char **saveptr)
{
	char *end;
	if (str == NULL)
		str = *saveptr;
	if (*str == '\0')
	{
		*saveptr = str;
		return NULL;
	}
	/* Scan leading delimiters.  */
	str += strspnc(str, delim);
	if (*str == '\0')
	{
		*saveptr = str;
		return NULL;
	}
	/* Find the end of the token.  */
	end = str + strcspnc(str, delim);
	if (*end == '\0')
	{
		*saveptr = end;
		return str;
	}
	/* Terminate the token and make *SAVE_PTR point past it.  */
	*end = '\0';
	*saveptr = end + 1;
	return str;
}
