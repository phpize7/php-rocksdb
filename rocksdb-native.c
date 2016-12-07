/

#ifndef STORAGE_ROCKSDB_INCLUDE_C_H_
#define STORAGE_ROCKSDB_INCLUDE_C_H_

#pragma once

#ifdef _WIN32
#ifdef ROCKSDB_DLL
#ifdef ROCKSDB_LIBRARY_EXPORTS
#define ROCKSDB_LIBRARY_API __declspec(dllexport)
#else
#define ROCKSDB_LIBRARY_API __declspec(dllimport)
#endif
#else
#define ROCKSDB_LIBRARY_API
#endif
#else
#define ROCKSDB_LIBRARY_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

/* Exported types */

typedef struct rocksdb_t                 rocksdb_t;
typedef struct rocksdb_backup_engine_t   rocksdb_backup_engine_t;
typedef struct rocksdb_backup_engine_info_t   rocksdb_backup_engine_info_t;
typedef struct rocksdb_restore_options_t rocksdb_restore_options_t;
typedef struct rocksdb_cache_t           rocksdb_cache_t;
typedef struct rocksdb_compactionfilter_t rocksdb_compactionfilter_t;
typedef struct rocksdb_compactionfiltercontext_t
    rocksdb_compactionfiltercontext_t;
typedef struct rocksdb_compactionfilterfactory_t
    rocksdb_compactionfilterfactory_t;
typedef struct rocksdb_comparator_t      rocksdb_comparator_t;
typedef struct rocksdb_env_t             rocksdb_env_t;
typedef struct rocksdb_fifo_compaction_options_t rocksdb_fifo_compaction_options_t;
typedef struct rocksdb_filelock_t        rocksdb_filelock_t;
typedef struct rocksdb_filterpolicy_t    rocksdb_filterpolicy_t;
typedef struct rocksdb_flushoptions_t    rocksdb_flushoptions_t;
typedef struct rocksdb_iterator_t        rocksdb_iterator_t;
typedef struct rocksdb_logger_t          rocksdb_logger_t;
typedef struct rocksdb_mergeoperator_t   rocksdb_mergeoperator_t;
typedef struct rocksdb_options_t         rocksdb_options_t;
typedef struct rocksdb_block_based_table_options_t
    rocksdb_block_based_table_options_t;
typedef struct rocksdb_cuckoo_table_options_t
    rocksdb_cuckoo_table_options_t;
typedef struct rocksdb_randomfile_t      rocksdb_randomfile_t;
typedef struct rocksdb_readoptions_t     rocksdb_readoptions_t;
typedef struct rocksdb_seqfile_t         rocksdb_seqfile_t;
typedef struct rocksdb_slicetransform_t  rocksdb_slicetransform_t;
typedef struct rocksdb_snapshot_t        rocksdb_snapshot_t;
typedef struct rocksdb_writablefile_t    rocksdb_writablefile_t;
typedef struct rocksdb_writebatch_t      rocksdb_writebatch_t;
typedef struct rocksdb_writeoptions_t    rocksdb_writeoptions_t;
typedef struct rocksdb_universal_compaction_options_t rocksdb_universal_compaction_options_t;
typedef struct rocksdb_livefiles_t     rocksdb_livefiles_t;
typedef struct rocksdb_column_family_handle_t rocksdb_column_family_handle_t;
typedef struct rocksdb_envoptions_t      rocksdb_envoptions_t;
typedef struct rocksdb_ingestexternalfileoptions_t rocksdb_ingestexternalfileoptions_t;
typedef struct rocksdb_sstfilewriter_t   rocksdb_sstfilewriter_t;
typedef struct rocksdb_ratelimiter_t     rocksdb_ratelimiter_t;

/* DB operations */

extern ROCKSDB_LIBRARY_API rocksdb_t* rocksdb_open(
    const rocksdb_options_t* options, const char* name, char** errptr);

extern ROCKSDB_LIBRARY_API rocksdb_t* rocksdb_open_for_read_only(
    const rocksdb_options_t* options, const char* name,
    unsigned char error_if_log_file_exist, char** errptr);

extern ROCKSDB_LIBRARY_API rocksdb_backup_engine_t* rocksdb_backup_engine_open(
    const rocksdb_options_t* options, const char* path, char** errptr);

extern ROCKSDB_LIBRARY_API void rocksdb_backup_engine_create_new_backup(
    rocksdb_backup_engine_t* be, rocksdb_t* db, char** errptr);

extern ROCKSDB_LIBRARY_API void rocksdb_backup_engine_purge_old_backups(
    rocksdb_backup_engine_t* be, uint32_t num_backups_to_keep, char** errptr);

