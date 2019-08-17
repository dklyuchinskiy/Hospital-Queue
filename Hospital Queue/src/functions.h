#pragma once
#include "Doctor.h"
#include "Libs.h"

void AddTimer(vector<Doctor>& global_docs, vector<Patient>& global_pats);

void CheckInput(vector<Doctor>& global_docs, vector<Patient>& global_pats);

void CheckResults(vector<Doctor>& global_docs, vector<Patient>& global_pats);

void CheckListOfDocs(vector<Patient>& global_pats);
