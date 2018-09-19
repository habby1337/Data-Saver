cacls data /e /p everyone:f
cacls File_Storage /e /p everyone:f

rd /S /Q data
rd /S /Q File_Storage