extern ROCKSDB_LIBRARY_API rocksdb_restore_options_t*
rocksdb_restore_options_create();
extern ROCKSDB_LIBRARY_API void rocksdb_restore_options_destroy(
    rocksdb_restore_options_t* opt);
extern ROCKSDB_LIBRARY_API void rocksdb_restore_options_set_keep_log_files(
    rocksdb_restore_options_t* opt, int v);

extern ROCKSDB_LIBRARY_API void
rocksdb_backup_engine_restore_db_from_latest_backup(
    rocksdb_backup_engine_t* be, const char* db_dir, const char* wal_dir,
    const rocksdb_restore_options_t* restore_options, char** errptr);

extern ROCKSDB_LIBRARY_API const rocksdb_backup_engine_info_t*
rocksdb_backup_engine_get_backup_info(rocksdb_backup_engine_t* be);

extern ROCKSDB_LIBRARY_API int rocksdb_backup_engine_info_count(
    const rocksdb_backup_engine_info_t* info);

extern ROCKSDB_LIBRARY_API int64_t
rocksdb_backup_engine_info_timestamp(const rocksdb_backup_engine_info_t* info,
                                     int index);

extern ROCKSDB_LIBRARY_API uint32_t
rocksdb_backup_engine_info_backup_id(const rocksdb_backup_engine_info_t* info,
                                     int index);

extern ROCKSDB_LIBRARY_API uint64_t
rocksdb_backup_engine_info_size(const rocksdb_backup_engine_info_t* info,
                                int index);

extern ROCKSDB_LIBRARY_API uint32_t rocksdb_backup_engine_info_number_files(
    const rocksdb_backup_engine_info_t* info, int index);

extern ROCKSDB_LIBRARY_API void rocksdb_backup_engine_info_destroy(
    const rocksdb_backup_engine_info_t* info);

extern ROCKSDB_LIBRARY_API void rocksdb_backup_engine_close(
    rocksdb_backup_engine_t* be);

extern ROCKSDB_LIBRARY_API rocksdb_t* rocksdb_open_column_families(
    const rocksdb_options_t* options, const char* name, int num_column_families,
    const char** column_family_names,
    const rocksdb_options_t** column_family_options,
    rocksdb_column_family_handle_t** column_family_handles, char** errptr);

extern ROCKSDB_LIBRARY_API rocksdb_t*
rocksdb_open_for_read_only_column_families(
    const rocksdb_options_t* options, const char* name, int num_column_families,
    const char** column_family_names,
    const rocksdb_options_t** column_family_options,
    rocksdb_column_family_handle_t** column_family_handles,
    unsigned char error_if_log_file_exist, char** errptr);

extern ROCKSDB_LIBRARY_API char** rocksdb_list_column_families(
    const rocksdb_options_t* options, const char* name, size_t* lencf,
    char** errptr);

extern ROCKSDB_LIBRARY_API void rocksdb_list_column_families_destroy(
    char** list, size_t len);

extern ROCKSDB_LIBRARY_API rocksdb_column_family_handle_t*
rocksdb_create_column_family(rocksdb_t* db,
                             const rocksdb_options_t* column_family_options,
                             const char* column_family_name, char** errptr);

extern ROCKSDB_LIBRARY_API void rocksdb_drop_column_family(
    rocksdb_t* db, rocksdb_column_family_handle_t* handle, char** errptr);

extern ROCKSDB_LIBRARY_API void rocksdb_column_family_handle_destroy(
    rocksdb_column_family_handle_t*);

extern ROCKSDB_LIBRARY_API void rocksdb_close(rocksdb_t* db);

extern ROCKSDB_LIBRARY_API void rocksdb_put(
    rocksdb_t* db, const rocksdb_writeoptions_t* options, const char* key,
    size_t keylen, const char* val, size_t vallen, char** errptr);

extern ROCKSDB_LIBRARY_API void rocksdb_put_cf(
    rocksdb_t* db, const rocksdb_writeoptions_t* options,
    rocksdb_column_family_handle_t* column_family, const char* key,
    size_t keylen, const char* val, size_t vallen, char** errptr);

extern ROCKSDB_LIBRARY_API void rocksdb_delete(
    rocksdb_t* db, const rocksdb_writeoptions_t* options, const char* key,
    size_t keylen, char** errptr);

extern ROCKSDB_LIBRARY_API void rocksdb_delete_cf(
    rocksdb_t* db, const rocksdb_writeoptions_t* options,
    rocksdb_column_family_handle_t* column_family, const char* key,
    size_t keylen, char** errptr);

extern ROCKSDB_LIBRARY_API void rocksdb_merge(
    rocksdb_t* db, const rocksdb_writeoptions_t* options, const char* key,
    size_t keylen, const char* val, size_t vallen, char** errptr);

