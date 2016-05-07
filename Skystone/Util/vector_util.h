#ifndef UTIL_VECTOR_UTIL_H
#define UTIL_VECTOR_UTIL_H

#include <vector>

namespace util
{
	namespace vector
	{
		/*
		Calls update on all elements in vector v unless toRemove(element) is true. Element is removed if true.
		RemPred: bool (*f)(E&) decides which E are removed
		Update: void (*f)(E&) decides how to update E if not removed
		RemAction: void (f*)(E&) optional: function called when object is removed
		*/
		template <typename E, typename RemPred, typename Update>
		void update_or_remove(std::vector<E>& v, RemPred toRemove, Update update)
		{
			update_or_remove(v, toRemove, update, [](E&) {});
		}

		template <typename E, typename RemPred, typename Update, typename RemAction>
		void update_or_remove(std::vector<E>& v, RemPred toRemove, Update update, RemAction onRemove)
		{
			for (size_t i = 0; i < v.size(); /*EMPTY*/)
			{
				E& element = v[i];
				if (toRemove(element))
				{
					onRemove(element);
					remove_at(v, i);
				}
				else
				{
					update(element);
					++i;
				}
			}
		}

		/*Calls removes elements in with toRemove returns true.
		RemPred: bool(*f)(E&) decides which E are removed
		RemAction: void (f*)(E&) optional: function called when object is removed
		*/
		template<typename E, typename RemPred>
		void remove(std::vector<E>&v, RemPred toRemove)
		{
			update_or_remove(v, toRemove, [](E&) {});
		}

		template<typename E, typename RemPred, typename RemAction>
		void remove(std::vector<E>&v, RemPred toRemove, RemAction onRemove)
		{
			update_or_remove(v, toRemove, [](E&) {}, onRemove);
		}

		/*
			Removes object at index of vector v by swapping with the end and popping back in O(1)
		*/
		template <typename E>
		void remove_at(std::vector<E>& v, int index)
		{
			v[index] = v.back();
			v.pop_back();
		}
	}
}

#endif //UTIL_VECTOR_UTIL_H