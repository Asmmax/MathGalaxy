#pragma once
#include "infrastruct/UnorderedMap.hpp"
#include "infrastruct/StringId.hpp"
#include "infrastruct/resources/Shader.hpp"
#include "glm/glm.hpp"
#include <tuple>
#include <utility>
#include <assert.h>

template<typename... Types>
class DrawState
{
private:
	std::tuple<UnorderedMap<StringId,Types>...> _maps;

public:
	template <typename Type>
	void add(const StringId& name, const Type& value);

	template <typename Type>
	void addOrSet(const StringId& name, const Type& value);

	template <typename Type>
	void set(const StringId& name, const Type& value);

	template <typename Type>
	Type& get(const StringId& name);

	void remove(const StringId& name);

	bool has(const StringId& name) const;

	void apply(Shader& shader);
	void apply(DrawState& otherState);

private:
	template<typename Type, std::size_t... Is>
	void add(const StringId& name, const Type& value, std::tuple<UnorderedMap<StringId, Types>...>& tuple, std::index_sequence<Is...>);

	template<typename Type, typename CurrentType, typename... Remains>
	void add(const StringId& name, const Type& value, UnorderedMap<StringId, CurrentType>& currentMap, UnorderedMap<StringId, Remains>&... remains);

	template<typename Type, typename... Remains>
	void add(const StringId& name, const Type& value, UnorderedMap<StringId, Type>& currentMap, UnorderedMap<StringId, Remains>&... remains);


	template<typename Type, std::size_t... Is>
	void addOrSet(const StringId& name, const Type& value, std::tuple<UnorderedMap<StringId, Types>...>& tuple, std::index_sequence<Is...>);

	template<typename Type, typename CurrentType, typename... Remains>
	void addOrSet(const StringId& name, const Type& value, UnorderedMap<StringId, CurrentType>& currentMap, UnorderedMap<StringId, Remains>&... remains);

	template<typename Type, typename... Remains>
	void addOrSet(const StringId& name, const Type& value, UnorderedMap<StringId, Type>& currentMap, UnorderedMap<StringId, Remains>&... remains);


	template<typename Type, std::size_t... Is>
	void set(const StringId& name, const Type& value, std::tuple<UnorderedMap<StringId, Types>...>& tuple, std::index_sequence<Is...>);

	template<typename Type, typename CurrentType, typename... Remains>
	void set(const StringId& name, const Type& value, UnorderedMap<StringId, CurrentType>& currentMap, UnorderedMap<StringId, Remains>&... remains);

	template<typename Type, typename... Remains>
	void set(const StringId& name, const Type& value, UnorderedMap<StringId, Type>& currentMap, UnorderedMap<StringId, Remains>&... remains);


	template<typename Type, std::size_t... Is>
	Type& get(const StringId& name, std::tuple<UnorderedMap<StringId, Types>...>& tuple, std::index_sequence<Is...>);

	template<typename Type, typename CurrentType, typename... Remains>
	Type& get(const StringId& name, UnorderedMap<StringId, CurrentType>& currentMap, UnorderedMap<StringId, Remains>&... remains);

	template<typename Type, typename... Remains>
	Type& get(const StringId& name, UnorderedMap<StringId, Type>& currentMap, UnorderedMap<StringId, Remains>&... remains);


	template<std::size_t... Is>
	void remove(const StringId& name, std::tuple<UnorderedMap<StringId, Types>...>& tuple, std::index_sequence<Is...>);

	template<typename CurrentType, typename... Remains>
	void remove(const StringId& name, UnorderedMap<StringId, CurrentType>& currentMap, UnorderedMap<StringId, Remains>&... remains);

	template<typename LastType>
	void remove(const StringId& name, UnorderedMap<StringId, LastType>& lastMap);


	template<std::size_t... Is>
	bool has(const StringId& name, const std::tuple<UnorderedMap<StringId, Types>...>& tuple, std::index_sequence<Is...>) const;

	template<typename CurrentType, typename... Remains>
	bool has(const StringId& name, const UnorderedMap<StringId, CurrentType>& currentMap, const UnorderedMap<StringId, Remains>&... remains) const;

	template<typename LastType>
	bool has(const StringId& name, const UnorderedMap<StringId, LastType>& lastMap) const;


	template<std::size_t... Is>
	void apply(Shader& shader, std::tuple<UnorderedMap<StringId, Types>...>& tuple, std::index_sequence<Is...>);

	template<typename CurrentType, typename... Remains>
	void apply(Shader& shader, UnorderedMap<StringId, CurrentType>& currentMap, UnorderedMap<StringId, Remains>&... remains);

	template<typename LastType>
	void apply(Shader& shader, UnorderedMap<StringId, LastType>& lastMap);


	template<std::size_t... Is>
	void apply(DrawState& otherState, std::tuple<UnorderedMap<StringId, Types>...>& tuple, std::index_sequence<Is...>);

	template<typename CurrentType, typename... Remains>
	void apply(DrawState& otherState, UnorderedMap<StringId, CurrentType>& currentMap, UnorderedMap<StringId, Remains>&... remains);

