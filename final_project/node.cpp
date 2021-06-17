#include "node.h"
#include "date.h"
bool EmptyNode::Evaluate(const Date& date, const std::string& event) const {
	return true;
}

DateComparisonNode::DateComparisonNode(Comparison cmp, Date date) : _date(date), _cmp(cmp){}

bool DateComparisonNode::Evaluate(const Date& date, const std::string& event) const {
	switch (_cmp)
	{
	case Comparison::Less:
		return _date > date;
		break;
	case Comparison::LessOrEqual:
		return _date >= date;
		break;
	case Comparison::Greater:
		return _date < date;
		break;
	case Comparison::GreaterOrEqual:
		return _date <= date;
		break;
	case Comparison::Equal:
		return _date == date;
		break;
	case Comparison::NotEqual:
		return _date != date;
		break;
	default:
		break;
	}
}

EventComparisonNode::EventComparisonNode(Comparison cmp, std::string event) : _cmp(cmp), _event(event) {}

bool EventComparisonNode::Evaluate(const Date& date, const std::string& event) const {
	switch (_cmp)
	{
	case Comparison::Less:
		return _event > event;
		break;
	case Comparison::LessOrEqual:
		return _event >= event;
		break;
	case Comparison::Greater:
		return _event < event;
		break;
	case Comparison::GreaterOrEqual:
		return _event <= event;
		break;
	case Comparison::Equal:
		return _event == event;
		break;
	case Comparison::NotEqual:
		return _event != event;
		break;
	default:
		break;
	}
}
 
LogicalOperationNode::LogicalOperationNode(LogicalOperation logical_operation, std::shared_ptr<Node> left, std::shared_ptr<Node> right) 
	: _logical_operation(logical_operation), _left(left), _right(right) {}

bool LogicalOperationNode::Evaluate(const Date& date, const std::string& event) const {
	switch (_logical_operation)
	{
	case LogicalOperation::Or:
		return _left->Evaluate(date, event) || _right->Evaluate(date, event);
		break;
	case LogicalOperation::And:
		return _left->Evaluate(date, event) && _right->Evaluate(date, event);
		break;
	default:
		break;
	}
}