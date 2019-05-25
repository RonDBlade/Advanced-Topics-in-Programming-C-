#include "matchManager.h"


matchManager matchManager::instance;

void matchManager::registerSoFiles(vector<string> algoFiles, vector<string> mazeFiles){
    vector<void*> fileHandles;
    void *handle;
    for (auto algoPath = std::begin(algoFiles); algoPath != std::end(algoFiles); algoPath++){
        instance.loadedAlgorithms.push_back(std::make_pair(std::filesystem::path(*algoPath).stem().string(), nullptr));
        handle = dlopen ((*algoPath).c_str(), RTLD_LAZY);
        if (!handle) {
            fprintf (stderr, "%s\n", dlerror());
        }
        else{
            fileHandles.push_back(handle);
        }
    }
    loadMazes(mazeFiles);
    for (auto& handle : fileHandles){
        dlclose(handle);
    }
}

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

void outputData(const vector<vector<int>> steps, const vector<string> algs, const vector<string> mazes){
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
            toprint=toprint+string(lengths[j]-std::to_string(steps[i][j]).length(),' ')+std::to_string(steps[i][j])+"|";
        }
        printer(toprint);
        printer(string(linelen,'-'));
    }
}

void matchManager::runGames(){
    gameInstance game;
    while(allGames.popElement(game)){
        game
    }
}

void matchManager::runThreads(){
    vector<std::thread> programThreads;
    for(int i = 0; i < numOfThreads; i++){
        progrmThreads.push_back(std::thread(runGames));
    }
    runGames();
    for (thread : programThreads){
        thread.join();
    }

}

void matchManager::pairGames(){
    gameInstance game;
    for(auto& maze : loadedMazes){
        for(auto algorithm& : loadedAlgorithms){
            game = gameInstance(maze, algorithm);
            allGames.push(game);
        }
    }
    runThreads();
}

void matchManager::loadMazes(vector<string> mazeFiles, string outputFolder){
    Maze gameMaze;
    for(auto& mazeFile : mazeFiles){
        gameMaze = addMaze(mazeFile);
        if (gameMaze != nullptr){
            loadedMazes.push_back(gameMaze);
        }
    }
    pairGames()
}




    vector<string> validMazes;
    string outputFileName;
    vector<vector<int>> steps;
    vector<int> stepsForMaze;
    vector<string> algorithmsNames;
    vector<pair<string, vector<gameInstance>>> resultsForMaze;
    for(auto algorithmInstance = instance.loadedAlgorithms.begin(); algorithmInstance != instance.loadedAlgorithms.end(); algorithmInstance++){
        algorithmsNames.push_back(algorithmInstance->first);
    }

    for(auto mazeFile = mazeFiles.begin(); mazeFile != mazeFiles.end(); mazeFile++){
        Maze gameMaze = addMaze(*mazeFile);
        if (gameMaze != nullptr){
            validMazes.push_back(std::filesystem::path(*mazeFile).stem().string());
            vector<gameInstance> algorithmsResultsOnMaze = runAlgorithmsOnMaze(gameMaze, instance.loadedAlgorithms);
            resultsForMaze.push_back(std::make_pair(*mazeFile, algorithmsResultsOnMaze));
            for(auto result = algorithmsResultsOnMaze.begin(); result!= algorithmsResultsOnMaze.end(); result++){
                stepsForMaze.push_back(result->getStepsTaken());
                if(outputFolder != ""){
                    outputFileName = outputFolder + std::filesystem::path(*mazeFile).stem().string() + "_" + (*result).getAlgorithmName() + ".output";
                    std::ofstream outputfile(outputFileName);
                    for (auto gameMove = (*result).getGameOutput().begin(); gameMove != (*result).getGameOutput().end(); gameMove++){
                        outputfile << *gameMove << endl;
                    }
                }
            }
            steps.push_back(stepsForMaze);
        }
    }
    outputData(steps, algorithmsNames, validMazes);
}


void matchManager::processMatch (int num_of_arguments, char *arguments[]){
    ParsedInput parsedInput = ParsedInput(num_of_arguments, arguments);
    vector<string> mazeFiles = findAllFilesByExtension(parsedInput.maze_path, ".maze");
    vector<string> algoFiles = findAllFilesByExtension(parsedInput.algorithm_path, ".so");
    outputFolder = parsedInput.output_path;
    numOfThreads = parsedInput.num_of_threads;
    registerSoFiles(algoFiles, mazeFiles);
}
