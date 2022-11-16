#include<iostream>
#include<string>
#include<fstream>
#include<vector>

using namespace std;

class LabelGenerator{
    protected:
    string prefix;
    int sequence;
    public:
    LabelGenerator() = default;
    LabelGenerator(string prefix, int sequence);
    string nextLabel();

};

class FileLabelGenerator : public LabelGenerator{
    private:
    string fileName;
    vector<string> fileLines;
    public:
    FileLabelGenerator(string prefix, int sequence, string fileName);
    string nextLabel();
    void loadFile();
    
};

FileLabelGenerator::FileLabelGenerator(string prefix, int sequence, string fileName){
    this->prefix = prefix;
    this->sequence = sequence;
    this->fileName = fileName;
    loadFile();
}

void FileLabelGenerator::loadFile(){
    ifstream file;
    file.open(fileName);
    while (file)
    {
        string line;
        getline(file, line);
        fileLines.push_back(line);
    }   
}

string FileLabelGenerator::nextLabel(){
    string result = prefix + to_string(sequence) + ' ' + fileLines[sequence-1];
    sequence++;
    return result;
}

LabelGenerator::LabelGenerator(string prefix, int sequence){
    this->prefix = prefix;
    this->sequence = sequence;
}

string LabelGenerator::nextLabel(){
    string result = prefix + to_string(sequence);
    sequence++;
    return result;
}

int main(){
    LabelGenerator figuret("figure ", 1);
    for(int i = 0; i< 5; i++){
        cout << figuret.nextLabel() << ", ";
    }
    LabelGenerator figureNumbers("Figure ", 1);
    LabelGenerator pointNumbers("P", 0);
    cout << "Figure numbers: ";
    for (int i = 0; i < 3; i++) {
        cout << figureNumbers.nextLabel() << ", ";
    }
    cout << endl << "Point numbers: ";
    for (int i = 0; i < 5; i++) {
        cout << pointNumbers.nextLabel() << ", ";
    }
    cout << endl << "More figures: ";
    for (int i = 0; i < 3; i++) {
        cout << figureNumbers.nextLabel() << ", ";
    }
    cout << endl;
    
    FileLabelGenerator figureLabels ("Figure ", 1, "labels.txt");
    cout << "Figure labels: \n";
    for (int i = 0; i < 3; i++) {
    cout << figureLabels.nextLabel() << endl;
    }
    cout << figureLabels.nextLabel();
    
}