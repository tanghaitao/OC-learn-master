/*
 * Copyright (c) 2008-2013 Apple Inc. All rights reserved.
 *
 * @APPLE_APACHE_LICENSE_HEADER_START@
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @APPLE_APACHE_LICENSE_HEADER_END@
 */

/*
 * IMPORTANT: This header file describes INTERNAL interfaces to libdispatch
 * which are subject to change in future releases of Mac OS X. Any applications
 * relying on these interfaces WILL break.
 */

#ifndef __DISPATCH_OBJECT_INTERNAL__
#define __DISPATCH_OBJECT_INTERNAL__

#if !OS_OBJECT_USE_OBJC
#define OS_OBJECT_DECL(name)  DISPATCH_DECL(name)
#define OS_OBJECT_DECL_SUBCLASS(name, super)  DISPATCH_DECL(name)
#endif

#if USE_OBJC
#define OS_OBJECT_EXTRA_VTABLE_SYMBOL(name) _OS_##name##_vtable
#define DISPATCH_CLASS_SYMBOL(name) OS_dispatch_##name##_class
#define DISPATCH_CLASS_RAW_SYMBOL_NAME(name) \
		OS_OBJC_CLASS_RAW_SYMBOL_NAME(DISPATCH_CLASS(name))
#else
#define OS_OBJECT_CLASS_SYMBOL(name) _##name##_vtable
#define OS_OBJC_CLASS_RAW_SYMBOL_NAME(name) \
		"__" OS_STRINGIFY(name) "_vtable"
#define DISPATCH_CLASS_SYMBOL(name) _dispatch_##name##_vtable
#define DISPATCH_CLASS_RAW_SYMBOL_NAME(name) \
		"__dispatch_" OS_STRINGIFY(name) "_vtable"
#endif

#define DISPATCH_CLASS(name) OS_dispatch_##name
#if USE_OBJC
#define DISPATCH_OBJC_CLASS_DECL(name) \
		extern void *DISPATCH_CLASS_SYMBOL(name) \
				asm(DISPATCH_CLASS_RAW_SYMBOL_NAME(name))
#endif

// define a new proper class
#define OS_OBJECT_CLASS_DECL(name, super, ...) \
		struct name##_s; \
		struct name##_extra_vtable_s { \
			__VA_ARGS__; \
		}; \
		struct name##_vtable_s { \
			_OS_OBJECT_CLASS_HEADER(); \
			struct name##_extra_vtable_s _os_obj_vtable; \
		}; \
		OS_OBJECT_EXTRA_VTABLE_DECL(name, name) \
		extern const struct name##_vtable_s OS_OBJECT_CLASS_SYMBOL(name) \
				asm(OS_OBJC_CLASS_RAW_SYMBOL_NAME(OS_OBJECT_CLASS(name)))

