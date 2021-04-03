/*
** Name: Conner Foster
** Date: Jan 8, 2021
** ASGN: Merge Sort 3 file(CS325 section 2)
** DESC: This program performs a more complex merge sort algorithm for an array of integers. What makes it more complex is the fact that it 
**		 devides and conqueres in thirds. The program reads inputs from a file named “data.txt” which is formatted such that the first value 
**		 of each line is the number of integers that need to be sorted, followed by the integers to be sorted.
**       The program outputs the sorted values without the preliminary first integer that indicated the number of integers.
**		 I utalized lecture notes, lecture recordings, previous code, and geeksforgeeks.com to complete this assignment
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>


/* Function to print an array */
void output(int inputArr[], int size) 
{
	for (int i = 0; i < size; i++)		//loop for the length of the array
		printf("%i, ", inputArr[i]);	//print the array cell by cell
}


void merge(int inputArr[], int low, int mid1, int mid2, int high)
{
	int tempArr[high];		//create a temporary array for the values to be stored into in order, then transfered back into the original array at the end
	for (int j = 0; j < high; j++)		//copy the array into the temporary array for comparison
		tempArr[j] = inputArr[j];

	int arrOnePos = low, arrTwoPos = mid1, arrThreePos = mid2, tempPos = low, tempInt = 0;		//arrOnePos, arrTwoPos, and arrThreePos all keep track of the position of the sub arrays when itterating through them

	for (int i = ((arrOnePos - low) + (arrTwoPos - mid1) + (arrThreePos - mid2)); i < high; i++)		//loop untill all #s in each sub array have been checked
	{
		if ((arrOnePos < mid1) && (arrTwoPos < mid2) && (arrThreePos < high))		//if there are #s to check in all three sub arrays...
		{
			if (inputArr[arrOnePos] <= inputArr[arrTwoPos] && inputArr[arrOnePos] <= inputArr[arrThreePos])		//if the current # in the first sub array is is the smallest... store it in the temp array
				tempArr[tempPos++] = inputArr[arrOnePos++];
			else if (inputArr[arrTwoPos] <= inputArr[arrOnePos] && inputArr[arrTwoPos] <= inputArr[arrThreePos])		//if the current # in the second sub array is is the smallest... store it in the temp array
				tempArr[tempPos++] = inputArr[arrTwoPos++];
			else if (inputArr[arrThreePos] <= inputArr[arrOnePos] && inputArr[arrThreePos] <= inputArr[arrTwoPos])		//if the current # in the Third sub array is is the smallest... store it in the temp array
				tempArr[tempPos++] = inputArr[arrThreePos++];
		}
		else if ((arrOnePos < mid1) && (arrTwoPos < mid2))		//if there are still #s to check only in the first two sub arays
		{
			if (inputArr[arrOnePos] <= inputArr[arrTwoPos])		//if the current # in the the first sub array is smaller than the current # in the second small array
				tempArr[tempPos++] = inputArr[arrOnePos++];		//the current # in the first sub array is the smallest so add it to the sorted tempArr and increment its position
			else if (inputArr[arrTwoPos] <= inputArr[arrThreePos])
				tempArr[tempPos++] = inputArr[arrTwoPos++];		//the current # in the second sub array is the smallest so add it to the sorted tempArr and increment its position
		}
		else if ((arrTwoPos < mid2) && (arrThreePos < high))		//if there are still #s to check only in the last two sub arays
		{
			if (inputArr[arrTwoPos] <= inputArr[arrThreePos])		//if the current # in the second sub array is smaller than the current # in the third sub array
				tempArr[tempPos++] = inputArr[arrTwoPos++];			//the current # in the second sub array is the smallest so add it to the sorted tempArr and increment its position
			else if (inputArr[arrThreePos] <= inputArr[arrTwoPos])
				tempArr[tempPos++] = inputArr[arrThreePos++];		//the current # in the third sub array is the smallest so add it to the sorted tempArr and increment its position
		}
		else if ((arrOnePos < mid1) && (arrThreePos < high))		//if there are still #s to check only in the first and last sub array
		{
			if (inputArr[arrOnePos] <= inputArr[arrThreePos])		//if the current # in the first sub array is smaller than the current # in the third sub array
				tempArr[tempPos++] = inputArr[arrOnePos++];			//the current # in the first sub array is the smallest so add it to the sorted tempArr and increment its position
			else if (inputArr[arrThreePos] <= inputArr[arrOnePos])
				tempArr[tempPos++] = inputArr[arrThreePos++];		//the current # in the third sub array is the smallest so add it to the sorted tempArr and increment its position
		}
		else if (arrOnePos < mid1)		//if there are still #s in the first sub array
			tempArr[tempPos++] = inputArr[arrOnePos++];		//add them to the sorted array
		else if (arrTwoPos < mid2)		//if there are still #s in the second sub array
			tempArr[tempPos++] = inputArr[arrTwoPos++];		//add them to the sorted array
		else if (arrThreePos < high)	//if there are still #s in the third sub array
			tempArr[tempPos++] = inputArr[arrThreePos++];		//add them to the sorted array
	}

	for (int j = 0; j < high; j++)		//copy the sorted array back over to the original array before finishing. 
		inputArr[j] = tempArr[j];
	//output(inputArr, high);
}


void mergeSort3WayRec(int inputArr[], int low, int high)
{
	int size = high - low;		//determines the size of the current sub array specifications being passed through
	if (size <= 1)			// If array size is 1 or 0 after recurssion then do nothing 
		return;

	int mid1 = low + (size / 3);	//determine the position of the two splits in the array that break it up into 3 parts
	int mid2 = low + 2 * (size / 3) + 1;

	mergeSort3WayRec(inputArr, low, mid1);  	//recursively split the first sub array
	mergeSort3WayRec(inputArr, mid1, mid2);		//recursively split the second sub array
	mergeSort3WayRec(inputArr, mid2, high);		//recursively split the thrid sub array

	merge(inputArr, low, mid1, mid2, high);			//sort and merge the sub arrays 
}


/*function to open file and fill an integer array*/
void processFile()
{
	int i = 0, size = 0, number = 0;	//var i keeps track of the position of the int array, size stores the first number of each line to determine the length of the array, and number is the number that is retrieved from the file
	FILE* file = fopen("data.txt", "r");	//open data file

	fscanf(file, "%d", &number);	//read first number of the first line to get required array size
	size = number;
	int inputArr[size];		//create an array and set it to the required size

	while (true)	//loops infinitely (programmer controlls when the loop stops)
	{
		fscanf(file, "%i", &number);	//get the next number in the file

		if (i <= size)	 //if there are still numbers in the line
		{
			if (i == size)	 //if the the end of the current line is reached
			{
				mergeSort3WayRec(inputArr, 0, size);
				output(inputArr, size);
				size = number;		//set the new size (first number of next line
				int inputArr[size];		//Re-create the array and set it to the required size for the new line
				printf("\n");
				i = 0;		//reset the conditions for the if statement for the new line

				if (feof(file))		//if the end of the text file is reached...
					break;		//end loop
			}
			else
			{
				inputArr[i] = number;		//fill the number array with the fetched integer
				i++;		//itterate through array
			}
		}
	}
	fclose(file);		//end file stream
}


int main()
{
	processFile();
}