#include <cstdio>

#ifndef LNI_VECTOR
#define LNI_VECTOR

namespace lni {

	template <typename T>
	class vector {
		public:
			vector();
			~vector();
			typedef T *iterator;
			iterator begin();
			iterator end();
			int size();
			void push_back(const T &);
			void emplace_back(T &&);
		private:
			int rsrv_sz = 4;
			int vec_sz = 0;
			T *arr;
	};

}

#include "vector.cpp"
#endif
