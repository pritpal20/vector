#include <cstdio>
#include <utility>

#ifndef LNI_VECTOR
#define LNI_VECTOR

namespace lni {

	template <typename T>
	class vector {
		public:
			typedef T *iterator;
			typedef const T *const_iterator;
			typedef std::size_t size_type;

			vector();
			vector(size_type count);
			vector(size_type count, const T &val);
			template <class InputIt> vector(InputIt first, InputIt last);
			vector(std::initializer_list<T>);
			vector(const lni::vector<T> &);
			vector(lni::vector<T> &&);
			~vector();
			lni::vector<T> & operator = (const lni::vector<T> &);
			lni::vector<T> & operator = (lni::vector<T> &&);
			lni::vector<T> & operator = (std::initializer_list<T>);
			inline T & operator [](size_type);

			iterator begin();
			const_iterator cbegin();
			iterator end();
			const_iterator cend();
			T & front();
			T & back();

			int size();
			bool empty();

			void assign(size_type, const T &value);
			template <class InputIt> void assign(InputIt, InputIt);
			void assign(std::initializer_list<T>);

			iterator insert(const_iterator, const T &);
			iterator insert(const_iterator, T &&);
			iterator insert(const_iterator, size_type, const T&);
			template <class InputIt> iterator insert(const_iterator, InputIt, InputIt);
			iterator insert(const_iterator, std::initializer_list<T>);
			iterator erase(const_iterator);
			iterator erase(const_iterator, const_iterator);

			void push_back(const T &);
			void push_back(T &&);
			void pop_back();
			void emplace_back(T &&);
			void reserve(size_type);
			void resize(size_type);
			void clear();
			void swap(lni::vector<T> &);

			bool operator == (const lni::vector<T> &) const;
			bool operator != (const lni::vector<T> &) const;
			bool operator < (const lni::vector<T> &) const;
			bool operator <= (const lni::vector<T> &) const;
			bool operator > (const lni::vector<T> &) const;
			bool operator >= (const lni::vector<T> &) const;
		private:
			size_type rsrv_sz = 4;
			size_type vec_sz = 0;
			T *arr;

			inline void reallocate();
	};

}

#include "vector.cpp"
#endif
