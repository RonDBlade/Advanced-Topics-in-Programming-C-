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

void outputData(bool tofile,const vector<vector<int>> steps,const vector<string> algs,const vector<string> mazes,int line_length)
{

}
void outputData(bool tofile,const vector<vector<int>> steps,const vector<string> algs,const vector<string> mazes){
    int length=find_line_length(); //give this the arguments by their length,calculate how long each line should be
    printer(tofile,steps,algs,mazes,length); //checks if tofile is true or false and by that prints to screen or sends to file
}

/*outputData is the real function,the main is just so that we give him the data.in the real implementation,we need to*/
int main()
{
    string outfile="outfile.txt";
    bool to_out=false;
    vector<string> mazes = {"maze1","maze2","maze3","maze4"}
    vector<string algs = {"alg1","alg2","alg3"}
    vector<vector<int>> steps_per_alg= {{1,2,3,999},{4,5,6,35},{7,8,-1,3}}; //each vector is what each alg did in each maze by order
    outputData(to_out,steps_per_alg,algs,mazes)
    return 0;
}
