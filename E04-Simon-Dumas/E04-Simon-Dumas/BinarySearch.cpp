#include <iostream>
using namespace std;

//recursively search an array by splitting it down the middle and comparing that value to the value being searched for
int binarySearch(int arr[], int left, int right, int x) 
{
	//calculate the middle value of the array
	int middle = left + (right - left) / 2;

	//if there are more indices that can be checked, check them
	if (right >= left)
	{
		//if the middle value is greater than x, search the indices below this index
		if (arr[middle] > x)
		{
			return binarySearch(arr, left, middle-1, x);
		}
		//if the middle value is less than x, search the indices above this index
		else if (arr[middle] < x)
		{
			return binarySearch(arr, middle+1, right, x);
		}
		//if the middle value is equal to x, return this index
		else if (arr[middle] == x)
		{
			return middle;
		}
	}

	//if x not found in array, return -1
	return -1;
	
}

//moved to helper function for testing
//arr is the array to be searched, x is the value being searched for, n is the number of elements in the array
void SearchForElement(int arr[], int x, int n)
{
	int result = binarySearch(arr, 0, n - 1, x);

	if (result == -1) {
		cout << "Element not found in the array" << endl;
	}
	else {
		cout << "Element found at index: " << result << endl;
	}
}

int main() {
	// Example sorted array
	int arr[] = { 2, 3, 4, 10, 40 };
	int n = sizeof(arr) / sizeof(arr[0]);
	int x = 10;
	int result = binarySearch(arr, 0, n - 1, x);//search for some element in the middle of the array

	if (result == -1) {
		cout << "Element not found in the array" << endl;
	}
	else {
		cout << "Element found at index: " << result << endl;
	}


	SearchForElement(arr, 15, n); //not in array
	SearchForElement(arr, 2, n); //first element
	SearchForElement(arr, 40, n); //last element

	return 0;
}
