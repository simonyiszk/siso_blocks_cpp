/********************************************************
 * 
 * My awesome and so disgusting Filter Factory
 * 
 * Kiss Adam 2018
 * 
 *******************************************************/

/*
 *  Reason:
 *
 *  Matlab exports filter coeffitients to C header files.
 *  If you want to create a filter (which structure is defined in a class)
 *  you create an instance of the class having the necessary coeffitients.
 * 
 *  Modes of giving the coeffitients to the class:
 *     1. Giving it as a constructor argument, and code general classses for every filter structure.
 *     2. Hardcode the coeffitients to a class.
 *     3. Use this filter factory, and do preprocessor metaprogramming :D
 *     4. Using a well constructed build system.
 * 
 *  Discussing the possibilities mentioned before:
 *  
 *     1. It is far not an optimal solution. The compiler cannot (in general) unroll loops, optimize out branches...
 *        You can save memory, but the computing performance is horrible. Anyway you will have every structure once
 *        in your codebase.
 *     2. Best performance, fully optimized code (in compile time), but with lots of code duplications.
 *     3. Get the advantages of the other ones, and forgot the disadvantages. The problem is that navigation in your
 *        IDE will probably be impossibe
 * 
 */

/*
 * Usage:
 * 
 *   1. Create a file for your filter (You will be able to reate multiply instances from it)
 *   2. Define the name of your filter to FILTER_NAME with #define directive
 *   3. Define the structure of you filter with #define directive (see the example below)
 *   4. Define the path and the name of the Matlab generated header file to COEFF_H_PATH with #define directive
 *   5. Include this file
 * 
 *   Note: You must not undef the vars mentioned above, this header does the work!
 * 
 *   Available filter types:
 *     *IIR_SOS_2 -- Secund order blocks in Direct form II -- filter_proto/iir_sos_2.h
 *     *FIR       -- Simple FIR filter                     -- filter_proto/fir.h
 * 
 */

/*
 * Example filter header file:
 * 
 * #define FILTER_NAME high_filter
 * #define FIR //Type of the filter is FIR
 * #define COEFF_H_PATH "high_filter_coeff.h"
 * #include "filter_factory.h"
 * 
 * //This creates class high_filter<typename input_type, typename output_type> : siso<...>
 * //
 * // Which implements a FIR filter. The functions used in this class can be found in
 * // filter_proto/fir.h
 * // The necessary coeffitients can be found in ./high_filter_coeff.h
 * 
 */

//-------------END OF DOC---------------//

#ifndef FILTER_NAME
    #error "FilterFactory:  You have not specified the name for the filter"
#endif

#ifndef COEFF_H_PATH
    #error "FilterFactory:  You have not specified coeffitient information for the filter " ## FILTER_NAME
#endif

#define PP_STR_CONCAT(a,b) a##b
#define __COEFF_NAMESPACE__ PP_STR_CONCAT(FILTER_NAME, __NAMESPACE__)

#if defined FIR
    #include "filter_proto/fir_filter.h"
    #undef FILTER_NAME
    #undef COEFF_H_PATH
    #undef __COEFF_NAMESPACE__ 
    #undef FIR
#elif defined IIR_SOS_2
    #include "filter_proto/iir_sos_2.h"
    #undef FILTER_NAME
    #undef COEFF_H_PATH
    #undef __COEFF_NAMESPACE__ 
    #undef IIR_SOS_2
#else
    #undef FILTER_NAME
    #undef COEFF_H_PATH
    #undef __COEFF_NAMESPACE__ 
    #error "FilterFactory:  filter type not supported or filter type not defined!"
#endif
