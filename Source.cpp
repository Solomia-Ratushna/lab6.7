#include <Windows.h>
#include <iostream>
#include <vector>
#include <deque>

using namespace std;

// інтерфейс, що описує функтори - унарні предикати
template<class T>
class Predicate
{
public:
	virtual bool operator () (T x) = 0;
};


// реалізуємо інтерфейс функтором - перевірка, чи число просте
// працює лише для числових типів
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

// реалізуємо інтерфейс функтором - перевірка, чи значення додатне
// працює лише для числових типів
template<class T>
class Positive : public Predicate<T>
{
public:
	virtual bool operator () (T x)override
	{
		return x > 0;
	}
};

// реалізуємо інтерфейс функтором - перевірка, чи значення від'ємне
// працює лише для числових типів
template<class T>
class Negative : public Predicate<T>
{
public:
	virtual bool operator () (T x)override
	{
		return x < 0;
	}
};

// реалізуємо інтерфейс функтором - перевірка, чи значення парне
// працює лише для цілих типів
template<class T>
class Even : public Predicate<T>
{
public:
	virtual bool operator () (T x)override
	{
		return x % 2 == 0;
	}
};

// реалізуємо інтерфейс функтором - перевірка, чи значення не парне
// працює лише для цілих типів
template<class T>
class Odd : public Predicate<T>
{
public:
	virtual bool operator () (T x)override
	{
		return x % 2 != 0;
	}
};

// сумуємо всі елементи (окрім останнього)
// begin - ітератор початку вхідного контейнера (вказує на перший елемент)
// end - ітератор кінця вхідного контейнера (вказує на елемент після останнього)
// init - початкове значення суми
template<class inputIt, class T>
T sum(inputIt begin, inputIt end, T init)
{
	for (; begin != end; ++begin)
	{
		init += *begin;
	}
	return init;
}

// сумуємо елементи, для яких предикат p набуває значення true
// begin - ітератор початку вхідного контейнера (вказує на перший елемент)
// end - ітератор кінця вхідного контейнера (вказує на елемент після останнього)
// init - початкове значення суми
template<class inputIt, class T>
int sum_if(inputIt begin, inputIt end, T init, Predicate<T>& p)
{
	for (; begin != end; ++begin) // ітеруємо begin
	{
		if (p(*begin)) // якщо справджується умова предикату
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

	cout << "Сума колекції а: " << sum(a.begin(), a.end(), 0) << endl;
	cout << "Сума колекції b: " << sum(b.begin(), b.end(), 0) << endl;
	cout << "Сума колекції c: " << sum(std::begin(c), std::end(c), 0) << endl;
	cout << endl;

	Predicate<int>* predicate = new Prime<int>();
	cout << "Сумуємо виключно прості елементи: " << endl;
	cout << "Сума колекції а: " << sum_if(a.begin(), a.end(), 0, *predicate) << endl;
	cout << "Сума колекції b: " << sum_if(b.begin(), b.end(), 0, *predicate) << endl;
	cout << "Сума колекції c: " << sum_if(std::begin(c), std::end(c), 0, *predicate) << endl;
	cout << endl;


	predicate = new Positive<int>();
	cout << "Сумуємо виключно додатні елементи: " << endl;
	cout << "Сума колекції а: " << sum_if(a.begin(), a.end(), 0, *predicate) << endl;
	cout << "Сума колекції b: " << sum_if(b.begin(), b.end(), 0, *predicate) << endl;
	cout << "Сума колекції c: " << sum_if(std::begin(c), std::end(c), 0, *predicate) << endl;
	cout << endl;

	predicate = new Negative<int>();
	cout << "Сумуємо виключно відємні елементи: " << endl;
	cout << "Сума колекції а: " << sum_if(a.begin(), a.end(), 0, *predicate) << endl;
	cout << "Сума колекції b: " << sum_if(b.begin(), b.end(), 0, *predicate) << endl;
	cout << "Сума колекції c: " << sum_if(std::begin(c), std::end(c), 0, *predicate) << endl;
	cout << endl;

	predicate = new Even<int>();
	cout << "Сумуємо виключно парні елементи: " << endl;
	cout << "Сума колекції а: " << sum_if(a.begin(), a.end(), 0, *predicate) << endl;
	cout << "Сума колекції b: " << sum_if(b.begin(), b.end(), 0, *predicate) << endl;
	cout << "Сума колекції c: " << sum_if(std::begin(c), std::end(c), 0, *predicate) << endl;
	cout << endl;

	predicate = new Odd<int>();
	cout << "Сумуємо виключно не парні елементи: " << endl;
	cout << "Сума колекції а: " << sum_if(a.begin(), a.end(), 0, *predicate) << endl;
	cout << "Сума колекції b: " << sum_if(b.begin(), b.end(), 0, *predicate) << endl;
	cout << "Сума колекції c: " << sum_if(std::begin(c), std::end(c), 0, *predicate) << endl;
	cout << endl;
	system("pause");
	return 0;
}
