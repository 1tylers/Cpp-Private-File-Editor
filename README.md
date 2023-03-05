# C++ Private File Editor

Normally, if a file on a system does not have its permissions set to public, you have to manually change the permissions to add text to it.

With this program, it changes the file permissions itself, allowing you to simply call the program to add on text to a private permission file. It then changes the permissions back to private, allowing you to add on to it without manually changing any permissions.

On top of this, I added a feature for when the "-c" command is included in the command line. If you were to add this command, instead of adding text onto the end of a file, it would instead delete the contents of that file and replace it with the text.
