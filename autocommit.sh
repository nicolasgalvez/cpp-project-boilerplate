#!/bin/bash

# Autocommit every x minutes
# Much like npm run watch which compiles code on change, this will commit and push code, but on a timer.

# Interval in minutes
INTERVAL=10

# accept an argument for the interval
if [ "$1" != "" ]; then
    INTERVAL=$1
fi

echo "Interval set to $INTERVAL minutes"
echo "Usage: $0 <interval>"
echo "Example: $0 5"

# Run watch
commit_code() {
    git pull && (git ls-files --modified --others --exclude-standard | grep . >/dev/null) && {
        echo -e "changes found, comitting code..."
        git add .
        git commit -m 'autocommit'
        git push
    }
}
# Since my mac doesn't have 'watch', I found a stackexchange post and adapted a solution 
# You can use brew to install but I figure I'll try this to avoid platform specific dependencies if possible
# However, I would like to adapt the script to be windows compatible which may mean using Node or Python
# https://superuser.com/questions/1061921/is-there-a-native-alternative-to-the-watch-command-for-darwin-os-x
fakewatch() {
    count=0
    while true; do
        DATE=$(date)
        RESULT=$(commit_code)
        clear
        echo "$DATE"
        echo "$RESULT"
        sleep $((INTERVAL * 60))
        count=$((count + 1))
        # echo "watched $count times" # TODO: make a -v argument to show this
    done
}


fakewatch
# https://www.markusdosch.com/2020/07/git-auto-commit-push-every-couple-of-minutes/
# watch -n <SECONDS-INTERVAL> "git pull && (git ls-files --modified --others --exclude-standard | grep . > /dev/null) && { git add . ; git commit -m '<MESSAGE>' ; git push; }"
