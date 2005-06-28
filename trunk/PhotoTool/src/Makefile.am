
SUFFIXES=.cxx

# TODO -lwx_gtk2u_foldbar-2.5

bin_PROGRAMS	  = phototool
phototool_LDADD   = $(WX_LIBS) 
phototool_SOURCES = \
	   AboutDialog.cxx AboutDialog.h \
	   Album.cxx Album.h \
	   Camera.cxx Camera.h \
	   DateTime.cxx DateTime.h \
	   EditDialog.cxx EditDialog.h \
	   EditPage.cxx EditPage.h \
	   Filters.cxx Filters.h \
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
	   MetadataDialog.cxx MetadataDialog.h \
	   Notify.cxx Notify.h \
	   PageBase.cxx PageBase.h \
	   PhotoDialog.cxx PhotoDialog.h \
	   PhotoDropTarget.cxx PhotoDropTarget.h \
	   PhotoEvent.cxx PhotoEvent.h \
	   PhotoList.cxx PhotoList.h \
	   PhotoTool.cxx PhotoTool.h \
	   PluginManager.cxx PluginManager.h \
	   Record.cxx Record.h \
	   SetupDialog.cxx SetupDialog.h \
	   SlideShowDialog.cxx SlideShowDialog.h \
	   SlideShowFrame.cxx SlideShowFrame.h \
	   sqlite.cxx SQL.h Util.h Config.h \
	   TakenCalendar.cxx TakenCalendar.h \
	   TestPage.cxx TestPage.h \
	   ThumbList.cxx ThumbList.h \
	   ViewerPage.cxx ViewerPage.h \
	   ViewerPanel.cxx ViewerPanel.h \
	   WorkerThread.cxx WorkerThread.h \
	   wxBoxList.cxx wxBoxList.h \
	   wxExif.cxx wxExif.h \
	   wxExifList.cxx wxExifList.h

CXXFLAGS=@CXXFLAGS@ -I. -I$(top_srcdir)/include 
CPPFLAGS=@CPPFLAGS@ -I. -I$(top_srcdir)/include

