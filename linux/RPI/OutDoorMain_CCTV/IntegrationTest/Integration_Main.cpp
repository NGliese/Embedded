/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <iostream>

#include "../LibraryModule-1.0-Source/Components/Objects/Timeservice/include/Timeservice.hpp"

#include "components/include/RPICam_Capture.hpp"
#include "components/include/System_Overall.hpp"

int main(int argc, char** argv)
{
#if 0 // TEST ENV
   RPICam_Capture m_sys;
   //m_sys.stream() ;
  // m_sys.capture_and_save();
   //m_sys.stream_vinfo();
 //  m_sys.segment_forground();
 //  m_sys.segment_forground_clean();
  // m_sys.segment_forground_clean_and_save();
 //  m_sys.segment_forground_clean_draw_Connected_Compoents_save();
//   m_sys.backgroundsubstractor_KNN_Save();
   m_sys.backgroundsubstractor_MOG2_Save();
  // m_sys.backgroundsubstractor_GMG_Save();
#endif
#if 1
	System_Overall m_sys;
	m_sys.run();
#endif
}
