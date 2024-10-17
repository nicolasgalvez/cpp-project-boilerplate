#!/bin/bash

# Autocommit every x minutes
# Much like npm run watch which compiles code on change, this will commit and push code, but on a timer.

# Since my mac doesn't have 'watch', I found a stackexchange post and adapted a solution
# You can use brew to install but I figure I'll try this to avoid platform specific dependencies if possible
# However, I would like to adapt the script to be windows compatible which may mean using Node or Python
# https://superuser.com/questions/1061921/is-there-a-native-alternative-to-the-watch-command-for-darwin-os-x
fakewatch() {
    count=0
    while true; do
        DATE=$(date)
        RESULT=$("${@}")
        clear
        echo "$DATE"
        echo "$RESULT"
        sleep 15
        count=$((count+1))
        echo "watched $count times"
    done
}

# Run watch
fakewatch $(git pull && (git ls-files --modified --others --exclude-standard | grep . >/dev/null) && {
    echo "changes found, comitting code..."
    git add .
    git commit -m 'autocommit'
    git push
})

# https://www.markusdosch.com/2020/07/git-auto-commit-push-every-couple-of-minutes/
# watch -n <SECONDS-INTERVAL> "git pull && (git ls-files --modified --others --exclude-standard | grep . > /dev/null) && { git add . ; git commit -m '<MESSAGE>' ; git push; }"
