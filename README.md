It is a project for Operating Systems for L2 at UPEC(Université Paris-Est Créteil).
The goal of the project is to create a Text Editor in C using only low level functions of C( like File Descriptors,Systems calls,etc....)
instead of (FILE,printf,etc...).
It runs in the terminal and allows to:
- Create a new file and write to him if it doesn't exist with the following File Permission: 0644(-rw-r--r--) and edit it.
- Open the existing file and print its content on the terminal's screen and edit it.
- Navigate through the terminal's window with arrows.
- For saving file press CTRL+S.

TODO
- Add cursor movement.
- Add code highlighting.
- Add finding (to try Knuth-Morris-Pratt)
- add replacement of the text.
