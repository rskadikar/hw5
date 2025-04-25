#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool hitLimit(
    const size_t maxShifts,
    DailySchedule& sched,
    Worker_T id);
bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    int day, int pos);


// Add your implementation of schedule() and other helper functions here
/**
 * @brief Produces a work schedule given worker availability,
 *        the number of needed workers per day, and the maximum
 *        shifts any single worker is allowed. Returns true if
 *        and the valid schedule if a solution exists, and false
 *        otherwise.
 *
 * @param [in]  avail n x k vector of vectors (i.e. matrix) of the availability
 *                    of the k workers for each of the n days
 * @param [in]  dailyNeed Number of workers needed per day (aka d)
 * @param [in]  maxShifts Maximum shifts any worker is allowed over
 *                        the n day period (aka m)
 * @param [out] sched n x d vector of vectors indicating the d workers
 *                    who are scheduled to work on each of the n days
 * @return true if a solution exists; sched contains the solution
 * @return false if no solution exists; sched is undefined (can be anything)
 */
bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    sched.resize(avail.size(), vector<Worker_T>(dailyNeed, INVALID_ID));
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, 0, 0);
}

bool hitLimit(
    const size_t maxShifts,
    DailySchedule& sched,
    Worker_T id)
{
    size_t count = 0;
    for (size_t i = 0; i < sched.size(); i++) {
        for (size_t j = 0; j < sched[i].size(); j++) {
            if (sched[i][j] == id) {
                count++;
                if (count >= maxShifts) return true;
            }
        }
    }
    return false;
}

bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    int day, int pos)
{
    if (day == avail.size()) {
        return true;
    }
    if (pos == dailyNeed) {
        return scheduleHelper(avail, dailyNeed, maxShifts, sched, day + 1, 0);
    }
    for (Worker_T id = 0; id < avail[0].size(); id++) {
        if (avail[day][id] == 1 && !hitLimit(maxShifts, sched, id)) {
            sched[day][pos] = id;
            if (scheduleHelper(avail, dailyNeed, maxShifts, sched, day, pos + 1)) return true;
            else sched[day][pos] = INVALID_ID;
        }
    }
    return false;
}
