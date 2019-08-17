#include <iostream>
#include "Libs.h"
#include "Doctor.h"
#include "functions.h"

#define FULL_TIME 65

int main()
{
	int n_docs = 10;
	int n_pats = 10;
	vector<Doctor> global_docs;
	vector<pair <Doctor, bool> > global_bool_docs;
	vector<Patient> global_pats;

#if 1
	for (int i = 0; i < n_docs; i++)
	{
		global_docs.push_back(Doctor{ i, i / 2 + i % 2 + 1 });
		global_bool_docs.push_back({ global_docs[i], false });
	}

	for (int i = 0; i < n_pats; i++)
	{
		global_pats.push_back(Patient{ i, global_bool_docs });
	}
#endif

	CheckInput(global_docs, global_pats);

	int timer = 0;

#if 1
	for(int timer = 0; timer < FULL_TIME; timer++)
	{
		CheckListOfDocs(global_pats);

		for (auto& doc : global_docs)
			doc.Take(global_pats);

		AddTimer(global_docs, global_pats);

		for (auto& doc : global_docs)
			doc.Unlock();		

		CheckResults(global_docs, global_pats);
		system("pause");
	}
#endif

	system("pause");
	return 0;
}