extern ROCKSDB_LIBRARY_API void rocksdb_merge_cf(
    rocksdb_t* db, const rocksdb_writeoptions_t* options,
    rocksdb_column_family_handle_t* column_family, const char* key,
    size_t keylen, const char* val, size_t vallen, char** errptr);

extern ROCKSDB_LIBRARY_API void rocksdb_write(
    rocksdb_t* db, const rocksdb_writeoptions_t* options,
    rocksdb_writebatch_t* batch, char** errptr);

/* Returns NULL if not found.  A malloc()ed array otherwise.
   Stores the length of the array in *vallen. */
extern ROCKSDB_LIBRARY_API char* rocksdb_get(
    rocksdb_t* db, const rocksdb_readoptions_t* options, const char* key,
    size_t keylen, size_t* vallen, char** errptr);

extern ROCKSDB_LIBRARY_API char* rocksdb_get_cf(
    rocksdb_t* db, const rocksdb_readoptions_t* options,
    rocksdb_column_family_handle_t* column_family, const char* key,
    size_t keylen, size_t* vallen, char** errptr);

// if values_list[i] == NULL and errs[i] == NULL,
// then we got status.IsNotFound(), which we will not return.
// all errors except status status.ok() and status.IsNotFound() are returned.
//
// errs, values_list and values_list_sizes must be num_keys in length,
// allocated by the caller.
// errs is a list of strings as opposed to the conventional one error,
// where errs[i] is the status for retrieval of keys_list[i].
// each non-NULL errs entry is a malloc()ed, null terminated string.
// each non-NULL values_list entry is a malloc()ed array, with
// the length for each stored in values_list_sizes[i].
extern ROCKSDB_LIBRARY_API void rocksdb_multi_get(
    rocksdb_t* db, const rocksdb_readoptions_t* options, size_t num_keys,
    const char* const* keys_list, const size_t* keys_list_sizes,
    char** values_list, size_t* values_list_sizes, char** errs);

extern ROCKSDB_LIBRARY_API void rocksdb_multi_get_cf(
    rocksdb_t* db, const rocksdb_readoptions_t* options,
    const rocksdb_column_family_handle_t* const* column_families,
    size_t num_keys, const char* const* keys_list,
    const size_t* keys_list_sizes, char** values_list,
    size_t* values_list_sizes, char** errs);

extern ROCKSDB_LIBRARY_API rocksdb_iterator_t* rocksdb_create_iterator(
    rocksdb_t* db, const rocksdb_readoptions_t* options);

extern ROCKSDB_LIBRARY_API rocksdb_iterator_t* rocksdb_create_iterator_cf(
    rocksdb_t* db, const rocksdb_readoptions_t* options,
    rocksdb_column_family_handle_t* column_family);

extern ROCKSDB_LIBRARY_API void rocksdb_create_iterators(
    rocksdb_t *db, rocksdb_readoptions_t* opts,
    rocksdb_column_family_handle_t** column_families,
    rocksdb_iterator_t** iterators, size_t size, char** errptr);

extern ROCKSDB_LIBRARY_API const rocksdb_snapshot_t* rocksdb_create_snapshot(
    rocksdb_t* db);

extern ROCKSDB_LIBRARY_API void rocksdb_release_snapshot(
    rocksdb_t* db, const rocksdb_snapshot_t* snapshot);

/* Returns NULL if property name is unknown.
   Else returns a pointer to a malloc()-ed null-terminated value. */
extern ROCKSDB_LIBRARY_API char* rocksdb_property_value(rocksdb_t* db,
                                                        const char* propname);

extern ROCKSDB_LIBRARY_API char* rocksdb_property_value_cf(
    rocksdb_t* db, rocksdb_column_family_handle_t* column_family,
    const char* propname);

extern ROCKSDB_LIBRARY_API void rocksdb_approximate_sizes(
    rocksdb_t* db, int num_ranges, const char* const* range_start_key,
    const size_t* range_start_key_len, const char* const* range_limit_key,
    const size_t* range_limit_key_len, uint64_t* sizes);

extern ROCKSDB_LIBRARY_API void rocksdb_approximate_sizes_cf(
    rocksdb_t* db, rocksdb_column_family_handle_t* column_family,
    int num_ranges, const char* const* range_start_key,
    const size_t* range_start_key_len, const char* const* range_limit_key,
    const size_t* range_limit_key_len, uint64_t* sizes);

extern ROCKSDB_LIBRARY_API void rocksdb_compact_range(rocksdb_t* db,
                                                      const char* start_key,
                                                      size_t start_key_len,
                                                      const char* limit_key,
                                                      size_t limit_key_len);

extern ROCKSDB_LIBRARY_API void rocksdb_compact_range_cf(
    rocksdb_t* db, rocksdb_column_family_handle_t* column_family,
    const char* start_key, size_t start_key_len, const char* limit_key,
    size_t limit_key_len);

