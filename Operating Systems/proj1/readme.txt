Blake Kershaw
Assignment 1
Tinyshell
1-19-18

This program demonstrates linux process commands made through the use of
execvp() function.  It executes process concurrently to give the user the the
illusion of infinite cpu power.

I began with this assignment by utilizing the template mtu-shell.c provided by
Dr. Uh.  I made slight modifications to the main() and execute() function.

In main() I had to first add the option for running tinyshell in batch-mode or
interactive mode.  Batch mode was implemented by using of argc and argv[]
parameters as mains arguments, this allows the user to select a batch file when
running the tinyshell.exe program.  Interactive mode was quite simple because
Dr. Uh already did the heavy lifting for us I just had to make a small
modification to strip the ';' from the incoming stdin string and than parse out
the ( \n\t) characters.  Once this was done it was just a matter of calling
execute which needed to loop through the fork() function in order to create the
children with their respective execvp() calls.  The other important step was to
make sure the parent was at a paused step by using the wait() function till the
children completed their process's.

The hardest part of the assignment was learning how to properly use the *char
and *char[] unlike c++, c does not have a robust string api so processing
strings is a bit more complicated, frequently leading to segmentation faults and
spending a lot of time finding where the error is.  But like all things only way
to learn is get messy, make mistakes and learn from them.  Fun little
assignment, really makes me appreciate the Linux developers ALOT more.
