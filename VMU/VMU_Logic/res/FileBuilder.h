#ifndef _FILE_BUILDER_HH
#define _FILE_BUILDER_HH

#include "FileVersion.h"



// comments
#define COMMENTS_STR( comments ) " " comments "\0"
#define COMMENTS_STRING COMMENTS_STR( COMMENTS ) 

// original filename
#define ORIGINAL_FILENAME_STR( originalFilename ) " " originalFilename "\0"
#define ORIGINAL_FILENAME_STRING ORIGINAL_FILENAME_STR( ORIGINAL_FILENAME ) 

// private build
#define PRIVATE_BUILD_STR( originalFilename ) " " originalFilename "\0"
#define PRIVATE_BUILD_STRING PRIVATE_BUILD_STR( PRIVATE_BUILD ) 

// file version
#define FILE_VERSION_STR( fileVersion ) " " #fileVersion "\0"
#define FILE_VERSION_STRING FILE_VERSION_STR( FILE_VERSION )



#endif