	template<typename LastType>
	void apply(DrawState& otherState, UnorderedMap<StringId, LastType>& lastMap);
};


template<typename... Types>
class DrawStatePool
{
private:
	std::vector<DrawState<Types...>> _pool;
	size_t _cursor;
public:
	DrawStatePool(size_t size);

	DrawState<Types...>& get();

	void push();
	void pop();
};


using DrawStateDef = DrawState<glm::mat4, glm::mat3, glm::vec4, glm::vec3, float, int>;
using DrawStatePoolDef = DrawStatePool<glm::mat4, glm::mat3, glm::vec4, glm::vec3, float, int>;




template<typename... Types>
template <typename Type>
void DrawState<Types...>::add(const StringId& name, const Type& value) 
{
	add(name, value, _maps, std::index_sequence_for<Types...>());
}

template<typename... Types>
template<typename Type, std::size_t... Is>
void DrawState<Types...>::add(const StringId& name, const Type& value, std::tuple<UnorderedMap<StringId, Types>...>& tuple, std::index_sequence<Is...>) 
{
	add(name, value, std::get<Is>(tuple)...);
}

template<typename... Types>
template<typename Type, typename CurrentType, typename... Remains>
void DrawState<Types...>::add(const StringId& name, const Type& value, UnorderedMap<StringId, CurrentType>& currentMap, UnorderedMap<StringId, Remains>&... remains)
{
	add(name, value, remains...);
}

template<typename... Types>
template<typename Type, typename... Remains>
void DrawState<Types...>::add(const StringId& name, const Type& value, UnorderedMap<StringId, Type>& currentMap, UnorderedMap<StringId, Remains>&... remains)
{
	currentMap.add(name, value);
}


template<typename... Types>
template <typename Type>
void DrawState<Types...>::addOrSet(const StringId& name, const Type& value) 
{
	addOrSet(name, value, _maps, std::index_sequence_for<Types...>());
}

template<typename... Types>
template<typename Type, std::size_t... Is>
void DrawState<Types...>::addOrSet(const StringId& name, const Type& value, std::tuple<UnorderedMap<StringId, Types>...>& tuple, std::index_sequence<Is...>) 
{
	addOrSet(name, value, std::get<Is>(tuple)...);
}

template<typename... Types>
template<typename Type, typename CurrentType, typename... Remains>
void DrawState<Types...>::addOrSet(const StringId& name, const Type& value, UnorderedMap<StringId, CurrentType>& currentMap, UnorderedMap<StringId, Remains>&... remains)
{
	addOrSet(name, value, remains...);
}

template<typename... Types>
template<typename Type, typename... Remains>
void DrawState<Types...>::addOrSet(const StringId& name, const Type& value, UnorderedMap<StringId, Type>& currentMap, UnorderedMap<StringId, Remains>&... remains)
{
	auto valuePtr = currentMap.getPtr(name);
	if (valuePtr) {
		*valuePtr = value;
		return;
	}

	add(name, value, currentMap, remains...);
}


template<typename... Types>
template <typename Type>
void DrawState<Types...>::set(const StringId& name, const Type& value) 
{
	set(name, value, _maps, std::index_sequence_for<Types...>());
}

template<typename... Types>
template<typename Type, std::size_t... Is>
void DrawState<Types...>::set(const StringId& name, const Type& value, std::tuple<UnorderedMap<StringId, Types>...>& tuple, std::index_sequence<Is...>) 
{
	set(name, value, std::get<Is>(tuple)...);
}

template<typename... Types>
template<typename Type, typename CurrentType, typename... Remains>
void DrawState<Types...>::set(const StringId& name, const Type& value, UnorderedMap<StringId, CurrentType>& currentMap, UnorderedMap<StringId, Remains>&... remains)
{
	set(name, value, remains...);
}

template<typename... Types>
template<typename Type, typename... Remains>
void DrawState<Types...>::set(const StringId& name, const Type& value, UnorderedMap<StringId, Type>& currentMap, UnorderedMap<StringId, Remains>&... remains)
{
	currentMap.get(name) = value;
}


template<typename... Types>
template <typename Type>
Type& DrawState<Types...>::get(const StringId& name) 
{
	return get<Type>(name, _maps, std::index_sequence_for<Types...>());
}

template<typename... Types>
template<typename Type, std::size_t... Is>
Type& DrawState<Types...>::get(const StringId& name, std::tuple<UnorderedMap<StringId, Types>...>& tuple, std::index_sequence<Is...>)
{
	return get(name, std::get<Is>(tuple)...);
}

template<typename... Types>
template<typename Type, typename CurrentType, typename... Remains>
Type& DrawState<Types...>::get(const StringId& name, UnorderedMap<StringId, CurrentType>& currentMap, UnorderedMap<StringId, Remains>&... remains)
{
	return get(name, value, remains...);
}

template<typename... Types>
template<typename Type, typename... Remains>
Type& DrawState<Types...>::get(const StringId& name, UnorderedMap<StringId, Type>& currentMap, UnorderedMap<StringId, Remains>&... remains)
{
	return currentMap.get(name);
}


