#ifndef _PTR_H_
#define _PTR_H_

template<class T>
class Shared_ptr
{
private:
	T* _ptr;
	size_t* _counter;
public:
	Shared_ptr();
	explicit Shared_ptr(T* ptr);
	Shared_ptr(Shared_ptr& ptr);
	//Shared_ptr& operator=(const Shared_ptr& ptr);
	size_t use_count() const { if(_counter) return *_counter; else return 0;}
	~Shared_ptr();
};

template<class T>
Shared_ptr<T>::Shared_ptr()
{
	_ptr = nullptr;
	_counter = 0;
}

template<class T>
Shared_ptr<T>::Shared_ptr(T* ptr)
{
	_ptr = ptr;
	_counter = new size_t(1);
}

template<class T>
Shared_ptr<T>::Shared_ptr(Shared_ptr& ptr)
{
	(*(ptr._counter))++;
	_ptr = ptr._ptr;
	_counter = ptr._counter;
}

template<class T>
Shared_ptr<T>::~Shared_ptr()
{
	if(!_counter)
		return;
	if (*_counter > 1)
		(*_counter)--;
	else if (*_counter == 1) {
		delete _ptr;
		delete _counter;
	}
}

#endif