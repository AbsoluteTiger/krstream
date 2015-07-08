#ifndef __KR_ENGINE_ENV_H__
#define __KR_ENGINE_ENV_H__

#include "krutils/kr_utils.h"
#include "krparam/kr_param.h"
#include "krcalc/kr_calc.h"
#include "krio/kr_io.h"
#include "krdb/kr_db.h"
#include "krdata/kr_data.h"
#include "krflow/kr_flow.h"
#include "kr_engine.h"

/* engine environment, create with config */
typedef struct _kr_engine_env_t
{
    T_KRParam        *ptParam;     /* parameter, read only in thread */
    T_KRModule       *krdbModule;  /* module for krdb */
    T_KRIO           *ptIO;        /* interface module */
    T_KRDB           *ptDB;        /* krdb, read only in thread */
    T_KRFuncTable    *ptFuncTable; /* function table */
    void             *extra;       /* engine startup extra data */
}T_KREngineEnv;

T_KREngineEnv *kr_engine_env_create(T_KREngineConfig *ptConfig);
void kr_engine_env_destroy(T_KREngineEnv *ptEnv);

#endif /* __KR_ENGINE_ENV_H__ */