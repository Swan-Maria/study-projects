#pragma once
#include <iostream>
#include <algorithm>
#include <iterator>

template<class T, size_t N> 
class Array 
{
private:
	T arr[N];

public:
	Array() :arr{ 0 } {}

	Array(std::initializer_list<T> values) :arr{ 0 } {
		if (values.size() > N) 
		{
			throw std::out_of_range("Initializer list exceeds array size");
		}
		std::copy(values.begin(), values.end(), arr);
	}

	Array(const Array& other) 
	{
		std::copy(other.arr, other.arr + N, arr);
	}

	Array(Array&& other) noexcept 
	{
		std::move(other.arr, other.arr + N, arr);
	}

	Array& operator=(const Array& other) 
	{
		if (this != &other) {
            std::copy(other.arr, other.arr + N, arr);
        }
        return *this;
	}

	Array& operator=(Array&& other) noexcept 
	{
		if (this != &other) {
			std::move(other.arr, other.arr + N, arr);
		}
		return *this;
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
		explicit Reverse_Iterator(T* iter) :  iter(iter) { }
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
	T& at(size_t pos);
	const T& at(size_t pos) const;
	T& operator [](size_t pos);
	const T& operator[](size_t pos)const;
	T& front();
	const T& front() const;
	T& back();
	const T& back() const;
	T* data() noexcept;
	const T* data()const noexcept;

	constexpr bool empty()const noexcept;
	constexpr size_t size()const noexcept;

	void fill(const T& value);
	void swap(Array& oth) noexcept;

	template<class T, size_t N>
	friend bool operator==(const Array<T, N>& left, const Array<T, N>& right);
	
	template<size_t I, class T, size_t N>
	friend constexpr T& get(Array<T, N>& a)noexcept;
	
	template<size_t I, class T, size_t N>
	friend constexpr const T& get(Array<T, N>& a)noexcept;
	
	template<size_t I, class T, size_t N>
	friend constexpr T&& get(Array<T, N>&& a)noexcept;
	
	template<size_t I, class T, size_t N>
	friend constexpr const T&& get(Array<T, N>&& a)noexcept;

};

template<class T, size_t N>
inline T& Array<T, N>::at(size_t pos)
{
	if (pos >= size())
	{
		throw std::out_of_range("Index out of range");
	}
	return arr[pos];
}

template<class T, size_t N>
inline const T& Array<T, N>::at(size_t pos) const
{
	if (pos >= size())
	{
		throw std::out_of_range("Index out of range");
	}
	return arr[pos];
}

template<class T, size_t N>
inline T& Array<T, N>::operator[](size_t pos)
{
	if (pos >= size())
	{
		throw std::out_of_range("Index out of range");
	}
	return arr[pos];
}

template<class T, size_t N>
inline const T& Array<T, N>::operator[](size_t pos) const
{
	if (pos >= size())
	{
		throw std::out_of_range("Index out of range");
	}
	return arr[pos];
}

template<class T, size_t N>
inline T& Array<T, N>::front()
{
	if (empty())
	{
		throw std::out_of_range("Array is empty");
	}
	return arr[0];
}

template<class T, size_t N>
inline const T& Array<T, N>::front() const
{
	if (empty())
	{
		throw std::out_of_range("Array is empty");
	}
	return arr[0];
}

template<class T, size_t N>
inline T& Array<T, N>::back()
{
	if (empty())
	{
		throw std::out_of_range("Array is empty");
	}
	return arr[size() - 1];
}

template<class T, size_t N>
inline const T& Array<T, N>::back() const
{
	if (empty())
	{
		throw std::out_of_range("Array is empty");
	}
	return arr[size() - 1];
}

template<class T, size_t N>
inline T* Array<T, N>::data() noexcept
{
	return arr;
}

template<class T, size_t N>
inline const T* Array<T, N>::data() const noexcept
{
	return arr;
}

template<class T, size_t N>
inline constexpr bool Array<T, N>::empty() const noexcept
{
	return size() == 0;
}

template<class T, size_t N>
inline constexpr size_t Array<T, N>::size() const noexcept
{
	return N;
}

template<class T, size_t N>
inline void Array<T, N>::fill(const T& value)
{
	for (size_t i = 0; i < N; ++i) 
	{
        arr[i] = value;
    }
}

template<class T, size_t N>
inline void Array<T, N>::swap(Array& oth) noexcept
{
	std::swap(arr, oth.arr);
}

template<class T, size_t N>
inline bool operator==(const Array<T, N>& left, const Array<T, N>& right)
{
	return std::equal(left.begin(), left.end(), right.begin());
}

template<size_t I, class T, size_t N>
inline constexpr T& get(Array<T, N>& a) noexcept
{
	static_assert(I < N, "Index out of bounds");
	return a[I];
}

template<size_t I, class T, size_t N>
inline constexpr const T& get(Array<T, N>& a) noexcept
{
	static_assert(I < N, "Index out of bounds");
	return a[I];
}

template<size_t I, class T, size_t N>
inline constexpr T&& get(Array<T, N>&& a) noexcept
{
	static_assert(I < N, "Index out of bounds");
	return std::move(a[I]);
}

template<size_t I, class T, size_t N>
inline constexpr const T&& get(Array<T, N>&& a) noexcept
{
	static_assert(I < N, "Index out of bounds");
	return std::move(a[I]);
}