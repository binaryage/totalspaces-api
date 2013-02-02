//
//  TSLib.h
//  totalspacesapi
//
//  Created by Stephen Sykes on 27/1/13.
//  Copyright (c) 2013 Stephen Sykes. All rights reserved.
//
//  The API is a premium feature, and will only work with registered versions of TotalSpaces.
//

#ifndef totalspacesapi_tslib
#define totalspacesapi_tslib_h

#import <Foundation/Foundation.h>

/*
 * In case of comm error, all the functions apart from tsapi_libTotalSpacesVersion() will 
 * return an empty string, zero, false or a pointer to a struct containing zero spaces (in 
 * the case of tsapi_windowList).
 * It is recommended to check that comms to TotalSpaces are working by, for instance,
 * checking that tsapi_numberOfSpaces() returns a number greater than zero when you initialize
 * your app.
 */

/*
 * The version of the API present in TotalSpaces.app
 *
 * You must call tsapi_freeString when you have finished with the returned string.
 */
const char *tsapi_apiVersion();

/*
 * The version number of TotalSpaces itself
 *
 * You must call tsapi_freeString when you have finished with the returned string.
 */
const char *tsapi_totalSpacesVersion();

/*
 * The version of the API dylib. This should match the string returned
 * by tsapi_apiVersion()
 *
 * You must call tsapi_freeString when you have finished with the returned string.
 */
const char *tsapi_libTotalSpacesVersion();

/*
 * The number of the current space
 *
 * If the current space is the dashboard, 0 is returned.
 */
unsigned int tsapi_currentSpaceNumber();

/*
 * The name for the given space number
 *
 * You must call tsapi_freeString when you have finished with the returned string.
 */
const char *tsapi_spaceNameForSpaceNumber(unsigned int spaceNumber);

/*
 * The total number of spaces
 * This includes the dashboard if you have it set as a space, and any
 * fullscreen apps
 */
unsigned int tsapi_numberOfSpaces();

/*
 * The number of fullscreen apps
 */
unsigned int tsapi_numberOfFullScreens();

/*
 * The number of desktops / normal spaces
 */
unsigned int tsapi_numberOfDesktops();

/*
 * The number of fullscreen apps that are allowed to be present
 * in the grid, defined in advanced preferences
 */
unsigned int tsapi_numberOfFullScreensInGrid();

/*
 * Is the dashboard set to be a space in Mission Control preferences
 */
bool tsapi_dashboardIsASpace();

/*
 * The number of rows defined in TotalSpaces layout preferences
 */
unsigned int tsapi_definedRows();

/*
 * The number of columns defined in TotalSpaces layout preferences
 */
unsigned int tsapi_definedColumns();

/*
 * Call this to free strings returned by the TotalSpaces API
 */
void tsapi_freeString(char *str);

/*
 * Switch the display to the given space
 * Returns false if the space number is invalid
 */
bool tsapi_moveToSpace(unsigned int spaceNumber);

/*
 * Set the name of a space
 * The maximum length is 255 bytes. The name should be in UTF-8
 * Returns true on success, false if the name was too long or the space number was invalid
 */
bool tsapi_setNameForSpace(unsigned int spaceNumber, char *name);

/*
 * Type for space change callback
 */
typedef void (*space_change_callback_t)(unsigned int fromSpaceNumber, unsigned int toSpaceNumber);

/*
 * Set the function that will be called when the visible space changes
 * There is only one callback per process, registering a new callback will supercede any previous one
 */
void tsapi_setSpaceWillChangeCallback(space_change_callback_t callback);

/*
 * Cancel space change callbacks
 */
void tsapi_unsetSpaceWillChangeCallback();

/*
 * Type for layout change callback
 */
typedef void (*space_layout_changed_callback_t)(void);

/*
 * Set the function that will be called when the layout changes
 * This could be any change - for instance adding or removing a fullscreen, changing the name of a space,
 * or a change of rows or columns.
 * It indicates that you should re-request any information you are holding on the spaces
 * There is only one callback per process, registering a new callback will supercede any previous one
 */
void tsapi_setLayoutChangedCallback(space_layout_changed_callback_t callback);

/*
 * Cancel layout change callbacks
 */
void tsapi_unsetLayoutChangedCallback();

/*
 * Struct containing information about a window
 */
struct tsapi_window {
  char *appName;
  unsigned int windowId;
  bool isOnAllSpaces;
  char *title;
  char *frame;
};

/*
 * Struct containing information about a space
 * Contains a pointer to an array of tsapi_window structs
 */
struct tsapi_space {
  unsigned int spaceNumber;
  unsigned int windowCount;
  struct tsapi_window *windows;
};

/*
 * Struct containing the count of spaces and a pointer to an
 * array of tsapi_space structs
 */
struct tsapi_spaces {
  unsigned int spacesCount;
  struct tsapi_space *spaces;
};

/*
 * Return a pointer to a tsapi_spaces struct containing information about all the windows
 * in all spaces
 *
 * The windows are listed front to back, so the first widow in the array is the frontmost
 *
 * You must call tsapi_freeWindowList when you have finished with this
 */
struct tsapi_spaces *tsapi_windowList();

/*
 * Free a previously returned spaceWindowsArray struct
 */
void tsapi_freeWindowList(struct tsapi_spaces *windowList);

/*
 * Move a window to a different space
 * The windowId must be one that has been returned in a tsapi_window struct
 *
 * Returns true on success, false if the windowId or spaceNumber was invalid
 */
bool tsapi_moveWindowToSpace(unsigned int windowId, unsigned int spaceNumber);

#endif

