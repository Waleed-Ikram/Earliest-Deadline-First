#include <iostream>
using namespace std;

class Process
{
public :

	int id;
	int exectime;
	int period;
};

int gcd(int a, int b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

typedef long long int ll;

ll findlcm(int arr[], int n)
{
	ll ans = arr[0];

	for (int i = 1; i < n; i++)
		ans = (((arr[i] * ans)) / (gcd(arr[i], ans)));

	return ans;
}

int Check_MinDeadline(int* deadline, bool* ready, int n)
{
	int min = 100000;
	int idx = 100;

	for (int i = 0; i < n; i++)
	{
		if (deadline[i] < min && ready[i] == true)
		{
			min = deadline[i];
			idx = i;
		}
	}

	return idx;
}


void EDF(Process* process, int n)
{
	//Declaration of arrays needed
	bool* ReadyProcess = new bool[n];
	int* curr_deadline = new int[n];
	int* RemainingTime = new int[n];
	int* ArrivalTime = new int[n];
	int current;

	//Initialization of arrays
	for (int i = 0; i < n; i++)
	{
		curr_deadline[i] = process[i].period;
		RemainingTime[i] = process[i].exectime;
		ReadyProcess[i] = true;
		ArrivalTime[i] = 0;
	}

	//Finding Lcm of the deadlines 
	int LCM = findlcm(curr_deadline, n);

	//User Interface 
	cout << "\t\t\t\t\tGANTT CHART : EARLIEST DEADLINE FIRST\n";
	cout << "Number of Processes : " << n << "\n";
	cout << "Processes : ";
	for (int i = 0; i < n; i++)
	{
		cout << "P" << i + 1 << " ";
	}
	cout << "\nLCM : " << LCM;
	cout << "\n\n";

	//Main code where EDF is written and execution happens
	
	for (int t = 0; t < LCM; t++)
	{
		for (int i = 0; i < n; i++)
		{
			//Checks if a process is available again
			if (ArrivalTime[i] == t && ReadyProcess[i] == false)
			{
				ReadyProcess[i] = true;
			}

			//Checks if a process has missed its deadline
			if (curr_deadline[i] == t)
			{
				cout << "\nNot Schedulable since Process " << i + 1 << " missed its deadline and still had " << RemainingTime[i] << " seconds left.\n\n";
				return;
			}
		}
		
		//current process to be executed
		current = Check_MinDeadline(curr_deadline, ReadyProcess, n);

		//value for idle = 100
		if (current == 100)
			cout << "\tTime[" << t << "-" << t + 1 << "] : IDLE\n";
		else
		{
			//execution of process 
			--RemainingTime[current];
			cout << "\tTime[" << t << "-" << t+1 << "] : " << "P" << process[current].id << "\n";
			
			//check if process has been executed fully
			if (RemainingTime[current] == 0)
			{
				ArrivalTime[current] = curr_deadline[current];
				curr_deadline[current] += process[current].period;
				RemainingTime[current] = process[current].exectime;
				ReadyProcess[current] = false;
			}
		}
	}
	
	cout << "\n\n";
}


int main()
{

	cout << "Enter the number of Processes needed to schedule : ";
	int num_of_process;
	cin >> num_of_process;

	Process* process = new Process[num_of_process];

	cout << "\nFor each process enter its execution time and Period.\n";
	int exec = 0;
	int prd = 0;
	
	for (int i = 0; i < num_of_process; i++)
	{
		cout << "\nExecution Time of process " << i + 1 << " : ";
		cin >> exec;
		process[i].exectime = exec;

		cout << "\nPeriod of process " << i + 1 << " : ";
		cin >> prd;
		process[i].period = prd;

		process[i].id = i + 1;
	}

	cout << "\n\n";

	//CPU utilization code 
	float schedule = 0;
	for (int i = 0; i < num_of_process; i++)
	{
		schedule += process[i].exectime / process[i].period;
	}

	if (schedule >= 1)
		cout << "\nThe processes can not be scheduled by Earliest Deadline First algorithm.\n";
	else
		EDF(process, num_of_process);

	return 0;
}
