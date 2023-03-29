#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;
int main(){
    /*
     Construct an array of 1500 random integers within range [0, 120]
    An input file input.txt is provide. Each line of input.txt is a query integer that you need to check how many of that number is in your random integer array. For each query integer, fork a new child process to do the counting. The output is for each input query, output the count and child process id. For example:

    $> query: 17    count: 5    pid: 13342
    $> query: 29    count: 3    pid: 13357
    */
   
    ifstream iFile;
    ofstream ofile;
    
    iFile.open("input.txt");
    //Reads my text file and opens it.
    if(!iFile.is_open()){
        cout << "Not inputting file!\n";
        return 0;
    }
    
    cout << "Search Inquiry\n";
    vector<int> queries;
    string line;
    while(getline(iFile, line)){
        int searchQuery = stoi(line);
        //Takes my string characters line by line and turns them into integers and puts them in a Search Query individually one by one.
        queries.push_back(searchQuery);
        // adds my integer query from txt file to my vector of integers;
        cout << "query: " << searchQuery << endl;
   }
    
   // cout << "Random Integers\n";
    int SizeOfArray = 1500;
    int RandomArray[SizeOfArray];
    for (int i = 0; i < SizeOfArray; i++){
        RandomArray[i] = rand() % 120;
    }
    for (int i = 0; i < queries.size(); i++){
        int searchQuery = queries[i];
        pid_t p_id = fork();
        //creates a process ID and sets it to fork to create a child process.
        if(p_id < 0){
            //Cant be less than 0 or error occurred
            cout << "Failed to fork!" << endl;
            exit(-1);
        }
        else if (p_id == 0){
            //counter to count the number of children for the parent process.
            // This creates a child process.
            int Counter = 0;
            for (int j = 0; j < SizeOfArray;j++){
                if(RandomArray[j] == searchQuery){
                    Counter++;
                }
            }
            cout << "query: " << searchQuery << " count: " << Counter << " pid: " << getpid() << endl;
            return 0;
            }
        }
        for(int i = 0; i < queries.size(); i++){
            wait(NULL);
        }

    
    
    
    iFile.close();
    
    return 0;
}
