#include <cstddef>
#include <utility>
#include <iterator>
#include <stdexcept>

#ifndef LNI_VECTOR
#define LNI_VECTOR

#define LNI_VECTOR_MAX_SZ 1000000000

namespace lni {

	template <typename T>
	class vector {
		public:
			// types:
			typedef T                                     value_type;
			typedef T &                                   reference;
			typedef const T &                             const_reference;
			typedef T *                                   pointer;
			typedef const T *                             const_pointer;
			typedef T *                                   iterator;
			typedef const T *                             const_iterator;
			typedef std::reverse_iterator<iterator>       reverse_iterator;
			typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef ptrdiff_t                             difference_type;
			typedef unsigned int                          size_type;

			// 23.3.11.2, construct/copy/destroy:
			vector() noexcept;
			explicit vector(size_type n);
			vector(size_type n, const T &val);
			template <class InputIt> vector(InputIt first, InputIt last);
			vector(std::initializer_list<T>);
			vector(const vector<T> &);
			vector(vector<T> &&) noexcept;
			~vector();
			vector<T> & operator = (const vector<T> &);
			vector<T> & operator = (vector<T> &&);
			vector<T> & operator = (std::initializer_list<T>);
			void assign(size_type, const T &value);
			template <class InputIt> void assign(InputIt, InputIt);
			void assign(std::initializer_list<T>);

			// iterators:
			iterator begin() noexcept;
			const_iterator cbegin() const noexcept;
			iterator end() noexcept;
			const_iterator cend() const noexcept;
			reverse_iterator rbegin() noexcept;
			const_reverse_iterator crbegin() const noexcept;
			reverse_iterator rend() noexcept;
			const_reverse_iterator crend() const noexcept;

			// 23.3.11.3, capacity:
			bool empty() const noexcept;
			size_type size() const noexcept;
			size_type max_size() const noexcept;
			size_type capacity() const noexcept;
			void resize(size_type);
			void resize(size_type, const T &);
			void reserve(size_type);
			void shrink_to_fit();

			// element access
			reference operator [](size_type);
			const_reference operator [](size_type) const;
			reference at(size_type);
			const_reference at(size_type) const;
			reference front();
			const_reference front() const;
			reference back();
			const_reference back() const;

			// 23.3.11.4, data access:
			T * data() noexcept;
			const T * data() const noexcept; 

			// 23.3.11.5, modifiers:
			template <class ... Args> void emplace_back(Args && ... args);
			void push_back(const T &);
			void push_back(T &&);
			void pop_back();
	
			template <class ... Args> iterator emplace(const_iterator, Args && ...); 
			iterator insert(const_iterator, const T &);
			iterator insert(const_iterator, T &&);
			iterator insert(const_iterator, size_type, const T&);
			template <class InputIt> iterator insert(const_iterator, InputIt, InputIt);
			iterator insert(const_iterator, std::initializer_list<T>);
			iterator erase(const_iterator);
			iterator erase(const_iterator, const_iterator);
			void swap(vector<T> &);
			void clear() noexcept;

			bool operator == (const vector<T> &) const;
			bool operator != (const vector<T> &) const;
			bool operator < (const vector<T> &) const;
			bool operator <= (const vector<T> &) const;
			bool operator > (const vector<T> &) const;
			bool operator >= (const vector<T> &) const;
		private:
			size_type rsrv_sz = 4;
			size_type vec_sz = 0;
			T *arr;

			inline void reallocate();

	};


	
	template <typename T>
	vector<T>::vector() noexcept {
		arr = new T[rsrv_sz];
	}

	template <typename T>
	vector<T>::vector(typename vector<T>::size_type n) {
		size_type i;
		rsrv_sz = n << 2;
		arr = new T[rsrv_sz];
		for (i = 0; i < n; ++i)
			arr[i] = T();
		vec_sz = n;
	}

	template <typename T>
	vector<T>::vector(typename vector<T>::size_type n, const T &value) {
		size_type i;
		rsrv_sz = n << 2;
		arr = new T[rsrv_sz];
		for (i = 0; i < n; ++i)
			arr[i] = value;
		vec_sz = n;
	}

	template <typename T>
	template <class InputIt>
	vector<T>::vector(InputIt first, InputIt last) {
		size_type i, count = last - first;
		rsrv_sz = count << 2;
		arr = new T[rsrv_sz];
		for (i = 0; i < count; ++i, ++first)
			arr[i] = *first;
	}

	template <typename T>
	vector<T>::vector(std::initializer_list<T> lst) {
		rsrv_sz = lst.size() << 2;
		arr = new T[rsrv_sz];
		for (auto &item: lst)
			arr[vec_sz++] = item;
	}

	template <typename T>
	vector<T>::vector(const vector<T> &other) {
		size_type i;
		rsrv_sz = other.rsrv_sz;
		arr = new T[rsrv_sz];
		for (i = 0; i < other.vec_sz; ++i)
			arr[i] = other.arr[i];
		vec_sz = other.vec_sz;
	}

	template <typename T>
	vector<T>::vector(vector<T> &&other) noexcept {
		size_type i;
		rsrv_sz = other.rsrv_sz;
		arr = new T[rsrv_sz];
		for (i = 0; i < other.vec_sz; ++i)
			arr[i] = std::move(other.arr[i]);
		vec_sz = other.vec_sz;
	}

