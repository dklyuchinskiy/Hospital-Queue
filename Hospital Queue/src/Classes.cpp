#include "Doctor.h"

// Patient

Patient::Patient() : id(0), wait_time(0), doc_time(0), full_time(0), finish_time(0), bus_time(0), docs_passed(0), lock(false), end(false) { };
Patient::Patient(int id_, const vector<pair<Doctor, bool>> &docs_) : id(id_), docs(docs_) {};

// Doctor

Doctor::Doctor() : id(0), wtime(0) { };
Doctor::Doctor(int id_) : id(id_), wtime(0) { };
Doctor::Doctor(int id_, int wtime_) : id(id_), wtime(wtime_) { };