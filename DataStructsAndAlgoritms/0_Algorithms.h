#pragma once
#include <iostream>
#include <vector>

int Linear_Search(const std::vector<int>& arr, const int& key)
{
	for (int i = 0; i < arr.size();++i)
	{
		if (arr[i] == key)
		{
			std::cout << "Index of element " << key << " is " << i<<"\n";
			return i;
		}
	}
	return -1;
}

int Binary_Search(const std::vector<int>& arr, const int& key)
{
	int left = 0, right = arr.size() - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (arr[mid] == key)
		{
			std::cout << "Index of element " << key << " is " << mid << "\n";
			return mid;
		}
		if (arr[mid] < key)
		{
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
	}
	return -1;
}

int Binary_Search(const std::vector<int>& arr, int l, int r, const int& key)
{
	if (l>r)
	{
		return -1;
	}
	int mid = l + (r - l) / 2;
	if (arr[mid] == key)
	{
		std::cout << "Index of element " << key << " is " << mid << "\n";
		return mid;
	}
	if (arr[mid] < key)
	{
		return Binary_Search(arr, mid + 1, r, key);
	}
	else
	{
		return Binary_Search(arr, l, mid - 1, key);
	}
}

inline int Find_Fibonacci(int n)
{
	if (n <= 1)
	{
		return n;
	}
	return Find_Fibonacci(n - 2) + Find_Fibonacci(n - 1);
}

inline void Fibonacci(int n, int a = 0, int b = 1)
{
	if (n > 0)
	{
		std::cout << a << "  ";
		Fibonacci(n - 1, b, a + b);
	}
}

void Bubble_Sort(std::vector<int>& arr)
{
	for (size_t i = 0; i < arr.size() - 1;i++)
	{
		for (size_t j = arr.size() - 1; j > i;j--)
		{
			if (arr[j] < arr[j - 1])
			{
				std::swap(arr[j], arr[j - 1]);
			}
		}
	}
}

void Selection_Sort(std::vector<int>& arr)
{
	for (size_t i = 0; i < arr.size(); i++)
	{
		for (size_t j = i + 1; j < arr.size(); j++)
		{
			if (arr[j] < arr[i])
			{
				std::swap(arr[j], arr[i]);
			}
		}
	}
}

void Insertion_Sort(std::vector<int>& arr)
{
	for (size_t i = 1; i < arr.size(); i++)
	{
		int key = arr[i];
		int j;
		for (j = i - 1;j >= 0 && arr[j] > key;j--)
		{
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = key;
	}
}

int partition(std::vector<int>& arr, int l, int r)
{
	int pivot = arr[r];
	int i = l - 1;
	for (int j = l; j < r; j++)
	{
		if (arr[j] < pivot)
		{
			i++;
			std::swap(arr[i], arr[j]);
		}
	}
	std::swap(arr[i + 1], arr[r]);
	return i + 1;
}

void Quick_Sort(std::vector<int>& arr, int l, int r)
{
	if (l >= r) 
	{
		return;
	}
	int pi = partition(arr, l, r);
	Quick_Sort(arr, l, pi - 1);
	Quick_Sort(arr, pi + 1, r);
}


void merge(std::vector<int>& arr, int left, int mid, int right)
{
	int l = mid - left + 1, r = right - mid;
	std::vector<int> L(l), R(r);
	for (size_t i = 0; i < l; i++)
	{
		L[i] = arr[left + i];
	}
	for (size_t i = 0; i < r; i++)
	{
		R[i] = arr[mid + 1 + i];
	}
	int i = 0, j = 0, k = left;
	while (i < l && j < r)
	{
		if (L[i] <= R[j])
		{
			arr[k++] = L[i++];
		}
		else
		{
			arr[k++] = R[j++];
		}
	}
	while (i < l)
	{
		arr[k++] = L[i++];
	}
	while(j < r)
	{
		arr[k++]=R[j++];
	}
}

void Merge_Sort(std::vector<int>& arr, int left, int right)
{
	if (left >= right)
	{
		return;
	}
	int mid = left + (right - left) / 2;
	Merge_Sort(arr, left, mid);
	Merge_Sort(arr, mid + 1,right);
	merge(arr, left, mid, right);
}