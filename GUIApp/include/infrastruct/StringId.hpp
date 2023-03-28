#pragma once
#include <vector>

class StringIdContainer
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

private:
	std::vector<CharsShell> _strings;

public:
	size_t add(const char* chars);
	std::pair<bool, size_t> find(const char* chars) const;
	const char* get(size_t id) const;
	size_t size() const;
};

class StringId
{
private:
	size_t _id;
	StringIdContainer* _container;

public:
	StringId(const char* chars, StringIdContainer& container);
	StringId(const char* chars);

	const char* getChars() const;
	bool operator==(const StringId& other) const;

private:
	static StringIdContainer& getDefaultContainer();
};
