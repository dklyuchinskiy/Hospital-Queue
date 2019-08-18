#pragma once

#include "Libs.h"
#include "Patient.h"

class Doctor
{
public:
	Doctor();
	Doctor(int id);
	Doctor(int id_, int wtime_);

	void Take(vector<Patient>& pats)
	{
		if (lock == false)
		{
		    auto it = find_if(pats.begin(), pats.end(), [=](Patient& pat)
			{ return (pat.LockStatus() == false && pat.ListOfDocs()[id].second == false && pat.Full_time() >= pat.Start_time()); });

			if (it != pats.end())
			{
				cur_pat = it;
				pat_id = cur_pat->Id();
				Lock();
			}
			else
			{
				pat_id = -1;
			}
		}
	}

	void AddTimer()
	{
		if (lock == true)
		{
			cur_time++;
		}
	}

	void Lock()
	{
		if (cur_time == 0 && pat_id != -1)
		{
			lock = true;
			cur_pat->SetLock();
		}
	}

	void Unlock()
	{
		if (cur_time == wtime)
		{
			cur_pat->ListOfDocs()[id].second = true;
			cur_pat->IncDocsPassed();
			lock = false;
			cur_pat->FreeLock();
			cur_time = 0;
		}
	}

	int Id() { return id; };
	int Wtime() { return wtime; };
	int PatId() { return pat_id; };
	vector<Patient>::iterator& Pat() { return cur_pat; };
	bool LockStatus() { return lock; };

private:
	int id = -1;
	int pat_id = -1;
	int cur_time = 0;
	int wtime = 0;
	vector<Patient>::iterator cur_pat;
	bool lock = false;
};
