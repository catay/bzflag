MAINTAINERCLEANFILES = \
	Makefile.in

AM_CPPFLAGS = $(CONF_CPPFLAGS) -I$(top_srcdir)/include
AM_CFLAGS = $(CONF_CFLAGS)
AM_CXXFLAGS = $(CONF_CXXFLAGS)

if CLIENT_INCLUDED
noinst_LTLIBRARIES =	libTank.la
endif

libTank_la_LDFLAGS = -static
libTank_la_SOURCES =	\
	high_barrel.cxx		\
	high_body.cxx		\
	high_ltread.cxx		\
	high_rtread.cxx		\
	high_turret.cxx		\
	low_barrel.cxx		\
	low_body.cxx		\
	low_ltread.cxx		\
	low_rtread.cxx		\
	low_turret.cxx		\
	medium_barrel.cxx	\
	medium_body.cxx		\
	medium_ltread.cxx	\
	medium_rtread.cxx	\
	medium_turret.cxx
