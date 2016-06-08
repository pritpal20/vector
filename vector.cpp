
namespace lni {

	template <typename T>
	vector<T>::vector() {
		arr = new T[rsrv_sz];
	}

	template <typename T>
	vector<T>::~vector() {
		delete [] arr;
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
	void vector<T>::push_back(const T &val) {
		if (vec_sz == rsrv_sz) {
			rsrv_sz <<= 2;
			reallocate();
		}
		arr[vec_sz] = val;
		++vec_sz;
	}

	template <typename T>
	void vector<T>::emplace_back(T &&val) {
		if (vec_sz == rsrv_sz) {
			rsrv_sz <<= 2;
			reallocate();
		}
		arr[vec_sz] = val;
		++vec_sz;
	}

	template <typename T>
	void vector<T>::reserve(const int &_sz) {
		if (_sz > rsrv_sz) {
			rsrv_sz = _sz;
			reallocate();
		}
	}

}

