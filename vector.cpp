
namespace lni {

	template <typename T>
	vector<T>::vector() {
		arr = new T[rsrv_sz];
	}

	template <typename T>
	vector<T>::vector(int count) {
		int i;
		rsrv_sz = count << 2;
		arr = new T[rsrv_sz];
		for (i = 0; i < count; ++i)
			arr[i] = T();
		vec_sz = count;
	}

	template <typename T>
	vector<T>::vector(int count, const T &val) {
		int i;
		rsrv_sz = count << 2;
		arr = new T[rsrv_sz];
		for (i = 0; i < count; ++i)
			arr[i] = val;
		vec_sz = count;
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
	inline T & vector<T>::operator [](const int &idx) {
		return arr[idx];
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::begin() {
		return arr;
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::end() {
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
		int i;
		T *tarr = new T[rsrv_sz];
		for (i = 0; i < vec_sz; ++i)
			tarr[i] = arr[i];
		delete [] arr;
		arr = tarr;
	}
	
	template <typename T>
	int vector<T>::size() {
		return vec_sz;
	}

	template <typename T>
	bool vector<T>::empty() {
		return vec_sz == 0;
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
	void vector<T>::reserve(const int &_sz) {
		if (_sz > rsrv_sz) {
			rsrv_sz = _sz;
			reallocate();
		}
	}

	template <typename T>
	void vector<T>::resize(const int &_sz) {
		if (_sz > vec_sz) {
			if (_sz > rsrv_sz) {
				rsrv_sz = _sz;
				reallocate();
			}
			vec_sz = _sz;
		} else {
			int i;
			for (i = vec_sz; i < _sz; ++i)
				arr[i].~T();
			vec_sz = _sz;
		}
	}

	template <typename T>
	void vector<T>::clear() {
		int i;
		for (i = 0; i < vec_sz; ++i)
			arr[i].~T();
		vec_sz = 0;
	}

	template <typename T>
	void vector<T>::swap(lni::vector<T> &rhs) {
		int i, sz = rhs.size();
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
}

