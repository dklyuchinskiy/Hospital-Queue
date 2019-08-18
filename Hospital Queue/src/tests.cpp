#include "Libs.h"
#include "Doctor.h"
#include "functions.h"
#include "test_runner.h"
#include "tests.h"

void TestLoop(size_t FULL_TIME, vector<Doctor>& global_docs, vector<Patient>& global_pats)
{
#define DEBUG
#ifdef DEBUG
	CheckInput(global_docs, global_pats);
#endif

	for (size_t timer = 0; timer < FULL_TIME; timer++)
	{
		CheckListOfDocs(global_pats);

		for (auto& doc : global_docs)
			doc.Take(global_pats);

		AddTimer(global_docs, global_pats);

		for (auto& doc : global_docs)
			doc.Unlock();

#ifdef DEBUG
		CheckResults(global_docs, global_pats);
		system("pause");
#endif
	}
}

void TestOnePatient()
{
	int FULL_TIME = 37;
	int n_docs = 10;
	int n_pats = 1;
	vector<Doctor> global_docs;
	vector<pair <Doctor, bool> > global_bool_docs;
	vector<Patient> global_pats;
	int doc_full_time = 0;
	int doc_cur_time = 0;
	int doc_count = 0;

	for (int i = 0; i < n_docs; i++)
	{
		doc_cur_time = i / 2 + i % 2 + 1;
		doc_full_time += doc_cur_time;
		doc_count++;
		global_docs.push_back(Doctor{ i, doc_cur_time });
		global_bool_docs.push_back({ global_docs[i], false });
	}

	for (int i = 0; i < n_pats; i++)
	{
		global_pats.push_back(Patient{ i, i + 1, doc_count, global_bool_docs });
	}

	TestLoop(FULL_TIME, global_docs, global_pats);

	ASSERT_EQUAL(global_pats[0].DocsPassed(), global_pats[0].ListOfDocs().size());
	ASSERT_EQUAL(global_pats[0].Start_time(), 1);
	ASSERT_EQUAL(global_pats[0].Doc_time(), doc_full_time);
	ASSERT_EQUAL(global_pats[0].Finish_time(), doc_full_time + global_pats[0].Start_time());
	ASSERT_EQUAL(global_pats[0].FinishStatus(), true);
	ASSERT_EQUAL(global_pats[0].Bus_time(), global_pats[0].Full_time() - global_pats[0].Finish_time());
	ASSERT_EQUAL(global_pats[0].Wait_time(), 0);
	ASSERT_EQUAL(global_pats[0].Wait_time(), global_pats[0].Finish_time() - global_pats[0].Doc_time() - global_pats[0].Start_time());
}

#if 0
void TestEqualDocTime()
{
	int FULL_TIME = 21;
	int n_docs = 10;
	int n_pats = 10;
	vector<Doctor> global_docs;
	vector<pair <Doctor, bool> > global_bool_docs;
	vector<Patient> global_pats;
	int doc_full_time = 0;
	int doc_cur_time = 0;

	for (int i = 0; i < n_docs; i++)
	{
		doc_cur_time = 2;
		doc_full_time += doc_cur_time;
		global_docs.push_back(Doctor{ i, doc_cur_time });
		global_bool_docs.push_back({ global_docs[i], false });
	}

	for (int i = 0; i < n_pats; i++)
	{
		global_pats.push_back(Patient{ i, i + 1, global_bool_docs });
	}

	for (int timer = 0; timer < FULL_TIME; timer++)
	{
		CheckListOfDocs(global_pats);

		for (auto& doc : global_docs)
			doc.Take(global_pats);

		AddTimer(global_docs, global_pats);

		for (auto& doc : global_docs)
			doc.Unlock();

		CheckResults(global_docs, global_pats);
	}

	for (size_t i = 0; i < global_pats.size(); i++)
	{
		ASSERT_EQUAL(global_pats[i].DocsPassed(), global_pats[0].ListOfDocs().size());
		ASSERT_EQUAL(global_pats[i].Doc_time(), doc_full_time);
		ASSERT_EQUAL(global_pats[i].Finish_time(), doc_full_time);
		ASSERT_EQUAL(global_pats[i].FinishStatus(), true);
		ASSERT_EQUAL(global_pats[i].Bus_time(), global_pats[0].Full_time() - global_pats[0].Finish_time());
		ASSERT_EQUAL(global_pats[i].Wait_time(), 0);
		ASSERT_EQUAL(global_pats[i].Wait_time(), global_pats[0].Finish_time() - global_pats[0].Doc_time());
	}
}
#endif

