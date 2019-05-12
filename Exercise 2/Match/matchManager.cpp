#include "matchManager.h"


matchManager matchManager::instance;


void runMatches(vector<string> mazeFiles, string outputFolder){
    vector<string> validMazes;
    vector<pair<string, vector<gameInstance>>> resultsForMaze;
    for(auto mazeFile = mazeFiles.begin(); mazeFile != mazeFiles.end(); mazeFile++){
        std::shared_ptr<Maze> gameMaze = addMaze(*mazeFile);
        if (gameMaze != nullptr){
            validMazes.push_back(*mazeFile);
            resultsForMaze.push_back(std::make_pair(*mazeFile, runAlgorithmsOnMaze(gameMaze, matchManager::getInstance().getAlgorithms(), outputFolder)));
        }
    }

}

vector<void*> registerSoFiles(vector<string> algoFiles){
    vector<void*> handles;
    void *handle;
    for (auto algoPath = std::begin(algoFiles); algoPath != std::end(algoFiles); algoPath++){
        handle = dlopen (algoPath, RTLD_LAZY);
        if (!handle) {
            fprintf (stderr, "%s\n", dlerror());
        }
        else{
            handles.push_back(handle);
            matchManager::getInstance().getAlgorithms().back().first = *algoPath;
        }
    }
    return handles;
}

void closeSoFiles(vector<void *> handles){
    for (auto handle = std::begin(handles); handle != std::end(handles); handle++){
        dlclose(handle);
    }
}


void processMatch (int num_of_arguments, char *arguments[]){
    FilePaths paths = FilePaths(num_of_arguments, arguments);
    vector<string> mazeFiles = findAllFilesByExtension(paths.maze_path, ".maze");
    vector<string> algoFiles = findAllFilesByExtension(paths.algorithm_path, ".so");
    vector<void*> handles = registerSoFiles(algoFiles);
    runMatches(mazeFiles, paths.output_path);
    closeSoFiles(handles);
}
