#include "parser.h"

string getPathFromVector(vector<string> arguments, string search_string){
    std::error_code err;
    auto place_in_vector = std::find(std::begin(arguments), std::end(arguments), search_string);
    string path = filesystem.current_path();
    if (place_in_vector != std::end(arguments)){
        if (std::next(place_in_vector) != std::end(arguments)){
            path = std::next(place_in_vector);
        }
    }
    if ((search_string == "-output") && (place_in_vector == std::end(arguments))){
        return nullptr;
    }
    // Return the path found in the arguments or the default path of current working directory
    return (std::filesystem::is_directory(path, err)) ? path : filesystem.current_path();
}


FilePaths :: FilePaths(int num_of_arguments, char* arguments[]): maze_path(std::filesystem::current_path()), algorithm_path(std::filesystem::current_path()){
    string argument;
    vector<string> arguments;
    auto place_in_vector;
    for (int i = 1; i <= num_of_arguments; i++){
        argument = string(arguments[i]);
        arguments.push_back(argument);
    }
    maze_path = getPathFromVector(arguments, "-maze_path");
    algorithm_path = getPathFromVector(arguments, "-algorithm_path");
    output_path = getPathFromVector(arguments, "-output");
}


vector<string> findAllFilesByExtension(string path, string extension){
    vector<string> filesPaths;
    for (auto& p: filesystem::directory_iterator(path)){
        if (p.path().extension() == extension){
            filesPaths.push_back(p.path());
        }
    }
    return filesPaths;
}
