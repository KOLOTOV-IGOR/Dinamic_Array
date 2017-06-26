#pragma once
#ifndef DIN_ARR_H_
#define DIN_ARR_H_
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::ostream;

template<class T> 
class din_arr {
protected:
	int len;
	T *v;
public:
	//Конструкторы/////////////////////////////////////////////////////////////////////////////
	din_arr() : v(0), len(0) {}

	din_arr(int n) : v(0), len(0) {
		if (n > 0) {
			v = new T[n];
			for (int i = 0; i < n; i++) { *(v + i) = 0; }
		}
		if (v) len = n;
	}

	din_arr(int n, T w){
		if (n > 0) {
			v = new T[n];
			for (int i = 0; i < n; i++) { *(v + i) = w; }
		}
		if (v) len = n;
	}
	////////////////////////////////////////////////////////////////////////////////////////////
	//Конструктор копирования.
	din_arr(const din_arr<T> &temp) : v(0), len(0) {
		if (temp.len > 0) v = new T[temp.len];
		if (v) {
			len = temp.len;
			for (int i = 0; i < len; i++) { v[i] = temp.v[i]; }
		}
	}
	din_arr<T> &operator=(const din_arr<T> &temp);
	~din_arr() { delete [] v; }
	int size() const { return len; }
	din_arr<T> assign(int l, T value);
	void show();
	T operator[](int index) const { return v[index]; }//Для использования в правой части присваивания. const для перегрузки функции.
	T & operator[](int index) { return v[index]; }//Для использования в левой части присваивания.
	din_arr<T> insert(T);
	din_arr<T> erase(int);
	template<class T> friend din_arr<T> merge(const din_arr<T> &, const din_arr<T> &);
	din_arr<T> reverse();
	template<class T> friend ostream &operator<<(ostream &, din_arr<T>);
	din_arr<T> operator+(din_arr<T> &);
	din_arr<T> operator-(din_arr<T> &);
	din_arr<T> operator*(double number) const;
	template<class T> 
	friend din_arr<T> operator*(double , const din_arr<T>& );
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Шаблонные функции необходимо помещать в Header-файл.
template<class T>
din_arr<T> din_arr<T>::assign(int l, T value) {
	din_arr<T> temp(l, value);
	*this = temp;
	return *this;
}

template<class T>
din_arr<T> &din_arr<T>::operator=(const din_arr<T> &temp) {
	if (temp.len > 0) v = new T[temp.len];
	if (v) {
		len = temp.len;
		for (int i = 0; i < len; i++) { v[i] = temp.v[i]; }
	}
	return *this;
}

template<class T>
din_arr<T> din_arr<T>::insert(T value) {
	din_arr<T> temp;
	temp.v = new T[len + 1];
	if (temp.v) {
		temp.len = len + 1;
		for (int i = 0; i < len; i++) {
			temp.v[i] = v[i];
		}
		temp.v[len] = value;
	}
	*this = temp;
	return *this;
}

template<class T>
din_arr<T> din_arr<T>::erase(int j) {//j is an array's index.
	din_arr<T> temp;
	temp.v = new T[len - 1];
	if (temp.v) {
		temp.len = len - 1;
		if (j != len - 1) {
			for (int i = 0; i < j; i++) {
				temp.v[i] = v[i];
			}
			for (int i = j + 1; i < len; i++) {
				temp.v[i - 1] = v[i];
			}
		}
		else {
			for (int i = 0; i < j; i++) {
				temp.v[i] = v[i];
			}
		}
	}
	*this = temp;
	return *this;
}

template<class T>
din_arr<T> merge(const din_arr<T> &first, const din_arr<T> &second) {
	din_arr<T> temp;
	temp.len = first.len + second.len;
	temp.v = new T[temp.len];
	if (temp.v) {
		for (int i = 0; i < first.len; i++) {
			temp.v[i] = first.v[i];
		}
		for (int i = first.len; i < temp.len; i++) {
			temp.v[i] = second.v[i - first.len];
		}
	}
	return temp;
}

template<class T>
din_arr<T> din_arr<T>::reverse() {
	din_arr<T> temp;
	temp.len = len;
	temp.v = new T[temp.len];
	if (temp.v) {
		for (int i = temp.len; i > 0; i--) {
			temp.v[temp.len - i] = v[i - 1];
		}
	}
	*this = temp;
	return *this;
}

template<class T>
ostream &operator<<(ostream &stream, din_arr<T> o) {
	cout << "(";
	for (int i = 0; i < o.len - 1; i++) {
		cout << o.v[i] << ", ";
	}
	cout << o.v[o.len - 1] << ")";
	return stream;
}

template<class T>
void din_arr<T>::show() {
	for (int i = 0; i < len; i++) {
		cout << *(v + i) << " ";
		//cout << v[i] << " ";
		//cout << *(this->v+i) << " ";
		//cout << this->v[i] << " ";
	}
	cout << endl;
}

template<class T>
din_arr<T> din_arr<T>::operator+(din_arr<T> &a) {
	din_arr<T> sum(a.len);
	if (len == a.len) {
		for (int i = 0; i < len; i++) {
			sum.v[i] = v[i] + a.v[i];
		}
	}
	else {
		std::cerr << "Error in arrays' dimensions." << endl;
		exit(1);
	}
	return sum;
}

template<class T>
din_arr<T> din_arr<T>::operator-(din_arr<T> &a) {
	din_arr<T> temp(a.len);
	if (len == a.len) {
		for (int i = 0; i < len; i++) {
			temp.v[i] = v[i] - a.v[i];
		}
	}
	else {
		std::cerr << "Error in arrays' dimensions." << endl;
		exit(1);
	}
	return temp;
}
 
template<class T>
din_arr<T> din_arr<T>::operator*(double number) const {
	din_arr<T> temp(len);
	for (int i = 0; i < len; i++) {
		temp.v[i] = number * v[i];
	}
	return temp;
}

template<class T>
din_arr<T> operator*(double number, const din_arr<T> &a) {//Для дружественной функции НЕ ПИСАТЬ din_arr<T>::operator*//
	din_arr<T> temp(a.len);
	for (int i = 0; i < a.len; i++) {
		temp.v[i] = number * a.v[i];
	}
	return temp;
}
#endif 