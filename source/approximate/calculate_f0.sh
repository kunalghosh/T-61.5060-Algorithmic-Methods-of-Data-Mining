#! /bin/bash

echo "Compiling code"
g++ -std=c++11 f0_args.cpp hashes.cpp -o f0_args

prime1=(363019    363277    363497    363751    363967    364271    364499    364747    365003    365257    365489    365747    366029    366239    366463    366733    366983    367219    367501    367721    367957    368231    368513    368789    369079    369353    369739    369997    370217    370529    370801    371141    371339    371627    371939    372173    372413    372707    372881    373183    373379    373693    373999    374203    374501    374761    374987    375163    375391    375623    375901    376147    376477    376699    376897    377183    377477    377717    378019    378269    378559    378809    379039    379307    379549)

prime2=(50591     50857     51071     51307     51481     51679     51893     52121     52321     52571     52807     53003     53201     53437     53653     53887     54101     54361     54539     54727     54979     55213     55441     55667     55843     56081     56269     56501     56701     56897     57089     57271     57527     57731     57943     58153     58369     58579     58831     59051     59221     59441     59651     59879     60107     60343     60617     60793     61031     61331     61519     61703     61979     62171     62423     62639     62897     63113     63361     63541     63709     63913     64187     64451     64679)



HASH_FUNC="poly"
INPUT_LIM=1000


if [[ $# -eq 1 ]]; then
    HASH_FUNC=$1
fi

if [[ $# -eq 2 ]]; then
    HASH_FUNC=$1
    INPUT_LIM=$2
fi

echo "Using hash function $HASH_FUNC and stream length $INPUT_LIM."

OUTPUT_FILE=f0_values_$HASH_FUNC\_$INPUT_LIM.txt 
echo "Moving old output to a temporary file. IF IT EXISTS"
BACKUP_FILE=f0_values_$HASH_FUNC\_$INPUT_LIM.bak
mv $OUTPUT_FILE $BACKUP_FILE

echo "Writing output to $OUTPUT_FILE"
exit 0
for ((i=0;i<${#prime1[@]};++i)); do
    if [ "$INPUT_LIM" == "full" ]; then
    	curl -s -N http://dendrite.ics.hut.fi/twitter_words.txt.gz | gunzip -c | ./f0_args $HASH_FUNC ${prime1[i]} ${prime2[i]} >> $OUTPUT_FILE & 
    else
    	curl -s -N http://dendrite.ics.hut.fi/twitter_words.txt.gz | gunzip -c | head -n $INPUT_LIM | ./f0_args $HASH_FUNC ${prime1[i]} ${prime2[i]} >> $OUTPUT_FILE & 
    fi
done

echo "Wait for the processes to complete."
S_TIME=5
while [ ${#prime1[@]} -ne `cat $OUTPUT_FILE | wc -l` ]; 
do
    echo "Sleeping for $S_TIME more seconds while we wait for ${#prime1[@]} processes to finish executing."
    sleep 5;
done;
python mean_of_medians.py $OUTPUT_FILE 4
