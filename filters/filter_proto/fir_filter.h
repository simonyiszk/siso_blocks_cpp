
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

namespace __COEFF_NAMESPACE__ {
  #include COEFF_H_PATH //MUST BE Directform FIR topology
};


#pragma GCC diagnostic push
#pragma GCC diagnostic error "-Wconversion"

#include "../../siso.h"
#include <array>

template <typename input_type, typename storagetype>
class FILTER_NAME : siso<input_type, storagetype>
{    
public:    
    virtual void put(const input_type& sample) override;
    virtual const storagetype& pull() override;
    
    FILTER_NAME();
    //TODO delete copy constructor
    ~FILTER_NAME() = default;
    
private:
    std::array<storagetype, __COEFF_NAMESPACE__::BL> delayers;
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
{       
    storagetype out_sum = 0;
    
    //calculate the feedback and the output
    for(size_t j=0; j < __COEFF_NAMESPACE__::BL; j++){
        out_sum += delayers[j] * __COEFF_NAMESPACE__::B[j];
    }
    
    //update delayers
    for(size_t j = (size_t) __COEFF_NAMESPACE__::BL; j != 0; j--){ //TODO consider using http://www.boost.org/doc/libs/1_66_0/doc/html/circular_buffer.html
        //https://github.com/Quuxplusone/ring_view
        //https://www.reddit.com/r/cpp/comments/854mu9/2018_jacksonville_iso_c_committee_reddit_trip/
        delayers[j] = delayers[j - 1];
    }
    
    if(__COEFF_NAMESPACE__::BL)
        delayers[0] = sample;
    
    out = out_sum;
}


#pragma GCC diagnostic pop //end frame: "Error on WConversion warning"
