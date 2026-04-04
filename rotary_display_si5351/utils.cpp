#include "utils.h"

// String formatInt(int a) {

//   String str = "";
  
//   if (a < 10) {
//     str = "00";  
//   } else if (a < 100) {
//     str = "0";   
//   }
  
//   str += String(a);
  
//   return str;
// }

String utils_draw_char_at(char c, int i){
  String str = "               ";
  str.setCharAt(i, c);
  return str;
}
