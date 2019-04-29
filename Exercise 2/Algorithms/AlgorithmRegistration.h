#ifndef ALGORITHMREGISTRATION_H_INCLUDED
#define ALGORITHMREGISTRATION_H_INCLUDED

#pragma once

#include <functional>
#include <memory>

class AlgorithmRegistration {
public:
AlgorithmRegistration(std::function<std::unique_ptr<AbstractAlgorithm>()>);
};

#define REGISTER_ALGORITHM(class_name) \
AlgorithmRegistration register_me_##class_name \
	([]{return std::make_unique<class_name>();} );

#endif // ALGORITHMREGISTRATION_H_INCLUDED
