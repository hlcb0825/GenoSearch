#pragma once
// ========================================
// AUTOMATON LOGIC - MAIN INTERFACE
// ========================================

#include <string>

namespace GenoSearchEngine {
    // Report structure matches the 3 UI tables
    struct SimulationReport {
        std::string summary; // Table 1
        std::string grammar; // Table 2 (Config)
        std::string matches; // Table 3 (Details/Trace)
    };

    struct VisualizationData {
        std::string nfaDot;
        std::string dfaDot;
		std::string pdaDot;
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