template<typename... Types>
void DrawState<Types...>::remove(const StringId& name) 
{
	remove(name, _maps, std::index_sequence_for<Types...>());
}

template<typename... Types>
template<std::size_t... Is>
void DrawState<Types...>::remove(const StringId& name, std::tuple<UnorderedMap<StringId, Types>...>& tuple, std::index_sequence<Is...>)
{
	remove(name, std::get<Is>(tuple)...);
}

template<typename... Types>
template<typename CurrentType, typename... Remains>
void DrawState<Types...>::remove(const StringId& name, UnorderedMap<StringId, CurrentType>& currentMap, UnorderedMap<StringId, Remains>&... remains)
{
	if (currentMap.remove(name)) {
		return;
	}
	remove(name, remains...);
}

template<typename... Types>
template<typename LastType>
void DrawState<Types...>::remove(const StringId& name, UnorderedMap<StringId, LastType>& lastMap)
{
	lastMap.remove(name);
}


template<typename... Types>
bool DrawState<Types...>::has(const StringId& name) const 
{
	return has(name, _maps, std::index_sequence_for<Types...>());
}

template<typename... Types>
template<std::size_t... Is>
bool DrawState<Types...>::has(const StringId& name, const std::tuple<UnorderedMap<StringId, Types>...>& tuple, std::index_sequence<Is...>) const
{
	return has(name, std::get<Is>(tuple)...);
}

template<typename... Types>
template<typename CurrentType, typename... Remains>
bool DrawState<Types...>::has(const StringId& name, const UnorderedMap<StringId, CurrentType>& currentMap, const UnorderedMap<StringId, Remains>&... remains) const
{
	if (currentMap.has(name)) {
		return true;
	}
	return has(name, remains...);
}

template<typename... Types>
template<typename LastType>
bool DrawState<Types...>::has(const StringId& name, const UnorderedMap<StringId, LastType>& lastMap) const
{
	return lastMap.has(name);
}


template<typename... Types>
void DrawState<Types...>::apply(Shader& shader) 
{
	apply(shader, _maps, std::index_sequence_for<Types...>());
}

template<typename... Types>
template<std::size_t... Is>
void DrawState<Types...>::apply(Shader& shader, std::tuple<UnorderedMap<StringId, Types>...>& tuple, std::index_sequence<Is...>)
{
	apply(shader, std::get<Is>(tuple)...);
}

template<typename... Types>
template<typename CurrentType, typename... Remains>
void DrawState<Types...>::apply(Shader& shader, UnorderedMap<StringId, CurrentType>& currentMap, UnorderedMap<StringId, Remains>&... remains)
{
	for (size_t i = 0; i < currentMap.size(); i++) {
		shader.setUniform(currentMap.keys()[i], currentMap.values()[i]);
	}

	apply(shader, remains...);
}

template<typename... Types>
template<typename LastType>
void DrawState<Types...>::apply(Shader& shader, UnorderedMap<StringId, LastType>& lastMap)
{
	for (size_t i = 0; i < lastMap.size(); i++) {
		shader.setUniform(lastMap.keys()[i], lastMap.values()[i]);
	}
}


template<typename... Types>
void DrawState<Types...>::apply(DrawState& otherState) 
{
	apply(otherState, _maps, std::index_sequence_for<Types...>());
}

template<typename... Types>
template<std::size_t... Is>
void DrawState<Types...>::apply(DrawState& otherState, std::tuple<UnorderedMap<StringId, Types>...>& tuple, std::index_sequence<Is...>) 
{
	apply(otherState, std::get<Is>(tuple)...);
}

template<typename... Types>
template<typename CurrentType, typename... Remains>
void DrawState<Types...>::apply(DrawState& otherState, UnorderedMap<StringId, CurrentType>& currentMap, UnorderedMap<StringId, Remains>&... remains)
{
	for (size_t i = 0; i < currentMap.size(); i++) {
		otherState.add(currentMap.keys()[i], currentMap.values()[i]);
	}

	apply(otherState, remains...);
}

template<typename... Types>
template<typename LastType>
void DrawState<Types...>::apply(DrawState& otherState, UnorderedMap<StringId, LastType>& lastMap)
{
	for (size_t i = 0; i < lastMap.size(); i++) {
		otherState.add(lastMap.keys()[i], lastMap.values()[i]);
	}
}




template<typename... Types>
DrawStatePool<Types...>::DrawStatePool(size_t size):
	_cursor(0)
{
	assert(size > 1);
	_pool.resize(size > 1 ? size : 1);
}

template<typename... Types>
DrawState<Types...>& DrawStatePool<Types...>::get()
{
	return _pool[_cursor];
}

template<typename... Types>
void DrawStatePool<Types...>::push()
{
	assert(_cursor < _pool.size() - 1);
	_cursor++;
	_pool[_cursor] = _pool[_cursor - 1];
}

template<typename... Types>
void DrawStatePool<Types...>::pop()
{
	assert(_cursor > 0);
	_cursor--;
}
