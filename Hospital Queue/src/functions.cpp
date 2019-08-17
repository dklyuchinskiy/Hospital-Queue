#include "Doctor.h"
#include "Libs.h"
#include "functions.h"


void CheckInput(vector<Doctor>& global_docs, vector<Patient>& global_pats)
{
	cout << global_docs.size() << endl;

	for (auto &x : global_docs)
		cout << "Doctor id = " << x.Id() << ". Work time = " << x.Wtime() << endl;

#if 1
	for (auto &x : global_pats)
	{
		cout << "Patient id = " << x.Id() << ". List of docs: ";
		for (auto &doc : x.ListOfDocs())
			cout << doc.first.Id() << " ";
		cout << endl;
	}
#endif
		
}

int CountPassedDocs(const vector<pair<Doctor, bool>>& vec)
{
	int docs = 0;
	for (auto& x : vec)
		if (x.second == true) docs++;

	return docs;
}

void CheckResults(vector<Doctor>& global_docs, vector<Patient>& global_pats)
{
#if 1
	for (auto &x : global_docs)
	{
		cout << "Doctor id = " << x.Id() << ". Patient id = " << x.PatId() << endl;
	}
	for (auto &x : global_pats)
	{
		cout << "Patient id = " << x.Id() << ". Full time = " << x.Full_time() << ". Doc time = " << x.Doc_time() << ". Wait time = " << x.Wait_time()
			<< ". Docs: " << x.DocsPassed() << " of " << x.ListOfDocs().size();

		if (x.FinishStatus() == true) cout << ". Finish time = " << x.Finish_time() << ". Bus_time = " << x.Bus_time() << endl;
		else cout << endl;
	}
#endif

}

void CheckListOfDocs(vector<Patient>& global_pats)
{
	for (auto& x : global_pats)
		if (x.DocsPassed() == x.ListOfDocs().size())
		{
			if (!x.FinishStatus()) x.SetFinishTime();
			x.SetCheckOut();
		}
}

#if 1
void AddTimer(vector<Doctor>& global_docs, vector<Patient>& global_pats)
{
	for (auto &doc : global_docs)
		doc.AddTimer();

	for (auto &pat : global_pats)
		pat.AddTimer();
}
#endif