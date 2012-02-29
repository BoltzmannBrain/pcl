/*
 * Software License Agreement (BSD License)
 *
 *  Point Cloud Library (PCL) - www.pointclouds.org
 *  Copyright (c) 2010-2011, Willow Garage, Inc.
 *
 *  All rights reserved. 
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef PCL_FEATURES_QUANTIZABLE_MODALITY
#define PCL_FEATURES_QUANTIZABLE_MODALITY

#include <vector>
#include "pcl/recognition/region_xy.h"
#include "pcl/recognition/sparse_quantized_multi_mod_template.h"

namespace pcl
{
  class MaskMap
  {
    public:
      MaskMap ();
      virtual ~MaskMap ();

      inline int 
      getWidth () const { return (width_); }
      
      inline int
      getHeight () const { return (height_); }
      
      inline unsigned char* 
      getData () { return (data_); }

      inline const unsigned char* 
      getData () const { return (data_); }

      inline unsigned char & 
      operator() (int x, int y) 
      { 
        return (data_[y*width_+x]); 
      }

      inline const unsigned char & 
      operator() (int x, int y) const
      { 
        return (data_[y*width_+x]); 
      }

      void 
      initialize (int width, int height);

      void 
      release ();

    private:
      unsigned char * data_;
      int width_;
      int height_;  
  };

  class QuantizedMap
  {
    public:

      QuantizedMap ();
      QuantizedMap (int width, int height);

      virtual ~QuantizedMap ();

      inline int
      getWidth () const { return (width_); }
      
      inline int
      getHeight () const { return (height_); }
      
      inline unsigned char*
      getData () { return (data_); }

      inline const unsigned char*
      getData () const { return (data_); }

      void 
      initialize (int width, int height);

      inline unsigned char & 
      operator() (int x, int y) 
      { 
        return (data_[y*width_+x]); 
      }

      inline const unsigned char & 
      operator() (int x, int y) const
      { 
        return (data_[y*width_+x]); 
      }

      static void
      spreadQuantizedMap (const QuantizedMap & input_map, QuantizedMap & output_map, int spreading_size);

    private:
      unsigned char * data_;
      int width_;
      int height_;  
    
  };

  class QuantizableModality
  {
    public:
      QuantizableModality ();
      virtual ~QuantizableModality ();

      //inline int getWidth () const { return width; }
      //inline int getHeight () const { return height; }

      //inline unsigned char & operator() (int x, int y) { return data[y*width+x]; }
      //inline const unsigned char & operator() (int x, int y) const { return data[y*width+x]; }

      virtual QuantizedMap &
      getQuantizedMap () = 0;

      virtual QuantizedMap &
      getSpreadedQuantizedMap () = 0;

      virtual void 
      extractFeatures (const MaskMap & mask, size_t nr_features, size_t modality_index, 
                       std::vector<QuantizedMultiModFeature> & features) = 0;

    private:
      //unsigned char * data_;
      //int width_;
      //int height_;  
  };
}

#endif    // PCL_FEATURES_QUANTIZABLE_MODALITY
