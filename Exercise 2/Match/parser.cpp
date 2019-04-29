#include "parser.h"

string get_path_from_vector(vector<string> arguments, string search_string){
    std::error_code err;
    auto place_in_vector = std::find(std::begin(arguments), std::end(arguments), search_string);
    string path = filesystem.current_path();
    if (place_in_vector != std::end(arguments)){
        if (std::next(place_in_vector) != std::end(arguments)){
            path = std::next(place_in_vector);
        }
    }
    return (std::filesystem::is_directory(path, err)) ? path : filesystem.current_path();
}


FilePaths :: FilePaths(int argv, char* args[]): maze_path(std::filesystem::current_path()), algorithm_path(std::filesystem::current_path()){
    string argument;
    vector<string> arguments;
    auto place_in_vector;
    for (int i = 1; i <= argv; i++){
        argument = string(args[i]);
        arguments.push_back(argument);
    }
    maze_path = get_path_from_vector(arguments, "-maze_path");
    algorithm_path = get_path_from_vector(arguments, "-algorithm_path");
    output_path = get_path_from_vector(arguments, "-output");
}
