#pragma once

#include <map>
#include <string>

#define StatesAmount 5
#define MaxState 4

class FiniteStateMachine
{
private:
	std::map<int, std::map<char, int>> states_;
	int currentState_;

	void AddDefaultStates(int statesAmount)
	{
		for (int i = 0; i < statesAmount; i++)
		{
			std::map<char, int> transitions;
			states_.insert(std::make_pair(i, transitions));
		}
	}

	void AddStateTransitions()
	{
		states_[0]['a'] = 4;
		states_[0]['b'] = 2;
		states_[0]['d'] = 3;

		states_[1]['e'] = 3;

		states_[2]['a'] = 1;
		states_[2]['c'] = 4;

		states_[3]['a'] = 4;
		states_[3]['b'] = 2;
	}

	void AddStates()
	{
		AddDefaultStates(StatesAmount);
		AddStateTransitions();
	}

public:
	FiniteStateMachine()
	{
		AddStates();
		Reset();
	}

	bool ChangeState(char c)
	{
		std::map<char, int> transitions = states_[currentState_];
		std::map<char, int>::iterator transition = transitions.find(c);

		if (transition == transitions.end())
		{
			return false;
		}

		currentState_ = transition->second;
		return true;
	}

	void Reset()
	{
		currentState_ = 0;
	}

	bool CheckTransitions(const std::string& transitions)
	{
		Reset();

		for (auto c : transitions)
		{
			if (!ChangeState(c))
			{
				return false;
			}
		}

		return currentState_ == MaxState;
	}
};

