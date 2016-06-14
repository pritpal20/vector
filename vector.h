#include <cstdio>
#include <utility>

#ifndef LNI_VECTOR
#define LNI_VECTOR

namespace lni {

	template <typename T>
	class vector {
		public:
			vector();
			vector(int count);
			vector(int count, const T &val);
			vector(std::initializer_list<T>);
			vector(const lni::vector<T> &);
			vector(lni::vector<T> &&);
			~vector();
			lni::vector<T> & operator = (const lni::vector<T> &);
			lni::vector<T> & operator = (lni::vector<T> &&);
			lni::vector<T> & operator = (std::initializer_list<T>);
			typedef T *iterator;
			typedef const T *const_iterator;
			inline T & operator [](const int &);

			iterator begin();
			const_iterator cbegin();
			iterator end();
			const_iterator cend();
			T & front();
			T & back();

			int size();
			bool empty();
			void push_back(const T &);
			void push_back(T &&);
			void pop_back();
			void emplace_back(T &&);
			void reserve(const int &);
			void resize(const int &);
			void clear();
			void swap(lni::vector<T> &);
		private:
			int rsrv_sz = 4;
			int vec_sz = 0;
			T *arr;

			inline void reallocate();
	};

}

#include "vector.cpp"
#endif
