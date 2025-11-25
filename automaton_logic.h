#ifndef AUTOMATON_LOGIC_H
#define AUTOMATON_LOGIC_H

#include <string>
#include <memory>
#include <utility>
#include <vector>
#include "Automaton.h"

namespace GenoSearchEngine {

    // Simulation report structure
    struct SimulationReport {
        std::string summary;
        std::string grammar;
        std::string matches;
    };

    // Visualization data structure
    struct VisualizationData {
        std::string nfaDot;
        std::string dfaDot;
        std::string pdaTrace;
        std::string fallbackText;
    };

    // Branch 1: Regex Engine
    void runBranch1_logic(
        const std::string& regex, const std::string& filepath,
        SimulationReport& out_report, VisualizationData& out_viz, std::string& out_error_msg);

    // Branch 2A: Approximate Matching
    void runBranch2A_logic(
        const std::string& pattern, int k, const std::string& filepath,
        SimulationReport& out_report, VisualizationData& out_viz, std::string& out_error_msg);

    // Branch 2B: Formal PDA
    void runBranch2B_logic(
        const std::string& input, bool isFile,
        SimulationReport& out_report, VisualizationData& out_viz, std::string& out_error_msg);

    // Graphviz generation
    bool GenerateGraphvizImage(const std::string& dot_string, const std::string& image_path,
        std::string& out_error_message, std::string& out_fallback_text);

} // namespace GenoSearchEngine

#endif // AUTOMATON_LOGIC_H