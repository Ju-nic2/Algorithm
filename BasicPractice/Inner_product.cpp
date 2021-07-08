#include <iostream>
#include <chrono>
#include <mutex>
#include <vector>
#include <random>
#include <numeric>// std::inner_product
#include <thread>
#include <execution>
#include <utility>
#include <future>


using namespace std;
mutex mtx;

void dotProductNaive(const vector<int>& v0, const vector<int>& v1,
	const unsigned i_start, const unsigned i_end, unsigned long long& sum)
{
	for (int i = i_start; i < i_end; i++)
		sum = sum + (v0[i] * v1[i]);
}
void dotProductLock(const vector<int>& v0, const vector<int>& v1,
	const unsigned i_start, const unsigned i_end, unsigned long long& sum)
{
	mtx.lock();
	for (int i = i_start; i < i_end; i++)
	{
		sum = sum + (v0[i] * v1[i]);
	}
	mtx.unlock();
}
void dotProductAtomic(const vector<int>& v0, const vector<int>& v1,
	const unsigned i_start, const unsigned i_end, atomic< unsigned long long>& sum)
{
	for (int i = i_start; i < i_end; i++)
		sum = sum + (v0[i] * v1[i]);
}


void dotProductAtomic2(const vector<int>& v0, const vector<int>& v1,
	const unsigned i_start, const unsigned i_end, atomic<int>& sum)
{
	for (int i = i_start; i < i_end; i++)
		sum = sum + (v0[i] * v1[i]);
}


auto dotProductFuture(const vector<int>& v0, const vector<int>& v1,
	const unsigned i_start, const unsigned i_end)
{
	int sum = 0;
	for (int i = i_start; i < i_end; i++)
		sum = sum + (v0[i] * v1[i]);
	return sum;
}