extern ROCKSDB_LIBRARY_API void rocksdb_delete_file(rocksdb_t* db,
                                                    const char* name);

extern ROCKSDB_LIBRARY_API const rocksdb_livefiles_t* rocksdb_livefiles(
    rocksdb_t* db);

extern ROCKSDB_LIBRARY_API void rocksdb_flush(
    rocksdb_t* db, const rocksdb_flushoptions_t* options, char** errptr);

extern ROCKSDB_LIBRARY_API void rocksdb_disable_file_deletions(rocksdb_t* db,
                                                               char** errptr);

extern ROCKSDB_LIBRARY_API void rocksdb_enable_file_deletions(
    rocksdb_t* db, unsigned char force, char** errptr);

/* Management operations */

extern ROCKSDB_LIBRARY_API void rocksdb_destroy_db(
    const rocksdb_options_t* options, const char* name, char** errptr);

extern ROCKSDB_LIBRARY_API void rocksdb_repair_db(
    const rocksdb_options_t* options, const char* name, char** errptr);

/* Iterator */

extern ROCKSDB_LIBRARY_API void rocksdb_iter_destroy(rocksdb_iterator_t*);
extern ROCKSDB_LIBRARY_API unsigned char rocksdb_iter_valid(
    const rocksdb_iterator_t*);
extern ROCKSDB_LIBRARY_API void rocksdb_iter_seek_to_first(rocksdb_iterator_t*);
extern ROCKSDB_LIBRARY_API void rocksdb_iter_seek_to_last(rocksdb_iterator_t*);
extern ROCKSDB_LIBRARY_API void rocksdb_iter_seek(rocksdb_iterator_t*,
                                                  const char* k, size_t klen);
extern ROCKSDB_LIBRARY_API void rocksdb_iter_seek_for_prev(rocksdb_iterator_t*,
                                                           const char* k,
                                                           size_t klen);
extern ROCKSDB_LIBRARY_API void rocksdb_iter_next(rocksdb_iterator_t*);
extern ROCKSDB_LIBRARY_API void rocksdb_iter_prev(rocksdb_iterator_t*);
extern ROCKSDB_LIBRARY_API const char* rocksdb_iter_key(
    const rocksdb_iterator_t*, size_t* klen);
extern ROCKSDB_LIBRARY_API const char* rocksdb_iter_value(
    const rocksdb_iterator_t*, size_t* vlen);
extern ROCKSDB_LIBRARY_API void rocksdb_iter_get_error(
    const rocksdb_iterator_t*, char** errptr);

/* Write batch */

extern ROCKSDB_LIBRARY_API rocksdb_writebatch_t* rocksdb_writebatch_create();
extern ROCKSDB_LIBRARY_API rocksdb_writebatch_t* rocksdb_writebatch_create_from(
    const char* rep, size_t size);
extern ROCKSDB_LIBRARY_API void rocksdb_writebatch_destroy(
    rocksdb_writebatch_t*);
extern ROCKSDB_LIBRARY_API void rocksdb_writebatch_clear(rocksdb_writebatch_t*);
extern ROCKSDB_LIBRARY_API int rocksdb_writebatch_count(rocksdb_writebatch_t*);
extern ROCKSDB_LIBRARY_API void rocksdb_writebatch_put(rocksdb_writebatch_t*,
                                                       const char* key,
                                                       size_t klen,
                                                       const char* val,
                                                       size_t vlen);
extern ROCKSDB_LIBRARY_API void rocksdb_writebatch_put_cf(
    rocksdb_writebatch_t*, rocksdb_column_family_handle_t* column_family,
    const char* key, size_t klen, const char* val, size_t vlen);
extern ROCKSDB_LIBRARY_API void rocksdb_writebatch_putv(
    rocksdb_writebatch_t* b, int num_keys, const char* const* keys_list,
    const size_t* keys_list_sizes, int num_values,
    const char* const* values_list, const size_t* values_list_sizes);
extern ROCKSDB_LIBRARY_API void rocksdb_writebatch_putv_cf(
    rocksdb_writebatch_t* b, rocksdb_column_family_handle_t* column_family,
    int num_keys, const char* const* keys_list, const size_t* keys_list_sizes,
    int num_values, const char* const* values_list,
    const size_t* values_list_sizes);
extern ROCKSDB_LIBRARY_API void rocksdb_writebatch_merge(rocksdb_writebatch_t*,
                                                         const char* key,
                                                         size_t klen,
                                                         const char* val,
                                                         size_t vlen);
extern ROCKSDB_LIBRARY_API void rocksdb_writebatch_merge_cf(
    rocksdb_writebatch_t*, rocksdb_column_family_handle_t* column_family,
    const char* key, size_t klen, const char* val, size_t vlen);
