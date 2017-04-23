#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <iomanip>
#include <limits>
#include <math.h>

using namespace std;

int wordlen;
int wordlen1;
string previous = "";
int previouslen = 0;
string current;
int currentlen;

class Item{
    public:
    string word;
    unsigned int distance;
    Item(string arg1, unsigned int arg2){
        word = arg1;
        distance = arg2;
    }
};

struct ItemCompare
{
	bool operator()(const Item& i1, const Item& i2) const
	{
		return i1.distance < i2.distance;
	}
};

int smallest(int x, int y, int z){
    return std::min(std::min(x, y), z);
}

unsigned int levenstein(string& word1, string& word2, vector<vector<unsigned int>>& matrix, unsigned int index)
{
	unsigned int length1 = word1.size(), length2 = word2.size();
    index = 0;
	for(unsigned int i = 1; i <= length1; ++i)
		for(unsigned int j = index + 1; j <= length2; ++j)
            // note that std::min({arg1, arg2, arg3}) works only in C++11,
            // for C++98 use std::min(std::min(arg1, arg2), arg3)
            matrix[i][j] = smallest(matrix[i - 1][j - 1] + (word1[i - 1] == word2[j - 1] ? 0 : 1), matrix[i - 1][j] + 1, matrix[i][j - 1] + 1);
	return matrix[length1][length2];
}

int main(int argc, char* argv[]) {
        int limit;
        string word;
        if(argc == 2){
            word = string(argv[1]);
            limit = 10;
        }else if(argc == 4 && string(argv[2]) == "-n"){
            word = string(argv[1]);
            string intstr(argv[3]);
            stringstream str(intstr);
            str >> limit;
            if(!limit){
                cerr << "argument is not a number" << endl;
                exit(0);
            }
        }else{
            cerr << "arguments are not correct" << endl;
            exit(0);
        }

        std::priority_queue<Item, std::vector<Item>, ItemCompare> pq;
        unsigned int maximum = numeric_limits<unsigned int>::min();
        std::ifstream infile("/usr/share/dict/words");
        std::string line;
        std::vector<std::vector<unsigned int>> m(word.length() + 1, std::vector<unsigned int>(40 + 1));
        m[0][0] = 0;
        for(unsigned int i = 1; i <= word.length(); ++i) m[i][0] = i;
        for(unsigned int i = 1; i <= 40; ++i) m[0][i] = i;
        while (std::getline(infile, line))
        {
            current = line;
            if(current == word) continue;
            unsigned int index = 0;
            while(current.length() >= index && previous.length() >= index && current[index] == previous[index]) index++;
            //cout << current << " " << index << endl;
            unsigned int result = levenstein(word, current, m, index);
            if(pq.size() < limit){
                pq.push(Item(current, result));
                maximum = max(result, maximum);
            }else if(result < maximum){
                pq.push(Item(current, result));
                pq.pop();
            }
            previous = line;
            previouslen = previous.length();
        }
        while(!pq.empty()){
            cout << pq.top().word << " " << pq.top().distance << endl;
            pq.pop();
        }
        return 0;
} 
