#pragma once
#include "CSVData.h"
#include <string>

/**
 * Reads and parses CSV files with state/timestamp data
 * 
 * Expected CSV format:
 * timestamp, state, duration, stateName, color
 * 1000, 0, 2.5, "Idle", "#CCCCCC"
 * 2500, 1, 1.2, "Processing", "#00FF00"
 * ...
 * 
 * Fields:
 * - timestamp: long long (Unix timestamp or milliseconds)
 * - state: int (0-7 or custom state index)
 * - duration: double (seconds spent in this state)
 * - stateName: string (display name for the state)
 * - color: string (hex color code like #FFFFFF)
 */
class CSVReader {
public:
    /**
     * Read CSV file and populate CSVData object
     * @param filename Path to CSV file
     * @param data Output CSVData object to populate
     * @return true if successful, false otherwise
     */
    static bool read(const std::string& filename, CSVData& data);
    
    /**
     * Parse a single CSV line
     * @param line Raw CSV line
     * @param record Output StateRecord
     * @return true if parsing successful
     */
    static bool parseLine(const std::string& line, StateRecord& record);
    
    /**
     * Trim whitespace from string
     */
    static std::string trim(const std::string& str);
    
    /**
     * Split string by delimiter
     */
    static std::vector<std::string> split(const std::string& str, char delimiter);
};
