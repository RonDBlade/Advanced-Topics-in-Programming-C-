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

void printer(bool tofile,const string toprint)
{
    cout<<toprint<<endl;
}

vector<int> find_line_length(const vector<string> algs,const vector<string> mazes){
    int i=0,maxlen=7,alglen=0;
    vector<int> lengths;
    for(i=0;i<algs.size();i++){
        if(alglen<algs[i].length())
            alglen=algs[i].length();
    }
    maxlen+=alglen;
    for(i=0;i<mazes.size();i++){
        if(mazes[i].length()<6){
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

void outputData(bool tofile,const vector<vector<int>> steps,const vector<string> algs,const vector<string> mazes){
    vector<int> lengths=find_line_length(algs,mazes); //give this the arguments by their length,calculate how long each line should be
    int linelen=lengths.back();
    lengths.pop_back();
    int alglen=lengths.back();
    lengths.pop_back();
    printer(tofile,string(linelen,'-'));
    string toprint="|"+string(alglen+1,' ')+"|";
    for(int i=0;i<mazes.size();i++){//print the first line here
        toprint=toprint+mazes[i]+string(lengths[i]-mazes[i].length(),' ')+"|";
    }
    printer(tofile,toprint);
    printer(tofile,string(linelen,'-'));
    for(int i=0;i<algs.size();i++){//print the rest of the lines
        toprint="|"+algs[i]+" |";
        for(int j=0;j<mazes.size();j++){
            toprint=toprint+string(lengths[i]-to_string(steps[i][j]).length(),' ')+to_string(steps[i][j])+"|";
        }
        printer(tofile,toprint);
        printer(tofile,string(linelen,'-'));
    }
}

/*outputData is the real function,the main is just so that we give him the data.in the real implementation,we need to*/
int main()
{
    string outfile="outfile.txt";
    bool to_out=false;
    vector<string> mazes = {"maze1","maze2","maze3","maze4"};
    vector<string> algs = {"alg1","alg2","alg3"};
    vector<vector<int>> steps_per_alg= {{1,2,3,999},{4,5,6,35},{7,8,-1,3}}; //each vector is what each alg did in each maze by order
    outputData(to_out,steps_per_alg,algs,mazes);
    return 0;
}
