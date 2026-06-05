#pragma once
#include <iostream>

template<class T>
class Vector {
private:
	T* data;
	size_t size;
	size_t capacity;
	void ensure_capacity(size_t new_capacity) {
		if (new_capacity > capacity) {
			T* new_data = new T[new_capacity];
			std::move(data, data + size, new_data);
			delete[] data;
			data = new_data;
			capacity = new_capacity;
		}
	}
public:
	Vector() : data(nullptr), size(0), capacity(0) {}

	Vector(std::initializer_list<T> values)
		: size(values.size()), capacity(values.size()), data(new T[size])
	{
		std::copy(values.begin(), values.end(), data);
	}

	Vector(size_t count, const T& value)
		: size(count), capacity(count), data(new T[count])
	{
		std::fill(data, data + count, value);
	}

	Vector(const Vector& oth)
		: size(oth.size), capacity(oth.capacity), data(new T[oth.capacity])
	{
		std::copy(oth.data, oth.data + oth.size, data);
	}

	Vector(Vector&& oth) noexcept
		: data(oth.data), size(oth.size), capacity(oth.capacity)
	{
		oth.data = nullptr;
		oth.size = 0;
		oth.capacity = 0;
	}

	~Vector()
	{
		delete[] data;
	}

	constexpr Vector& operator=(const Vector& other) {
		if (this != &other) {
			delete[] data;
			size = other.size;
			capacity = other.capacity;
			data = new T[capacity];
			std::copy(other.data, other.data + size, data);
		}
		return *this;
	}

	constexpr Vector& operator=(Vector&& other) noexcept {
		if (this != &other) {
			delete[] data;
			data = other.data;
			size = other.size;
			capacity = other.capacity;
			other.data = nullptr;
			other.size = 0;
			other.capacity = 0;
		}
		return *this;
	}

	void assign(size_t count, const T& value) {
		if (count > capacity) {
			ensure_capacity(count);
		}
		std::fill(data, data + count, value);
		size = count;
	}

	void assign(size_t count, const T& value) {
		if (count > capacity) {
			ensure_capacity(count);
		}
		std::fill(data, data + count, value);
		size = count;
	}

public:
	class Iterator
	{
	private:
		T* iter;
	public:
		explicit Iterator(T* iter) : iter(iter) {}
		T& operator* ()const { return *iter; }
		T* operator->() const { return iter; }
		Iterator& operator++() { ++iter; return *this; }
		Iterator& operator--() { --iter; return *this; }
		Iterator operator+(size_t offset)const { return Iterator(iter + offset); }
		Iterator& operator+=(size_t offset) { iter += offset; return *this; }
		bool operator == (const Iterator& oth)const { return iter == oth.iter; }
		bool operator !=(const Iterator& oth)const { return iter != oth.iter; }
	};

	class Const_Iterator
	{
	private:
		T* iter;
	public:
		explicit Const_Iterator(T* iter) : iter(iter) {}
		const T& operator *()const { return *iter; }
		const T* operator->() const { return iter; }
		Const_Iterator& operator++() { ++iter; return *this; }
		Const_Iterator& operator--() { --iter; return *this; }
		Const_Iterator operator+(size_t offset) const { return Const_Iterator(iter + offset); }
		Const_Iterator& operator+=(size_t offset) { iter += offset; return *this; }
		bool operator == (const Const_Iterator& oth)const { return iter == oth.iter; }
		bool operator !=(const Const_Iterator& oth)const { return iter != oth.iter; }
	};

	class Reverse_Iterator
	{
	private:
		T* iter;
	public:
		explicit Reverse_Iterator(T* iter) : iter(iter) {}
		T& operator* ()const { return *iter; }
		T* operator->()const { return iter; }
		Reverse_Iterator& operator++() { --iter; return *this; }
		Reverse_Iterator& operator--() { ++iter; return *this; }
		Reverse_Iterator operator+(size_t offset)const { return Reverse_Iterator(iter - offset); }
		Reverse_Iterator& operator+=(size_t offset) { iter -= offset; return *this; }
		bool operator == (const Reverse_Iterator& oth)const { return iter == oth.iter; }
		bool operator !=(const Reverse_Iterator& oth)const { return iter != oth.iter; }
	};

	class Const_Reverse_Iterator
	{
	private:
		T* iter;
	public:
		explicit Const_Reverse_Iterator(T* iter) : iter(iter) {}
		const T& operator* ()const { return *iter; }
		const T* operator->()const { return iter; }
		Const_Reverse_Iterator& operator++() { --iter; return *this; }
		Const_Reverse_Iterator& operator--() { ++iter; return *this; }
		Const_Reverse_Iterator operator+(size_t offset)const { return Const_Reverse_Iterator(iter - offset); }
		Const_Reverse_Iterator& operator+=(size_t offset) { iter -= offset; return *this; }
		bool operator == (const Const_Reverse_Iterator& oth)const { return iter == oth.iter; }
		bool operator !=(const Const_Reverse_Iterator& oth)const { return iter != oth.iter; }
		};

