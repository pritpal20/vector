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
			vector(const vector<T> &);
			vector(vector<T> &&);
			~vector();
			typedef T *iterator;
			inline T & operator [](const int &);

			iterator begin();
			iterator end();
			T & front();
			T & back();

			int size();
			bool empty();
			void push_back(const T &);
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
