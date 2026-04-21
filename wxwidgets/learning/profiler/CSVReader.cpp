#include "CSVReader.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

bool CSVReader::read(const std::string& filename, CSVData& data)
{
    std::ifstream file(filename);
    
    if(!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }
    
    data.clear();
    std::string line;
    int lineNum = 0;
    
    // Skip header line if present
    if(std::getline(file, line)) {
        lineNum++;
        // Check if this looks like a header (contains non-numeric content in first field)
        auto parts = split(line, ',');
        if(!parts.empty()) {
            std::string firstField = trim(parts[0]);
            // If first field is not a number, skip it
            try {
                std::stoll(firstField);
            } catch(...) {
                // It's a header, skip it
                lineNum = 0;
            }
        }
    }
    
    // Reset to beginning if we didn't skip header
    if(lineNum == 0) {
        file.seekg(0);
    }
    
    // Read data lines
    while(std::getline(file, line)) {
        lineNum++;
        
        // Skip empty lines
        if(trim(line).empty()) continue;
        
        StateRecord record;
        if(parseLine(line, record)) {
            data.addRecord(record);
        } else {
            std::cerr << "Warning: Failed to parse line " << lineNum << ": " << line << std::endl;
        }
    }
    
    file.close();
    
    if(data.getRecordCount() == 0) {
        std::cerr << "Warning: No valid records found in CSV" << std::endl;
        return false;
    }
    
    std::cout << "Successfully loaded " << data.getRecordCount() << " records from " << filename << std::endl;
    return true;
}

bool CSVReader::parseLine(const std::string& line, StateRecord& record)
{
    auto parts = split(line, ',');
    
    // Minimum required fields: timestamp, state, duration
    if(parts.size() < 3) {
        return false;
    }
    
    try {
        // Parse timestamp
        record.timestamp = std::stoll(trim(parts[0]));
        
        // Parse state
        record.state = std::stoi(trim(parts[1]));
        
        // Parse duration
        record.duration = std::stod(trim(parts[2]));
        
        // Parse state name (optional)
        if(parts.size() > 3) {
            record.stateName = trim(parts[3]);
            // Remove quotes if present
            if(!record.stateName.empty() && record.stateName.front() == '"') {
                record.stateName = record.stateName.substr(1);
            }
            if(!record.stateName.empty() && record.stateName.back() == '"') {
                record.stateName.pop_back();
            }
        } else {
            record.stateName = "State " + std::to_string(record.state);
        }
        
        // Parse color (optional)
        if(parts.size() > 4) {
            record.color = trim(parts[4]);
            // Remove quotes if present
            if(!record.color.empty() && record.color.front() == '"') {
                record.color = record.color.substr(1);
            }
            if(!record.color.empty() && record.color.back() == '"') {
                record.color.pop_back();
            }
        } else {
            // Default color scheme
            const std::string colors[] = {
                "#CCCCCC", "#FF6B6B", "#4ECDC4", "#45B7D1",
                "#FFA07A", "#98D8C8", "#F7DC6F", "#BB8FCE"
            };
            record.color = colors[record.state % 8];
        }
        
        return true;
    } catch(...) {
        return false;
    }
}

std::string CSVReader::trim(const std::string& str)
{
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");
    
    if(start == std::string::npos) {
        return "";
    }
    
    return str.substr(start, end - start + 1);
}

std::vector<std::string> CSVReader::split(const std::string& str, char delimiter)
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    
    while(std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}