void TestDifferentAmountOfDocs()
{
	int FULL_TIME = 37;
	int n_docs = 10;
	int n_pats = 1;
	vector<Doctor> global_docs;
	vector<pair <Doctor, bool> > global_bool_docs;
	vector<Patient> global_pats;
	vector<int> doc_count(n_pats);
	int doc_full_time = 0;
	int doc_cur_time = 0;

	for (int j = 0; j < n_pats; j++)
	{
		for (int i = 0; i < n_docs; i++)
		{
			doc_cur_time = i / 2 + i % 2 + 1;
			global_docs.push_back(Doctor{ i, doc_cur_time });
			global_bool_docs.push_back({ global_docs[i], false });
			if (i % 2 == 0) global_bool_docs[i].second = true;
			else
			{
				doc_full_time += doc_cur_time;
				doc_count[j]++;
			};
		}
	}

	for (int i = 0; i < n_pats; i++)
	{
		global_pats.push_back(Patient{ i, i + 1, doc_count[i], global_bool_docs });
	}

	TestLoop(FULL_TIME, global_docs, global_pats);

	ASSERT_EQUAL(global_pats[0].DocsPassed(), doc_count[0]);
	ASSERT_EQUAL(global_pats[0].Start_time(), 1);
	ASSERT_EQUAL(global_pats[0].Doc_time(), doc_full_time);
	ASSERT_EQUAL(global_pats[0].Finish_time(), doc_full_time + global_pats[0].Start_time());
	ASSERT_EQUAL(global_pats[0].FinishStatus(), true);
	ASSERT_EQUAL(global_pats[0].Bus_time(), global_pats[0].Full_time() - global_pats[0].Finish_time());
	ASSERT_EQUAL(global_pats[0].Wait_time(), 0);
	ASSERT_EQUAL(global_pats[0].Wait_time(), global_pats[0].Finish_time() - global_pats[0].Doc_time() - global_pats[0].Start_time());
}


void TestBasicEqualPatsAndDocs()
{
	int FULL_TIME = 100;
	int n_docs = 10;
	int n_pats = 10;
	vector<Doctor> global_docs;
	vector<pair <Doctor, bool> > global_bool_docs;
	vector<Patient> global_pats;
	int doc_count = 0;
	int doc_full_time = 0;
	int doc_cur_time = 0;

	for (int i = 0; i < n_docs; i++)
	{
		doc_cur_time = i / 2 + i % 2 + 1;
		global_docs.push_back(Doctor{ i, doc_cur_time });
		global_bool_docs.push_back({ global_docs[i], false });

		doc_full_time += doc_cur_time;
		doc_count++;
	}

	for (int i = 0; i < n_pats; i++)
	{
		global_pats.push_back(Patient{ i, i + 1, doc_count, global_bool_docs });
	}

	TestLoop(FULL_TIME, global_docs, global_pats);

	for (int i = 0; i < doc_count; i++)
	{
		ASSERT_EQUAL(global_pats[i].Start_time(), i + 1);
		ASSERT_EQUAL(global_pats[i].DocsPassed(), doc_count);
		ASSERT_EQUAL(global_pats[i].Doc_time(), doc_full_time);
		ASSERT_EQUAL(global_pats[i].Finish_time(), global_pats[i].Wait_time() + global_pats[i].Doc_time() + global_pats[i].Start_time());
		ASSERT_EQUAL(global_pats[i].FinishStatus(), true);
		ASSERT_EQUAL(global_pats[i].Bus_time(), global_pats[i].Full_time() - global_pats[i].Finish_time());
		ASSERT_EQUAL(global_pats[i].Wait_time(), global_pats[i].Finish_time() - global_pats[0].Doc_time() - global_pats[i].Start_time());
	}
}