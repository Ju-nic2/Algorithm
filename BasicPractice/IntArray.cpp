#include <iostream>
#include <initializer_list>
#include <cassert>

using namespace std;

class IntArray
{
private:
	int m_length=0;
	int m_capacity=0;
	int* m_data = nullptr;
public:
	IntArray(const int& length_in)
		:m_length(length_in)
	{
		m_data = new int[length_in];
	}

	IntArray(const initializer_list<int>& list)
		:IntArray(list.size())
	{
		int count = 0;
		for (auto& num : list)
			m_data[count++] = num;
	}
	IntArray(const IntArray& input)
		:m_length(input.m_length)
	{
		initialization(input);
	}
	IntArray& reset()
	{
		delete[] m_data;
		m_length = 0;
		m_capacity = 0;
		m_data = nullptr;
		return (*this);
	}
	IntArray& resize(const int& resize)
	{
		
		if (resize == m_length)
			return (*this);

		else if (resize > m_length) 
		{
		
			int* temp = new int[resize];
			temp= new int[resize];

			for (int i = 0; i < m_length; i++)
				temp[i] = m_data[i];

			for (int i = m_length; i < resize; i++)
				temp[i] = 0;
			
			delete[] m_data;
			m_data = temp;
			m_capacity = resize;
		
		}
		else 
		{
			m_length = resize;
			m_capacity = resize;
			int* temp = new int[resize];
			for (int i = 0; i < m_length; i++)
				temp[i] = m_data[i];

			delete[] m_data;
			m_data = temp;
		}
		return(*this);
	}
	IntArray& insertBefore(const int& value,const int& index)
	{
		resize(m_length+1);
		m_length++;
		for (int i = m_length - 1; i > index; i--)
		{
			m_data[i] = m_data[i - 1];
		}	
		m_data[index] = value;
		return (*this);
	}
	IntArray& remove(const int& index)
	{		
		for (int i = index; i <m_length-1; i++)
		{
			m_data[i] = m_data[i + 1];
		}
		m_length--;
		return (*this);
	}
	IntArray& push_back(const int& value)
	{
		resize(m_length + 1);
		m_length++;
		m_data[m_length - 1] = value;
		return (*this);
	}

	int getSize()
	{
		return m_length;
	}
	int getCapacity()
	{
		return m_capacity;
	}

	void initialization(const int& size)
	{
		int* temp = new int[size];
		for (int i = 0; i < size; i++)
			temp[i] = m_data[i];

		delete[] m_data;
		m_data = temp;	
	}

	void initialization(const IntArray& input)
	{
		m_length = input.m_length;
		if (input.m_data != nullptr)
		{
			m_data = new int[m_length];
			for (int i = 0; i < input.m_length; i++)
				m_data[i] = input.m_data[i];
		}
		else
		{
			m_data = nullptr;
		}
	}
	

	friend ostream& operator << (ostream& out, const IntArray& input)
	{
		for (int i = 0; i < input.m_length; i++)
			out << input.m_data[i] << " ";
		return out;
	}

	IntArray& operator = (const IntArray& input) 
	{
		if (this == &input)
			return (*this);
		delete[] m_data;
		initialization(input);
		return (*this);
	}
	int& operator[] (const int& index) 
	{
		assert(index > 0);
		assert(index <= m_length);
		return m_data[index];
	}
	~IntArray()
	{
		delete[] m_data;
	}
};

int main()
{

	IntArray my_arr{ 1, 3, 5, 7, 9 };
	cout << my_arr << endl;

	my_arr.insertBefore(10, 1);//1 10 3 5 7 9
	cout << my_arr << endl;
	my_arr.remove(3);          //1 10 3 7 9
	cout << my_arr << endl;
	cout << my_arr.getSize() << endl;
	my_arr.resize(10);
	cout << my_arr.getSize() << endl;
	cout << my_arr.getCapacity() << endl;
	cout << my_arr[1] << endl;
	my_arr[1] = 2;
	cout << my_arr[1] << endl;

	my_arr.reset();
	my_arr.push_back(13);
	cout << my_arr << endl;
	cout << my_arr.getSize() << endl;
	cout << my_arr.getCapacity() << endl;
	my_arr.push_back(13);      //1 10 3 7 9 13
	cout << my_arr << endl;
}