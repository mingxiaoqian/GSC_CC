#define LVS_COLOR_BLACK                           0    /*黑                     两者均可*/
#define LVS_COLOR_BLUE                            1    /*兰                     两者均可*/
#define LVS_COLOR_GREEN                           2    /*绿                     两者均可*/
#define LVS_COLOR_CYAN                            3    /*青                     两者均可*/
#define LVS_COLOR_RED                             4    /*红                     两者均可*/
#define LVS_COLOR_MAGENTA                         5    /*洋红               两者均可*/
#define LVS_COLOR_BROWN                           6    /*棕                     两者均可*/
#define LVS_COLOR_LIGHTGRAY                       7    /*淡灰               两者均可*/
#define LVS_COLOR_DARKGRAY                        8    /*深灰               只用于字符*/
#define LVS_COLOR_LIGHTBLUE                       9    /*淡兰               只用于字符*/
#define LVS_COLOR_LIGHTGREEN                     10    /*淡绿               只用于字符*/
#define LVS_COLOR_LIGHTCYAN                      11    /*淡青               只用于字符*/
#define LVS_COLOR_LIGHTRED                       12    /*淡红               只用于字符*/
#define LVS_COLOR_LIGHTMAGENTA                   13    /*淡洋红         只用于字符*/
#define LVS_COLOR_YELLOW                         14    /*黄                     只用于字符*/
#define LVS_COLOR_WHITE                          15    /*白                     只用于字符*/
#define LVS_COLOR_BLINK                         128    /*闪烁               只用于字符*/

void set_console_color(unsigned short color_index);