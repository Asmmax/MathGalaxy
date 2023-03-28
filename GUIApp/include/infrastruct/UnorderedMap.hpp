#pragma once
#include <vector>
#include <assert.h>

template <typename Key, typename Value>
class UnorderedMap
{
public:
	using KeyType = Key;
	using ValueType = Value;

private:
	std::vector<Key> _keys;
	std::vector<Value> _values;
public:

	void add(const Key& key, const Value& value);
	bool remove(const Key& key);
	void clear();

	Value* getPtr(const Key& key);
	Value& get(const Key& key);
	Value& getOrCreate(const Key& key, const Value& defaultValue);
	const Value& get(const Key& key) const;
	const Value* getPtr(const Key& key) const;

	bool has(const Key& key) const;

	const std::vector<Key>& keys() const { return _keys; }
	const std::vector<Value>& values() const { return _values; }

	size_t size() const { return _keys.size(); }
};

template <typename Key, typename Value>
void UnorderedMap<Key, Value>::add(const Key& key, const Value& value)
{
	assert(!has(key));

	_keys.emplace_back(key);
	_values.emplace_back(value);
}

template <typename Key, typename Value>
bool UnorderedMap<Key, Value>::remove(const Key& key)
{
	auto keyIt = std::find(_keys.begin(), _keys.end(), key);
	if (keyIt == _keys.end()) {
		return false;
	}

	size_t id = std::distance(_keys.begin(), keyIt);

	auto valueIt = _values.begin();
	std::advance(valueIt, id);

	_keys.erase(keyIt);
	_values.erase(valueIt);
	return true;
}

template <typename Key, typename Value>
void UnorderedMap<Key, Value>::clear()
{
	_keys.clear();
	_values.clear();
}

template <typename Key, typename Value>
Value* UnorderedMap<Key, Value>::getPtr(const Key& key)
{
	return const_cast<Value*>(static_cast<const UnorderedMap<Key, Value>*>(this)->getPtr(key));
}

template <typename Key, typename Value>
Value& UnorderedMap<Key, Value>::get(const Key& key)
{
	return const_cast<Value&>(static_cast<const UnorderedMap<Key, Value>*>(this)->get(key));
}

template <typename Key, typename Value>
Value& UnorderedMap<Key, Value>::getOrCreate(const Key& key, const Value& defaultValue)
{
	auto keyIt = std::find(_keys.begin(), _keys.end(), key);
	if (keyIt == _keys.end()) {
		_keys.emplace_back(key);
		return _values.emplace_back(defaultValue);
	}

	auto id = std::distance(_keys.begin(), keyIt);
	return _values[id];
}

template <typename Key, typename Value>
const Value* UnorderedMap<Key, Value>::getPtr(const Key& key) const
{
	auto keyIt = std::find(_keys.begin(), _keys.end(), key);
	if (keyIt == _keys.end()) {
		return nullptr;
	}

	auto id = std::distance(_keys.begin(), keyIt);
	return &_values[id];
}

template <typename Key, typename Value>
const Value& UnorderedMap<Key, Value>::get(const Key& key) const
{
	auto keyIt = std::find(_keys.begin(), _keys.end(), key);
	assert(keyIt != _keys.end());

	auto id = std::distance(_keys.begin(), keyIt);
	return _values[id];
}

template <typename Key, typename Value>
bool UnorderedMap<Key, Value>::has(const Key& key) const
{
	auto keyIt = std::find(_keys.begin(), _keys.end(), key);
	return keyIt != _keys.end();
}
