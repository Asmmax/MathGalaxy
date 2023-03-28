#include "infrastruct/StringId.hpp"

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




StringId::StringId(const char* chars, StringIdContainer& container):
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

StringId::StringId(const char* chars):
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
