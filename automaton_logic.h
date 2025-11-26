#pragma once
// ========================================
// AUTOMATON LOGIC - MAIN INTERFACE
// ========================================

#include <string>

// Forward declarations for report structures
namespace GenoSearchEngine {
    struct SimulationReport {
        std::string summary;
        std::string grammar;
        std::string matches;
    };

    struct VisualizationData {
        std::string nfaDot;
        std::string dfaDot;
        std::string pdaTrace;
    };

    // Main simulation functions
    void runBranch1_logic(
        const std::string& regex, const std::string& filepath,
        SimulationReport& out_report, VisualizationData& out_viz, std::string& out_error_msg);

    void runBranch2A_logic(
        const std::string& pattern, int k, const std::string& filepath,
        SimulationReport& out_report, VisualizationData& out_viz, std::string& out_error_msg);

    void runBranch2B_logic(
        const std::string& input, bool isFile,
        SimulationReport& out_report, VisualizationData& out_viz, std::string& out_error_msg);

    // Utility functions
    bool GenerateGraphvizImage(const std::string& dot_string, const std::string& image_path,
        std::string& out_error_message, std::string& out_fallback_text);

} // namespace GenoSearchEngine