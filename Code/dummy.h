/* 	After generating solution using 5.4 once, 
	modify the top-level CMakeLists.txt file (in this directory) like so:

	1. Find the following line(11):
		include(${TOOLS_CMAKE_DIR}/Configure.cmake)
	
	2. Find the following line(38):
		#BEGIN-CUSTOM
	
	3. Delete everything between the mentioned lines.
	
	4. Delete "dummy.h" (this file)
	
	5. Delete "Solutions" folder.
	
	5. Regenerate solution again.

	To re-cap, assuming the 1st line is on line number 11, 
	and the 2nd line is on line number 38, delete lines 12 
	through 37 including. Such that the result is both 
	lines are next to each other.
	
	--
	
	Note: The project will build, some "unnecessarily built" projects will say they have failed, 
	these are not required, a slight cmake modification (CryEngineModule()->CryFileContainer()) 
	will remove these erroneous build errors.
	
	[ALTERNATIVELY TO ALL OF THE ABOVE]
	(Before generating solution from 5.3 to 5.4 for the first time....)
	
	If you are using a local git repo of the engine source code, you can simply 
	go to my github @ uniflare and apply the branch containing the words "cryrun_cmake".
	You will need to install PyInstaller and Python 3.5. Python 3.5 should be installed to: "C:/Python35".
	For PyInstaller, a simple google search will give you step by step instructions "how to install PyInstaller".
	
	Make sure to delete this file.
*/