/*
 * This source file is part of the Swift.org open source project
 *
 * Copyright (c) 2015 Apple Inc. and the Swift project authors
 *
 * Licensed under Apache License v2.0 with Runtime Library Exception
 *
 * See http://swift.org/LICENSE.txt for license information
 * See http://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
 *
 */

#ifndef __OS_LINUX_BASE__
#define __OS_LINUX_BASE__

// #include <sys/event.h>
#include <sys/user.h>

// marker for hacks we have made to make progress
#define __LINUX_PORT_HDD__ 1

/*
 * Stub out defines for some mach types and related macros
 */

typedef uint32_t mach_port_t;

#define  MACH_PORT_NULL (0)
#define  MACH_PORT_DEAD (-1)

#define EVFILT_MACHPORT (-8)

typedef uint32_t mach_error_t;

typedef uint32_t mach_vm_size_t;

typedef uint32_t mach_msg_return_t;

typedef uintptr_t mach_vm_address_t;

typedef uint32_t dispatch_mach_msg_t;

typedef uint32_t dispatch_mach_t;

typedef uint32_t dispatch_mach_reason_t;

typedef uint32_t voucher_activity_mode_t;

typedef uint32_t voucher_activity_trace_id_t;

typedef uint32_t voucher_activity_id_t;

typedef uint32_t _voucher_activity_buffer_hook_t;;

typedef uint32_t voucher_activity_flag_t;

typedef struct
{
} mach_msg_header_t;


typedef void (*dispatch_mach_handler_function_t)(void*, dispatch_mach_reason_t,
						 dispatch_mach_msg_t, mach_error_t);

typedef void (*dispatch_mach_msg_destructor_t)(void*);

// Print a warning when an unported code path executes.
#define LINUX_PORT_ERROR()  do { printf("LINUX_PORT_ERROR_CALLED %s:%d: %s\n",__FILE__,__LINE__,__FUNCTION__); } while (0)

/*
 * Stub out defines for other missing types
 */

#if __linux__
// we fall back to use kevent
#define kevent64_s kevent
#define kevent64(kq,cl,nc,el,ne,f,to)  kevent(kq,cl,nc,el,ne,to)
#endif

// SIZE_T_MAX should not be hardcoded like this here.
#define SIZE_T_MAX (0x7fffffff)

// Define to 0 the NOTE_ values that are not present on Linux.
// Revisit this...would it be better to ifdef out the uses instead??

// The following values are passed as part of the EVFILT_TIMER requests

#define IGNORE_KEVENT64_EXT   /* will force the kevent64_s.ext[] to not be used -> leeway ignored */

#define NOTE_SECONDS	0x01
#define NOTE_USECONDS	0x02
#define NOTE_NSECONDS	0x04
#define NOTE_ABSOLUTE	0x08
#define NOTE_CRITICAL	0x10
#define NOTE_BACKGROUND	0x20
#define NOTE_LEEWAY	0x40

// need to catch the following usage if it happens ..
// we simply return '0' as a value probably not correct

#define NOTE_VM_PRESSURE ({LINUX_PORT_ERROR(); 0;})

/*
 * Stub out misc linking and compilation attributes
 */

#ifdef OS_EXPORT
#undef OS_EXPORT
#endif
#define OS_EXPORT

#ifdef OS_WARN_RESULT_NEEDS_RELEASE
#undef OS_WARN_RESULT_NEEDS_RELEASE
#endif

#ifdef OS_WARN_RESULT
#undef OS_WARN_RESULT
#endif
#define OS_WARN_RESULT

#ifdef OS_NOTHROW
#undef OS_NOTHROW
#endif
#define OS_NOTHROW


// These and similar macros come from Availabilty.h on OS X
// Need a better way to do this long term.
#define __OSX_AVAILABLE_BUT_DEPRECATED(a,b,c,d) //
#define __OSX_AVAILABLE_BUT_DEPRECATED_MSG(a,b,c,d,msg) //



#endif /* __OS_LINUX_BASE__ */
