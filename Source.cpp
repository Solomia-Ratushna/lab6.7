#include <Windows.h>
#include <iostream>
#include <vector>
#include <deque>

using namespace std;

// ���������, �� ����� �������� - ����� ���������
template<class T>
class Predicate
{
public:
	virtual bool operator () (T x) = 0;
};


// �������� ��������� ��������� - ��������, �� ����� ������
// ������ ���� ��� �������� ����
template<class T>
class Prime : public Predicate<T>
{
public:
	virtual bool operator () (T x)override
	{
		if (x > 1)
		{
			for (int i = 2; i < x; i++) {
				if (x % i == 0) {
					return false;
				}
			}
			return true;
		}
		return false;
	}

};

// �������� ��������� ��������� - ��������, �� �������� �������
// ������ ���� ��� �������� ����
template<class T>
class Positive : public Predicate<T>
{
public:
	virtual bool operator () (T x)override
	{
		return x > 0;
	}
};

// �������� ��������� ��������� - ��������, �� �������� ��'����
// ������ ���� ��� �������� ����
template<class T>
class Negative : public Predicate<T>
{
public:
	virtual bool operator () (T x)override
	{
		return x < 0;
	}
};

// �������� ��������� ��������� - ��������, �� �������� �����
// ������ ���� ��� ����� ����
template<class T>
class Even : public Predicate<T>
{
public:
	virtual bool operator () (T x)override
	{
		return x % 2 == 0;
	}
};

// �������� ��������� ��������� - ��������, �� �������� �� �����
// ������ ���� ��� ����� ����
template<class T>
class Odd : public Predicate<T>
{
public:
	virtual bool operator () (T x)override
	{
		return x % 2 != 0;
	}
};

// ������ �� �������� (���� ����������)
// begin - �������� ������� �������� ���������� (����� �� ������ �������)
// end - �������� ���� �������� ���������� (����� �� ������� ���� ����������)
// init - ��������� �������� ����
template<class inputIt, class T>
T sum(inputIt begin, inputIt end, T init)
{
	for (; begin != end; ++begin)
	{
		init += *begin;
	}
	return init;
}

// ������ ��������, ��� ���� �������� p ������ �������� true
// begin - �������� ������� �������� ���������� (����� �� ������ �������)
// end - �������� ���� �������� ���������� (����� �� ������� ���� ����������)
// init - ��������� �������� ����
template<class inputIt, class T>
int sum_if(inputIt begin, inputIt end, T init, Predicate<T>& p)
{
	for (; begin != end; ++begin) // ������� begin
	{
		if (p(*begin)) // ���� ������������ ����� ���������
		{
			init += *begin;
		}
	}
	return init;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	vector<int> a = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	deque<int> b = { -1, -2, -3, -4, -5 };
	int  c[] = { -1, -2, -3, -4, -5, 0,  1, 2, 3, 4, 5 };

	cout << "���� �������� �: " << sum(a.begin(), a.end(), 0) << endl;
	cout << "���� �������� b: " << sum(b.begin(), b.end(), 0) << endl;
	cout << "���� �������� c: " << sum(std::begin(c), std::end(c), 0) << endl;
	cout << endl;

	Predicate<int>* predicate = new Prime<int>();
	cout << "������ �������� ����� ��������: " << endl;
	cout << "���� �������� �: " << sum_if(a.begin(), a.end(), 0, *predicate) << endl;
	cout << "���� �������� b: " << sum_if(b.begin(), b.end(), 0, *predicate) << endl;
	cout << "���� �������� c: " << sum_if(std::begin(c), std::end(c), 0, *predicate) << endl;
	cout << endl;


	predicate = new Positive<int>();
	cout << "������ �������� ������ ��������: " << endl;
	cout << "���� �������� �: " << sum_if(a.begin(), a.end(), 0, *predicate) << endl;
	cout << "���� �������� b: " << sum_if(b.begin(), b.end(), 0, *predicate) << endl;
	cout << "���� �������� c: " << sum_if(std::begin(c), std::end(c), 0, *predicate) << endl;
	cout << endl;

	predicate = new Negative<int>();
	cout << "������ �������� ���� ��������: " << endl;
	cout << "���� �������� �: " << sum_if(a.begin(), a.end(), 0, *predicate) << endl;
	cout << "���� �������� b: " << sum_if(b.begin(), b.end(), 0, *predicate) << endl;
	cout << "���� �������� c: " << sum_if(std::begin(c), std::end(c), 0, *predicate) << endl;
	cout << endl;

	predicate = new Even<int>();
	cout << "������ �������� ���� ��������: " << endl;
	cout << "���� �������� �: " << sum_if(a.begin(), a.end(), 0, *predicate) << endl;
	cout << "���� �������� b: " << sum_if(b.begin(), b.end(), 0, *predicate) << endl;
	cout << "���� �������� c: " << sum_if(std::begin(c), std::end(c), 0, *predicate) << endl;
	cout << endl;

	predicate = new Odd<int>();
	cout << "������ �������� �� ���� ��������: " << endl;
	cout << "���� �������� �: " << sum_if(a.begin(), a.end(), 0, *predicate) << endl;
	cout << "���� �������� b: " << sum_if(b.begin(), b.end(), 0, *predicate) << endl;
	cout << "���� �������� c: " << sum_if(std::begin(c), std::end(c), 0, *predicate) << endl;
	cout << endl;
	system("pause");
	return 0;
}
