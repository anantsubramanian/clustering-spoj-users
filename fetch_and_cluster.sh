#!/bin/bash

echo -n "Clean up old data? (y = yes, n = no): "
read cleanup

if [[ "$cleanup" == "y" || "$cleanup" == "Y" ]]; then
	rm userdata.dat
	rm parsed_data.dat
	rm clustered_data.dat
	rm plot_graph.gml
	rm clusterdata
fi

echo -n "Enter python execution command: "
read pyexec

echo -n "Enter g++ execution command: "
read ccexec

echo -n "Enter gephi execution command: "
read gephiexec

echo -n "Fetch data again? (y = yes, n = no): "
read fetch

if [[ "$fetch" == "y" || "$fetch" == "Y" ]]; then
	$pyexec getuserdata.py
	echo "Fetched user data!"
fi

$pyexec parseuserdata.py

echo "Starting clustering..."
$ccexec clusterdata.cpp -O3 -o clusterdata

./clusterdata
echo "Done clustering!"

$pyexec gmlconverter.py
$gephiexec plot_graph.gml

