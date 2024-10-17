#!/bin/bash
#Autocommit every x minutes

# Since my mac doesn't have watch, I found a stackexchange post that suggested this function
# https://superuser.com/questions/1061921/is-there-a-native-alternative-to-the-watch-command-for-darwin-os-x
fakewatch() {
    while true; do
        DATE=$(date)
        RESULT=$("${@}")
        clear
        echo "$DATE"
        echo "$RESULT"
        sleep 1
    done
}

fakewatch git pull && (git ls-files --modified --others --exclude-standard | grep . >/dev/null) && {
    git add .
    git commit -m 'autocommit'
    git push
}

# https://www.markusdosch.com/2020/07/git-auto-commit-push-every-couple-of-minutes/
# watch -n <SECONDS-INTERVAL> "git pull && (git ls-files --modified --others --exclude-standard | grep . > /dev/null) && { git add . ; git commit -m '<MESSAGE>' ; git push; }"
