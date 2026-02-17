# task-cli.

# how to use:

1. clone this repo
2. cd to the repo directory
3. run "make"
4. run "make install" (as root)
5. then run "task"

to clean, run "make clean" 

# commands:

## add
to add a new task. example:

```
task add "take a bath (please)"
```

## read
to read all your tasks

example:
```
task read
```

the output will look like:
```
0. [ ] take a bath (please)
```

## done
to mark a task as done

example:
```
task done 0
```

the output of `task read` will no longer print the task 0

---

please give a star if you like it :( i love you
