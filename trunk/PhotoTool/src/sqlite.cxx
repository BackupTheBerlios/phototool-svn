
#ifdef __GNUG__
    #pragma implementation "wxsqlite.cpp"
#endif

// For compilers that support precompilation
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sqlite.h>
#include <wx/sqlite.h>
#include <wx/dynlib.h>

// function prototypes
typedef const char *(*Tsqlite_libversion)(void);
typedef void (*Tsqlite_freemem)(void *p);
typedef sqlite *(*Tsqlite_open)(const char *filename, int mode, char **errmsg);
typedef void (*Tsqlite_close)(sqlite *);
typedef int (*Tsqlite_last_insert_rowid)(sqlite *);
typedef int (*Tsqlite_finalize)(sqlite_vm*, char **pzErrMsg);
typedef int (*Tsqlite_compile)(sqlite *db, const char *zSql, const char **pzTail, sqlite_vm **ppVm, char **pzErrmsg);
typedef int (*Tsqlite_step)(sqlite_vm *pVm, int *pN, const char ***pazValue, const char ***pazColName);
typedef void (*Tsqlite_free_table)(char **result);
typedef int (*Tsqlite_get_table_vprintf)(sqlite*, const char *sqlFormat, char ***resultp, int *nrow, int *ncolumn, char **errmsg, va_list ap);
typedef int (*Tsqlite_changes)(sqlite*);
typedef char *(*Tsqlite_vmprintf)(const char* format, va_list va);

static wxDynamicLibrary				s_dll;
static Tsqlite_libversion			s_sqlite_libversion = NULL;
static Tsqlite_freemem				s_sqlite_freemem = NULL;
static Tsqlite_open					s_sqlite_open = NULL;
static Tsqlite_close				s_sqlite_close = NULL;
static Tsqlite_last_insert_rowid    s_sqlite_last_insert_rowid = NULL;
static Tsqlite_finalize				s_sqlite_finalize = NULL;
static Tsqlite_compile				s_sqlite_compile = NULL;
static Tsqlite_step					s_sqlite_step = NULL;
static Tsqlite_free_table			s_sqlite_free_table = NULL;
static Tsqlite_get_table_vprintf	s_sqlite_get_table_vprintf = NULL;
static Tsqlite_changes				s_sqlite_changes = NULL;
static Tsqlite_vmprintf				s_sqlite_vmprintf = NULL;

