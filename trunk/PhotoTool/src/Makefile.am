
SUFFIXES=.cxx

bin_PROGRAMS	  = PhotoTool
PhotoTool_LDADD   = $(WX_LIBS) -lwx_gtk2u_foldbar-2.5
PhotoTool_SOURCES = \
	   AboutDialog.cxx AboutDialog.h \
	   Album.cxx Album.h \
	   Camera.cxx Camera.h \
	   DateTimeDialog.cxx DateTimeDialog.h \
	   EditDialog.cxx EditDialog.h \
	   EditPage.cxx EditPage.h \
	   Frame.cxx Frame.h \
	   Image.cxx Image.h \
	   ImportDialog.cxx ImportDialog.h \
	   InputDialog.cxx InputDialog.h \
	   Library.cxx Library.h \
	   LibraryEvent.cxx LibraryEvent.h \
	   ListDialog.cxx ListDialog.h \
	   Location.cxx Location.h \
	   LookupList.cxx LookupList.h \
	   LookupPage.cxx LookupPage.h \
	   Notify.cxx Notify.h \
	   PageBase.cxx PageBase.h \
	   PhotoDialog.cxx PhotoDialog.h \
	   PhotoDropTarget.cxx PhotoDropTarget.h \
	   PhotoEvent.cxx PhotoEvent.h \
	   PhotoList.cxx PhotoList.h \
	   PhotoTool.cxx PhotoTool.h \
	   Record.cxx Record.h \
	   SetupDialog.cxx SetupDialog.h \
	   SlideShowDialog.cxx SlideShowDialog.h \
	   SlideShowFrame.cxx SlideShowFrame.h \
	   sqlite.cxx SQL.h Util.h Config.h \
	   TakenCalendar.cxx TakenCalendar.h \
	   TestPage.cxx TestPage.h \
	   ThumbList.cxx ThumbList.h \
	   ViewerPage.cxx ViewerPage.h \
	   wxBoxList.cxx wxBoxList.h \
	   ViewerPanel.cxx ViewerPanel.h

CXXFLAGS=@CXXFLAGS@ -I. -I$(top_srcdir)/include 
CPPFLAGS=@CPPFLAGS@ -I. -I$(top_srcdir)/include

