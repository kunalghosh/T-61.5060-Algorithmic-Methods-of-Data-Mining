#!/usr/bin/zsh

# Compile the command
g++ -std=c++11 -Ofast exactMultiPass.cpp -o exactMultiPass

# Initial value of the exit code of our script
exit_code=1

# First time, get the data from the stream and dump the filtered data into temp.txt
curl -s -N http://dendrite.ics.hut.fi/twitter_words.txt.gz | gunzip -c | ./exactMultiPass > data
exit_code=$?
# zip data to data.gz
gzip data
while [[ $exit_code -ne 0 ]]; do
    cat data.gz | gunzip -c | ./exactMultiPass > temp
    exit_code=$?
    gzip temp
    mv temp.gz data.gz
done
rm data.gz
