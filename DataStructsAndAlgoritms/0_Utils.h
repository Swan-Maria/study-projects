#pragma once
#include <iostream>
#include <vector>
#include <numeric>

namespace custom_utils
{
	template <typename InputIter, typename Function>
	Function for_each(InputIter first, InputIter last, Function func)
	{
		for (;first != last;++first)
		{
			func(*first);
		}
		return func;
	}

	template <typename InputIter, typename OutputIter>
	OutputIter copy(InputIter first, InputIter last, OutputIter dest_first)
	{
		while (first != last)
		{
			*dest_first = *first;
			++first;
			++dest_first;
		}
		return dest_first;
	}

	template <typename InputIter, typename OutputIter, typename UnaryPredicat>
	OutputIter copy_if(InputIter first, InputIter last, OutputIter dest_first, UnaryPredicat pred)
	{
		while (first != last)
		{
			if (pred(*first))
			{
				*dest_first = *first;
				++dest_first;
			}
			++first;
		}
		return dest_first;
	}

	template <typename InputIt, typename T>
	size_t count(InputIt first, InputIt last, const T& value)
	{
		size_t counter = 0;
		while (first != last)
		{
			if(*first==value)
			{
				++counter;
			}
			++first;
		}
		return counter;
	}

	template <typename InputIt, typename UnaryPredicat>
	size_t count_if(InputIt first, InputIt last, UnaryPredicat pred)
	{
		size_t counter = 0;
		while (first != last)
		{
			if (pred(*first))
			{
				++counter;
			}
			++first;
		}
		return counter;
	}

	template< typename ForwardIt, typename T >
	void replace(ForwardIt first, ForwardIt last, const T& old_value, const T& new_value)
	{
		while (first != last)
		{
			if (*first == old_value)
			{
				*first = new_value;
			}
			++first;
		}
	}

	template< class ForwardIt, class UnaryPred, class T >
	void replace_if(ForwardIt first, ForwardIt last, UnaryPred pred, const T& new_value)
	{
		while (first != last)
		{
			if (pred(*first))
			{
				*first = new_value;
			}
			++first;
		}
	}

	template< class InputIt, class T >
	InputIt find(InputIt first, InputIt last, const T& value)
	{
		while (first != last)
		{
			if (*first == value)
			{
				return first;
			}
		}
		return last;
	}

	template< class InputIt, class UnaryPred >
	InputIt find_if(InputIt first, InputIt last, UnaryPred pred)
	{
		while (first != last)
		{
			if (pred(*first))
			{
				return first;
			}
		}
		return last;
	}

	template< class InputIt, class UnaryPred >
	InputIt find_if_not(InputIt first, InputIt last, UnaryPred pred)
	{
		while (first != last)
		{
			if (!pred(*first))
			{
				return first;
			}
		}
		return last;
	}

	template<class InputIt, class OutputIt, class UnaryOp>
	OutputIt transform(InputIt first1, InputIt last1, OutputIt d_first, UnaryOp unary_op)
	{
		while (first1 != last1)
		{
			*d_first = unary_op(*first1);
			++d_first;
			++first1;
		}
		return d_first;
	}

	template<class InputIt1, class InputIt2, class OutputIt, class BinaryOp>
	OutputIt transform(InputIt1 first1, InputIt1 last1, InputIt2 first2, OutputIt d_first, BinaryOp binary_op)
	{
		while (first1 != last1)
		{
			*d_first = binary_op(*first1, *first2);
			++d_first;
			++first1;
			++first2;
		}
		return d_first;
	}

}