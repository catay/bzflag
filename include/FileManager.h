/* bzflag
 * Copyright (c) 1993 - 2001 Tim Riker
 *
 * This package is free software;  you can redistribute it and/or
 * modify it under the terms of the license found in the file
 * named LICENSE that should have accompanied this file.
 *
 * THIS PACKAGE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef BZF_FILE_MANAGER_H
#define BZF_FILE_MANAGER_H

#include "common.h"
#include "bzfio.h"

#define FILEMGR (FileManager::getInstance())

class BzfString;

class FileManager {
public:
	~FileManager();

	// create an input stream for a file in the data directory.
	// this will look in several places until it finds the file.
	// if filename is an absolute path then only that place is
	// checked.  if the file cannot be found or isn't readable
	// then NULL is returned.
	istream*			createDataInStream(const BzfString& filename,
							bool binary = false) const;

	// create an output stream in the data directory (or wherever
	// indicated if filename is an absolute path).  if the file
	// can be opened for writing then NULL is returned.
	ostream*			createDataOutStream(const BzfString& filename,
							bool binary = false,
							bool truncate = true) const;

	// returns true if the path is absolute, false if relative
	bool				isAbsolute(const BzfString& path) const;

	// concatenate two pathname components with a directory separator
	// between them.
	BzfString			catPath(const BzfString& a, const BzfString& b) const;

	// get the singleton instance
	static FileManager*	getInstance();

private:
	FileManager();

private:
	static FileManager*	mgr;
};

#endif
