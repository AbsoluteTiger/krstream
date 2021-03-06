#ifndef __KR_DB_INTERNAL_H__
#define __KR_DB_INTERNAL_H__

#include "krdb/kr_db.h"

typedef struct _kr_table_t T_KRTable;
typedef struct _kr_index_t T_KRIndex;
typedef struct _kr_index_table_t T_KRIndexTable;
typedef struct _kr_index_slot_t T_KRIndexSolt;

/*ptDB table size keep mode*/
typedef enum {
    KR_SIZEKEEPMODE_COUNT   = '0', /*keep record counts*/ 
    KR_SIZEKEEPMODE_TIME    = '1'  /*keep transtime interval*/
}E_KRSizeKeepMode;

/*index's hashtable slot define*/
struct _kr_index_slot_t
{
    E_KRType        eKeyType;
    void            *pKeyValue;
    time_t          tLocMinProcTime;    /*set while add */
    time_t          tLocMinTransTime;   /*set while add */
    time_t          tExtMaxProcTime;    /*set while remove */
    time_t          tExtMaxTransTime;   /*set while remove */
    T_KRList        *pRecList;
};

/*hash table index definition*/
struct _kr_index_t
{
    T_KRDB           *ptDB;
    int              iIndexId;
    char             caIndexName[30+1];
    char             caIndexDesc[100+1];
    E_KRType         eIndexFieldType;
    T_KRHashTable    *pHashTable;
    T_KRList         *pIndexTableList;    /* tables in this index */
};

struct _kr_table_t
{
    pthread_mutex_t  tLock;
    T_KRDB           *ptDB;
    int              iTableId;
    char             caTableName[30+1];
    
    E_KRSizeKeepMode eKeepMode;
    long             lKeepValue;
    int              iSortFieldId;
    T_KRList         *pRecordList;      /* records of this table */
    
    T_KRList         *pIndexTableList;  /* indexes of this table */
};

struct _kr_index_table_t
{
    T_KRIndex        *ptIndex;
    T_KRTable        *ptTable;
    int              iIndexFieldId;
    int              iSortFieldId;
};

struct _kr_db_t
{
    char             caDBName[30+1];       /* name of this db */
    T_KRList         *pTableList;          /* tables in this db */
    T_KRList         *pIndexList;          /* indexes of this db */
    T_KRList         *pIndexTableList;     /* indexes of this db */
};


extern T_KRTable* kr_table_create(T_KRDB *ptDB, int iTableId, char *psTableName);
extern void kr_table_drop(T_KRTable *ptTable);
extern T_KRTable* kr_table_get(T_KRDB *ptDB, int iTableId);
extern void kr_table_insert_record(T_KRTable *ptTable, T_KRRecord *ptRecord);
extern void kr_table_delete_record(T_KRTable *ptTable, T_KRRecord *ptRecord);

extern T_KRIndex* kr_index_create(T_KRDB *ptDB,
        int iIndexId, char *psIndexName, 
        E_KRType eIndexFieldType);
extern void kr_index_drop(T_KRIndex *ptIndex);
extern T_KRIndex* kr_index_get(T_KRDB *ptDB, int iIndexId);

extern T_KRIndexTable* kr_index_table_create(T_KRDB *ptDB,
        int iIndexId, int iTableId,
        int iIndexFieldId, int iSortFieldId);
extern void kr_index_table_drop(T_KRIndexTable *ptIndexTable);
extern T_KRIndexTable* kr_index_table_get(T_KRDB *ptDB, int iIndexId, int iTableId);

extern T_KRDB* kr_db_create(char *name);
extern void kr_db_drop(T_KRDB *ptDB);

#endif /* __KR_DB_INTERNAL_H__ */
