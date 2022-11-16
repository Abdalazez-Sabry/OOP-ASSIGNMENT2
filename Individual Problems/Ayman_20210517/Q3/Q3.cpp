#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

class StringSet
{
    private:
        vector<string> vec;
       
        void set_vec(string set_str)
        {
            string word = "";
            int index = -1;
            for (char i : set_str)
            {
                ++index;
                if (i == ' ' || (set_str.begin() + index) == (set_str.end() - 1))
                {
                    if (isalpha(i))
                        word += tolower(i);
                    for (string j : vec)
                    {
                        if (word == j)
                        {
                            word = "";
                            break;
                        }
                    }
                    if (word == "")
                        continue;
                    vec.push_back(word);
                    word ="";
                    continue;
                }
                if (ispunct(i))
                {
                    continue;
                }
                word += tolower(i);
            }
        }
    
    public:
        StringSet() {}

        StringSet(const string& str)
        {
            set_vec(str);
        }

        StringSet(char name[])
        {
            string word = "", word_punc = "";
            fstream file;
            file.open(name, ios::in);
            if (!file)
            {
                cout << "file not found!!" << endl;
            }
            while (file)
            {
                file >> word_punc;
                for (char i : word_punc)
                {
                    if (ispunct(i))
                    {
                        continue;
                    }
                    word += tolower(i);
                }
                if (word == "")
                    continue;
                vec.push_back(word);
                word = "";
                word_punc = "";    
            } 
            file.close();  
        }
        
        void add(string new_string)
        {
            set_vec(new_string);
        }
        
        void remove(string remove_string)
        {
            for (int i = 0; i < vec.size(); ++i)
            {
                if (vec[i] == remove_string)
                {
                    vec.erase(vec.begin()+i);
                    return;
                }
            }
            cout << "This word is not in set!!" << endl;
        }
       
        void clear()
        {
            vec.clear();
        }
        
        int numOfStrings()
        {
            return vec.size();
        }
        
        void outAllStrings()
        {
            for (string i : vec)
            {
                cout << i << " ";
            }
            cout << "\n";
        }
        
        StringSet& operator+(StringSet& another)
        {
            for (string s : another.vec)
            {
                this->vec.push_back(s);
            }
            return *this;
        }
        
        StringSet operator*(StringSet& another)
        {
            vector<string> intersection;
            string s = "";
            StringSet inter(s);
            for (string i : this->vec)
            {
                for (string j : another.vec)
                {
                    if (i == j)
                    {
                        intersection.push_back(i);
                    }
                }
            }
            for (string k : intersection)
            {
                inter.add(k);
            }
            return inter;
        }
        
        double similarity(StringSet another)
        {
            string s = "";
            StringSet intersection(s);
            intersection = *this * another;
            double sim = (intersection.numOfStrings() / (sqrt(this->numOfStrings()) * sqrt(another.numOfStrings())));
            return sim;
        }

};

int main()
{
    // constructors and creat objects
    string s = "I! am, @A@ STUDENT, . . in f#Ca.I.";
    StringSet s1(s);
    char name[] = "StringSet.txt";
    StringSet s2(name);
    s1.outAllStrings();
    s2.outAllStrings();
    cout << "\n";

    // test add and remove functions
    s1.add("i am 19 years old");
    s2.remove("job");
    s2.remove("19");
    s1.outAllStrings();
    s2.outAllStrings();
    cout << "\n";

    // test number of strings function
    cout << s1.numOfStrings() << "()" << s2.numOfStrings() << endl;    
    cout << "\n";

    // test (+, *) operators
    s1 = s1 + s2;
    s1.outAllStrings();
    s2.outAllStrings();
    s2 = s2 * s1;
    s1.outAllStrings();
    s2.outAllStrings();
    cout << "\n";

    // test similarity function
    cout << s1.similarity(s2) << endl;
    cout << "\n";

    // test clear function
    s2.clear();
    s1.outAllStrings();
    s2.outAllStrings();
    cout << s1.numOfStrings() << "()" << s2.numOfStrings() << endl;
    return 0;
}
