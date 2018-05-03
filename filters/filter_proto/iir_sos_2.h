/*
 * Copyright (c) 2018 Kiss Adam <email>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

//You must not use any kind of include guard

#include <stddef.h>

namespace __COEFF_NAMESPACE__ {
  #include COEFF_H_PATH //MUST BE Direct-Form II structured second-order sections
  const size_t lMWSPT_NSEC = MWSPT_NSEC;
  #undef MWSPT
};

#pragma GCC diagnostic push
#pragma GCC diagnostic error "-Wconversion"


#include "../../siso.h"

//TODO formula to calculate delayers
#define NUM_OF_DELAYERS 100


#include <array>

template <typename input_type, typename storagetype>

//TODO Check the matlab generated header file for typematch with storagetype, or at least compatibility

class FILTER_NAME : siso<input_type, storagetype>
{
public:    
    virtual void put(const input_type& sample) override;
    virtual const storagetype& pull() override;
    
    FILTER_NAME();
    
    ~FILTER_NAME() = default;
    
private:
    std::array<storagetype, NUM_OF_DELAYERS> delayers;
    storagetype out;
};

template<typename input_type, typename storagetype> const storagetype& FILTER_NAME<input_type, storagetype>::pull()
{
    return out;
}

template<typename input_type, typename storagetype> FILTER_NAME<input_type, storagetype>::FILTER_NAME()
{
    delayers.fill(0);
    out = 0;
}

template<typename input_type, typename storagetype> void FILTER_NAME<input_type, storagetype>::put(const input_type& sample)
//TODO optimeze forever
//TODO optimize
//TODO optiimize
//TODO optiimize
//TODO optiimize
//TODO optiimize
//TODO optiimize
//TODO optiimize
//TODO optiimize
//TODO optiimize
//TODO optiimize
{
    storagetype last_sos_out = sample;
    
    size_t d_index_offset = 0;
    
    for(size_t i=0; i < __COEFF_NAMESPACE__::lMWSPT_NSEC; i++){
        storagetype feedback_sum = last_sos_out;
        storagetype out_sum      = 0;
        
        //calculate the feedback and the output
        for(size_t j=1; j < __COEFF_NAMESPACE__::NL[i]; j++){
            feedback_sum += delayers[d_index_offset + j - 1] * __COEFF_NAMESPACE__::DEN[i][j];
            out_sum      += delayers[d_index_offset + j - 1] * __COEFF_NAMESPACE__::NUM[i][j];
        }
       
        feedback_sum *= __COEFF_NAMESPACE__::DEN[i][0];
        out_sum      += feedback_sum * __COEFF_NAMESPACE__::NUM[i][0];
        
        //update delayers
        for(size_t j = (size_t) __COEFF_NAMESPACE__::NL[i]-1; j != 0; j--){ //TODO consider using http://www.boost.org/doc/libs/1_66_0/doc/html/circular_buffer.html
            delayers[d_index_offset + j] = delayers[d_index_offset + j - 1];
        }
        //if there is any delayer in this block, update the first
        //TODO no if ==> no branch predition ==> :-)
        if(__COEFF_NAMESPACE__::NL[i]-1)
            delayers[d_index_offset] = feedback_sum;
        
        
        last_sos_out = out_sum;
        d_index_offset+=(size_t) __COEFF_NAMESPACE__::NL[i]-1;
    }
    
    out = last_sos_out;
}




#pragma GCC diagnostic pop //end frame: "Error on WConversion warning"
