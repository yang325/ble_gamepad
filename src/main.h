#ifndef __MAIN_H_
#define __MAIN_H_

#define LOG_COLOR_DEFAULT      "\x1B[0m"
#define LOG_COLOR_BLACK        "\x1B[1;30m"
#define LOG_COLOR_RED          "\x1B[1;31m"
#define LOG_COLOR_GREEN        "\x1B[1;32m"
#define LOG_COLOR_YELLOW       "\x1B[1;33m"
#define LOG_COLOR_BLUE         "\x1B[1;34m"
#define LOG_COLOR_MAGENTA      "\x1B[1;35m"
#define LOG_COLOR_CYAN         "\x1B[1;36m"
#define LOG_COLOR_WHITE        "\x1B[1;37m"

#define LOG_ERROR(_fmt_, ...)                       printk(LOG_COLOR_RED "[E] " _fmt_ "\n", ##__VA_ARGS__)
#define LOG_WARNING(_fmt_, ...)                     printk(LOG_COLOR_YELLOW "[W] " _fmt_ "\n", ##__VA_ARGS__)
#define LOG_INFO(_fmt_, ...)                        printk(LOG_COLOR_BLUE "[I] " _fmt_ "\n", ##__VA_ARGS__)
#define LOG_DEBUG(_fmt_, ...)                       printk(LOG_COLOR_DEFAULT "[D] " _fmt_ "\n", ##__VA_ARGS__)

#endif