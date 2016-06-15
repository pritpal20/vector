
namespace lni {

	template <typename T>
	vector<T>::vector() {
		arr = new T[rsrv_sz];
	}

	template <typename T>
	vector<T>::vector(const lni::vector<T> &other) {
		size_type i;
		rsrv_sz = other.rsrv_sz;
		arr = new T[rsrv_sz];
		for (i = 0; i < other.vec_sz; ++i)
			arr[i] = other.arr[i];
		vec_sz = other.vec_sz;
	}

	template <typename T>
	vector<T>::vector(lni::vector<T> &&other) {
		size_type i;
		rsrv_sz = other.rsrv_sz;
		arr = new T[rsrv_sz];
		for (i = 0; i < other.vec_sz; ++i)
			arr[i] = std::move(other.arr[i]);
		vec_sz = other.vec_sz;
	}

	template <typename T>
	vector<T>::vector(typename vector<T>::size_type count) {
		size_type i;
		rsrv_sz = count << 2;
		arr = new T[rsrv_sz];
		for (i = 0; i < count; ++i)
			arr[i] = T();
		vec_sz = count;
	}

	template <typename T>
	vector<T>::vector(typename vector<T>::size_type count, const T &val) {
		size_type i;
		rsrv_sz = count << 2;
		arr = new T[rsrv_sz];
		for (i = 0; i < count; ++i)
			arr[i] = val;
		vec_sz = count;
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
	vector<T>::~vector() {
		delete [] arr;
	}

	template <typename T>
	lni::vector<T> & vector<T>::operator = (const lni::vector<T> &other) {
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
	lni::vector<T> & vector<T>::operator = (lni::vector<T> &&other) {
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
	lni::vector<T> & vector<T>::operator = (std::initializer_list<T> lst) {
		if (rsrv_sz < lst.size()) {
			rsrv_sz = lst.size() << 2;
			reallocate();
		}
		vec_sz = 0;
		for (auto &item: lst)
			arr[vec_sz++] = item;
	}

	template <typename T>
	inline T & vector<T>::operator [](typename vector<T>::size_type idx) {
		return arr[idx];
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::begin() {
		return arr;
	}

	template <typename T>
	typename vector<T>::const_iterator vector<T>::cbegin() {
		return arr;
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::end() {
		return arr + vec_sz;
	}

	template <typename T>
	typename vector<T>::const_iterator vector<T>::cend() {
		return arr + vec_sz;
	}

	template <typename T>
	T & vector<T>::front() {
		return arr[0];
	}

	template <typename T>
	T & vector<T>::back() {
		return arr[vec_sz - 1];
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
	typename vector<T>::size_type vector<T>::size() {
		return vec_sz;
	}

	template <typename T>
	bool vector<T>::empty() {
		return vec_sz == 0;
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
			rsrv_sz = vec_sz + cnt;
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
			rsrv_sz = vec_sz + cnt;
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
			rsrv_sz = vec_sz + cnt;
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
	void vector<T>::emplace_back(T &&val) {
		if (vec_sz == rsrv_sz) {
			rsrv_sz <<= 2;
			reallocate();
		}
		arr[vec_sz] = std::move(val);
		++vec_sz;
	}

	template <typename T>
	void vector<T>::reserve(typename vector<T>::size_type _sz) {
		if (_sz > rsrv_sz) {
			rsrv_sz = _sz;
			reallocate();
		}
	}

	template <typename T>
	void vector<T>::resize(typename vector<T>::size_type _sz) {
		if (_sz > vec_sz) {
			if (_sz > rsrv_sz) {
				rsrv_sz = _sz;
				reallocate();
			}
			vec_sz = _sz;
		} else {
			size_type i;
			for (i = vec_sz; i < _sz; ++i)
				arr[i].~T();
			vec_sz = _sz;
		}
	}

	template <typename T>
	void vector<T>::clear() {
		size_type i;
		for (i = 0; i < vec_sz; ++i)
			arr[i].~T();
		vec_sz = 0;
	}

	template <typename T>
	void vector<T>::swap(lni::vector<T> &rhs) {
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
	bool vector<T>::operator == (const lni::vector<T> &rhs) const {
		if (vec_sz != rhs.vec_sz) return false;
		size_type i;
		for (i = 0; i < vec_sz; ++i)
			if (arr[i] != rhs.arr[i])
				return false;
		return true;
	}

	template <typename T>
	bool vector<T>::operator != (const lni::vector<T> &rhs) const {
		if (vec_sz != rhs.vec_sz) return true;
		size_type i;
		for (i = 0; i < vec_sz; ++i)
			if (arr[i] != rhs.arr[i])
				return true;
		return false;
	}

	template <typename T>
	bool vector<T>::operator < (const lni::vector<T> &rhs) const {
		size_type i, j, ub = vec_sz < rhs.vec_sz ? vec_sz : rhs.vec_sz;
		for (i = 0; i < ub; ++i)
			if (arr[i] != rhs.arr[i])
				return arr[i] < rhs.arr[i];
		return vec_sz < rhs.vec_sz;
	}

	template <typename T>
	bool vector<T>::operator <= (const lni::vector<T> &rhs) const {
		size_type i, j, ub = vec_sz < rhs.vec_sz ? vec_sz : rhs.vec_sz;
		for (i = 0; i < ub; ++i)
			if (arr[i] != rhs.arr[i])
				return arr[i] < rhs.arr[i];
		return vec_sz <= rhs.vec_sz;
	}

	template <typename T>
	bool vector<T>::operator > (const lni::vector<T> &rhs) const {
		size_type i, j, ub = vec_sz < rhs.vec_sz ? vec_sz : rhs.vec_sz;
		for (i = 0; i < ub; ++i)
			if (arr[i] != rhs.arr[i])
				return arr[i] > rhs.arr[i];
		return vec_sz > rhs.vec_sz;
	}

	template <typename T>
	bool vector<T>::operator >= (const lni::vector<T> &rhs) const {
		size_type i, j, ub = vec_sz < rhs.vec_sz ? vec_sz : rhs.vec_sz;
		for (i = 0; i < ub; ++i)
			if (arr[i] != rhs.arr[i])
				return arr[i] > rhs.arr[i];
		return vec_sz >= rhs.vec_sz;
	}
}

