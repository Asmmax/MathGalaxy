#pragma once
#include <vector>

class StringId
{
private:
	class CharsShell
	{
	private:
		char* _data;
	public:
		CharsShell(const char* chars);
		CharsShell(const CharsShell& other);
		CharsShell& operator=(const CharsShell& other);

		~CharsShell();

		const char* data() const { return _data; }
	};

	static std::vector<CharsShell> _strings;
	size_t _id;

public:
	StringId(const char* chars);

	const char* getChars() const;
	bool operator==(const StringId& other) const;

private:
	static std::pair<bool, size_t> find(const char* chars);
};