#if OS_OBJECT_SWIFT3
#define OS_OBJECT_INTERNAL_CLASS_DECL(name, super, ...) \
		OS_OBJECT_OBJC_RUNTIME_VISIBLE \
		OS_OBJECT_DECL_IMPL_CLASS(name, OS_OBJECT_CLASS(super)); \
		OS_OBJECT_CLASS_DECL(name, super, ## __VA_ARGS__)
#elif OS_OBJECT_USE_OBJC
#define OS_OBJECT_INTERNAL_CLASS_DECL(name, super, ...) \
		OS_OBJECT_DECL(name); \
		OS_OBJECT_CLASS_DECL(name, super, ## __VA_ARGS__)
#else
#define OS_OBJECT_INTERNAL_CLASS_DECL(name, super, ...) \
		typedef struct name##_s *name##_t; \
		OS_OBJECT_CLASS_DECL(name, super, ## __VA_ARGS__)
#endif

#define DISPATCH_CLASS_DECL_BARE(name) \
		OS_OBJECT_CLASS_DECL(dispatch_##name, dispatch_object, \
				DISPATCH_OBJECT_VTABLE_HEADER(dispatch_##name))

#define DISPATCH_CLASS_DECL(name) \
		_OS_OBJECT_DECL_PROTOCOL(dispatch_##name, dispatch_object) \
		_OS_OBJECT_CLASS_IMPLEMENTS_PROTOCOL(dispatch_##name, dispatch_##name) \
		DISPATCH_CLASS_DECL_BARE(name)

#define DISPATCH_INTERNAL_CLASS_DECL(name) \
		DISPATCH_DECL(dispatch_##name); \
		DISPATCH_CLASS_DECL(name)

// define a new subclass used in a cluster
#define OS_OBJECT_SUBCLASS_DECL(name, super) \
		_OS_OBJECT_DECL_SUBCLASS_INTERFACE(name, super) \
		struct name##_s; \
		OS_OBJECT_EXTRA_VTABLE_DECL(name, super) \
		extern const struct super##_vtable_s OS_OBJECT_CLASS_SYMBOL(name) \
				asm(OS_OBJC_CLASS_RAW_SYMBOL_NAME(OS_OBJECT_CLASS(name)))

#define DISPATCH_SUBCLASS_DECL(name, super) \
		OS_OBJECT_SUBCLASS_DECL(dispatch_##name, super)

#if OS_OBJECT_SWIFT3
// define a new internal subclass used in a class cluster
#define OS_OBJECT_INTERNAL_SUBCLASS_DECL(name, super) \
		_OS_OBJECT_DECL_PROTOCOL(name, super); \
		OS_OBJECT_SUBCLASS_DECL(name, super)

#define DISPATCH_INTERNAL_SUBCLASS_DECL(name, super) \
		_OS_OBJECT_DECL_PROTOCOL(dispatch_##name, dispatch_##super) \
		DISPATCH_SUBCLASS_DECL(name, dispatch_##super)
#else
// define a new internal subclass used in a class cluster
#define OS_OBJECT_INTERNAL_SUBCLASS_DECL(name, super) \
		OS_OBJECT_DECL_SUBCLASS(name, super); \
		OS_OBJECT_SUBCLASS_DECL(name, super)

#define DISPATCH_INTERNAL_SUBCLASS_DECL(name, super) \
		OS_OBJECT_DECL_SUBCLASS(dispatch_##name, dispatch_##super); \
		DISPATCH_SUBCLASS_DECL(name, dispatch_##super)
#endif

// vtable symbols
#define OS_OBJECT_VTABLE(name)		(&OS_OBJECT_CLASS_SYMBOL(name))
#define DISPATCH_OBJC_CLASS(name)	(&DISPATCH_CLASS_SYMBOL(name))

// vtables for subclasses used in a class cluster
#if USE_OBJC
// ObjC classes and dispatch vtables are co-located via linker order and alias
// files rdar://10640168
#if OS_OBJECT_HAVE_OBJC2
#define OS_OBJECT_VTABLE_SUBCLASS_INSTANCE(name, super, xdispose, dispose, ...) \
		__attribute__((section("__DATA,__objc_data"), used)) \
		const struct super##_extra_vtable_s \
		OS_OBJECT_EXTRA_VTABLE_SYMBOL(name) = { __VA_ARGS__ }
#define OS_OBJECT_EXTRA_VTABLE_DECL(name, super)
#define DISPATCH_VTABLE(name) DISPATCH_OBJC_CLASS(name)
#else
#define OS_OBJECT_VTABLE_SUBCLASS_INSTANCE(name, super, xdispose, dispose, ...) \
		const struct super##_vtable_s \
		OS_OBJECT_EXTRA_VTABLE_SYMBOL(name) = { \
			._os_obj_objc_isa = &OS_OBJECT_CLASS_SYMBOL(name), \
			._os_obj_vtable = { __VA_ARGS__ }, \
		}
#define OS_OBJECT_EXTRA_VTABLE_DECL(name, super) \
		extern const struct super##_vtable_s \
				OS_OBJECT_EXTRA_VTABLE_SYMBOL(name);
#define DISPATCH_VTABLE(name) &OS_OBJECT_EXTRA_VTABLE_SYMBOL(dispatch_##name)
#endif
#else
#define OS_OBJECT_VTABLE_SUBCLASS_INSTANCE(name, super, xdispose, dispose, ...) \
		const struct super##_vtable_s OS_OBJECT_CLASS_SYMBOL(name) = { \
			._os_obj_xref_dispose = xdispose, \
			._os_obj_dispose = dispose, \
			._os_obj_vtable = { __VA_ARGS__ }, \
		}
#define OS_OBJECT_EXTRA_VTABLE_DECL(name, super)
#define DISPATCH_VTABLE(name) DISPATCH_OBJC_CLASS(name)
#endif // USE_OBJC

#define DISPATCH_VTABLE_SUBCLASS_INSTANCE(name, super, ...) \
		OS_OBJECT_VTABLE_SUBCLASS_INSTANCE(dispatch_##name, dispatch_##super, \
				_dispatch_xref_dispose, _dispatch_dispose, __VA_ARGS__)

// vtables for proper classes
#define OS_OBJECT_VTABLE_INSTANCE(name, xdispose, dispose, ...) \
		OS_OBJECT_VTABLE_SUBCLASS_INSTANCE(name, name, \
				xdispose, dispose, __VA_ARGS__)

#define DISPATCH_VTABLE_INSTANCE(name, ...) \
		DISPATCH_VTABLE_SUBCLASS_INSTANCE(name, name, __VA_ARGS__)

#define DISPATCH_INVOKABLE_VTABLE_HEADER(x) \
	unsigned long const do_type; \
	const char *const do_kind; \
	void (*const do_invoke)(struct x##_s *, dispatch_invoke_flags_t)

#define DISPATCH_QUEUEABLE_VTABLE_HEADER(x) \
	DISPATCH_INVOKABLE_VTABLE_HEADER(x); \
	void (*const do_wakeup)(struct x##_s *, \
			pthread_priority_t, dispatch_wakeup_flags_t); \
	void (*const do_dispose)(struct x##_s *)

#define DISPATCH_OBJECT_VTABLE_HEADER(x) \
	DISPATCH_QUEUEABLE_VTABLE_HEADER(x); \
	void (*const do_set_targetq)(struct x##_s *, dispatch_queue_t); \
	void (*const do_suspend)(struct x##_s *); \
	void (*const do_resume)(struct x##_s *, bool activate); \
	void (*const do_finalize_activation)(struct x##_s *); \
	size_t (*const do_debug)(struct x##_s *, char *, size_t)

#define dx_vtable(x) (&(x)->do_vtable->_os_obj_vtable)
#define dx_type(x) dx_vtable(x)->do_type
#define dx_subtype(x) (dx_vtable(x)->do_type & _DISPATCH_SUB_TYPE_MASK)
#define dx_metatype(x) (dx_vtable(x)->do_type & _DISPATCH_META_TYPE_MASK)
#define dx_hastypeflag(x, f) (dx_vtable(x)->do_type & _DISPATCH_##f##_TYPEFLAG)
#define dx_kind(x) dx_vtable(x)->do_kind
#define dx_debug(x, y, z) dx_vtable(x)->do_debug((x), (y), (z))
#define dx_dispose(x) dx_vtable(x)->do_dispose(x)
#define dx_invoke(x, z) dx_vtable(x)->do_invoke(x, z)
#define dx_wakeup(x, y, z) dx_vtable(x)->do_wakeup(x, y, z)

#define DISPATCH_OBJECT_GLOBAL_REFCNT		_OS_OBJECT_GLOBAL_REFCNT

#if OS_OBJECT_HAVE_OBJC1
#define DISPATCH_GLOBAL_OBJECT_HEADER(name) \
	.do_vtable = DISPATCH_VTABLE(name), \
	._objc_isa = DISPATCH_OBJC_CLASS(name), \
	.do_ref_cnt = DISPATCH_OBJECT_GLOBAL_REFCNT, \
	.do_xref_cnt = DISPATCH_OBJECT_GLOBAL_REFCNT
#else
#define DISPATCH_GLOBAL_OBJECT_HEADER(name) \
	.do_vtable = DISPATCH_VTABLE(name), \
	.do_ref_cnt = DISPATCH_OBJECT_GLOBAL_REFCNT, \
	.do_xref_cnt = DISPATCH_OBJECT_GLOBAL_REFCNT
#endif

#ifdef __LP64__
// the bottom nibble must not be zero, the rest of the bits should be random
// we sign extend the 64-bit version so that a better instruction encoding is
// generated on Intel
#define DISPATCH_OBJECT_LISTLESS ((void *)0xffffffff89abcdef)
#else
#define DISPATCH_OBJECT_LISTLESS ((void *)0x89abcdef)
#endif

DISPATCH_ENUM(dispatch_wakeup_flags, uint32_t,
	// The caller of dx_wakeup owns an internal refcount on the object being
	// woken up
	DISPATCH_WAKEUP_CONSUME                 = 0x00000001,

	// Some change to the object needs to be published to drainers.
	// If the drainer isn't the same thread, some scheme such as the dispatch
	// queue DIRTY bit must be used and a release barrier likely has to be
	// involved before dx_wakeup returns
	DISPATCH_WAKEUP_FLUSH					= 0x00000002,

	// A slow waiter was just enqueued
	DISPATCH_WAKEUP_SLOW_WAITER				= 0x00000004,

	// The caller desires to apply an override on the object being woken up
	// and has already adjusted the `oq_override` field. When this flag is
	// passed, the priority passed to dx_wakeup() should not be 0
	DISPATCH_WAKEUP_OVERRIDING              = 0x00000008,

	// At the time this queue was woken up it had an override that must be
	// preserved (used to solve a race with _dispatch_queue_drain_try_unlock())
	DISPATCH_WAKEUP_WAS_OVERRIDDEN          = 0x00000010,

#define _DISPATCH_WAKEUP_OVERRIDE_BITS \
		((dispatch_wakeup_flags_t)(DISPATCH_WAKEUP_OVERRIDING | \
		DISPATCH_WAKEUP_WAS_OVERRIDDEN))
);

DISPATCH_ENUM(dispatch_invoke_flags, uint32_t,
	DISPATCH_INVOKE_NONE					= 0x00000000,

	// Invoke modes
	//
	// @const DISPATCH_INVOKE_STEALING
	// This invoke is a stealer, meaning that it doesn't own the
	// enqueue lock at drain lock time.
	//
	// @const DISPATCH_INVOKE_OVERRIDING
	// This invoke is draining the hierarchy on another root queue and needs
	// to fake the identity of the original one.
	//
	DISPATCH_INVOKE_STEALING				= 0x00000001,
	DISPATCH_INVOKE_OVERRIDING				= 0x00000002,

	// Below this point flags are propagated to recursive calls to drain(),
	// continuation pop() or dx_invoke().
#define _DISPATCH_INVOKE_PROPAGATE_MASK		  0xffff0000u

	// Drain modes
	//
	// @const DISPATCH_INVOKE_WORKER_DRAIN
	// Invoke has been issued by a worker thread (work queue thread, or
	// pthread root queue) drain. This flag is NOT set when the main queue,
	// manager queue or runloop queues are drained
	//
	// @const DISPATCH_INVOKE_REDIRECTING_DRAIN
	// Has only been draining concurrent queues so far
	// Implies DISPATCH_INVOKE_WORKER_DRAIN
	//
	// @const DISPATCH_INVOKE_MANAGER_DRAIN
	// We're draining from a manager context
	//
	DISPATCH_INVOKE_WORKER_DRAIN			= 0x00010000,
	DISPATCH_INVOKE_REDIRECTING_DRAIN		= 0x00020000,
	DISPATCH_INVOKE_MANAGER_DRAIN			= 0x00040000,
#define _DISPATCH_INVOKE_DRAIN_MODE_MASK	  0x000f0000u

	// Autoreleasing modes
	//
	// @const DISPATCH_INVOKE_AUTORELEASE_ALWAYS
	// Always use autoreleasepools around callouts
	//
	// @const DISPATCH_INVOKE_AUTORELEASE_NEVER
	// Never use autoreleasepools around callouts
	//
	DISPATCH_INVOKE_AUTORELEASE_ALWAYS		= 0x00100000,
	DISPATCH_INVOKE_AUTORELEASE_NEVER		= 0x00200000,
#define _DISPATCH_INVOKE_AUTORELEASE_MASK	  0x00300000u
);

enum {
	_DISPATCH_META_TYPE_MASK		= 0xffff0000, // mask for object meta-types
	_DISPATCH_TYPEFLAGS_MASK		= 0x0000ff00, // mask for object typeflags
	_DISPATCH_SUB_TYPE_MASK			= 0x000000ff, // mask for object sub-types

	_DISPATCH_CONTINUATION_TYPE		=    0x00000, // meta-type for continuations
	_DISPATCH_QUEUE_TYPE			=    0x10000, // meta-type for queues
	_DISPATCH_SOURCE_TYPE			=    0x20000, // meta-type for sources
	_DISPATCH_SEMAPHORE_TYPE		=    0x30000, // meta-type for semaphores
	_DISPATCH_NODE_TYPE				=    0x40000, // meta-type for data node
	_DISPATCH_IO_TYPE				=    0x50000, // meta-type for io channels
	_DISPATCH_OPERATION_TYPE		=    0x60000, // meta-type for io operations
	_DISPATCH_DISK_TYPE				=    0x70000, // meta-type for io disks

	_DISPATCH_QUEUE_ROOT_TYPEFLAG	=     0x0100, // bit set for any root queues

#define DISPATCH_CONTINUATION_TYPE(name)  \
		(_DISPATCH_CONTINUATION_TYPE | DC_##name##_TYPE)
	DISPATCH_DATA_TYPE				= 1 | _DISPATCH_NODE_TYPE,
	DISPATCH_MACH_MSG_TYPE			= 2 | _DISPATCH_NODE_TYPE,
	DISPATCH_QUEUE_ATTR_TYPE		= 3 | _DISPATCH_NODE_TYPE,

	DISPATCH_IO_TYPE				= 0 | _DISPATCH_IO_TYPE,
	DISPATCH_OPERATION_TYPE			= 0 | _DISPATCH_OPERATION_TYPE,
	DISPATCH_DISK_TYPE				= 0 | _DISPATCH_DISK_TYPE,

	DISPATCH_QUEUE_LEGACY_TYPE		= 1 | _DISPATCH_QUEUE_TYPE,
	DISPATCH_QUEUE_SERIAL_TYPE		= 2 | _DISPATCH_QUEUE_TYPE,
	DISPATCH_QUEUE_CONCURRENT_TYPE	= 3 | _DISPATCH_QUEUE_TYPE,
	DISPATCH_QUEUE_GLOBAL_ROOT_TYPE	= 4 | _DISPATCH_QUEUE_TYPE |
			_DISPATCH_QUEUE_ROOT_TYPEFLAG,
	DISPATCH_QUEUE_RUNLOOP_TYPE		= 5 | _DISPATCH_QUEUE_TYPE |
			_DISPATCH_QUEUE_ROOT_TYPEFLAG,
	DISPATCH_QUEUE_MGR_TYPE			= 6 | _DISPATCH_QUEUE_TYPE,
	DISPATCH_QUEUE_SPECIFIC_TYPE	= 7 | _DISPATCH_QUEUE_TYPE,

	DISPATCH_SEMAPHORE_TYPE			= 1 | _DISPATCH_SEMAPHORE_TYPE,
	DISPATCH_GROUP_TYPE				= 2 | _DISPATCH_SEMAPHORE_TYPE,

	DISPATCH_SOURCE_KEVENT_TYPE		= 1 | _DISPATCH_SOURCE_TYPE,
	DISPATCH_MACH_CHANNEL_TYPE		= 2 | _DISPATCH_SOURCE_TYPE,

};

typedef struct _os_object_vtable_s {
	_OS_OBJECT_CLASS_HEADER();
} _os_object_vtable_s;

typedef struct _os_object_s {
	_OS_OBJECT_HEADER(
	const _os_object_vtable_s *os_obj_isa,
	os_obj_ref_cnt,
	os_obj_xref_cnt);
} _os_object_s;

#if OS_OBJECT_HAVE_OBJC1
#define OS_OBJECT_STRUCT_HEADER(x) \
	_OS_OBJECT_HEADER(\
	const void *_objc_isa, \
	do_ref_cnt, \
	do_xref_cnt); \
	const struct x##_vtable_s *do_vtable
#else
#define OS_OBJECT_STRUCT_HEADER(x) \
	_OS_OBJECT_HEADER(\
	const struct x##_vtable_s *do_vtable, \
	do_ref_cnt, \
	do_xref_cnt)
#endif

#define _DISPATCH_OBJECT_HEADER(x) \
	struct _os_object_s _as_os_obj[0]; \
	OS_OBJECT_STRUCT_HEADER(dispatch_##x); \
	struct dispatch_##x##_s *volatile do_next; \
	struct dispatch_queue_s *do_targetq; \
	void *do_ctxt; \
	void *do_finalizer

#define DISPATCH_OBJECT_HEADER(x) \
	struct dispatch_object_s _as_do[0]; \
	_DISPATCH_OBJECT_HEADER(x)

// Swift-unavailable -init requires method in each class.
#define DISPATCH_UNAVAILABLE_INIT() \
	- (instancetype)init { \
		DISPATCH_CLIENT_CRASH(0, "-init called directly"); \
		return [super init]; \
	}

_OS_OBJECT_DECL_PROTOCOL(dispatch_object, object);

OS_OBJECT_CLASS_DECL(dispatch_object, object,
		DISPATCH_OBJECT_VTABLE_HEADER(dispatch_object));

struct dispatch_object_s {
	_DISPATCH_OBJECT_HEADER(object);
};

#if OS_OBJECT_HAVE_OBJC1
#define _OS_MPSC_QUEUE_FIELDS(ns, __state_field__) \
	struct dispatch_object_s *volatile ns##_items_head; \
	unsigned long ns##_serialnum; \
	union { \
		uint64_t volatile __state_field__; \
		DISPATCH_STRUCT_LITTLE_ENDIAN_2( \
			dispatch_lock __state_field__##_lock, \
			uint32_t __state_field__##_bits \
		); \
	}; /* needs to be 64-bit aligned */ \
	/* LP64 global queue cacheline boundary */ \
	const char *ns##_label; \
	voucher_t ns##_override_voucher; \
	dispatch_priority_t ns##_priority; \
	dispatch_priority_t volatile ns##_override; \
	struct dispatch_object_s *volatile ns##_items_tail
#else
#define _OS_MPSC_QUEUE_FIELDS(ns, __state_field__) \
	struct dispatch_object_s *volatile ns##_items_head; \
	union { \
		uint64_t volatile __state_field__; \
		DISPATCH_STRUCT_LITTLE_ENDIAN_2( \
			dispatch_lock __state_field__##_lock, \
			uint32_t __state_field__##_bits \
		); \
	}; /* needs to be 64-bit aligned */ \
	/* LP64 global queue cacheline boundary */ \
	unsigned long ns##_serialnum; \
	const char *ns##_label; \
	voucher_t ns##_override_voucher; \
	dispatch_priority_t ns##_priority; \
	dispatch_priority_t volatile ns##_override; \
	struct dispatch_object_s *volatile ns##_items_tail
#endif

OS_OBJECT_INTERNAL_CLASS_DECL(os_mpsc_queue, object,
		DISPATCH_QUEUEABLE_VTABLE_HEADER(os_mpsc_queue));

struct os_mpsc_queue_s {
	struct _os_object_s _as_os_obj[0];
	OS_OBJECT_STRUCT_HEADER(os_mpsc_queue);
	struct dispatch_object_s *volatile oq_next;
	void *oq_opaque1; // do_targetq
	void *oq_opaque2; // do_ctxt
	void *oq_opaque3; // do_finalizer
	_OS_MPSC_QUEUE_FIELDS(oq, __oq_state_do_not_use);
};

size_t _dispatch_object_debug_attr(dispatch_object_t dou, char* buf,
		size_t bufsiz);
void *_dispatch_alloc(const void *vtable, size_t size);
#if !USE_OBJC
void _dispatch_xref_dispose(dispatch_object_t dou);
#endif
void _dispatch_dispose(dispatch_object_t dou);
#if DISPATCH_COCOA_COMPAT
#if USE_OBJC
#include <objc/runtime.h>
#include <objc/objc-internal.h>
#define _dispatch_autorelease_pool_push() \
	objc_autoreleasePoolPush()
#define _dispatch_autorelease_pool_pop(context) \
	objc_autoreleasePoolPop(context)
#else
void *_dispatch_autorelease_pool_push(void);
void _dispatch_autorelease_pool_pop(void *context);
#endif
void *_dispatch_last_resort_autorelease_pool_push(void);
void _dispatch_last_resort_autorelease_pool_pop(void *context);

#define dispatch_invoke_with_autoreleasepool(flags, ...)  ({ \
		void *pool = NULL; \
		if ((flags) & DISPATCH_INVOKE_AUTORELEASE_ALWAYS) { \
			pool = _dispatch_autorelease_pool_push(); \
			DISPATCH_COMPILER_CAN_ASSUME(pool); \
		}; \
		__VA_ARGS__; \
		if (pool) _dispatch_autorelease_pool_pop(pool); \
	})
#else
#define dispatch_invoke_with_autoreleasepool(flags, ...) \
	do { __VA_ARGS__; } while (0)
#endif


#if USE_OBJC
OS_OBJECT_OBJC_CLASS_DECL(object);
#endif

#if OS_OBJECT_HAVE_OBJC2
// ObjC toll-free bridging, keep in sync with libdispatch.order file
//
// This is required by the dispatch_data_t/NSData bridging, which is not
// supported on the old runtime.
#define DISPATCH_OBJECT_TFB(f, o, ...) \
	if (slowpath((uintptr_t)((o)._os_obj->os_obj_isa) & 1) || \
			slowpath((Class)((o)._os_obj->os_obj_isa) < \
					(Class)OS_OBJECT_VTABLE(dispatch_object)) || \
			slowpath((Class)((o)._os_obj->os_obj_isa) >= \
					(Class)OS_OBJECT_VTABLE(object))) { \
		return f((o), ##__VA_ARGS__); \
	}

id _dispatch_objc_alloc(Class cls, size_t size);
void _dispatch_objc_retain(dispatch_object_t dou);
void _dispatch_objc_release(dispatch_object_t dou);
void _dispatch_objc_set_context(dispatch_object_t dou, void *context);
void *_dispatch_objc_get_context(dispatch_object_t dou);
void _dispatch_objc_set_finalizer_f(dispatch_object_t dou,
		dispatch_function_t finalizer);
void _dispatch_objc_set_target_queue(dispatch_object_t dou,
		dispatch_queue_t queue);
void _dispatch_objc_suspend(dispatch_object_t dou);
void _dispatch_objc_resume(dispatch_object_t dou);
void _dispatch_objc_activate(dispatch_object_t dou);
size_t _dispatch_objc_debug(dispatch_object_t dou, char* buf, size_t bufsiz);

#if __OBJC2__
@interface NSObject (DISPATCH_CONCAT(_,DISPATCH_CLASS(object)))
- (void)_setContext:(void*)context;
- (void*)_getContext;
- (void)_setFinalizer:(dispatch_function_t)finalizer;
- (void)_setTargetQueue:(dispatch_queue_t)queue;
- (void)_suspend;
- (void)_resume;
- (void)_activate;
@end
#endif // __OBJC2__
#else
#define DISPATCH_OBJECT_TFB(f, o, ...)
#endif // OS_OBJECT_HAVE_OBJC2

#pragma mark -
#pragma mark _os_object_s

/*
 * Low level _os_atomic_refcnt_* actions
 *
 * _os_atomic_refcnt_inc2o(o, f):
 *   performs a refcount increment and returns the new refcount value
 *
 * _os_atomic_refcnt_dec2o(o, f):
 *   performs a refcount decrement and returns the new refcount value
 *
 * _os_atomic_refcnt_dispose_barrier2o(o, f):
 *   a barrier to perform prior to tearing down an object when the refcount
 *   reached -1.
 */
#define _os_atomic_refcnt_perform2o(o, f, op, m)   ({ \
		typeof(o) _o = (o); \
		int _ref_cnt = _o->f; \
		if (fastpath(_ref_cnt != _OS_OBJECT_GLOBAL_REFCNT)) { \
			_ref_cnt = os_atomic_##op##2o(_o, f, m); \
		} \
		_ref_cnt; \
	})

#define _os_atomic_refcnt_inc2o(o, m) \
		_os_atomic_refcnt_perform2o(o, m, inc, relaxed)

#define _os_atomic_refcnt_dec2o(o, m) \
		_os_atomic_refcnt_perform2o(o, m, dec, release)

#define _os_atomic_refcnt_dispose_barrier2o(o, m) \
		(void)os_atomic_load2o(o, m, acquire)


/*
 * Higher level _os_object_{x,}refcnt_* actions
 *
 * _os_atomic_{x,}refcnt_inc(o):
 *   increment the external (resp. internal) refcount and
 *   returns the new refcount value
 *
 * _os_atomic_{x,}refcnt_dec(o):
 *   decrement the external (resp. internal) refcount and
 *   returns the new refcount value
 *
 * _os_atomic_{x,}refcnt_dispose_barrier(o):
 *   performs the pre-teardown barrier for the external
 *   (resp. internal) refcount
 *
 */
#define _os_object_xrefcnt_inc(o) \
		_os_atomic_refcnt_inc2o(o, os_obj_xref_cnt)

#define _os_object_xrefcnt_dec(o) \
		_os_atomic_refcnt_dec2o(o, os_obj_xref_cnt)

#define _os_object_xrefcnt_dispose_barrier(o) \
		_os_atomic_refcnt_dispose_barrier2o(o, os_obj_xref_cnt)

#define _os_object_refcnt_inc(o) \
		_os_atomic_refcnt_inc2o(o, os_obj_ref_cnt)

#define _os_object_refcnt_dec(o) \
		_os_atomic_refcnt_dec2o(o, os_obj_ref_cnt)

#define _os_object_refcnt_dispose_barrier(o) \
		_os_atomic_refcnt_dispose_barrier2o(o, os_obj_ref_cnt)

void _os_object_init(void);
unsigned long _os_object_retain_count(_os_object_t obj);
bool _os_object_retain_weak(_os_object_t obj);
bool _os_object_allows_weak_reference(_os_object_t obj);
void _os_object_dispose(_os_object_t obj);
void _os_object_xref_dispose(_os_object_t obj);

#endif // __DISPATCH_OBJECT_INTERNAL__
