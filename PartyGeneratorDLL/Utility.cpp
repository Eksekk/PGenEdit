#include "pch.h"
#include "main.h"
#include "Utility.h"

extern int MMVER;

template<typename T>
bool existsInVector(const std::vector<T>& vec, const T& val)
{
	for (int i = 0; i < vec.size(); ++i)
	{
		if (vec[i] == val)
		{
			return true;
		}
	}
	return false;
}

template<typename T>
const T& mmv(const T& e6, const T& e7, const T& e8)
{
	if (MMVER == 6)
	{
		return e6;
	}
	else if (MMVER == 7)
	{
		return e7;
	}
	else if (MMVER == 8)
	{
		return e8;
	}
	else
	{
		throw std::runtime_error(std::format("Invalid MM version ({})!", MMVER));
	}
}

wxString concatWxStrings(const std::vector<wxString>& container, const wxString& separator)
{
	wxString s;
	for (int i = 0; i < container.size(); ++i)
	{
		s << container[i];
		if (i < container.size() - 1)
		{
			s << separator;
		}
	}
	return s;
}

std::string tolowerStr(const std::string& source)
{
	std::string out = source;
	for (char& c : out)
	{
		c = std::tolower(c);
	}
	return out;
}

template<typename Vector>
Vector mergeVectors(const Vector& first, const Vector& second)
{
	size_t n = first.size();
	auto out = first;
	out.resize(n + second.size());
	for (int i = 0; i < second.size(); ++i)
	{
		out[n + i] = second[i];
	}
	return out;
}

template<typename Vector, typename... Vectors>
Vector mergeVectors(const Vector& first, const Vector& second, const Vectors... vectors)
{
	return mergeVectors(mergeVectors(first, second), vectors...);
}