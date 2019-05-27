#include "matchManager.h"


matchManager matchManager::instance;

matchManager::~matchManager(){
    for (auto& handle : fileHandles){
        cout << "Closing file" << endl;
        dlclose(handle);
        cout << "Closed successfully" << endl;
    }
}

void matchManager::registerSoFiles(vector<string> algoFiles, vector<string> mazeFiles){
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
    if (instance.loadedAlgorithms.size() < 1){
        cout << "No valid algorithms files found, aborting." << endl;
        exit(1);
    }
    loadMazes(mazeFiles);
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
    // As long there are games in the queue, the thread will run more games.
    // Since all the games are produced before we run the threads, when the queue is empty, all the games have started running.
    gameInstance game;
    string outputFileName;
    int gameID;
    while((gameID = allGames.popElement(game)) > -1){
        game.runGame();
        if(outputFolder != ""){
            outputFileName = outputFolder + game.getMazeName() + "_" + game.getAlgorithmName() + ".output";
            std::ofstream outputfile(outputFileName);
            for (auto gameMove : game.getGameOutput()){
                outputfile << gameMove << endl;
            }
        }
        if(!allGames.updateElement(gameID, game)){
            cout << "There was an error updating game score for algorithm " << game.getAlgorithmName() << " run on maze " << game.getMazeName() << ". Summary table may be wrong." << endl;
        }
    }
}

void matchManager::printScores(){
    allGames.rewindQueue();
    gameInstance currentGame;
    vector<vector<int>> steps;
    vector<int> stepsForAlgorithm;
    vector<string> mazeNames;
    vector<string> algorithmsNames;
    for(auto& algorithm : instance.loadedAlgorithms){
        algorithmsNames.push_back(algorithm.first);
    }
    for(auto& maze : loadedMazes){
        mazeNames.push_back(maze.getMazeName());
    }
    for(size_t i = 0; i < instance.loadedAlgorithms.size(); i++){
        stepsForAlgorithm.clear();
        for(size_t j = 0; j < loadedMazes.size(); j++){
            allGames.popElement(currentGame);
            cout << "Game: " << currentGame.getAlgorithmName() << "_" << currentGame.getMazeName() << " got " << currentGame.getStepsTaken() << " steps" << endl;
            stepsForAlgorithm.push_back(currentGame.getStepsTaken());
        }
        steps.push_back(stepsForAlgorithm);
    }
    outputData(steps, algorithmsNames, mazeNames);
}

void matchManager::runThreads(){
    vector<std::thread> programThreads;
    for(int i = 0; i < numOfThreads; i++){
        programThreads.push_back((std::thread(&matchManager::runGames, this)));
    }
    runGames();
    for (auto& thread : programThreads){
        thread.join();
    }
    printScores();
}

void matchManager::pairGames(){
    allGames.setSize(loadedMazes.size() * instance.loadedAlgorithms.size());
    for(auto& algorithm : instance.loadedAlgorithms){
        for(auto& maze : loadedMazes){
            gameInstance game = gameInstance(maze, algorithm);
            allGames.addElement(game);
        }
    }
    runThreads();
}

void matchManager::loadMazes(vector<string> mazeFiles){
    Maze gameMaze;
    for(auto& mazeFile : mazeFiles){
        gameMaze = addMaze(mazeFile);
        if (gameMaze.isValidMaze()){
            loadedMazes.push_back(gameMaze);
        }
        if (loadedMazes.size() < 1){
            cout << "No valid maze files, aborting" << endl;
            exit(1);
        }
    }
    pairGames();
}

void matchManager::processMatch (int num_of_arguments, char *arguments[]){
    ParsedInput parsedInput = ParsedInput(num_of_arguments, arguments);
    vector<string> mazeFiles = findAllFilesByExtension(parsedInput.maze_path, ".maze");
    vector<string> algoFiles = findAllFilesByExtension(parsedInput.algorithm_path, ".so");
    outputFolder = parsedInput.output_path;
    // Adding backslash in case the user didn't added one
    if (outputFolder.back() != '/'){
        outputFolder += "/";
    }
    numOfThreads = parsedInput.num_of_threads;
    if (numOfThreads < 0){
        cout << "usage error" << endl;
        return;
    }
    registerSoFiles(algoFiles, mazeFiles);
}