#define GET_PROC(proc)\
	s_##proc = (T##proc) s_dll.GetSymbol(wxT(#proc));\
	if (! s_##proc)\
	{\
		s_dll.Unload();\
		throw wxSQLiteException(wxT("error getting symbol <") wxT(#proc) wxT(">"));\
	}

void InitDLL()
{
	if (s_dll.IsLoaded())
		return;

    // Use the correct library name
#if defined (__WXMSW__)
    wxString libname = wxT("sqlite");
#else
    wxString libname = wxT("libsqlite");
#endif

	if (! s_dll.Load(libname))
		throw wxSQLiteException(wxT("error loading dynamic library"));

	// get procs
	GET_PROC(sqlite_libversion);
	GET_PROC(sqlite_freemem);
	GET_PROC(sqlite_open);
    GET_PROC(sqlite_last_insert_rowid);
	GET_PROC(sqlite_close);
	GET_PROC(sqlite_finalize);
	GET_PROC(sqlite_compile);
	GET_PROC(sqlite_step);
	GET_PROC(sqlite_free_table);
	GET_PROC(sqlite_get_table_vprintf);
	GET_PROC(sqlite_changes);
	GET_PROC(sqlite_vmprintf);
};


const char *wxsqlite_libversion(void)
{
	InitDLL();

	return s_sqlite_libversion();
};

void wxsqlite_freemem(void *p)
{
	InitDLL();

	s_sqlite_freemem(p);
};

sqlite *wxsqlite_open(const char *filename, int mode, char **errmsg)
{
	InitDLL();

	return s_sqlite_open(filename, mode, errmsg);

};

void wxsqlite_close(sqlite *s)
{
	InitDLL();

	s_sqlite_close(s);
};

int wxsqlite_last_insert_rowid(sqlite *s)
{
    InitDLL();

    return s_sqlite_last_insert_rowid(s);
};

int wxsqlite_finalize(sqlite_vm* vm, char **pzErrMsg)
{
	InitDLL();

	return s_sqlite_finalize(vm, pzErrMsg);

};

int wxsqlite_compile(sqlite *db, const char *zSql, const char **pzTail, sqlite_vm **ppVm, char **pzErrmsg)
{
	InitDLL();

	return s_sqlite_compile(db, zSql, pzTail, ppVm, pzErrmsg);
};

int wxsqlite_step(sqlite_vm *pVm, int *pN, const char ***pazValue, const char ***pazColName)
{
	InitDLL();

	return s_sqlite_step(pVm, pN, pazValue, pazColName);
};

void wxsqlite_free_table(char **result)
{
	InitDLL();

	s_sqlite_free_table(result);
};

int wxsqlite_get_table_vprintf(sqlite* sq, const char *sqlFormat, char ***resultp, int *nrow, int *ncolumn, char **errmsg, va_list ap)
{
	InitDLL();

	return s_sqlite_get_table_vprintf(sq, sqlFormat, resultp, nrow, ncolumn, errmsg, ap);
};

int wxsqlite_changes(sqlite* sq)
{
	InitDLL();

	return s_sqlite_changes(sq);

};

char *wxsqlite_vmprintf(const char* format, va_list va)
{
	InitDLL();

	return s_sqlite_vmprintf(format, va);
};


const char *wxSQLiteVersion()
{
	return wxsqlite_libversion();
};


//////////////////////////////////////////////////////
class wxSQLiteDatabaseLocker
{
private:
    wxSQLiteDatabase&        m_DB;
    wxCriticalSectionLocker  cs;

public:
    wxSQLiteDatabaseLocker(wxSQLiteDatabase& DB);
    ~wxSQLiteDatabaseLocker();

    sqlite *GetDB();
};


wxSQLiteDatabase::wxSQLiteDatabase(wxString fname) :
	db(NULL)
{
	if (fname != wxT(""))
		Open(fname);
};

wxSQLiteDatabase::~wxSQLiteDatabase()
{
	Close();
};

bool wxSQLiteDatabase::Open(wxString fname)
{
	Close();
	char *errmsg = NULL;


    {
        wxSQLiteDatabaseLocker locker(*this);
	    db = wxsqlite_open(fname.mb_str(), 0, &errmsg);
    };

	if (! db)
	{
		if (errmsg)
		{
			//lastErr = (const char *) errmsg;
			lastErr = wxString(errmsg, wxConvUTF8);
            wxSQLiteDatabaseLocker locker(*this);
			wxsqlite_freemem(errmsg);
		};
		return false;
	};

	return true;
};

bool wxSQLiteDatabase::Close()
{
	if (db)
    {
        wxSQLiteDatabaseLocker locker(*this);
		wxsqlite_close(db);
	
    	db = NULL;
    };

	return true;
};

int wxSQLiteDatabase::LastInsertRowId()
{
    if (db) 
    {
        wxSQLiteDatabaseLocker locker(*this);
        return wxsqlite_last_insert_rowid(db);
    };

    return 0;
};

wxSQLiteDatabaseLocker::wxSQLiteDatabaseLocker(wxSQLiteDatabase& DB) :
    m_DB(DB), cs(DB.csDB)
{
};

wxSQLiteDatabaseLocker::~wxSQLiteDatabaseLocker()
{
};

sqlite *wxSQLiteDatabaseLocker::GetDB()
{
    return m_DB.db;
};

wxSQLiteQueryBase::wxSQLiteQueryBase(wxSQLiteDatabase& db) :
	db(db)
{
};

void wxSQLiteQueryBase::InitCols(const char **pazColNames, int ncols)
{
	colNames.clear();
	for (int i = 0; i < ncols; i++)
	{
		wxString name = wxString(pazColNames[i], wxConvUTF8);
		name.MakeLower();
		colNames[name] = i;
	};
};

// returns -1 if not found
int wxSQLiteQueryBase::GetFieldIndex(wxString fieldName)
{
	fieldName.MakeLower();
	ColNamesMap::iterator it = colNames.find(fieldName);
	if (it == colNames.end())
		return -1;
	
	return it->second;
};

const char * wxSQLiteQueryBase::TField::AsChar() const
{
    return data;
};

wxString wxSQLiteQueryBase::TField::AsString() const
{
    return wxString(data, wxConvUTF8);
};

long wxSQLiteQueryBase::TField::AsLong() const
{
    return atol(data);
};

double wxSQLiteQueryBase::TField::AsDouble() const
{
    return atof(data);
};

bool wxSQLiteQueryBase::TField::AsBool() const
{
    return AsLong() != 0;
};

wxDateTime wxSQLiteQueryBase::TField::AsDate() const
{
    time_t t = AsLong();;
    return t;
};

wxSQLiteQuery::wxSQLiteQuery(wxSQLiteDatabase& db) : 
	wxSQLiteQueryBase(db),
    pVm(NULL),
	ncol(-1), pazValue(NULL), pazColName(NULL)
{
}

wxSQLiteQuery::~wxSQLiteQuery()
{
	Close();
};


bool wxSQLiteQuery::Close()
{
	if (! pVm)
		return true;

    lastErr = wxT("");
	char *pzErrMsg = NULL;
	int rc = wxsqlite_finalize(pVm, &pzErrMsg);
	if (rc != SQLITE_OK)
	{
		if (pzErrMsg)
		{
			lastErr = wxString(pzErrMsg, wxConvUTF8);
			wxsqlite_freemem(pzErrMsg);
		};

	};

	pVm = NULL;

	return rc == SQLITE_OK;
};

bool wxSQLiteQuery::Execute(wxString sqlstr, ...)
{
	Close();

    lastErr = wxT("");
	
	va_list args;
	va_start(args, sqlstr);

	const char *pzTail = NULL;  /* OUT: Part of zSQL not compiled */
	char *pzErrMsg = NULL;

	char *sql = wxsqlite_vmprintf(sqlstr.mb_str(), args);


	wxSQLiteDatabaseLocker dbl(db);

	int rc = wxsqlite_compile(dbl.GetDB(), sql, &pzTail, &pVm, &pzErrMsg);
	wxsqlite_freemem(sql);
	va_end(args);

	if (rc != SQLITE_OK)
	{
		if (pzErrMsg)
		{
			lastErr = wxString(pzErrMsg, wxConvUTF8);
			wxsqlite_freemem(pzErrMsg);
		};
	}
	else
	{
		Fetch();
	};


	return lastErr == wxT("");
};

bool wxSQLiteQuery::eof() const
{
	return pVm == NULL;
};

bool wxSQLiteQuery::Fetch()
{
	int nc = 0;
	int rc = wxsqlite_step(pVm, &nc, &pazValue, &pazColName);
	
	if (nc != ncol)
	{
		ncol = nc;
		InitCols(pazColName, ncol);
	};

	if (rc == SQLITE_ROW)
		return true;
	else
	{
		Close();
		return false;
	};
};


int wxSQLiteQuery::NumFields() const
{
    return ncol;
};

const char *wxSQLiteQuery::GetFieldName(int fieldIdx)
{
    wxASSERT(fieldIdx >= 0 && fieldIdx < ncol);
    wxASSERT(pazColName != NULL);

    return pazColName[fieldIdx];
};

wxSQLiteQueryBase::TField wxSQLiteQuery::Fields(int fieldIdx)
{
    wxASSERT(fieldIdx >= 0 && fieldIdx < ncol);
    wxASSERT(pazValue != NULL);

    return TField(pazValue[fieldIdx]);
};

// raise exception if not found
wxSQLiteQueryBase::TField wxSQLiteQuery::FieldByName(wxString fieldName)
{
	int idx = GetFieldIndex(fieldName);
	if (idx < 0)
	{
		wxString err;
		err.Printf(wxT("Unknown field name <%s>"), fieldName.c_str());
		throw wxSQLiteException(err);
	};

	return Fields(idx);
};


////////////////////////////////////////////////

wxSQLiteQueryResult::wxSQLiteQueryResult(wxSQLiteDatabase& db) :
    wxSQLiteQueryBase(db),
    result(NULL), nrow(0), ncolumn(0)
{
};

wxSQLiteQueryResult::~wxSQLiteQueryResult()
{
    wxsqlite_free_table(result);
};

bool wxSQLiteQueryResult::Execute(wxString sql, ...)
{
    wxsqlite_free_table(result);
    lastErr = wxT("");
    char *errmsg = NULL;

    va_list args;

    va_start(args, sql);
    int rc = SQLITE_ERROR;
    
    {
        wxSQLiteDatabaseLocker locker(db);
        rc = wxsqlite_get_table_vprintf(locker.GetDB(), sql.mb_str(), &result, &nrow, &ncolumn, &errmsg, args);
    };

    va_end(args);
    
    if (rc != SQLITE_OK)
    {
        if (errmsg)
        {
            lastErr = wxString(errmsg, wxConvUTF8);
            wxSQLiteDatabaseLocker locker(db);
            wxsqlite_freemem(errmsg);
        };

        return false;
    };

	InitCols((const char **) result, ncolumn);

    return true;
};

int wxSQLiteQueryResult::NumChanges()
{
    wxSQLiteDatabaseLocker locker(db);

    return wxsqlite_changes(locker.GetDB());
};

int wxSQLiteQueryResult::NumRows()
{
    return nrow;
};

int wxSQLiteQueryResult::NumCols()
{
    return ncolumn;
};

char *wxSQLiteQueryResult::GetFieldName(int fieldIdx)
{
    wxASSERT(fieldIdx >= 0 && fieldIdx < ncolumn);
    wxASSERT(result != NULL);

    return result[fieldIdx];
};

wxSQLiteQueryBase::TField wxSQLiteQueryResult::Fields(int rowIdx, int fieldIdx)
{
    wxASSERT(fieldIdx >= 0 && fieldIdx < ncolumn);
    wxASSERT(result != NULL);
    wxASSERT(rowIdx >= 0 && rowIdx < nrow);

    return TField(result[(rowIdx + 1) * ncolumn + fieldIdx]);
};

// raise exception if not found
wxSQLiteQueryBase::TField wxSQLiteQueryResult::FieldByName(int rowIdx, wxString fieldName)
{
	int idx = GetFieldIndex(fieldName);
	if (idx < 0)
	{
		wxString err;
		err.Printf(wxT("Unknown field name <%s>"), fieldName.c_str());
		throw wxSQLiteException(err);
	};

	return Fields(rowIdx, idx);
};

