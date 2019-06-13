#include "parser.h"
#include "matchManager.h"
#include "Match.h"

vector<void*> initializeMatch(int num_of_arguments, char *arguments[]){
    ParsedInput parsedInput = ParsedInput(num_of_arguments, arguments);
    vector<string> mazeFiles = findAllFilesByExtension(parsedInput.maze_path, ".maze");
    vector<string> algoFiles = findAllFilesByExtension(parsedInput.algorithm_path, ".so");
    using MyMatch = Match<matchManager, Maze, AbstractAlgorithm>;
    matchManager mM = matchManager();
    // Adding backslash in case the user didn't added one
    if (parsedInput.output_path.back() != '/'){
        parsedInput.output_path += "/";
    }
    mm.setOutputFolder(parsedInput.output_path);
    vector<void*> fileHandles = mm.registerSoFiles(algoFiles, mazeFiles);
    return fileHandles;
}

int main(int argc, char *argv[]){
    auto fileHandlers = initializeMatch(argc, argv);
    match.addPlayer([](int init){return Player{init};});
    GameData gd;
    match.addGame(gd);
    MyMatch::Report report = match.runMatch();
    // TODO: print report to screen
    for (auto& handle : fileHandlers){
 //       dlclose(handle);
    }
    return 0;
}