	template <typename T>
	vector<T>::~vector() {
		delete [] arr;
	}

	template <typename T>
	vector<T> & vector<T>::operator = (const vector<T> &other) {
		size_type i;
		if (rsrv_sz < other.vec_sz) {
			rsrv_sz = other.vec_sz << 2;
			reallocate();
		}
		for (i = 0; i < other.vec_sz; ++i)
			arr[i] = other.arr[i];
		vec_sz = other.vec_sz;
	}

	template <typename T>
	vector<T> & vector<T>::operator = (vector<T> &&other) {
		size_type i;
		if (rsrv_sz < other.vec_sz) {
			rsrv_sz = other.vec_sz << 2;
			reallocate();
		}
		for (i = 0; i < other.vec_sz; ++i)
			arr[i] = std::move(other.arr[i]);
		vec_sz = other.vec_sz;
	}

	template <typename T>
	vector<T> & vector<T>::operator = (std::initializer_list<T> lst) {
		if (rsrv_sz < lst.size()) {
			rsrv_sz = lst.size() << 2;
			reallocate();
		}
		vec_sz = 0;
		for (auto &item: lst)
			arr[vec_sz++] = item;
	}

	template <typename T>
	void vector<T>::assign(typename vector<T>::size_type count, const T &value) {
		size_type i;
		if (count > rsrv_sz) {
			rsrv_sz = count << 2;
			reallocate();
		}
		for (i = 0; i < count; ++i)
			arr[i] = value;
		vec_sz = count;
	}

	template <typename T>
	template <class InputIt>
	void vector<T>::assign(InputIt first, InputIt last) {
		size_type i, count = last - first;
		if (count > rsrv_sz) {
			rsrv_sz = count << 2;
			reallocate();
		}
		for (i = 0; i < count; ++i, ++first)
			arr[i] = *first;
		vec_sz = count;
	}

	template <typename T>
	void vector<T>::assign(std::initializer_list<T> lst) {
		size_type i, count = lst.size();
		if (count > rsrv_sz) {
			rsrv_sz = count << 2;
			reallocate();
		}
		i = 0;
		for (auto &item: lst)
			arr[i++] = item;
	}


	template <typename T>
	typename vector<T>::iterator vector<T>::begin() noexcept {
		return arr;
	}

