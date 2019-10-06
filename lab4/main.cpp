#include <stdio.h>
#include "TaskQueue.h"
#include "TasksExecutor.h"
#include <thread>
#include <string>
#include <iostream>
#include <fstream>
#include <functional>

#define THREADS_COUNT 6
#define FILE_PATH "C:\\Users\\User\\Source\\Repos\\ThreadPool\\Debug\\text.txt"

#define TYPE std::function<void(void)>

std::vector<std::string>* vecOfStr = new std::vector<std::string>();
std::vector < std::vector<std::string>*>* vectorOfParts = new std::vector < std::vector<std::string>*>();


bool getFileContent(std::string fileName, std::vector<std::string> *vecOfStrs)
{

	std::ifstream dict_file(FILE_PATH);
	std::string line;

	if (!dict_file.good()) {
		return false;
	}

	while (std::getline(dict_file, line))
	{
		std::string new_line;
		new_line = line + "\n";
	
		if (new_line.size() != 0)
			vecOfStrs->push_back(new_line);
	}

	return true;
}


void addVector(std::vector<std::string>* vect, TaskQueue queue) {

	queue.addTask([vect]() {
		std::vector<std::string>* copy = vect;
		std::sort(vect->begin(), vect->end());
		});
}

#define Vector std::vector<std::string>
Vector mergeTwo(Vector A, Vector B)
{
	// Get sizes of vectors 
	int m = A.size();
	int n = B.size();

	// Vector for storing Result 
	Vector D;
	D.reserve(m + n);

	int i = 0, j = 0;
	while (i < m && j < n) {

		if (A[i] <= B[j])
			D.push_back(A[i++]);
		else
			D.push_back(B[j++]);
	}

	// B has exhausted 
	while (i < m)
		D.push_back(A[i++]);

	// A has exhausted 
	while (j < n)
		D.push_back(B[j++]);

	return D;
}

Vector mergeVectors() {
	Vector tmpVector;
	if (vectorOfParts->size() > 0) {
		tmpVector = *(*vectorOfParts)[0];
	}
	for (int i = 1; i < vectorOfParts->size(); i++) {
		tmpVector = mergeTwo(tmpVector, *(*vectorOfParts)[i]);
	}
	return tmpVector;
}

void outPutVector(Vector vector) {
	for (int i = 0; i < vector.size(); i++) {
		printf("   %s", vector[i].c_str());
	}
}

void splitAndSortVectors(TaskQueue taskQueue, int threadsCount) {
	int onePartCount = floor((((double)vecOfStr->size()) / threadsCount) + .5);



	for (int i = 0; i < vecOfStr->size(); i += onePartCount) {
		std::vector<std::string>* newVector = new std::vector<std::string>;
		vectorOfParts->push_back(newVector);
		for (int j = i; j < i + onePartCount; j++) {
			if (j < vecOfStr->size()) {
				std::string str = (*vecOfStr)[j];
				newVector->push_back(str);
			}
		}
		addVector(newVector, taskQueue);

	}
}

int main() {

	bool result = getFileContent(FILE_PATH, vecOfStr);

	if (!result) {
		printf("File isn't exist");
		return -1;
	}


	TaskQueue taskQueue;
	TasksExecutor taskExecutor(taskQueue);

	int threadsCount = THREADS_COUNT > vecOfStr->size() ? vecOfStr->size() : THREADS_COUNT;


	splitAndSortVectors(taskQueue, threadsCount);
	taskExecutor.startExecution(threadsCount);

	Vector vector = mergeVectors();
	outPutVector(vector);
}
