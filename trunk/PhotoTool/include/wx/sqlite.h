#ifndef WX_SQLITE_H
#define WX_SQLITE_H

//#pragma warning( disable : 4101 4786)

#include <wx/thread.h>
#include <wx/string.h>
#include <wx/datetime.h>
#include <wx/hashmap.h>

const char *wxSQLiteVersion();

typedef struct sqlite sqlite;
typedef struct sqlite_vm sqlite_vm;

class wxSQLiteException
{
public:
	wxString m_err;

	wxSQLiteException(wxString err = wxT("")) : m_err(err) {}

	inline operator wxString ()  const {return m_err;}
};

class wxSQLiteDatabase
{
private:
    friend class wxSQLiteDatabaseLocker;
	sqlite              *db;
    wxCriticalSection   csDB;

public:
	wxString lastErr;

	wxSQLiteDatabase(wxString fname = wxT(""));
	~wxSQLiteDatabase();

	bool Open(wxString fname);
	bool Close();

    int LastInsertRowId();

	bool Ok() const {return db != NULL;};
};


class wxSQLiteQueryBase
{
public:
	WX_DECLARE_STRING_HASH_MAP(int, ColNamesMap);
protected:
	wxSQLiteDatabase& db;
    

	//typedef map<wxString, int, sqliteLess_wxStringI> ColNamesMap;
	ColNamesMap colNames;

	wxSQLiteQueryBase(wxSQLiteDatabase& db);
	void InitCols(const char **pazColNames, int ncols);

public:

	int GetFieldIndex(wxString fieldName);		// returns -1 if not found

    class TField
    {
    private:
        const char *data;

    public:
        TField(const char *data) : data(data) {}

        const char * AsChar() const;
        wxString AsString() const;
        long AsLong() const;
        double AsDouble() const;
        bool AsBool() const;
        wxDateTime AsDate() const;
    };
};

class wxSQLiteQuery : public wxSQLiteQueryBase
{
private:
    sqlite_vm	*pVm;
	int			ncol;
	const char	**pazValue;
	const char	**pazColName;

public:
	wxString lastErr;

	wxSQLiteQuery(wxSQLiteDatabase& db);
	~wxSQLiteQuery();

	bool Close();
	bool Execute(wxString sqlstr, ...);

	bool eof() const;
	bool Fetch();
	void Terminate();

    int NumFields() const;
    const char *GetFieldName(int fieldIdx);
    TField Fields(int fieldIdx);
	TField FieldByName(wxString fieldName);	// raise exception if not found
};

class wxSQLiteQueryResult : public wxSQLiteQueryBase
{
private:   
    char    **result;
    int     nrow;
    int     ncolumn;

public:
    wxString lastErr;

	wxSQLiteQueryResult(wxSQLiteDatabase& db);
	~wxSQLiteQueryResult();

	bool Execute(wxString sql, ...);
    int NumChanges();

    int NumRows();
    int NumCols();

    char *GetFieldName(int fieldIdx);
    TField Fields(int rowIdx, int fieldIdx);
	TField FieldByName(int rowIdx, wxString fieldName);	// raise exception if not found
};


#endif