		Iterator begin() noexcept { return Iterator(arr); }
		Iterator end() noexcept { return Iterator(arr + size()); }
		Iterator begin() const noexcept { return Iterator(arr); }
		Iterator end() const noexcept { return Iterator(arr + size()); }
		Const_Iterator cbegin() const noexcept { return Const_Iterator(arr); }
		Const_Iterator cend() const noexcept { return Const_Iterator(arr + size()); }
		Reverse_Iterator rbegin() noexcept { return Reverse_Iterator(arr + size() - 1); }
		Reverse_Iterator rend() noexcept { return Reverse_Iterator(arr - 1); }
		Const_Reverse_Iterator crbegin() noexcept { return Const_Reverse_Iterator(arr + size() - 1); }
		Const_Reverse_Iterator crend() noexcept { return Const_Reverse_Iterator(arr - 1); }

public:
	T& at(size_t pos) {
		if (pos >= size())
		{
			throw std::out_of_range("Index out of range");
		}
		return data[pos];
	}
	const T& at(size_t pos)const {
		check_bounds(pos);
		return data[pos];
	}
	T& operator [](size_t pos) { return data[pos];}
	const T& operator[](size_t pos)const { return data[pos]; }
	T& front() {
		if (empty()) throw std::out_of_range("Vector is empty");
		return data[0];
	}
	const T& front() const {
		if (empty()) throw std::out_of_range("Vector is empty");
		return data[0];
	}
	T& back() {
		if (empty()) throw std::out_of_range("Vector is empty");
		return data[size - 1];
	}
	const T& back() cons {
		if (empty()) throw std::out_of_range("Vector is empty");
		return data[size - 1];
	}
	T* data() noexcept{ return data; }
	const T* data()const noexcept { return data; }

	bool empty() const { return size == 0; }
	size_t size() const { return size; }
	size_t max_size() const;
	void reserve(size_t new_cap) {
		if (new_cap > capacity) {
			T* new_data = new T[new_cap];
			std::move(data, data + size, new_data);
			delete[] data;
			data = new_data;
			capacity = new_cap;
		}
	}
	size_t capacity() const { return capacity; }
	void shrink_to_fit() {
		if (capacity > size) {
			T* new_data = new T[size];
			std::move(data, data + size, new_data);
			delete[] data;
			data = new_data;
			capacity = size;
		}
	}

	void clear() { return size == 0; }
	Iterator insert(Const_Iterator pos, const T& value) {
		size_t index = pos.iter - data;
		ensure_capacity(size + 1);
		std::move_backward(data + index, data + size, data + size + 1);
		data[index] = value;
		++size;
		return Iterator(data + index);
	}
	Iterator insert(Const_Iterator pos, T&& value) {
		size_t index = pos.iter - data;
		ensure_capacity(size + 1);
		std::move_backward(data + index, data + size, data + size + 1);
		data[index] = std::move(value);
		++size;
		return Iterator(data + index);
	}
	Iterator insert(Const_Iterator pos, size_t count, const T& value) {
		size_t index = pos.iter - data;
		ensure_capacity(size + count);
		std::move_backward(data + index, data + size, data + size + count);
		std::fill(data + index, data + index + count, value);
		size += count;
		return Iterator(data + index);
	}
	Iterator insert(Const_Iterator pos, std::initializer_list<T> ilist) {
		size_t index = pos.iter - data;
		size_t count = ilist.size();
		ensure_capacity(size + count);
		std::move_backward(data + index, data + size, data + size + count);
		std::copy(ilist.begin(), ilist.end(), data + index);
		size += count;
		return Iterator(data + index);
	}
	Iterator erase(Iterator pos) {
		size_t index = pos.iter - data;
		std::move(data + index + 1, data + size, data + index);
		--size;
		return Iterator(data + index);
	}
	Iterator erase(Const_Iterator pos) {
		size_t index = pos.iter - data;
		std::move(data + index + 1, data + size, data + index);
		--size;
		return Iterator(data + index);
	}
	Iterator erase(Iterator first, Iterator second) {
		size_t start = first.iter - data;
		size_t end = second.iter - data;
		std::move(data + end, data + size, data + start);
		size -= (end - start);
		return Iterator(data + start);
	}
	Iterator erase(Const_Iterator first, Const_Iterator second) {
		size_t start = first.iter - data;
		size_t end = second.iter - data;
		std::move(data + end, data + size, data + start);
		size -= (end - start);
		return Iterator(data + start);
	}		void push_back(const T& value);
	void push_back(T&& value) {
		ensure_capacity(size + 1);
		data[size++] = value;
	}
	void push_back(T&& value) {
		ensure_capacity(size + 1);
		data[size++] = std::move(value);
	}
	void pop_back() {
		if (!empty()) {
			--size;
		}
	}
	void resize(size_t count) {
		if (count > size) {
			ensure_capacity(count);
			std::fill(data + size, data + count, T());
		}
		size = count;
	}
	void resize(size_t count, const T& value) {
		if (count > size) {
			ensure_capacity(count);
			std::fill(data + size, data + count, value);
		}
		size = count;
	}	
	void swap(Vector& oth) noexcept {
			std::swap(data, oth.data);
			std::swap(size, oth.size);
			std::swap(capacity, oth.capacity);
		}

};