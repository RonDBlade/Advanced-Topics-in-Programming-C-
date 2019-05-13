#include "matchManager.h"


matchManager matchManager::instance;

void matchManager::updateAlgorithmName(string algorithmName){
    loadedAlgorithms.back().first = algorithmName;
        std::cout << "QWE" << std::endl;
}

vector<void*> registerSoFiles(vector<string> algoFiles){
    vector<void*> handles;
    void *handle;
    for (auto algoPath = std::begin(algoFiles); algoPath != std::end(algoFiles); algoPath++){
        handle = dlopen ((*algoPath).c_str(), RTLD_LAZY);
        if (!handle) {
            fprintf (stderr, "%s\n", dlerror());
        }
        else{
            handles.push_back(handle);
        //matchManager::getInstance().updateAlgorithmName(std::filesystem::path(*algoPath).stem().string());
//std::cout << matchManager::getInstance().getAlgorithms().back().first << endl;
        }
    }
    return handles;
}

void closeSoFiles(vector<void *> handles){
    for (auto handle = std::begin(handles); handle != std::end(handles); handle++){
        dlclose(*handle);
    }
}


void printer(const string toprint)
{
    cout<<toprint<<endl;
}

vector<int> find_line_length(const vector<string> algs,const vector<string> mazes){
    unsigned int i=0,maxlen=7,alglen=0;
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
        toprint="|"+algs[i]+" |";
        for(unsigned int j=0;j<mazes.size();j++){
            toprint=toprint+string(lengths[i]-std::to_string(steps[i][j]).length(),' ')+std::to_string(steps[i][j])+"|";
        }
        printer(toprint);
        printer(string(linelen,'-'));
    }
}

void runMatches(vector<string> mazeFiles){
    vector<string> validMazes;
    vector<vector<int>> steps;
    vector<int> stepsForMaze;
    vector<string> algorithmsNames;
    vector<pair<string, vector<gameInstance>>> resultsForMaze;
    vector<pair<string, std::function<std::unique_ptr<AbstractAlgorithm>()>>> loadedAlgorithms = matchManager::getInstance().getAlgorithms();
    for(auto algorithmInstance = loadedAlgorithms.begin(); algorithmInstance != loadedAlgorithms.end(); algorithmInstance++){
        algorithmsNames.push_back(algorithmInstance->first);
    }
    for(auto mazeFile = mazeFiles.begin(); mazeFile != mazeFiles.end(); mazeFile++){
        std::shared_ptr<Maze> gameMaze = addMaze(*mazeFile);
        if (gameMaze != nullptr){
            validMazes.push_back(std::filesystem::path(*mazeFile).stem().string());
            vector<gameInstance> algorithmsResultsOnMaze = runAlgorithmsOnMaze(gameMaze, loadedAlgorithms);
            resultsForMaze.push_back(std::make_pair(*mazeFile, algorithmsResultsOnMaze));
            for(auto result = algorithmsResultsOnMaze.begin(); result!= algorithmsResultsOnMaze.end(); result++){
                stepsForMaze.push_back(result->getStepsTaken());
            }
            steps.push_back(stepsForMaze);
        }
    }
    outputData(steps, algorithmsNames, validMazes);
}

void matchManager::processMatch (int num_of_arguments, char *arguments[]){
    FilePaths filesPaths = FilePaths(num_of_arguments, arguments);
    vector<string> mazeFiles = findAllFilesByExtension(filesPaths.maze_path, ".maze");
    vector<string> algoFiles = findAllFilesByExtension(filesPaths.algorithm_path, ".so");
    vector<void*> handles = registerSoFiles(algoFiles);
    runMatches(mazeFiles);
    closeSoFiles(handles);
}
