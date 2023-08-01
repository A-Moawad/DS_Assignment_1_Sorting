#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;
class Student {
private: 
	int id;
	string name;
	double gpa;
public:
	Student(int id, string name, double gpa) {
		this->id = id;
		this->name = name;
		this->gpa = gpa;
	}
	bool  operator < (const Student& s) const {
		return this->name < s.name;
	}
    bool operator > (const Student &s) const {
        return this->gpa > s.gpa;
    }
	int getId(){
		return id;
    }
	string getName(){
		return name;
    }
	double getGpa(){
		return  gpa;
    }

};

// Function to read student objects from the file
vector<Student> read_students_from_file(const string& file_name) {
    vector<Student> students;
    ifstream file(file_name); // open file

    if (!file.is_open()) { // Check if the file is open
        cout << "Error: File not found." << std::endl;
        return students;
    }

    int student_id;
    string name;
    double gpa;

    while (file >> student_id >> name >> gpa) {
        students.emplace_back(student_id, name, gpa);
    }

    file.close();
    return students;
}
template<typename T>
void insertion_sort(vector<T>&arr, int n , int &comparisons , double &timeTaken,  bool byName = true){

    // Get the starting time
    auto start = std::chrono::high_resolution_clock::now();

    for(int i = 1; i < n; ++i){
        T key = arr[i];
        int j = i - 1; 
        while (j >= 0 && ((byName && key < arr[j]) || (!byName && arr[j] > key))) {
            arr[j + 1] = arr[j];
            j--;
            comparisons++;
        }
        arr[j + 1] = key;
    }

    // Get the ending time
    auto end = std::chrono::high_resolution_clock::now();

     // Calculate the duration
    auto time_taken = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}
template<typename T>
void selection_sort(vector<T>&arr, int n , int &comparisons , double &timeTaken, bool byName = true){

     // Get the starting time
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            if ((byName && arr[j] < arr[min_index] ) || (!byName && arr[min_index] > arr[j])) {
                min_index = j;
                comparisons++;
            }
        }
        swap(arr[min_index], arr[i]);
    }
    // Get the ending time
    auto end = std::chrono::high_resolution_clock::now();
    // Calculate the duration
    auto time_taken = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}
void writeStudentsToFile(const string& filename, const string& algorithmName, int comparisons, double timeTaken,  vector<Student>& students) {
    ofstream file(filename, ios::app);
    if (!file) {
        cerr << "Error: Unable to open file: " << filename << endl;
        exit(1);
    }

    file << "Algorithm: " << algorithmName << endl;
    file << "Number of comparisons: " << comparisons << endl;
    file << "Running Time: " << timeTaken << " microseconds" << endl;
    file << "Sorted Student Elements: " << endl;

    for (auto& s : students) {
       file << s.getName() << "\n" << s.getId() << "\n" << s.getGpa() << "\n";
    }
    file << '\n' << '\n';
    file.close();
}

int main(){
	std::string file_name = "students.txt";
	std::vector<Student>list = read_students_from_file(file_name);


// sort by name
    int comparisons_insertion = 0;
    double timeTaken_insertion = 0;
    insertion_sort(list, list.size(), comparisons_insertion, timeTaken_insertion, true);
    writeStudentsToFile("SortedByName.txt", "insertionSort", comparisons_insertion, timeTaken_insertion, list);

    int comparisons_selection = 0;
    double timeTaken_selection = 0;
    selection_sort(list, list.size(), comparisons_selection, timeTaken_selection, true);
    writeStudentsToFile("SortedByName.txt", "selectionSort", comparisons_selection, timeTaken_selection, list);
    cout << "done";

//sort by gpa

    insertion_sort(list, list.size(), comparisons_insertion, timeTaken_insertion, false);
    writeStudentsToFile("SortedByGPA.txt", "insertionSort", comparisons_insertion, timeTaken_insertion, list);

    selection_sort(list, list.size(), comparisons_selection, timeTaken_selection, false);
    writeStudentsToFile("SortedByGPA.txt", "selectionSort", comparisons_selection, timeTaken_selection, list);
}

