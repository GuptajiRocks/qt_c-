#pragma once
#include <vector>
#include <string>

/**
 * Represents a single state transition record from CSV
 */
struct StateRecord {
    long long timestamp;  // Unix timestamp or milliseconds
    int state;            // State index (0-6 or custom)
    double duration;      // Duration in this state (seconds)
    std::string stateName; // Human-readable state name
    std::string color;    // Hex color for this state (e.g., "#FF0000")
};

/**
 * Container for all parsed CSV data
 */
class CSVData {
public:
    CSVData() = default;
    
    void addRecord(const StateRecord& record) {
        records.push_back(record);
    }
    
    const std::vector<StateRecord>& getRecords() const {
        return records;
    }
    
    StateRecord* findRecordByState(int state) {
        for(auto& record : records) {
            if(record.state == state) {
                return &record;
            }
        }
        return nullptr;
    }
    
    size_t getRecordCount() const {
        return records.size();
    }
    
    void clear() {
        records.clear();
    }
    
    long long getMinTimestamp() const {
        if(records.empty()) return 0;
        long long min = records[0].timestamp;
        for(const auto& r : records) {
            if(r.timestamp < min) min = r.timestamp;
        }
        return min;
    }
    
    long long getMaxTimestamp() const {
        if(records.empty()) return 0;
        long long max = records[0].timestamp;
        for(const auto& r : records) {
            if(r.timestamp > max) max = r.timestamp;
        }
        return max;
    }
    
private:
    std::vector<StateRecord> records;
};
