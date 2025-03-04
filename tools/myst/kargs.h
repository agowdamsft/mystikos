#ifndef _MYST_MYST_KARGS_H
#define _MYST_MYST_KARGS_H

#include <myst/kernel.h>

int init_kernel_args(
    myst_kernel_args_t* args,
    const char* target,
    int argc,
    const char* argv[],
    int envc,
    const char* envp[],
    const char* cwd,
    const char* hostname,
    const void* regions_end,
    const void* image_data,
    size_t image_size,
    size_t max_threads,
    bool trace_errors,
    bool trace_syscalls,
    bool export_ramfs,
    bool have_syscall_instruction,
    bool tee_debug_mode,
    uint64_t thread_event,
    long (*tcall)(long n, long params[6]),
    const char* rootfs,
    char* err,
    size_t err_size);

#endif /* _MYST_MYST_KARGS_H */
