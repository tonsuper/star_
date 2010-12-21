#define HOST_IPAD1_1_4_2_1
#define TARGET_IPAD1_1_4_2_1
#define DEBUG 1
#define DEBUG_VERBOSE 1
#define DEBUG_VERY_VERBOSE 1
#define PUTC 1
#define HAVE_SERIAL 0

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <mach-o/loader.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <unistd.h>

#define stringify(line) #line
#define trace_(file, line) do { if(DEBUG_VERY_VERBOSE) serial_putstring("trace: " file ":" stringify(line) "\n"); } while(0)
#define trace trace_(__FILE__, __LINE__)

extern void IOLog(const char *, ...);
extern void IOSleep(unsigned int);

// stuff.c
extern void *map_from_iokit(const char *name);
#if DEBUG
// call this before clobbering the kernel kthx
extern int uart_set_rate(uint32_t rate);
extern void serial_putstring(const char *string);
extern void serial_puthexbuf(void *buf, uint32_t size);
extern void serial_puthex(uint32_t number);
extern bool serial_important;
#else
#define uart_set_rate(x)
#define serial_putstring(x)
#define serial_puthexbuf(x, y)
#define serial_puthex(x)
#endif
extern int my_strcmp(const char *a, const char *b);
extern int my_memcmp(const char *a, const char *b, size_t n);
extern size_t my_strlen(const char *a);
// {bcopy, bzero}.s
extern void *my_memcpy(void *dest, const void *src, size_t n);
extern void *my_memset(void *b, int c, size_t len);

extern void IOLog(const char *fmt, ...);

void *IOService_nameMatching(const char *buf, void *table)
asm("__ZN9IOService12nameMatchingEPKcP12OSDictionary");

void *IOService_getMatchingServices(void *matching)
asm("__ZN9IOService19getMatchingServicesEP12OSDictionary");

static inline void *OSIterator_getNextObject(void *iterator) {
    return ((void *(***)(void *)) iterator)[0][21](iterator);
}

void *IOService_mapDeviceMemoryWithIndex(void *service, unsigned int index, unsigned int options)
asm("__ZN9IOService24mapDeviceMemoryWithIndexEjm");
void *IOMemoryMap_getAddress(void *map)
asm("__ZN11IOMemoryMap10getAddressEv");
// These are actually virtual but I don't care
// this is the char * version
extern void *IORegistryEntry_getProperty(void *entry, const char *key) asm("__ZNK15IORegistryEntry11getPropertyEPKc");

extern void *OSMetaClassBase_safeMetaCast(void *obj, void *metaclass)
asm("__ZN15OSMetaClassBase12safeMetaCastEPKS_PK11OSMetaClass");

extern void *OSData_metaClass asm("__ZN6OSData9metaClassE");
extern void *OSData_getBytesNoCopy(void *data) asm("__ZNK6OSData14getBytesNoCopyEv");
extern unsigned int OSData_getLength(void *data) asm("__ZNK6OSData9getLengthEv");

extern void *OSNumber_metaClass asm("__ZN8OSNumber9metaClassE");
extern unsigned long long OSNumber_unsigned64BitValue(const void *number) asm("__ZNK8OSNumber18unsigned64BitValueEv");

#if !PUTC
extern void fancy_set_rate(uint32_t, uint32_t) asm("$_80_40_2d_e9_00_70_8d_e2_XX_XX_XX_XX_4b_0f_51_e3_96_1d_a0_33");
#endif

extern void *kalloc(uint32_t size);
extern void kfree(void *data, uint32_t size);
extern int copyin(const user_addr_t user_addr, void *kernel_addr, uint32_t nbytes);

// dt.c

typedef bool (^dt_iterate_cb)(const char *path, size_t path_len, char *entry);
void dt_iterate(char **dt, dt_iterate_cb callback);

typedef bool (^dt_prop_iterate_cb)(char *name, char *value, size_t value_len);
bool dt_prop_iterate(char **dt, dt_prop_iterate_cb callback);

char *dt_get_entry(char **dt, const char *desired);
bool dt_entry_set_prop(char *entry, const char *key, const char *replacement_key /* could be NULL */, const void *replacement_value, size_t replacement_value_len);
void dt_super_iterate(char **dt);