void dotProductPromise(const vector<int>& v0, const vector<int>& v1,
	const unsigned i_start, const unsigned i_end, promise<int>& prom)
{
	int sum = 0;
	for (int i = i_start; i < i_end; i++)
		sum = sum + (v0[i] * v1[i]);
	prom.set_value(sum);
}
int main()
{
	/*
		  v0 = {1,2,3}
		  v1 = {4,5,6}
		  v0 dot v1 = 1*4 + 2*5 + 3*6
	*/
	const long long n_data = 100000000;
	const unsigned n_threads = 4;

	//initialize vectors
	std::vector<int> v0, v1;
	v0.reserve(n_data);
	v1.reserve(n_data);

	random_device seed;
	mt19937 engine(seed());

	uniform_int_distribution<> uniformDist(1, 10);
	cout << "data insert" << endl;

	const auto sta = chrono::steady_clock::now();

	for (long long i = 0; i < n_data; ++i)
	{
		v0.push_back(uniformDist(engine));
		v1.push_back(uniformDist(engine));
	}

	const chrono::duration<double> dur = chrono::steady_clock::now() - sta;

	cout << dur.count() << endl;
	cout << endl;

	cout << "std::inner_product" << endl;
	{
		const auto sta = chrono::steady_clock::now();

		const auto sum = std::inner_product(v0.begin(), v0.end(), v1.begin(), 0ull);

		const chrono::duration<double> dur = chrono::steady_clock::now() - sta;

		cout << dur.count() << endl;
		cout << sum << endl;
		cout << endl;
	}
	cout << "Naive" << endl;
	{
		const auto sta = chrono::steady_clock::now();

		unsigned long long sum = 0;

		vector<thread> threads;
		threads.resize(n_threads);

		const unsigned n_per_thread = n_data / n_threads;
		for (unsigned t = 0; t < n_threads; ++t)
			threads[t] = thread(dotProductNaive, std::ref(v0), std::ref(v1),
				t * n_per_thread, (t + 1) * n_per_thread, std::ref(sum));
		for (unsigned t = 0; t < n_threads; ++t)
			threads[t].join();

		//time check
		const chrono::duration<double> dur = chrono::steady_clock::now() - sta;

		cout << dur.count() << endl;
		cout << sum << endl;
		cout << endl;
	}
	cout << "Naive Lock" << endl;
	{
		const auto sta = chrono::steady_clock::now();

		unsigned long long sum = 0;

		vector<thread> threads;
		threads.resize(n_threads);

		const unsigned n_per_thread = n_data / n_threads;
		for (unsigned t = 0; t < n_threads; ++t)
			threads[t] = thread(dotProductLock, std::ref(v0), std::ref(v1),
				t * n_per_thread, (t + 1) * n_per_thread, std::ref(sum));
		for (unsigned t = 0; t < n_threads; ++t)
			threads[t].join();

		//time check
		const chrono::duration<double> dur = chrono::steady_clock::now() - sta;

		cout << dur.count() << endl;
		cout << sum << endl;
		cout << endl;
	}
	cout << "Atomic" << endl;
	{
		const auto sta = chrono::steady_clock::now();

		atomic<unsigned long long> sum = 0;

		vector<thread> threads;
		threads.resize(n_threads);

		const unsigned n_per_thread = n_data / n_threads;
		for (unsigned t = 0; t < n_threads; ++t)
			threads[t] = thread(dotProductAtomic, std::ref(v0), std::ref(v1),
				t * n_per_thread, (t + 1) * n_per_thread, std::ref(sum));
		for (unsigned t = 0; t < n_threads; ++t)
			threads[t].join();

		//time check
		const chrono::duration<double> dur = chrono::steady_clock::now() - sta;

		cout << dur.count() << endl;
		cout << sum << endl;
		cout << endl;
	}
	cout << "Atomic palle" << endl;
	{
		const auto sta = chrono::steady_clock::now();

		unsigned long long sum = 0;
		vector<atomic<int>> atomics(n_threads);

		vector<thread> threads;
		threads.resize(n_threads);

		const unsigned n_per_thread = n_data / n_threads;
		for (unsigned t = 0; t < n_threads; ++t)
			threads[t] = thread(dotProductAtomic2, std::ref(v0), std::ref(v1),
				t * n_per_thread, (t + 1) * n_per_thread, std::ref(atomics[t]));
		for (unsigned t = 0; t < n_threads; ++t)
			threads[t].join();
		for (unsigned t = 0; t < n_threads; ++t)
			sum += atomics[t];
		//time check
		const chrono::duration<double> dur = chrono::steady_clock::now() - sta;

		cout << dur.count() << endl;
		cout << sum << endl;
		cout << endl;
	}
	cout << "Future" << endl;
	{
		const auto sta = chrono::steady_clock::now();

		unsigned long long sum = 0;

		vector<future<int>> futures;
		futures.resize(n_threads);

		const unsigned n_per_thread = n_data / n_threads;
		for (unsigned t = 0; t < n_threads; ++t)
			futures[t] = async(dotProductFuture, std::ref(v0), std::ref(v1),
				t * n_per_thread, (t + 1) * n_per_thread);
		for (unsigned t = 0; t < n_threads; ++t)
			sum += futures[t].get();

		//time check
		const chrono::duration<double> dur = chrono::steady_clock::now() - sta;

		cout << dur.count() << endl;
		cout << sum << endl;
		cout << endl;
	}
	cout << "use future and promise" << endl;
	{
		const auto sta = chrono::steady_clock::now();
		const unsigned n_per_thread = n_data / n_threads;
		unsigned long long sum = 0;

		vector<promise<int>> promises(n_threads);
		vector<future<int>> futures(n_threads);
		vector<thread> threads(n_threads);

		for (int i = 0; i < n_threads; i++)
			futures[i] = promises[i].get_future();

		for (int t = 0; t < n_threads; t++)
			threads[t] = thread(dotProductPromise, std::ref(v0), std::ref(v1),
				t * n_per_thread, (t + 1) * n_per_thread, std::ref(promises[t]));

		for (int i = 0; i < n_threads; i++)
			sum += futures[i].get();

		for (int i = 0; i < n_threads; i++)
			threads[i].join();

		const chrono::duration<double> dur = chrono::steady_clock::now() - sta;
		cout << dur.count() << endl;
		cout << sum << endl;
		cout << endl;
	}
}
