/*
 * automaton_logic.h (Corrected)
 * The public "menu" for your C++ engine.
 * MyForm.h will include this file to call these functions.
 */

#pragma once

#include <string>
#include <utility> // For std::pair
#include <vector>

 // We wrap our C++ engine in a namespace
 // to keep it separate from the GUI code.
namespace GenoSearchEngine {

    // This struct will hold all the results
    struct SimulationReport {
        std::string summary;
        std::string grammar;
        std::string matches;
    };

    // This struct will hold all the visualization data
    struct VisualizationData {
        std::string nfaDot;
        std::string dfaDot;
        std::string pdaTrace;
        std::string fallbackText;
    };


    // This is the function for Branch 1
    void runBranch1_logic(
        const std::string& regex,
        const std::string& filepath,
        SimulationReport& out_report,      // Output
        VisualizationData& out_viz,       // Output
        std::string& out_error_msg        // Output
    );

    // This is the function for Branch 2A
    void runBranch2A_logic(
        const std::string& pattern,
        int k,
        const std::string& filepath,
        SimulationReport& out_report,      // Output
        VisualizationData& out_viz,       // Output
        std::string& out_error_msg        // Output
    );

    // This is the function for Branch 2B
    void runBranch2B_logic(
        const std::string& input,
        bool isFile,
        SimulationReport& out_report,      // Output
        VisualizationData& out_viz,       // Output
        std::string& out_error_msg        // Output
    );

    // This function generates the Graphviz .png file
    // It returns true on success, false on failure
    bool GenerateGraphvizImage(
        const std::string& dot_string,
        const std::string& image_path,
        std::string& out_error_message,    // Output
        std::string& out_fallback_text     // Output
    );

} // End namespace GenoSearchEngine