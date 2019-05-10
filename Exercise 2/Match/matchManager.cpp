#include "matchManager.h"


void initializeMatch (int num_of_arguments, char *arguments[]){
    FilePaths paths = FilePaths(num_of_arguments, arguments);
    vector<string> mazeFiles = findAllFilesByExtension(paths.maze_path, ".maze");
    vector<string> algoFiles = findAllFilesByExtension(paths.algorithm_path, ".so");

}


void runMatches(vector<string> mazeFiles, string outputFolder){
    vector<string> validMazes;
    vector<pair<string, vector<gameInstance>>> resultsForMaze;
    int longestMazeName = 0;
    for(auto mazeFile = mazeFiles.begin(), mazeFile != mazeFiles.end(); mazeFile++){
        std::shared_ptr<Maze> gameMaze = parser::addMaze(*mazeFile);
        if (gameMaze != nullptr){
            validMazes.push_back(*mazeFile);
            resultsForMaze.push_back(std::make_pair(*mazeFile, gameManager::runAlgorithmsOnMaze(gameMaze, loadedAlgorithms, outputFolder));
        }
    }

}

void openSOFile(string filePath){
    void *handle;
    std::function<std::unique_ptr<AbstractAlgorithm>()> algorithm;
    char *error;
    handle = dlopen (filePath, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();
    algorithm = dlsym(handle, "NEED TO ADD ALGORITHM SYMBOL HERE");
    if ((error = dlerror()) != NULL)
    {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    dlclose(handle);
}