extern ROCKSDB_LIBRARY_API void rocksdb_writebatch_mergev(
    rocksdb_writebatch_t* b, int num_keys, const char* const* keys_list,
    const size_t* keys_list_sizes, int num_values,
    const char* const* values_list, const size_t* values_list_sizes);
extern ROCKSDB_LIBRARY_API void rocksdb_writebatch_mergev_cf(
    rocksdb_writebatch_t* b, rocksdb_column_family_handle_t* column_family,
    int num_keys, const char* const* keys_list, const size_t* keys_list_sizes,
    int num_values, const char* const* values_list,
    const size_t* values_list_sizes);
extern ROCKSDB_LIBRARY_API void rocksdb_writebatch_delete(rocksdb_writebatch_t*,
                                                          const char* key,
                                                          size_t klen);
extern ROCKSDB_LIBRARY_API void rocksdb_writebatch_delete_cf(
    rocksdb_writebatch_t*, rocksdb_column_family_handle_t* column_family,
    const char* key, size_t klen);
extern ROCKSDB_LIBRARY_API void rocksdb_writebatch_deletev(
    rocksdb_writebatch_t* b, int num_keys, const char* const* keys_list,
    const size_t* keys_list_sizes);
extern ROCKSDB_LIBRARY_API void rocksdb_writebatch_deletev_cf(
    rocksdb_writebatch_t* b, rocksdb_column_family_handle_t* column_family,
    int num_keys, const char* const* keys_list, const size_t* keys_list_sizes);
extern ROCKSDB_LIBRARY_API void rocksdb_writebatch_put_log_data(
    rocksdb_writebatch_t*, const char* blob, size_t len);
extern ROCKSDB_LIBRARY_API void rocksdb_writebatch_iterate(
    rocksdb_writebatch_t*, void* state,
    void (*put)(void*, const char* k, size_t klen, const char* v, size_t vlen),
    void (*deleted)(void*, const char* k, size_t klen));
extern ROCKSDB_LIBRARY_API const char* rocksdb_writebatch_data(
    rocksdb_writebatch_t*, size_t* size);

enum {
  rocksdb_block_based_table_index_type_binary_search = 0,
  rocksdb_block_based_table_index_type_hash_search = 1,
};
enum {
  rocksdb_tolerate_corrupted_tail_records_recovery = 0,
  rocksdb_absolute_consistency_recovery = 1,
  rocksdb_point_in_time_recovery = 2,
  rocksdb_skip_any_corrupted_records_recovery = 3
};

enum {
  rocksdb_no_compression = 0,
  rocksdb_snappy_compression = 1,
  rocksdb_zlib_compression = 2,
  rocksdb_bz2_compression = 3,
  rocksdb_lz4_compression = 4,
  rocksdb_lz4hc_compression = 5
};
enum {
  rocksdb_level_compaction = 0,
  rocksdb_universal_compaction = 1,
  rocksdb_fifo_compaction = 2
};

/* RateLimiter */
extern ROCKSDB_LIBRARY_API rocksdb_ratelimiter_t* rocksdb_ratelimiter_create(
    int64_t rate_bytes_per_sec, int64_t refill_period_us, int32_t fairness);
extern ROCKSDB_LIBRARY_API void rocksdb_ratelimiter_destroy(rocksdb_ratelimiter_t*);

/* Compaction Filter */

extern ROCKSDB_LIBRARY_API rocksdb_compactionfilter_t*
rocksdb_compactionfilter_create(
    void* state, void (*destructor)(void*),
    unsigned char (*filter)(void*, int level, const char* key,
                            size_t key_length, const char* existing_value,
                            size_t value_length, char** new_value,
                            size_t* new_value_length,
                            unsigned char* value_changed),
    const char* (*name)(void*));
extern ROCKSDB_LIBRARY_API void rocksdb_compactionfilter_set_ignore_snapshots(
    rocksdb_compactionfilter_t*, unsigned char);
extern ROCKSDB_LIBRARY_API void rocksdb_compactionfilter_destroy(
    rocksdb_compactionfilter_t*);

/* Compaction Filter Context */

extern ROCKSDB_LIBRARY_API unsigned char
rocksdb_compactionfiltercontext_is_full_compaction(
    rocksdb_compactionfiltercontext_t* context);

extern ROCKSDB_LIBRARY_API unsigned char
rocksdb_compactionfiltercontext_is_manual_compaction(
    rocksdb_compactionfiltercontext_t* context);

/* Compaction Filter Factory */

extern ROCKSDB_LIBRARY_API rocksdb_compactionfilterfactory_t*
rocksdb_compactionfilterfactory_create(
    void* state, void (*destructor)(void*),
    rocksdb_compactionfilter_t* (*create_compaction_filter)(
        void*, rocksdb_compactionfiltercontext_t* context),
    const char* (*name)(void*));
