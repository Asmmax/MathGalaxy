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
		inline CharsShell(const char* chars);
		inline CharsShell(const CharsShell& other);
		inline CharsShell& operator=(const CharsShell& other);

		inline ~CharsShell();

		inline const char* data() const { return _data; }
	};

private:
	std::vector<CharsShell> _strings;

public:
	inline size_t add(const char* chars);
	inline std::pair<bool, size_t> find(const char* chars) const;
	inline const char* get(size_t id) const;
	inline size_t size() const;
};

class StringId
{
private:
	size_t _id;
	StringIdContainer* _container;

public:
	inline StringId(const char* chars, StringIdContainer& container);
	inline StringId(const char* chars);

	inline const char* getChars() const;
	inline bool operator==(const StringId& other) const;

private:
	inline static StringIdContainer& getDefaultContainer();
};




StringIdContainer::CharsShell::CharsShell(const char* chars) :
	_data(nullptr)
{
	size_t len = strlen(chars);
	_data = new char[len + 1];
	strcpy_s(_data, len + 1, chars);
}

StringIdContainer::CharsShell::CharsShell(const CharsShell& other) :
	CharsShell(other._data)
{
}

StringIdContainer::CharsShell& StringIdContainer::CharsShell::operator=(const CharsShell& other)
{
	delete[] _data;

	size_t len = strlen(other._data);
	_data = new char[len + 1];
	strcpy_s(_data, len + 1, other._data);

	return *this;
}

StringIdContainer::CharsShell::~CharsShell()
{
	delete[] _data;
}

size_t StringIdContainer::add(const char* chars)
{
	_strings.emplace_back(chars);
	return _strings.size() - 1;
}

std::pair<bool, size_t> StringIdContainer::find(const char* chars) const
{
	auto foundIt = std::find_if(_strings.begin(), _strings.end(), [chars](const CharsShell& string) {
		return strcmp(chars, string.data()) == 0;
		});
	if (foundIt == _strings.end()) {
		return { false, 0 };
	}

	size_t id = std::distance(_strings.begin(), foundIt);
	return { true, id };
}

const char* StringIdContainer::get(size_t id) const
{
	return _strings[id].data();
}

size_t StringIdContainer::size() const
{
	return _strings.size();
}




StringId::StringId(const char* chars, StringIdContainer& container) :
	_id(0),
	_container(&container)
{
	auto res = _container->find(chars);
	if (res.first) {
		_id = res.second;
	}
	else {
		_id = _container->add(chars);
	}
}

StringId::StringId(const char* chars) :
	StringId(chars, getDefaultContainer())
{
}

const char* StringId::getChars() const
{
	return _container->get(_id);
}

bool StringId::operator==(const StringId& other) const
{
	return _id == other._id && _container == other._container;
}

StringIdContainer& StringId::getDefaultContainer()
{
	static StringIdContainer defaultContainer;
	return defaultContainer;
}
