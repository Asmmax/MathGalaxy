#include "infrastruct/StringId.hpp"

StringId::CharsShell::CharsShell(const char* chars):
	_data(nullptr)
{
	size_t len = strlen(chars);
	_data = new char[len + 1];
	strcpy_s(_data, len + 1, chars);
}

StringId::CharsShell::CharsShell(const CharsShell& other):
	CharsShell(other._data)
{
}

StringId::CharsShell& StringId::CharsShell::operator=(const CharsShell& other)
{
	delete[] _data;

	size_t len = strlen(other._data);
	_data = new char[len + 1];
	strcpy_s(_data, len + 1, other._data);

	return *this;
}

StringId::CharsShell::~CharsShell()
{
	delete[] _data;
}

std::vector<StringId::CharsShell> StringId::_strings;

StringId::StringId(const char* chars):
	_id(0)
{
	auto res = find(chars);
	if (res.first) {
		_id = res.second;
	}
	else {
		_id = _strings.size();
		_strings.emplace_back(chars);
	}
}

const char* StringId::getChars() const
{
	return _strings[_id].data();
}

bool StringId::operator==(const StringId& other) const
{
	return _id == other._id;
}

std::pair<bool, size_t> StringId::find(const char* chars)
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
