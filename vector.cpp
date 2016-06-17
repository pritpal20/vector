
namespace lni {

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
			vec_sz = sz;
		} else {
			size_type i;
			for (i = vec_sz; i < sz; ++i)
				arr[i].~T();
			vec_sz = sz;
		}
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
			vec_sz = sz;
		} else {
			size_type i;
			for (i = vec_sz; i < sz; ++i)
				arr[i].~T();
			vec_sz = sz;
		}
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
	void vector<T>::clear() {
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
}

