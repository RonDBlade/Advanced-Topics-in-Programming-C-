/*
this .cpp file is to show what the template of printing the output in the new way will be. Just need to give him all the information in the
vectors (for steps_per_alg,because its a vector of vectors,can be tranfered by the move constructor,that will just steal the data).
just give
*/
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::to_string;

void printer(const string toprint)
{
    cout<<toprint<<endl;
}

vector<int> find_line_length(const vector<string> algs,const vector<string> mazes){
    unsigned int i=0,maxlen=3+mazes.size(),alglen=0;
    vector<int> lengths;
    for(i=0;i<algs.size();i++){
        if(alglen<algs[i].length())
            alglen=algs[i].length();
    }
    maxlen+=alglen;
    for(i=0;i<mazes.size();i++){
        if(mazes[i].length()<3){
            maxlen+=6;
            lengths.push_back(6);
        }
        else{
            maxlen+=mazes[i].length()+3;
            lengths.push_back(mazes[i].length()+3);
        }
    }
    lengths.push_back(alglen);
    lengths.push_back(maxlen);
    return lengths;
}

void outputData(const vector<vector<int>> steps,const vector<string> algs,const vector<string> mazes){
    vector<int> lengths=find_line_length(algs,mazes); //give this the arguments by their length,calculate how long each line should be
    int linelen=lengths.back();
    lengths.pop_back();
    int alglen=lengths.back();
    lengths.pop_back();
    printer(string(linelen,'-'));
    string toprint="|"+string(alglen+1,' ')+"|";
    for(unsigned int i=0;i<mazes.size();i++){//print the first line here
        toprint=toprint+mazes[i]+string(lengths[i]-mazes[i].length(),' ')+"|";
    }
    printer(toprint);
    printer(string(linelen,'-'));
    for(unsigned int i=0;i<algs.size();i++){//print the rest of the lines
        toprint="|"+algs[i]+string(alglen-algs[i].length(),' ')+" |";
        for(unsigned int j=0;j<mazes.size();j++){
            toprint=toprint+string(lengths[j]-to_string(steps[i][j]).length(),' ')+to_string(steps[i][j])+"|";
        }
        printer(toprint);
        printer(string(linelen,'-'));
    }
}

/*outputData is the real function,the main is just so that we give him the data.in the real implementation,we need to*/
int main()
{
    vector<string> mazes = {"ma","maze23","maze456","maze7890","dsa","fidajskfda","skdaosd"};
    vector<string> algs = {"alg1j","alg2kjk","alg3lkkjk"};
    vector<vector<int>> steps_per_alg= {{1,2,3,999,-1,-1,-1},{4,5,6,35,3,3,5},{7,8,-1,3,1293,293,488}}; //each vector is what each alg did in each maze by order
    outputData(steps_per_alg,algs,mazes);
    return 0;
}
