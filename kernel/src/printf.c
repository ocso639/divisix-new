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

static bool print(char *dest, const char *src, size_t length) {
    char *ptr = dest + strlen(dest);

	for (size_t i = 0; i < length; i++)
		*ptr++ = *src++;

	*ptr = 0;

	return true;
}

int vsprintf(char *str, const char* restrict fmt, va_list params) {
    int written = 0;
    int min_digits = 0;

    while (*fmt) {
        size_t maxleft = INT32_MAX - written;

        if (fmt[0] != '%' || fmt[1] != '%') {
            if (fmt[0] == '%')
                fmt++;
            size_t amount = 1;

            while (fmt[amount] && fmt[amount] != '%')
                amount++;
             
            if (maxleft < amount) {
                return -1;
            }

            if (!print(str, fmt, amount))
                return -1;
            
            fmt += amount;
            written += amount;
            continue;
        }
        
        const char *format_began_at = fmt++;
        size_t len;

        switch (*fmt) {
            case 'c': 
                fmt++;
                char c = (char) va_arg(params, int);

                if (!maxleft) {
                    return -1;
                } 

                if (!print(str, &c, sizeof(c)))
                    return -1;

                written++;
                break;
            case 'd':
                fmt++;
                const int num = va_arg(params, int);
                char *d_str = itoa(num * ((num > 0) - (num < 0)), 10, min_digits);
                len = strlen(d_str);

                if (maxleft < len) {
                    return -1;
                }

                if (num < 0) {
                    written++;
                    char neg = '-';
                    if (!print(str, &neg, sizeof(neg)))
                        return -1;
                }

                if (!print(str, d_str, len))
                    return -1;
                
                written += len;
                break;
            case 's':
                fmt++;
                const char* s_str = va_arg(params, const char*);
                len = strlen(s_str);

                if (maxleft < len) {
                    return -1;
                }

                if (!print(str, s_str, len))
                    return -1;

                written += len;
                break;
            case 'l':
                fmt++;
                const uint64_t num_hex_64 = va_arg(params, uint64_t);
				char *x_str_64 = itoa(num_hex_64, 16, min_digits);
                len = strlen(x_str_64);

                if (maxleft < len) {
                    return -1;
                }

                if (!print(str, "0x", sizeof("0x") - 1))
					return -1;

				if (!print(str, x_str_64, len))
					return -1;

				written += len + 2;
                break;
            case 'x':
                fmt++;
				const uint32_t num_hex = va_arg(params, uint32_t);
				char *x_str = itoa(num_hex, 16, min_digits);
				len = strlen(x_str);

				if (maxleft < len) {
					// TODO set errno to EOVERFLOW
					return -1;
				}

				if (!print(str, "0x", sizeof("0x") - 1))
					return -1;

				if (!print(str, x_str, len))
					return -1;

				written += len + 2;
				break;
            default:
                if (*fmt >= '0' && *fmt <= '9') {
                    fmt++;
                    min_digits *= 10;
                    min_digits += *fmt - '0';

                    written++;
                    break;
                }
                fmt = format_began_at;
                len = strlen(fmt);
                
                if (maxleft < len) {
                    return -1;
                }

                if (!print(str, fmt, len))
                    return -1;

                written += len;
                fmt += len;
        }
    }
    return written;
}

int vprintf(const char* restrict fmt, va_list params) {
    char *str;
    memset(str, 0, 256);
    int ret = vsprintf(str, fmt, params);

    while (*str) {
        kputc(*str++);}

    return ret;
}

int printf(const char* restrict fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}