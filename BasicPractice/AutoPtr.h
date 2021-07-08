#pragma once

template <typename T>
class AutoPtr
{
private:
	T* m_ptr = nullptr;
public:
	AutoPtr(T* input_ptr=nullptr)
		:m_ptr(input_ptr)
	{
		std::cout << "AutoPtr default constructor" << std::endl;
	}
	//// deep copy constuctor and assignment
	//AutoPtr(const AutoPtr& input)
	//{
	//	//deep copy more slower
	//	std::cout << "AutoPtr copy constructor" << std::endl;
	//	m_ptr = new T;
	//	//call copy constructor if input is class 
	//	*m_ptr = *input.m_ptr;
	//}

	//AutoPtr& operator = (const AutoPtr& input)
	//{
	//	std::cout << "AutoPtr copy assignment" << std::endl;
	//	if (&input == this)
	//	{
	//		return *this;
	//	}
	//	if(m_ptr != nullptr) delete m_ptr;
	//	//deep copy
	//	m_ptr = new T;
	//	//call copy constructor if input was class 
	//	*m_ptr = *input.m_ptr;
	//	return *this;
	//}

	//move constuctor and assignment
	AutoPtr(AutoPtr&& input)
	{
		//deep copy more slower
		std::cout << "AutoPtr move constructor" << std::endl;
		//shallow copy
		m_ptr = input.m_ptr;
		input.m_ptr = nullptr;
	}

	AutoPtr& operator = (AutoPtr&& input)
	{
		std::cout << "AutoPtr move assignment" << std::endl;
		if (&input == this)
		{
			return *this;
		}
		if (m_ptr != nullptr) delete m_ptr;
		//shallow copy
		m_ptr = input.m_ptr;
		input.m_ptr = nullptr;
	}


	T& operator*() const
	{
		return *m_ptr;
	}
	T* operator-> () const
	{
		return m_ptr;
	}

	~AutoPtr()
	{
		std::cout << "AutoPtr default destructor" << std::endl;
		if (m_ptr != nullptr)
			delete m_ptr;
	}
};