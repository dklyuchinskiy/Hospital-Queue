#pragma once

#include "Libs.h"

class Doctor;

class Patient
{
public:
	Patient();
	Patient(int id_, const vector<pair<Doctor, bool>> &docs_);

	void AddTimer()
	{
		full_time++;

		if (end != true)
		{
			if (lock == true) doc_time++;
			else wait_time++;
		}
		else
		{
			bus_time++;
		}
	}
	void IncDocsPassed() { docs_passed++; };
	void SetFinishTime() { finish_time = full_time; };
	void SetCheckOut() { end = true; };
	void SetLock() { lock = true; };
	void FreeLock() { lock = false; };
	int Id() { return id; };
	int Wait_time() { return wait_time; };
	int Doc_time() { return doc_time; };
	int Full_time() { return full_time; };
	int Bus_time() { return bus_time; };
	int Finish_time() { return finish_time; };
	int DocsPassed() { return docs_passed; };
	vector<pair<Doctor, bool>>& ListOfDocs() { return docs; };
	bool LockStatus() { return lock; };
	bool FinishStatus() { return end; };

private:
	int id = -1;
	int wait_time = 0;
	int doc_time = 0;
	int full_time = 0;
	int finish_time = 0;
	int bus_time = 0;
	int docs_passed = 0;
	vector<pair<Doctor, bool>> docs;
	bool lock = false;
	bool end = false;
};