extern ROCKSDB_LIBRARY_API void rocksdb_compactionfilterfactory_destroy(
    rocksdb_compactionfilterfactory_t*);

/* Comparator */

extern ROCKSDB_LIBRARY_API rocksdb_comparator_t* rocksdb_comparator_create(
    void* state, void (*destructor)(void*),
    int (*compare)(void*, const char* a, size_t alen, const char* b,
                   size_t blen),
    const char* (*name)(void*));
extern ROCKSDB_LIBRARY_API void rocksdb_comparator_destroy(
    rocksdb_comparator_t*);

/* Filter policy */

extern ROCKSDB_LIBRARY_API rocksdb_filterpolicy_t* rocksdb_filterpolicy_create(
    void* state, void (*destructor)(void*),
    char* (*create_filter)(void*, const char* const* key_array,
                           const size_t* key_length_array, int num_keys,
                           size_t* filter_length),
    unsigned char (*key_may_match)(void*, const char* key, size_t length,
                                   const char* filter, size_t filter_length),
    void (*delete_filter)(void*, const char* filter, size_t filter_length),
    const char* (*name)(void*));
extern ROCKSDB_LIBRARY_API void rocksdb_filterpolicy_destroy(
    rocksdb_filterpolicy_t*);

extern ROCKSDB_LIBRARY_API rocksdb_filterpolicy_t*
rocksdb_filterpolicy_create_bloom(int bits_per_key);
extern ROCKSDB_LIBRARY_API rocksdb_filterpolicy_t*
rocksdb_filterpolicy_create_bloom_full(int bits_per_key);

/* Merge Operator */

extern ROCKSDB_LIBRARY_API rocksdb_mergeoperator_t*
rocksdb_mergeoperator_create(
    void* state, void (*destructor)(void*),
    char* (*full_merge)(void*, const char* key, size_t key_length,
                        const char* existing_value,
                        size_t existing_value_length,
                        const char* const* operands_list,
                        const size_t* operands_list_length, int num_operands,
                        unsigned char* success, size_t* new_value_length),
    char* (*partial_merge)(void*, const char* key, size_t key_length,
                           const char* const* operands_list,
                           const size_t* operands_list_length, int num_operands,
                           unsigned char* success, size_t* new_value_length),
    void (*delete_value)(void*, const char* value, size_t value_length),
    const char* (*name)(void*));
extern ROCKSDB_LIBRARY_API void rocksdb_mergeoperator_destroy(
    rocksdb_mergeoperator_t*);

/* Read options */

extern ROCKSDB_LIBRARY_API rocksdb_readoptions_t* rocksdb_readoptions_create();
extern ROCKSDB_LIBRARY_API void rocksdb_readoptions_destroy(
    rocksdb_readoptions_t*);
extern ROCKSDB_LIBRARY_API void rocksdb_readoptions_set_verify_checksums(
    rocksdb_readoptions_t*, unsigned char);
extern ROCKSDB_LIBRARY_API void rocksdb_readoptions_set_fill_cache(
    rocksdb_readoptions_t*, unsigned char);
extern ROCKSDB_LIBRARY_API void rocksdb_readoptions_set_snapshot(
    rocksdb_readoptions_t*, const rocksdb_snapshot_t*);
extern ROCKSDB_LIBRARY_API void rocksdb_readoptions_set_iterate_upper_bound(
    rocksdb_readoptions_t*, const char* key, size_t keylen);
extern ROCKSDB_LIBRARY_API void rocksdb_readoptions_set_read_tier(
    rocksdb_readoptions_t*, int);
extern ROCKSDB_LIBRARY_API void rocksdb_readoptions_set_tailing(
    rocksdb_readoptions_t*, unsigned char);
extern ROCKSDB_LIBRARY_API void rocksdb_readoptions_set_readahead_size(
    rocksdb_readoptions_t*, size_t);

/* Write options */

extern ROCKSDB_LIBRARY_API rocksdb_writeoptions_t*
rocksdb_writeoptions_create();
extern ROCKSDB_LIBRARY_API void rocksdb_writeoptions_destroy(
    rocksdb_writeoptions_t*);
extern ROCKSDB_LIBRARY_API void rocksdb_writeoptions_set_sync(
    rocksdb_writeoptions_t*, unsigned char);
extern ROCKSDB_LIBRARY_API void rocksdb_writeoptions_disable_WAL(
    rocksdb_writeoptions_t* opt, int disable);

/* Flush options */

extern ROCKSDB_LIBRARY_API rocksdb_flushoptions_t*
rocksdb_flushoptions_create();
extern ROCKSDB_LIBRARY_API void rocksdb_flushoptions_destroy(
    rocksdb_flushoptions_t*);
