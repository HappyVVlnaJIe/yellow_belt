#pragma once

#include "date.h"
#include <memory>

enum class LogicalOperation {
	Or,
	And
};

enum class Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual
};

enum class NodeType {
	Empty,
	Date,
	Event,
	Logical
};

class Node {
public:
	virtual bool Evaluate(const Date& date, const std::string& event) const=0;

protected:

};

class EmptyNode :public Node {
public:
	bool Evaluate(const Date& date, const std::string& event) const override ;
};

class DateComparisonNode :public Node {
public:
	DateComparisonNode(Comparison cmp, Date date);
	bool Evaluate(const Date& date, const std::string& event) const override;
private:
	Date _date;
	Comparison _cmp;
};

class EventComparisonNode :public Node {
public:
	EventComparisonNode(Comparison cmp, std::string event);
	bool Evaluate(const Date& date, const std::string& event) const override;
private:
	Comparison _cmp;
	std::string _event;
};

class LogicalOperationNode :public Node {
public:
	LogicalOperationNode(LogicalOperation logical_operation, std::shared_ptr<Node> left, std::shared_ptr<Node> right);
	bool Evaluate(const Date& date, const std::string& event) const override;
private:
	std::shared_ptr<Node> _left;
	std::shared_ptr<Node> _right;
	LogicalOperation _logical_operation;
};