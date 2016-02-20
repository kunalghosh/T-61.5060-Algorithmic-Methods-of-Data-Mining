echo "Compiling get_hashes.cpp [ensure hashes.cpp is present in the parent directory.]"
g++ -std=c++11 -Ofast get_hashes.cpp ../hashes.cpp -o get_hashes
BITS=32
CHARS=3; HASH_FUNC=poly; python generate_strings.py $CHARS | ./get_hashes $HASH_FUNC $BITS| python plot_data.py $HASH_FUNC-$BITS-plot-$CHARS-chars.png
CHARS=3; HASH_FUNC=rsh; python generate_strings.py $CHARS | ./get_hashes $HASH_FUNC $BITS| python plot_data.py $HASH_FUNC-$BITS-plot-$CHARS-chars.png
CHARS=3; HASH_FUNC=cheap; python generate_strings.py $CHARS | ./get_hashes $HASH_FUNC $BITS| python plot_data.py $HASH_FUNC-$BITS-plot-$CHARS-chars.png
CHARS=3; HASH_FUNC=djb2; python generate_strings.py $CHARS | ./get_hashes $HASH_FUNC $BITS| python plot_data.py $HASH_FUNC-$BITS-plot-$CHARS-chars.png
CHARS=3; HASH_FUNC=mm2; python generate_strings.py $CHARS | ./get_hashes $HASH_FUNC $BITS| python plot_data.py $HASH_FUNC-$BITS-plot-$CHARS-chars.png
CHARS=3; HASH_FUNC=mm64a; python generate_strings.py $CHARS | ./get_hashes $HASH_FUNC $BITS| python plot_data.py $HASH_FUNC-$BITS-plot-$CHARS-chars.png

CHARS=4; HASH_FUNC=poly; python generate_strings.py $CHARS | ./get_hashes $HASH_FUNC $BITS| python plot_data.py $HASH_FUNC-$BITS-plot-$CHARS-chars.png
CHARS=4; HASH_FUNC=rsh; python generate_strings.py $CHARS | ./get_hashes $HASH_FUNC $BITS| python plot_data.py $HASH_FUNC-$BITS-plot-$CHARS-chars.png
CHARS=4; HASH_FUNC=cheap; python generate_strings.py $CHARS | ./get_hashes $HASH_FUNC $BITS| python plot_data.py $HASH_FUNC-$BITS-plot-$CHARS-chars.png
CHARS=4; HASH_FUNC=djb2; python generate_strings.py $CHARS | ./get_hashes $HASH_FUNC $BITS| python plot_data.py $HASH_FUNC-$BITS-plot-$CHARS-chars.png
CHARS=4; HASH_FUNC=mm2; python generate_strings.py $CHARS | ./get_hashes $HASH_FUNC $BITS| python plot_data.py $HASH_FUNC-$BITS-plot-$CHARS-chars.png
CHARS=4; HASH_FUNC=mm64a; python generate_strings.py $CHARS | ./get_hashes $HASH_FUNC $BITS| python plot_data.py $HASH_FUNC-$BITS-plot-$CHARS-chars.png