extern ROCKSDB_LIBRARY_API void rocksdb_flushoptions_set_wait(
    rocksdb_flushoptions_t*, unsigned char);

/* Cache */

extern ROCKSDB_LIBRARY_API rocksdb_cache_t* rocksdb_cache_create_lru(
    size_t capacity);
extern ROCKSDB_LIBRARY_API void rocksdb_cache_destroy(rocksdb_cache_t* cache);
extern ROCKSDB_LIBRARY_API void rocksdb_cache_set_capacity(
    rocksdb_cache_t* cache, size_t capacity);

/* Env */

extern ROCKSDB_LIBRARY_API rocksdb_env_t* rocksdb_create_default_env();
extern ROCKSDB_LIBRARY_API rocksdb_env_t* rocksdb_create_mem_env();
extern ROCKSDB_LIBRARY_API void rocksdb_env_set_background_threads(
    rocksdb_env_t* env, int n);
extern ROCKSDB_LIBRARY_API void
rocksdb_env_set_high_priority_background_threads(rocksdb_env_t* env, int n);
extern ROCKSDB_LIBRARY_API void rocksdb_env_join_all_threads(
    rocksdb_env_t* env);
extern ROCKSDB_LIBRARY_API void rocksdb_env_destroy(rocksdb_env_t*);

extern ROCKSDB_LIBRARY_API rocksdb_envoptions_t* rocksdb_envoptions_create();
extern ROCKSDB_LIBRARY_API void rocksdb_envoptions_destroy(
    rocksdb_envoptions_t* opt);

/* SstFile */

extern ROCKSDB_LIBRARY_API rocksdb_sstfilewriter_t*
rocksdb_sstfilewriter_create(const rocksdb_envoptions_t* env,
                             const rocksdb_options_t* io_options);
extern ROCKSDB_LIBRARY_API rocksdb_sstfilewriter_t*
rocksdb_sstfilewriter_create_with_comparator(
    const rocksdb_envoptions_t* env, const rocksdb_options_t* io_options,
    const rocksdb_comparator_t* comparator);
extern ROCKSDB_LIBRARY_API void rocksdb_sstfilewriter_open(
    rocksdb_sstfilewriter_t* writer, const char* name, char** errptr);
extern ROCKSDB_LIBRARY_API void rocksdb_sstfilewriter_add(
    rocksdb_sstfilewriter_t* writer, const char* key, size_t keylen,
    const char* val, size_t vallen, char** errptr);
extern ROCKSDB_LIBRARY_API void rocksdb_sstfilewriter_finish(
    rocksdb_sstfilewriter_t* writer, char** errptr);
extern ROCKSDB_LIBRARY_API void rocksdb_sstfilewriter_destroy(
    rocksdb_sstfilewriter_t* writer);

extern ROCKSDB_LIBRARY_API rocksdb_ingestexternalfileoptions_t*
rocksdb_ingestexternalfileoptions_create();
extern ROCKSDB_LIBRARY_API void
rocksdb_ingestexternalfileoptions_set_move_files(
    rocksdb_ingestexternalfileoptions_t* opt, unsigned char move_files);
extern ROCKSDB_LIBRARY_API void
rocksdb_ingestexternalfileoptions_set_snapshot_consistency(
    rocksdb_ingestexternalfileoptions_t* opt,
    unsigned char snapshot_consistency);
extern ROCKSDB_LIBRARY_API void
rocksdb_ingestexternalfileoptions_set_allow_global_seqno(
    rocksdb_ingestexternalfileoptions_t* opt, unsigned char allow_global_seqno);
extern ROCKSDB_LIBRARY_API void
rocksdb_ingestexternalfileoptions_set_allow_blocking_flush(
    rocksdb_ingestexternalfileoptions_t* opt,
    unsigned char allow_blocking_flush);
extern ROCKSDB_LIBRARY_API void rocksdb_ingestexternalfileoptions_destroy(
    rocksdb_ingestexternalfileoptions_t* opt);

extern ROCKSDB_LIBRARY_API void rocksdb_ingest_external_file(
    rocksdb_t* db, const char* const* file_list, const size_t list_len,
    const rocksdb_ingestexternalfileoptions_t* opt, char** errptr);
extern ROCKSDB_LIBRARY_API void rocksdb_ingest_external_file_cf(
    rocksdb_t* db, rocksdb_column_family_handle_t* handle,
    const char* const* file_list, const size_t list_len,
    const rocksdb_ingestexternalfileoptions_t* opt, char** errptr);

/* SliceTransform */

