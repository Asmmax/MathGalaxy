#pragma once
#include <utility>
#include <cstdlib>
#include <vector>
#include <assert.h>

template <typename Type>
class PoolAllocator
{
private:
	class Chunk
	{
	private:
		size_t _size;
		Type* _firstBlock;
		std::vector<Type*> _blockHeaders;

	public:
		Chunk();

		Type* init(size_t chunkSize);
		Type* reset();
		void deinit();
		void bind(Type* nextChunk);

		bool hasBlock(Type* pointer) const;
		Type* getNextBlock(Type* pointer) const;
		void setNextBlock(Type* pointer, Type* nextBlock);
	};

	Type* _nextFreeBlock;
	size_t _chunkSize;
	std::vector<Chunk> _chunks;

public:
	PoolAllocator(size_t chunkSize, size_t chunkCount = 1);
	~PoolAllocator();

	Type* allocate();
	void deallocate(Type* pointer);
	void reset();

	template<typename... Args>
	void construct(Type* pointer, Args&&... args);
	void destroy(Type* pointer);

private:
	Chunk* findChunk(Type* pointer);
	void expand();
};

template <typename Type>
PoolAllocator<Type>::Chunk::Chunk():
	_size(0),
	_firstBlock(nullptr)
{
}

template <typename Type>
Type* PoolAllocator<Type>::Chunk::init(size_t chunkSize)
{
	_size = chunkSize;
	_firstBlock = reinterpret_cast<Type*>(malloc(sizeof(Type) * chunkSize));
	if (!_firstBlock) {
		assert(false);
		return nullptr;
	}

	_blockHeaders.resize(chunkSize, nullptr);
	return reset();
}

template <typename Type>
Type* PoolAllocator<Type>::Chunk::reset()
{
	Type* next = _firstBlock;
	for (size_t i = 0; i < _blockHeaders.size() - 1; i++) {
		_blockHeaders[i] = ++next;
	}

	return _firstBlock;
}

template <typename Type>
void PoolAllocator<Type>::Chunk::deinit()
{
	free(_firstBlock);
	_size = 0;
	_firstBlock = nullptr;
}

template <typename Type>
void PoolAllocator<Type>::Chunk::bind(Type* nextChunk)
{
	_blockHeaders[_size - 1] = nextChunk;
}

template <typename Type>
bool PoolAllocator<Type>::Chunk::hasBlock(Type* pointer) const
{
	return pointer >= _firstBlock && pointer < _firstBlock + _size;
}

template <typename Type>
Type* PoolAllocator<Type>::Chunk::getNextBlock(Type* pointer) const
{
	assert(hasBlock(pointer));
	size_t offset = reinterpret_cast<size_t>(pointer) - reinterpret_cast<size_t>(_firstBlock);
	size_t id = offset / sizeof(Type);
	return _blockHeaders[id];
}

template <typename Type>
void PoolAllocator<Type>::Chunk::setNextBlock(Type* pointer, Type* nextBlock)
{
	assert(hasBlock(pointer));
	assert(pointer >= _firstBlock);
	size_t offset = reinterpret_cast<size_t>(pointer) - reinterpret_cast<size_t>(_firstBlock);
	size_t id = offset / sizeof(Type);
	assert(id < _size);
	_blockHeaders[id] = nextBlock;
}


template <typename Type>
PoolAllocator<Type>::PoolAllocator(size_t chunkSize, size_t chunkCount /*= 1*/):
	_nextFreeBlock(nullptr),
	_chunkSize(chunkSize)
{
	assert(chunkSize > 0);
	assert(chunkCount >= 0);

	_chunks.resize(chunkCount);
	_nextFreeBlock = nullptr;
	for (auto chunkIt = _chunks.rbegin(); chunkIt != _chunks.rend(); chunkIt++) {
		Type* nextChunk = _nextFreeBlock;
		_nextFreeBlock = chunkIt->init(chunkSize);
		chunkIt->bind(nextChunk);
	}
}

template <typename Type>
PoolAllocator<Type>::~PoolAllocator()
{
	for (auto& chunk : _chunks) {
		chunk.deinit();
	}
}

template <typename Type>
Type* PoolAllocator<Type>::allocate()
{
	if (!_nextFreeBlock) {
		expand();
	}

	Type* currentBlock = _nextFreeBlock;

	Chunk* currentChunk = findChunk(currentBlock);
	_nextFreeBlock = currentChunk ? currentChunk->getNextBlock(currentBlock) : nullptr;

	return currentBlock;
}

template <typename Type>
void PoolAllocator<Type>::deallocate(Type* pointer)
{
	Chunk* currentChunk = findChunk(pointer);
	if (!currentChunk) {
		assert(false);
		return;
	}

	currentChunk->setNextBlock(pointer, _nextFreeBlock);
	_nextFreeBlock = pointer;
}

template <typename Type>
void PoolAllocator<Type>::reset()
{
	_nextFreeBlock = nullptr;
	for (auto chunkIt = _chunks.rbegin(); chunkIt != _chunks.rend(); chunkIt++) {
		Type* nextChunk = _nextFreeBlock;
		_nextFreeBlock = chunkIt->reset();
		chunkIt->bind(nextChunk);
	}
}

template <typename Type>
template<typename... Args>
void PoolAllocator<Type>::construct(Type* pointer, Args&&... args)
{
	assert(pointer);
	::new (pointer) Type(std::forward<Args>(args)...);
}

template <typename Type>
void PoolAllocator<Type>::destroy(Type* pointer)
{
	assert(pointer);
	pointer->~Type();
}

template <typename Type>
typename PoolAllocator<Type>::Chunk* PoolAllocator<Type>::findChunk(Type* pointer)
{
	for (auto& chunk : _chunks) {
		if (chunk.hasBlock(pointer)) {
			return &chunk;
		}
	}
	return nullptr;
}

template <typename Type>
void PoolAllocator<Type>::expand()
{
	assert(_nextFreeBlock == nullptr);
	Chunk& newChunk = _chunks.emplace_back();
	_nextFreeBlock = newChunk.init(_chunkSize);
}
