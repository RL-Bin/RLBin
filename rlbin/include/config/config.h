#ifndef _RLBIN_CONFIG_H
#define _RLBIN_CONFIG_H

/** @file config.h
    @brief Reads an initial config file and command line and create the final config file    
*/

/**
 * @brief The function that parses command line and config file
 * @param [in] argc the number of arguments passed to RLBin   
 * @param [in] argv the arguments passed to RL-Bin
 * @return The target and its arguments
 */
std::string ParseCLIConfig(int argc, char **argv);


#endif