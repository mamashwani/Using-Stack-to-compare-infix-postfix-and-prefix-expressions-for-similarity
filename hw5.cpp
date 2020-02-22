#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "ArgumentManager.h"
using namespace std;

template <class T>
class stacks
{
private:
	stacks* top; // pointer to top of stack
	T  data; // data to store of dataType T 
	stacks* next; // pointer to next element of stack 
	int stack_size; // helps to keep track of stack size
public:
	stacks() // intialization of overall stack 
	{
		top = nullptr; // setting top to null (i.e. no elements in stack)
	}
	stacks(T info) // constructor to add to the stack by intializing next node 
	{
		data = info;
		next = nullptr;
	}
	void push(T info) // to add to stack (add from begining)
	{
		stacks<T>* add = new stacks<T>(info); // creating dynamically allocated element of stack 
		if (top == nullptr) // checking to see if no stack exists 
		{
			top = add; // assiging add's address to top 
			add->next = nullptr; // assiging the next element to nullptr 
			stack_size++;
		}
		else // top already exists, so add to the begining of the stack 
		{
			add->next = top; // linking previous element with new element 
			top = add;  // reassigning top
			stack_size++;
		}
	}
	void pop(T &popped) // deleting from the top of the stack 
	{
		stacks<T>* toDelete = top;
		if (top == nullptr) // if no stack then can't delete anything 
		{
			return;
		}
		else
		{
			top = toDelete->next; // shifting the top variable node to next in stack 
			popped = toDelete->data; // storing the value of the popped element into outside variable in main 
			delete toDelete; // deallocating memory address 
			stack_size--;
		}
	}
	bool empty()
	{
		if (top == nullptr)
		{
			return true;
		}
		else
			return false;
	}
	bool isBalanced(string expr)
	{
		stacks<char> c;
		char x = '!';
		for (int i = 0; i < expr.length(); i++) // iterating through entire expression
		{
			if (expr[i] == '(' || expr[i] == '[' || expr[i] == '{')
			{
				// Push the element in the stack 
				c.push(expr[i]);
				continue;
			}
			switch (expr[i])
			{
			case ')':

				// Store the top element in a 
				c.pop(x);
				if (x == '{' || x == '[' || x == '!')
					return false;
				break;

			case '}':

				// Store the top element in b 
				c.pop(x);
				if (x == '(' || x == '[' || x == '!')
					return false;
				break;

			case ']':

				// Store the top element in c 
				c.pop(x);
				if (x == '(' || x == '{' || x == '!')
					return false;
				break;
			}
		}
		// Check Empty Stack 
		return (c.empty());
	}
};
// credit to Fazal Mahmoud who helped me write the function . 
int solveEquation(string s)
{
	int val = 0; // returned value 
	int numofOpenParSeen = 0;
	int numOfClosedParSeen = 0;


	for (int k = 0; k < s.length(); k++) // traversing through the entire string 
	{
		if (isalpha(s[k])) // if a character 
		{
			if ((k == 0) || (s[k - 1] == '+')) // if the first character or the preceding character is a +
			{
				val += ((int)s[k] * (int)s[k]); // add to the total value the ascii value of the letter squared
			}
			else if (s[k - 1] == '-') // if preceding character is negative then subtract that number from total value 
			{
				val -= ((int)s[k] * (int)s[k]);
			}
		}

		else if (isdigit(s[k])) // if a number (should only be given numbers 0-9) Have to account for > 9?
		{
			if ((k == 0) || (s[k - 1] == '+')) // same as above
			{
				val += s[k] - 48; // we subtract 48 because complier automatically translates to ascii so we want to retain the true value
			}
			else if (s[k - 1] == '-')
			{
				val -= s[k] - 48;
			}
		}
		else if ((s[k] == '-') || (s[k] == '+')) // if the charcter is an operator, just skip it 
		{
			continue;
		}

		else if (((int)s[k] == 40) || ((int)s[k] == 91) || ((int)s[k] == 123)) // if we encounter any of the brackets
		{
			int i;
			string temp = "";
			numofOpenParSeen++;

			for (i = k + 1; i < s.length(); i++) // scan through the string starting after the brace enouncter 
			{
				if (((int)s[i] == 41) || ((int)s[i] == 93) || ((int)s[i] == 125)) // when we see a close parenthesis, assuming that the equation is balanced 
				{
					numOfClosedParSeen++;
					if (numOfClosedParSeen == numofOpenParSeen)
						break;
				}
				else if (((int)s[i] == 40) || ((int)s[i] == 91) || ((int)s[i] == 123)) // otherwise keep on counting open parenthesis
					numofOpenParSeen++;

				temp += s[i]; // add what's in the parenthesis to the temp holder variable
			}

			int temp2 = solveEquation(temp); // call the equation again with temp 

			if ((k == 0) || (s[k - 1] == '+'))
			{
				val += temp2;
			}
			else if (s[k - 1] == '-')
			{
				val -= temp2;
			}

			k = i; // make our main iterator equal where i left off to continue the process of evaluating the entire string 
		}
	}

	return val; // return the value of the entire expression 
}

int main(int argc, char * argv[])
{
	ArgumentManager am(argc, argv); // Argument manager constructor 
	string ipn = am.get("input"); // getting input file name 
	string opn = am.get("output"); // getting output file name 
	string input;
	fstream ifs(ipn);
	ofstream ofs(opn);
	int line_count = 0;
	int iterator = 0;;
	stacks<char> balance;
	bool balance_error = false; // used to make sure only one process is completed to save time, either checking similarity or validity 	 
	vector<int> value_holder; // creating vector to hold enough for max amount of expressions 
	while (getline(ifs, input))
	{
		if (input != "")
		{
			line_count++;
			if (!balance.isBalanced(input))
			{
				ofs << "Error at: " << line_count << endl;
				balance_error = true;
			}
			else if (balance.isBalanced(input) && !balance_error) // evaluate the expression and sotre value into vector 
			{
				value_holder.push_back(solveEquation(input));
			}
		}
	}
	if (balance_error) // if there were balancing errors then just exit program 
	{
		return 0;
	}
	else // if not then..
	{
		cout << "size of vector before shrink to fit: " << value_holder.size() << endl;
		value_holder.shrink_to_fit();
		cout << "size of vector after shrink to fit: " << value_holder.size() << endl;
		int compare = value_holder[0];
		for (int i = 1; i < value_holder.capacity(); i++)
		{
			if (compare != value_holder[i]) // if non matching value found it will record NO to output file and then exit the program
			{
				ofs << "No" << endl;
				return 0;
			}
		}
		// if the entire for loop goes and the if statement is not triggered then all equations similar and Yes will be printed 
		ofs << "Yes" << endl;
		return 0;
	}

}




