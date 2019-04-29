#ifndef ABSTRACTALGORITHM_H_INCLUDED
#define ABSTRACTALGORITHM_H_INCLUDED

#pragma once

class AbstractAlgorithm {
public:
virtual ~AbstractAlgorithm(){}

enum Move { UP, RIGHT, DOWN, LEFT, BOOKMARK };

	virtual Move move() = 0;
	virtual void hitWall() = 0;
	virtual void hitBookmark(int seq) = 0;
};

#endif // ABSTRACTALGORITHM_H_INCLUDED