extern ROCKSDB_LIBRARY_API rocksdb_slicetransform_t*
rocksdb_slicetransform_create(
    void* state, void (*destructor)(void*),
    char* (*transform)(void*, const char* key, size_t length,
                       size_t* dst_length),
    unsigned char (*in_domain)(void*, const char* key, size_t length),
    unsigned char (*in_range)(void*, const char* key, size_t length),
    const char* (*name)(void*));
extern ROCKSDB_LIBRARY_API rocksdb_slicetransform_t*
    rocksdb_slicetransform_create_fixed_prefix(size_t);
extern ROCKSDB_LIBRARY_API rocksdb_slicetransform_t*
rocksdb_slicetransform_create_noop();
extern ROCKSDB_LIBRARY_API void rocksdb_slicetransform_destroy(
    rocksdb_slicetransform_t*);

/* Universal Compaction options */

enum {
  rocksdb_similar_size_compaction_stop_style = 0,
  rocksdb_total_size_compaction_stop_style = 1
};

extern ROCKSDB_LIBRARY_API rocksdb_universal_compaction_options_t*
rocksdb_universal_compaction_options_create();
extern ROCKSDB_LIBRARY_API void
rocksdb_universal_compaction_options_set_size_ratio(
    rocksdb_universal_compaction_options_t*, int);
extern ROCKSDB_LIBRARY_API void
rocksdb_universal_compaction_options_set_min_merge_width(
    rocksdb_universal_compaction_options_t*, int);
extern ROCKSDB_LIBRARY_API void
rocksdb_universal_compaction_options_set_max_merge_width(
    rocksdb_universal_compaction_options_t*, int);
extern ROCKSDB_LIBRARY_API void
rocksdb_universal_compaction_options_set_max_size_amplification_percent(
    rocksdb_universal_compaction_options_t*, int);
extern ROCKSDB_LIBRARY_API void
rocksdb_universal_compaction_options_set_compression_size_percent(
    rocksdb_universal_compaction_options_t*, int);
extern ROCKSDB_LIBRARY_API void
rocksdb_universal_compaction_options_set_stop_style(
    rocksdb_universal_compaction_options_t*, int);
extern ROCKSDB_LIBRARY_API void rocksdb_universal_compaction_options_destroy(
    rocksdb_universal_compaction_options_t*);

extern ROCKSDB_LIBRARY_API rocksdb_fifo_compaction_options_t*
rocksdb_fifo_compaction_options_create();
extern ROCKSDB_LIBRARY_API void
rocksdb_fifo_compaction_options_set_max_table_files_size(
    rocksdb_fifo_compaction_options_t* fifo_opts, uint64_t size);
extern ROCKSDB_LIBRARY_API void rocksdb_fifo_compaction_options_destroy(
    rocksdb_fifo_compaction_options_t* fifo_opts);

extern ROCKSDB_LIBRARY_API int rocksdb_livefiles_count(
    const rocksdb_livefiles_t*);
extern ROCKSDB_LIBRARY_API const char* rocksdb_livefiles_name(
    const rocksdb_livefiles_t*, int index);
extern ROCKSDB_LIBRARY_API int rocksdb_livefiles_level(
    const rocksdb_livefiles_t*, int index);
extern ROCKSDB_LIBRARY_API size_t
rocksdb_livefiles_size(const rocksdb_livefiles_t*, int index);
extern ROCKSDB_LIBRARY_API const char* rocksdb_livefiles_smallestkey(
    const rocksdb_livefiles_t*, int index, size_t* size);
extern ROCKSDB_LIBRARY_API const char* rocksdb_livefiles_largestkey(
    const rocksdb_livefiles_t*, int index, size_t* size);
extern ROCKSDB_LIBRARY_API void rocksdb_livefiles_destroy(
    const rocksdb_livefiles_t*);

/* Utility Helpers */

extern ROCKSDB_LIBRARY_API void rocksdb_get_options_from_string(
    const rocksdb_options_t* base_options, const char* opts_str,
    rocksdb_options_t* new_options, char** errptr);

extern ROCKSDB_LIBRARY_API void rocksdb_delete_file_in_range(
    rocksdb_t* db, const char* start_key, size_t start_key_len,
    const char* limit_key, size_t limit_key_len, char** errptr);

extern ROCKSDB_LIBRARY_API void rocksdb_delete_file_in_range_cf(
    rocksdb_t* db, rocksdb_column_family_handle_t* column_family,
    const char* start_key, size_t start_key_len, const char* limit_key,
    size_t limit_key_len, char** errptr);

// referring to convention (3), this should be used by client
// to free memory that was malloc()ed
extern ROCKSDB_LIBRARY_API void rocksdb_free(void* ptr);

#ifdef __cplusplus
}  /* end extern "C" */
#endif

#endif  /* STORAGE_ROCKSDB_INCLUDE_C_H_ */