# Shell
This project was an attempt to recreate a Unix Shell as accurately as possible.
While most functionality replicates this well, in the future I would like to adjust and fix the following problems with the shell:
Currently the program exits when using a pipe and redirect in the same command: Ex; ls -l | w > out
Additionally, while using aliases piping and redirecting doesn't execute the command properly. Ex; LL | w > out
Lastly, certain problems were found with the functionality of the history, where ! and !! occasionally have issues finding the proper previous command to execute.