	template <typename T>
	typename vector<T>::const_iterator vector<T>::cbegin() const noexcept {
		return arr;
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::end() noexcept {
		return arr + vec_sz;
	}

	template <typename T>
	typename vector<T>::const_iterator vector<T>::cend() const noexcept {
		return arr + vec_sz;
	}

	template <typename T>
	typename vector<T>::reverse_iterator vector<T>::rbegin() noexcept {
		return reverse_iterator(arr + vec_sz);
	}

	template <typename T>
	typename vector<T>::const_reverse_iterator vector<T>::crbegin() const noexcept {
		return reverse_iterator(arr + vec_sz);
	}

	template <typename T>
	typename vector<T>::reverse_iterator vector<T>::rend() noexcept {
		return reverse_iterator(arr);
	}
	
	template <typename T>
	typename vector<T>::const_reverse_iterator vector<T>::crend() const noexcept {
		return reverse_iterator(arr);
	}


	template <typename T>
	inline void vector<T>::reallocate() {
		size_type i;
		T *tarr = new T[rsrv_sz];
		for (i = 0; i < vec_sz; ++i)
			tarr[i] = arr[i];
		delete [] arr;
		arr = tarr;
	}


	template <typename T>
	bool vector<T>::empty() const noexcept {
		return vec_sz == 0;
	}
	
	template <typename T>
	typename vector<T>::size_type vector<T>::size() const noexcept{
		return vec_sz;
	}

	template <typename T>
	typename vector<T>::size_type vector<T>::max_size() const noexcept {
		return LNI_VECTOR_MAX_SZ;
	}

	template <typename T>
	typename vector<T>::size_type vector<T>::capacity() const noexcept {
		return rsrv_sz;
	}
	
	template <typename T>
	void vector<T>::resize(typename vector<T>::size_type sz) {
		if (sz > vec_sz) {
			if (sz > rsrv_sz) {
				rsrv_sz = sz;
				reallocate();
			}
		} else {
			size_type i;
			for (i = vec_sz; i < sz; ++i)
				arr[i].~T();
		}
		vec_sz = sz;
	}

	template <typename T>
	void vector<T>::resize(typename vector<T>::size_type sz, const T &c) {
		if (sz > vec_sz) {
			if (sz > rsrv_sz) {
				rsrv_sz = sz;
				reallocate();
			}
			size_type i;
			for (i = vec_sz; i < sz; ++i)
				arr[i] = c;
		} else {
			size_type i;
			for (i = vec_sz; i < sz; ++i)
				arr[i].~T();
		}
		vec_sz = sz;
	}

	template <typename T>
	void vector<T>::reserve(typename vector<T>::size_type _sz) {
		if (_sz > rsrv_sz) {
			rsrv_sz = _sz;
			reallocate();
		}
	}

	template <typename T>
	void vector<T>::shrink_to_fit() {
		rsrv_sz = vec_sz;
		reallocate();
	}

	
	template <typename T>
	typename vector<T>::reference vector<T>::operator [](typename vector<T>::size_type idx) {
		return arr[idx];
	}

	template <typename T>
	typename vector<T>::const_reference vector<T>::operator [](typename vector<T>::size_type idx) const {
		return arr[idx];
	}

	template <typename T>
	typename vector<T>::reference vector<T>::at(size_type pos) {
		if (pos < vec_sz)
			return arr[pos];
		else
			throw std::out_of_range("accessed position is out of range");
	}

	template <typename T>
	typename vector<T>::const_reference vector<T>::at(size_type pos) const {
		if (pos < vec_sz)
			return arr[pos];
		else
			throw std::out_of_range("accessed position is out of range");
	}

	template <typename T>
	typename vector<T>::reference vector<T>::front() {
		return arr[0];
	}

	template <typename T>
	typename vector<T>::const_reference vector<T>::front() const {
		return arr[0];
	}

	template <typename T>
	typename vector<T>::reference vector<T>::back() {
		return arr[vec_sz - 1];
	}

	template <typename T>
	typename vector<T>::const_reference vector<T>::back() const {
		return arr[vec_sz - 1];
	}

	
	template <typename T>
	T * vector<T>::data() noexcept {
		return arr;
	}

	template <typename T>
	const T * vector<T>::data() const noexcept {
		return arr;
	}


	template <typename T>
	template <class ... Args>
	void vector<T>::emplace_back(Args && ... args) {
		if (vec_sz == rsrv_sz) {
			rsrv_sz <<= 2;
			reallocate();
		}
		arr[vec_sz] = std::move( T( std::forward<Args>(args) ... ) );
		++vec_sz;
	}

	template <typename T>
	void vector<T>::push_back(const T &val) {
		if (vec_sz == rsrv_sz) {
			rsrv_sz <<= 2;
			reallocate();
		}
		arr[vec_sz] = val;
		++vec_sz;
	}

	template <typename T>
	void vector<T>::push_back(T &&val) {
		if (vec_sz == rsrv_sz) {
			rsrv_sz <<= 2;
			reallocate();
		}
		arr[vec_sz] = std::move(val);
		++vec_sz;
	}

	template <typename T>
	void vector<T>::pop_back() {
		--vec_sz;
		arr[vec_sz].~T();
	}


	template <typename T>
	template <class ... Args>
	typename vector<T>::iterator vector<T>::emplace(typename vector<T>::const_iterator it, Args && ... args) {
		size_type i, idx = it - arr;
		if (vec_sz == rsrv_sz) {
			rsrv_sz <<= 2;
			reallocate();
		}
		for (i = vec_sz - 1; i > idx; --i)
			arr[i + 1] = arr[i];
		arr[idx + 1] = arr[idx];
		arr[idx] = std::move( T( std::forward<Args>(args) ... ) );
		++vec_sz;
		return arr + idx;
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::insert(typename vector<T>::const_iterator it, const T &val) {
		size_type i, idx = it - arr;
		if (vec_sz == rsrv_sz) {
			rsrv_sz <<= 2;
			reallocate();
		}
		for (i = vec_sz - 1; i > idx; --i) // idx can be 0
			arr[i + 1] = arr[i];
		arr[idx + 1] = arr[idx];
		arr[idx] = val;
		++vec_sz;
		return arr + idx;
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::insert(typename vector<T>::const_iterator it, T &&val) {
		size_type i, idx = it - arr;
		if (vec_sz == rsrv_sz) {
			rsrv_sz <<= 2;
			reallocate();
		}
		for (i = vec_sz - 1; i > idx; --i) // idx can be 0
			arr[i + 1] = arr[i];
		arr[idx + 1] = arr[idx];
		arr[idx] = std::move(val);
		++vec_sz;
		return arr + idx;
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::insert(typename vector<T>::const_iterator it, typename vector<T>::size_type cnt, const T &val) {
		size_type i, idx = it - arr;
		if (!cnt) return arr + idx;
		if (vec_sz + cnt > rsrv_sz) {
			rsrv_sz = (vec_sz + cnt) << 2;
			reallocate();
		}
		for (i = vec_sz - 1; i > idx; --i) // idx can be 0
			arr[i + cnt] = arr[i];
		arr[idx + cnt] = arr[idx];
		for (i = idx; i < idx + cnt; ++i)
			arr[i] = val;
		vec_sz += cnt;
		return arr + idx;
	}

	template <typename T>
	template <class InputIt>
	typename vector<T>::iterator vector<T>::insert(typename vector<T>::const_iterator it, InputIt first, InputIt last) {
		size_type i, idx = it - arr, cnt = last - first;
		if (!cnt) return arr + idx;
		if (vec_sz + cnt > rsrv_sz) {
			rsrv_sz = (vec_sz + cnt) << 2;
			reallocate();
		}
		for (i = vec_sz - 1; i > idx; --i)
			arr[i + cnt] = arr[i];
		arr[idx + cnt] = arr[idx];
		for (i = idx; first != last; ++i, ++first)
			arr[i] = *first;
		vec_sz += cnt;
		return arr + idx;
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::insert(typename vector<T>::const_iterator it, std::initializer_list<T> lst) {
		size_type i, idx = it - arr, cnt = lst.size();
		if (!cnt) return arr + idx;
		if (vec_sz + cnt > rsrv_sz) {
			rsrv_sz = (vec_sz + cnt) << 2;
			reallocate();
		}
		for (i = vec_sz - 1; i > idx; --i)
			arr[i + cnt] = arr[i];
		arr[idx + cnt] = arr[idx];
		i = idx;
		for (auto &item: lst)
			arr[i++] = item;
		vec_sz += cnt;
		return arr + idx;
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::erase(typename vector<T>::const_iterator it) {
		size_type i, idx = it - arr;
		iterator iit = arr + idx;
		(*iit).~T();
		for (i = idx + 1; i < vec_sz; ++i)
			arr[i - 1] = arr[i];
		--vec_sz;
		return iit;
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::erase(typename vector<T>::const_iterator first, typename vector<T>::const_iterator last) {
		size_type i, idx_f = first - arr, idx_l = last - arr, cnt = last - first;
		if (!cnt) return arr + idx_f;
		for (i = idx_f; i != idx_l; ++i)
			arr[i].~T();
		for (i = idx_l; i < vec_sz; ++i)
			arr[i - cnt] = arr[i];
		vec_sz -= cnt;
		return arr + idx_f;
	}

	template <typename T>
	void vector<T>::swap(vector<T> &rhs) {
		size_type i, sz = rhs.size();
		T *tmp = new T[sz];
		for (i = 0; i < sz; ++i)
			tmp[i] = rhs.arr[i];
		rhs.reserve(vec_sz);
		for (i = 0; i < vec_sz; ++i)
			rhs.arr[i] = arr[i];
		rhs.vec_sz = vec_sz;
		reserve(sz);
		for (i = 0; i < sz; ++i)
			arr[i] = tmp[i];
		vec_sz = sz;
		delete [] tmp;
	}

	template <typename T>
	void vector<T>::clear() noexcept {
		size_type i;
		for (i = 0; i < vec_sz; ++i)
			arr[i].~T();
		vec_sz = 0;
	}

	
	template <typename T>
	bool vector<T>::operator == (const vector<T> &rhs) const {
		if (vec_sz != rhs.vec_sz) return false;
		size_type i;
		for (i = 0; i < vec_sz; ++i)
			if (arr[i] != rhs.arr[i])
				return false;
		return true;
	}

	template <typename T>
	bool vector<T>::operator != (const vector<T> &rhs) const {
		if (vec_sz != rhs.vec_sz) return true;
		size_type i;
		for (i = 0; i < vec_sz; ++i)
			if (arr[i] != rhs.arr[i])
				return true;
		return false;
	}

	template <typename T>
	bool vector<T>::operator < (const vector<T> &rhs) const {
		size_type i, j, ub = vec_sz < rhs.vec_sz ? vec_sz : rhs.vec_sz;
		for (i = 0; i < ub; ++i)
			if (arr[i] != rhs.arr[i])
				return arr[i] < rhs.arr[i];
		return vec_sz < rhs.vec_sz;
	}

	template <typename T>
	bool vector<T>::operator <= (const vector<T> &rhs) const {
		size_type i, j, ub = vec_sz < rhs.vec_sz ? vec_sz : rhs.vec_sz;
		for (i = 0; i < ub; ++i)
			if (arr[i] != rhs.arr[i])
				return arr[i] < rhs.arr[i];
		return vec_sz <= rhs.vec_sz;
	}

	template <typename T>
	bool vector<T>::operator > (const vector<T> &rhs) const {
		size_type i, j, ub = vec_sz < rhs.vec_sz ? vec_sz : rhs.vec_sz;
		for (i = 0; i < ub; ++i)
			if (arr[i] != rhs.arr[i])
				return arr[i] > rhs.arr[i];
		return vec_sz > rhs.vec_sz;
	}

	template <typename T>
	bool vector<T>::operator >= (const vector<T> &rhs) const {
		size_type i, j, ub = vec_sz < rhs.vec_sz ? vec_sz : rhs.vec_sz;
		for (i = 0; i < ub; ++i)
			if (arr[i] != rhs.arr[i])
				return arr[i] > rhs.arr[i];
		return vec_sz >= rhs.vec_sz;
	}



	template <>
	void vector<bool>::resize(typename vector<bool>::size_type sz) {
		if (sz > rsrv_sz) {
			rsrv_sz = sz;
			reallocate();
		}
		vec_sz = sz;
	}

	template <>
	void vector<signed char>::resize(typename vector<signed char>::size_type sz) {
		if (sz > rsrv_sz) {
			rsrv_sz = sz;
			reallocate();
		}
		vec_sz = sz;
	}

	template <>
	void vector<unsigned char>::resize(typename vector<unsigned char>::size_type sz) {
		if (sz > rsrv_sz) {
			rsrv_sz = sz;
			reallocate();
		}
		vec_sz = sz;
	}

	template <>
	void vector<char>::resize(typename vector<char>::size_type sz) {
		if (sz > rsrv_sz) {
			rsrv_sz = sz;
			reallocate();
		}
		vec_sz = sz;
	}

	template <>
	void vector<short int>::resize(typename vector<short int>::size_type sz) {
		if (sz > rsrv_sz) {
			rsrv_sz = sz;
			reallocate();
		}
		vec_sz = sz;
	}

	template <>
	void vector<unsigned short int>::resize(typename vector<unsigned short int>::size_type sz) {
		if (sz > rsrv_sz) {
			rsrv_sz = sz;
			reallocate();
		}
		vec_sz = sz;
	}

	template <>
	void vector<int>::resize(typename vector<int>::size_type sz) {
		if (sz > rsrv_sz) {
			rsrv_sz = sz;
			reallocate();
		}
		vec_sz = sz;
	}

	template <>
	void vector<unsigned int>::resize(typename vector<unsigned int>::size_type sz) {
		if (sz > rsrv_sz) {
			rsrv_sz = sz;
			reallocate();
		}
		vec_sz = sz;
	}

	template <>
	void vector<long int>::resize(typename vector<long int>::size_type sz) {
		if (sz > rsrv_sz) {
			rsrv_sz = sz;
			reallocate();
		}
		vec_sz = sz;
	}

	template <>
	void vector<unsigned long int>::resize(typename vector<unsigned long int>::size_type sz) {
		if (sz > rsrv_sz) {
			rsrv_sz = sz;
			reallocate();
		}
		vec_sz = sz;
	}

	template <>
	void vector<long long int>::resize(typename vector<long long int>::size_type sz) {
		if (sz > rsrv_sz) {
			rsrv_sz = sz;
			reallocate();
		}
		vec_sz = sz;
	}

	template <>
	void vector<unsigned long long int>::resize(typename vector<unsigned long long int>::size_type sz) {
		if (sz > rsrv_sz) {
			rsrv_sz = sz;
			reallocate();
		}
		vec_sz = sz;
	}

	template <>
	void vector<float>::resize(typename vector<float>::size_type sz) {
		if (sz > rsrv_sz) {
			rsrv_sz = sz;
			reallocate();
		}
		vec_sz = sz;
	}

	template <>
	void vector<double>::resize(typename vector<double>::size_type sz) {
		if (sz > rsrv_sz) {
			rsrv_sz = sz;
			reallocate();
		}
		vec_sz = sz;
	}

	template <>
	void vector<long double>::resize(typename vector<long double>::size_type sz) {
		if (sz > rsrv_sz) {
			rsrv_sz = sz;
			reallocate();
		}
		vec_sz = sz;
	}


	template <>
	void vector<bool>::resize(typename vector<bool>::size_type sz, const bool &c) {
		if (sz > vec_sz) {
			if (sz > rsrv_sz) {
				rsrv_sz = sz;
				reallocate();
			}
			size_type i;
			for (i = vec_sz; i < sz; ++i)
				arr[i] = c;
		}
		vec_sz = sz;
	}

	template <>
	void vector<signed char>::resize(typename vector<signed char>::size_type sz, const signed char &c) {
		if (sz > vec_sz) {
			if (sz > rsrv_sz) {
				rsrv_sz = sz;
				reallocate();
			}
			size_type i;
			for (i = vec_sz; i < sz; ++i)
				arr[i] = c;
		}
		vec_sz = sz;
	}

	template <>
	void vector<unsigned char>::resize(typename vector<unsigned char>::size_type sz, const unsigned char &c) {
		if (sz > vec_sz) {
			if (sz > rsrv_sz) {
				rsrv_sz = sz;
				reallocate();
			}
			size_type i;
			for (i = vec_sz; i < sz; ++i)
				arr[i] = c;
		}
		vec_sz = sz;
	}

	template <>
	void vector<char>::resize(typename vector<char>::size_type sz, const char &c) {
		if (sz > vec_sz) {
			if (sz > rsrv_sz) {
				rsrv_sz = sz;
				reallocate();
			}
			size_type i;
			for (i = vec_sz; i < sz; ++i)
				arr[i] = c;
		}
		vec_sz = sz;
	}

	template <>
	void vector<short int>::resize(typename vector<short int>::size_type sz, const short int &c) {
		if (sz > vec_sz) {
			if (sz > rsrv_sz) {
				rsrv_sz = sz;
				reallocate();
			}
			size_type i;
			for (i = vec_sz; i < sz; ++i)
				arr[i] = c;
		}
		vec_sz = sz;
	}

	template <>
	void vector<unsigned short int>::resize(typename vector<unsigned short int>::size_type sz, const unsigned short int &c) {
		if (sz > vec_sz) {
			if (sz > rsrv_sz) {
				rsrv_sz = sz;
				reallocate();
			}
			size_type i;
			for (i = vec_sz; i < sz; ++i)
				arr[i] = c;
		}
		vec_sz = sz;
	}

	template <>
	void vector<int>::resize(typename vector<int>::size_type sz, const int &c) {
		if (sz > vec_sz) {
			if (sz > rsrv_sz) {
				rsrv_sz = sz;
				reallocate();
			}
			size_type i;
			for (i = vec_sz; i < sz; ++i)
				arr[i] = c;
		}
		vec_sz = sz;
	}

	template <>
	void vector<unsigned int>::resize(typename vector<unsigned int>::size_type sz, const unsigned int &c) {
		if (sz > vec_sz) {
			if (sz > rsrv_sz) {
				rsrv_sz = sz;
				reallocate();
			}
			size_type i;
			for (i = vec_sz; i < sz; ++i)
				arr[i] = c;
		}
		vec_sz = sz;
	}

	template <>
	void vector<long int>::resize(typename vector<long int>::size_type sz, const long int &c) {
		if (sz > vec_sz) {
			if (sz > rsrv_sz) {
				rsrv_sz = sz;
				reallocate();
			}
			size_type i;
			for (i = vec_sz; i < sz; ++i)
				arr[i] = c;
		}
		vec_sz = sz;
	}

	template <>
	void vector<unsigned long int>::resize(typename vector<unsigned long int>::size_type sz, const unsigned long int &c) {
		if (sz > vec_sz) {
			if (sz > rsrv_sz) {
				rsrv_sz = sz;
				reallocate();
			}
			size_type i;
			for (i = vec_sz; i < sz; ++i)
				arr[i] = c;
		}
		vec_sz = sz;
	}

	template <>
	void vector<long long int>::resize(typename vector<long long int>::size_type sz, const long long int &c) {
		if (sz > vec_sz) {
			if (sz > rsrv_sz) {
				rsrv_sz = sz;
				reallocate();
			}
			size_type i;
			for (i = vec_sz; i < sz; ++i)
				arr[i] = c;
		}
		vec_sz = sz;
	}

	template <>
	void vector<unsigned long long int>::resize(typename vector<unsigned long long int>::size_type sz, const unsigned long long int &c) {
		if (sz > vec_sz) {
			if (sz > rsrv_sz) {
				rsrv_sz = sz;
				reallocate();
			}
			size_type i;
			for (i = vec_sz; i < sz; ++i)
				arr[i] = c;
		}
		vec_sz = sz;
	}

	template <>
	void vector<float>::resize(typename vector<float>::size_type sz, const float &c) {
		if (sz > vec_sz) {
			if (sz > rsrv_sz) {
				rsrv_sz = sz;
				reallocate();
			}
			size_type i;
			for (i = vec_sz; i < sz; ++i)
				arr[i] = c;
		}
		vec_sz = sz;
	}

	template <>
	void vector<double>::resize(typename vector<double>::size_type sz, const double &c) {
		if (sz > vec_sz) {
			if (sz > rsrv_sz) {
				rsrv_sz = sz;
				reallocate();
			}
			size_type i;
			for (i = vec_sz; i < sz; ++i)
				arr[i] = c;
		}
		vec_sz = sz;
	}

	template <>
	void vector<long double>::resize(typename vector<long double>::size_type sz, const long double &c) {
		if (sz > vec_sz) {
			if (sz > rsrv_sz) {
				rsrv_sz = sz;
				reallocate();
			}
			size_type i;
			for (i = vec_sz; i < sz; ++i)
				arr[i] = c;
		}
		vec_sz = sz;
	}


	template <>
	void vector<bool>::pop_back() {
		--vec_sz;
	}

	template <>
	void vector<signed char>::pop_back() {
		--vec_sz;
	}

	template <>
	void vector<unsigned char>::pop_back() {
		--vec_sz;
	}

	template <>
	void vector<char>::pop_back() {
		--vec_sz;
	}

	template <>
	void vector<short int>::pop_back() {
		--vec_sz;
	}

	template <>
	void vector<unsigned short int>::pop_back() {
		--vec_sz;
	}

	template <>
	void vector<int>::pop_back() {
		--vec_sz;
	}

	template <>
	void vector<unsigned int>::pop_back() {
		--vec_sz;
	}

	template <>
	void vector<long int>::pop_back() {
		--vec_sz;
	}

	template <>
	void vector<unsigned long int>::pop_back() {
		--vec_sz;
	}

	template <>
	void vector<long long int>::pop_back() {
		--vec_sz;
	}

	template <>
	void vector<unsigned long long int>::pop_back() {
		--vec_sz;
	}

	template <>
	void vector<float>::pop_back() {
		--vec_sz;
	}

	template <>
	void vector<double>::pop_back() {
		--vec_sz;
	}

	template <>
	void vector<long double>::pop_back() {
		--vec_sz;
	}


	template <>
	typename vector<bool>::iterator vector<bool>::erase(typename vector<bool>::const_iterator it) {
		size_type i, idx = it - arr;
		iterator iit = arr + idx;
		for (i = idx + 1; i < vec_sz; ++i)
			arr[i - 1] = arr[i];
		--vec_sz;
		return iit;
	}

	template <>
	typename vector<signed char>::iterator vector<signed char>::erase(typename vector<signed char>::const_iterator it) {
		size_type i, idx = it - arr;
		iterator iit = arr + idx;
		for (i = idx + 1; i < vec_sz; ++i)
			arr[i - 1] = arr[i];
		--vec_sz;
		return iit;
	}

	template <>
	typename vector<unsigned char>::iterator vector<unsigned char>::erase(typename vector<unsigned char>::const_iterator it) {
		size_type i, idx = it - arr;
		iterator iit = arr + idx;
		for (i = idx + 1; i < vec_sz; ++i)
			arr[i - 1] = arr[i];
		--vec_sz;
		return iit;
	}

	template <>
	typename vector<char>::iterator vector<char>::erase(typename vector<char>::const_iterator it) {
		size_type i, idx = it - arr;
		iterator iit = arr + idx;
		for (i = idx + 1; i < vec_sz; ++i)
			arr[i - 1] = arr[i];
		--vec_sz;
		return iit;
	}

	template <>
	typename vector<short int>::iterator vector<short int>::erase(typename vector<short int>::const_iterator it) {
		size_type i, idx = it - arr;
		iterator iit = arr + idx;
		for (i = idx + 1; i < vec_sz; ++i)
			arr[i - 1] = arr[i];
		--vec_sz;
		return iit;
	}

	template <>
	typename vector<unsigned short int>::iterator vector<unsigned short int>::erase(typename vector<unsigned short int>::const_iterator it) {
		size_type i, idx = it - arr;
		iterator iit = arr + idx;
		for (i = idx + 1; i < vec_sz; ++i)
			arr[i - 1] = arr[i];
		--vec_sz;
		return iit;
	}

	template <>
	typename vector<int>::iterator vector<int>::erase(typename vector<int>::const_iterator it) {
		size_type i, idx = it - arr;
		iterator iit = arr + idx;
		for (i = idx + 1; i < vec_sz; ++i)
			arr[i - 1] = arr[i];
		--vec_sz;
		return iit;
	}

	template <>
	typename vector<unsigned int>::iterator vector<unsigned int>::erase(typename vector<unsigned int>::const_iterator it) {
		size_type i, idx = it - arr;
		iterator iit = arr + idx;
		for (i = idx + 1; i < vec_sz; ++i)
			arr[i - 1] = arr[i];
		--vec_sz;
		return iit;
	}

	template <>
	typename vector<long int>::iterator vector<long int>::erase(typename vector<long int>::const_iterator it) {
		size_type i, idx = it - arr;
		iterator iit = arr + idx;
		for (i = idx + 1; i < vec_sz; ++i)
			arr[i - 1] = arr[i];
		--vec_sz;
		return iit;
	}

	template <>
	typename vector<unsigned long int>::iterator vector<unsigned long int>::erase(typename vector<unsigned long int>::const_iterator it) {
		size_type i, idx = it - arr;
		iterator iit = arr + idx;
		for (i = idx + 1; i < vec_sz; ++i)
			arr[i - 1] = arr[i];
		--vec_sz;
		return iit;
	}

	template <>
	typename vector<long long int>::iterator vector<long long int>::erase(typename vector<long long int>::const_iterator it) {
		size_type i, idx = it - arr;
		iterator iit = arr + idx;
		for (i = idx + 1; i < vec_sz; ++i)
			arr[i - 1] = arr[i];
		--vec_sz;
		return iit;
	}

	template <>
	typename vector<unsigned long long int>::iterator vector<unsigned long long int>::erase(typename vector<unsigned long long int>::const_iterator it) {
		size_type i, idx = it - arr;
		iterator iit = arr + idx;
		for (i = idx + 1; i < vec_sz; ++i)
			arr[i - 1] = arr[i];
		--vec_sz;
		return iit;
	}

	template <>
	typename vector<float>::iterator vector<float>::erase(typename vector<float>::const_iterator it) {
		size_type i, idx = it - arr;
		iterator iit = arr + idx;
		for (i = idx + 1; i < vec_sz; ++i)
			arr[i - 1] = arr[i];
		--vec_sz;
		return iit;
	}

	template <>
	typename vector<double>::iterator vector<double>::erase(typename vector<double>::const_iterator it) {
		size_type i, idx = it - arr;
		iterator iit = arr + idx;
		for (i = idx + 1; i < vec_sz; ++i)
			arr[i - 1] = arr[i];
		--vec_sz;
		return iit;
	}

	template <>
	typename vector<long double>::iterator vector<long double>::erase(typename vector<long double>::const_iterator it) {
		size_type i, idx = it - arr;
		iterator iit = arr + idx;
		for (i = idx + 1; i < vec_sz; ++i)
			arr[i - 1] = arr[i];
		--vec_sz;
		return iit;
	}


	template <>
	typename vector<bool>::iterator vector<bool>::erase(typename vector<bool>::const_iterator first, typename vector<bool>::const_iterator last) {
		size_type i, idx_f = first - arr, idx_l = last - arr, cnt = last - first;
		if (!cnt) return arr + idx_f;
		for (i = idx_l; i < vec_sz; ++i)
			arr[i - cnt] = arr[i];
		vec_sz -= cnt;
		return arr + idx_f;
	}

	template <>
	typename vector<signed char>::iterator vector<signed char>::erase(typename vector<signed char>::const_iterator first, typename vector<signed char>::const_iterator last) {
		size_type i, idx_f = first - arr, idx_l = last - arr, cnt = last - first;
		if (!cnt) return arr + idx_f;
		for (i = idx_l; i < vec_sz; ++i)
			arr[i - cnt] = arr[i];
		vec_sz -= cnt;
		return arr + idx_f;
	}

	template <>
	typename vector<unsigned char>::iterator vector<unsigned char>::erase(typename vector<unsigned char>::const_iterator first, typename vector<unsigned char>::const_iterator last) {
		size_type i, idx_f = first - arr, idx_l = last - arr, cnt = last - first;
		if (!cnt) return arr + idx_f;
		for (i = idx_l; i < vec_sz; ++i)
			arr[i - cnt] = arr[i];
		vec_sz -= cnt;
		return arr + idx_f;
	}

	template <>
	typename vector<char>::iterator vector<char>::erase(typename vector<char>::const_iterator first, typename vector<char>::const_iterator last) {
		size_type i, idx_f = first - arr, idx_l = last - arr, cnt = last - first;
		if (!cnt) return arr + idx_f;
		for (i = idx_l; i < vec_sz; ++i)
			arr[i - cnt] = arr[i];
		vec_sz -= cnt;
		return arr + idx_f;
	}

	template <>
	typename vector<short int>::iterator vector<short int>::erase(typename vector<short int>::const_iterator first, typename vector<short int>::const_iterator last) {
		size_type i, idx_f = first - arr, idx_l = last - arr, cnt = last - first;
		if (!cnt) return arr + idx_f;
		for (i = idx_l; i < vec_sz; ++i)
			arr[i - cnt] = arr[i];
		vec_sz -= cnt;
		return arr + idx_f;
	}

	template <>
	typename vector<unsigned short int>::iterator vector<unsigned short int>::erase(typename vector<unsigned short int>::const_iterator first, typename vector<unsigned short int>::const_iterator last) {
		size_type i, idx_f = first - arr, idx_l = last - arr, cnt = last - first;
		if (!cnt) return arr + idx_f;
		for (i = idx_l; i < vec_sz; ++i)
			arr[i - cnt] = arr[i];
		vec_sz -= cnt;
		return arr + idx_f;
	}

	template <>
	typename vector<int>::iterator vector<int>::erase(typename vector<int>::const_iterator first, typename vector<int>::const_iterator last) {
		size_type i, idx_f = first - arr, idx_l = last - arr, cnt = last - first;
		if (!cnt) return arr + idx_f;
		for (i = idx_l; i < vec_sz; ++i)
			arr[i - cnt] = arr[i];
		vec_sz -= cnt;
		return arr + idx_f;
	}

	template <>
	typename vector<unsigned int>::iterator vector<unsigned int>::erase(typename vector<unsigned int>::const_iterator first, typename vector<unsigned int>::const_iterator last) {
		size_type i, idx_f = first - arr, idx_l = last - arr, cnt = last - first;
		if (!cnt) return arr + idx_f;
		for (i = idx_l; i < vec_sz; ++i)
			arr[i - cnt] = arr[i];
		vec_sz -= cnt;
		return arr + idx_f;
	}

	template <>
	typename vector<long long int>::iterator vector<long long int>::erase(typename vector<long long int>::const_iterator first, typename vector<long long int>::const_iterator last) {
		size_type i, idx_f = first - arr, idx_l = last - arr, cnt = last - first;
		if (!cnt) return arr + idx_f;
		for (i = idx_l; i < vec_sz; ++i)
			arr[i - cnt] = arr[i];
		vec_sz -= cnt;
		return arr + idx_f;
	}

	template <>
	typename vector<unsigned long long int>::iterator vector<unsigned long long int>::erase(typename vector<unsigned long long int>::const_iterator first, typename vector<unsigned long long int>::const_iterator last) {
		size_type i, idx_f = first - arr, idx_l = last - arr, cnt = last - first;
		if (!cnt) return arr + idx_f;
		for (i = idx_l; i < vec_sz; ++i)
			arr[i - cnt] = arr[i];
		vec_sz -= cnt;
		return arr + idx_f;
	}

	template <>
	typename vector<float>::iterator vector<float>::erase(typename vector<float>::const_iterator first, typename vector<float>::const_iterator last) {
		size_type i, idx_f = first - arr, idx_l = last - arr, cnt = last - first;
		if (!cnt) return arr + idx_f;
		for (i = idx_l; i < vec_sz; ++i)
			arr[i - cnt] = arr[i];
		vec_sz -= cnt;
		return arr + idx_f;
	}

	template <>
	typename vector<double>::iterator vector<double>::erase(typename vector<double>::const_iterator first, typename vector<double>::const_iterator last) {
		size_type i, idx_f = first - arr, idx_l = last - arr, cnt = last - first;
		if (!cnt) return arr + idx_f;
		for (i = idx_l; i < vec_sz; ++i)
			arr[i - cnt] = arr[i];
		vec_sz -= cnt;
		return arr + idx_f;
	}

	template <>
	typename vector<long double>::iterator vector<long double>::erase(typename vector<long double>::const_iterator first, typename vector<long double>::const_iterator last) {
		size_type i, idx_f = first - arr, idx_l = last - arr, cnt = last - first;
		if (!cnt) return arr + idx_f;
		for (i = idx_l; i < vec_sz; ++i)
			arr[i - cnt] = arr[i];
		vec_sz -= cnt;
		return arr + idx_f;
	}


	template <>
	void vector<bool>::clear() noexcept {
		vec_sz = 0;
	}

	template <>
	void vector<signed char>::clear() noexcept {
		vec_sz = 0;
	}

	template <>
	void vector<unsigned char>::clear() noexcept {
		vec_sz = 0;
	}

	template <>
	void vector<char>::clear() noexcept {
		vec_sz = 0;
	}

	template <>
	void vector<short int>::clear() noexcept {
		vec_sz = 0;
	}

	template <>
	void vector<unsigned short int>::clear() noexcept {
		vec_sz = 0;
	}

	template <>
	void vector<int>::clear() noexcept {
		vec_sz = 0;
	}

	template <>
	void vector<unsigned int>::clear() noexcept {
		vec_sz = 0;
	}

	template <>
	void vector<long int>::clear() noexcept {
		vec_sz = 0;
	}

	template <>
	void vector<unsigned long int>::clear() noexcept {
		vec_sz = 0;
	}

	template <>
	void vector<long long int>::clear() noexcept {
		vec_sz = 0;
	}

	template <>
	void vector<unsigned long long int>::clear() noexcept {
		vec_sz = 0;
	}

	template <>
	void vector<float>::clear() noexcept {
		vec_sz = 0;
	}

	template <>
	void vector<double>::clear() noexcept {
		vec_sz = 0;
	}

	template <>
	void vector<long double>::clear() noexcept {
		vec_sz = 0;
	}


}


#endif
