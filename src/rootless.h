#ifndef _ROOTLESS_H_
#define _ROOTLESS_H_

#include <os/availability.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/stat.h>
#include <sys/types.h>

__BEGIN_DECLS

bool rootless_allows_task_for_pid(pid_t target_pid);

int rootless_check_restricted_flag(const char *path, const char *storage_class);

int rootless_check_datavault_flag(const char *path, const char *storage_class);

int rootless_check_trusted(const char *path);
int rootless_check_trusted_class(const char *path, const char *storage_class);
int rootless_check_trusted_fd(int fd);

int rootless_protected_volume(const char *path);

int rootless_mkdir_restricted(const char *path, mode_t mode, const char *storage_class);

int rootless_mkdir_datavault(const char *path, mode_t mode, const char *storage_class);

int rootless_mkdir_nounlink(const char *path, mode_t mode, const char *storage_class);

int rootless_convert_to_datavault(const char *path, const char *storage_class);

int rootless_restricted_environment(void);

int rootless_apply(const char *dstroot, const char *manifest);

int rootless_apply_relative(const char *dstroot, const char *prefix, const char *manifest);

struct rootless_apply_rule;

struct rootless_apply_rule *rootless_manifest_parse(const char *manifest);

void rootless_manifest_free(struct rootless_apply_rule *rules);

int rootless_preflight(const char *path, const struct rootless_apply_rule *rules);

int rootless_suspend(void);

int rootless_whitelist_push(const void *data, size_t size);

#pragma mark -

typedef uint rootless_trust_token_t;

typedef enum _rootless_resource_use {
    ROOTLESS_RESOURCE_USE_IMAGEIO = 1 /*! ImageIO may handle content in-process. */
} rootless_resource_use_t;

API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void rootless_register_trusted_storage_class(const char *storage_class, rootless_resource_use_t use);

API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
__result_use_check
    rootless_trust_token_t
    rootless_trusted_by_self_token(int fd, rootless_resource_use_t use);

API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
__result_use_check bool rootless_verify_trusted_by_self_token(rootless_trust_token_t token, rootless_resource_use_t use);

__END_DECLS

#endif /* _ROOTLESS_H_ */
