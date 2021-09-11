

#include "components/include/System_Overall.hpp"
#include "components/include/RPICam_Capture.hpp"

int main(int argc, char** argv )
{
 std::cout << " hello from m2ain! \n";

#ifdef UNIT_TEST_MODE
 std::cout << " WE ARE IN UNIT TEST\n";
 sleep(5);
 exit(-1);
#endif

#ifdef __ESP32__
 std::cout << " WE ARE DEFINED __ESP32__\n";
 sleep(5);
 exit(-1);
#endif

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
