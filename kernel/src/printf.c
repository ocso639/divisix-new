#include "include/printf.h"

void koks(const char msg[]) {
    kputs("[ \e[0;92mOKAY\e[1;97m ] "); kputs(msg);
    return;
}

void kfails(const char msg[]) {
    kputs("[ \e[0;91mFAIL\e[1;97m ] "); kputs(msg);
    return;
}

void kinfos(const char msg[]) {
    kputs("[ \e[0;93mINFO\e[1;97m ] "); kputs(msg);
    return;
}

void kunimps(const char msg[]) {
    kputs("[ \e[0;37mUNIM\e[1;97m ] "); kputs(msg);
}

void printf(const char *fmt, ...) {
    va_list ap;
    int i, c;
    char *s;

    va_start(ap, fmt);
    for (i = 0; (c = fmt[i] & 0xff) != 0; i++) {
        if (c != '%') {
            kputc(c);
            continue;
        }
        c = fmt[++i] & 0xff;
        if (c == 0)
            break;
        switch(c) {
            case 'd': {
                itoa(va_arg(ap, int), 10, 1);
                break;
            }
            case 'x': {
                itoa(va_arg(ap, unsigned int), 16, 1);
                break;
            }
            case 'p': {
                //itoa(va_arg(ap, uint64_t), 16, 1);
                itoa(va_arg(ap, int), 16, 1);
                break;
            }
            case 's': {
                if ((s = va_arg(ap, char*)) == 0) 
                    s = "(null)";
                for (; *s; s++) 
                    kputc(*s);
                break;
            }
            case '%': {
                kputc('%');
                break;
            }
            default: {
                kputc('%');
                kputc(c);
                break;
            }
        }
        va_end(ap);
    }
}