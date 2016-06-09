#include <cstdio>
#include <utility>

#ifndef LNI_VECTOR
#define LNI_VECTOR

namespace lni {

	template <typename T>
	class vector {
		public:
			vector();
			vector(std::initializer_list<T> &&);
			~vector();
			typedef T *iterator;
			inline int & operator [](const int &);

			iterator begin();
			iterator end();
			int size();
			void push_back(const T &);
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
