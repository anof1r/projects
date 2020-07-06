#include <iostream>

const int Nmax = 1000;
int main()
{
	double Numbers[Nmax];
	int n;

	std::cout << "Input array size" << std::endl;
	std::cin >> n;
	std::cout << "Input elements" << std::endl;

	for ( int i = 0; i < n; i++)
	{
		std::cin >> Numbers[i];
	}
	double sum_stack = Numbers[0];
	double sum_max = sum_stack;
	for ( int i = 1; i < n; i++)
	{
		if (Numbers[i] >= Numbers[i - 1]) {
			sum_stack += Numbers[i];
		}
		else {
			if (sum_stack > sum_max)
			{
				sum_max = sum_stack;				
			}
			sum_stack = Numbers[i];
		}
	}

	std::cout << "Summa posledov = " << sum_max << std::endl;

}




